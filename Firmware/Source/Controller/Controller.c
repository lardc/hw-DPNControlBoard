// Header
#include "Controller.h"

// Includes
#include "DataTable.h"
#include "Board.h"
#include "Controller.h"
#include "Diagnostic.h"
#include "BCCIMHighLevel.h"
#include "LowLevel.h"
#include "BCCIxParams.h"
#include "math.h"
#include "InitConfig.h"
#include "Delay.h"
// Types
//
typedef void (*FUNC_AsyncDelegate)();

// Variables
DeviceState CONTROL_State = DS_None;
static Boolean CycleActive = false;
ChargeState	CapChargeState = PassiveDischarge;
float 	CachedCapVoltage = 0;
DUTPosition CachedDUTPosition = Off;
Inductance CachedInductance = L_300uH;

volatile Int64U CONTROL_TimeCounter = 0;

// Forward functions
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState);
void CONTROL_ResetToDefaults();
void CONTROL_ResetData();
void CONTROL_ResetHardware();
void CONTROL_WatchDogUpdate();
void CONTROL_SetDUTPosition(DUTPosition NewPosition, DUTPosition *LastPosition);
void CONTROL_SetInductance(Inductance Coil, Inductance *LastCoil);
void CONTROL_BatteryCharge();
void CONTROL_CacheVariables();
void CONTROL_Commutation();
void CONTROL_CheckInductance(Inductance Coil);
void CONTROL_CheckDUTPosition(DUTPosition Position);

// Functions
//
void CONTROL_Init()
{
	DT_SaveFirmwareInfo(CAN_SLAVE_NID, CAN_MASTER_NID);
	
	// Инициализация device profile
	DEVPROFILE_Init(&CONTROL_DispatchAction, &CycleActive);
	
	// Сброс значений
	DEVPROFILE_ResetControlSection();
	CONTROL_ResetToDefaults();
}
//-----------------------------------------------

void CONTROL_ResetToDefaults()
{
	CONTROL_ResetData();
	CONTROL_ResetHardware();

	CONTROL_SetDeviceState(DS_None);
}
//-----------------------------------------------

void CONTROL_ResetData()
{
	DataTable[REG_FAULT_REASON] = DF_NONE;
	DataTable[REG_DISABLE_REASON] = DF_NONE;
	DataTable[REG_WARNING] = WARNING_NONE;
	DataTable[REG_PROBLEM] = PROBLEM_NONE;
	DataTable[REG_OP_RESULT] = OPRESULT_NONE;
}
//-----------------------------------------------

void CONTROL_ResetHardware()
{
	CachedDUTPosition = Off;
	CachedInductance = L_300uH;
	LL_Charge(false);
	LL_Discharge(false);
}
//-----------------------------------------------

static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError)
{
	*pUserError = ERR_NONE;
	
	switch (ActionID)
	{
		case ACT_ENABLE_POWER:
			{
				if(CONTROL_State == DS_None)
					CONTROL_SetDeviceState(DS_InSelfTest);
				else if(CONTROL_State != DS_Ready)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready)
					CONTROL_SetDeviceState(DS_None);
				else if(CONTROL_State != DS_None)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_FAULT_CLEAR:
			{
				if(CONTROL_State == DS_Fault)
					CONTROL_ResetToDefaults();
			}
			break;
			
		case ACT_WARNING_CLEAR:
			DataTable[REG_WARNING] = 0;
			break;

		case ACT_CONFIG:
			CONTROL_CacheVariables();
			CONTROL_SetDeviceState(DS_InProcess);
			break;

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
	}
	
	return true;
}
//-----------------------------------------------

void CONTROL_Idle()
{
	CONTROL_BatteryCharge();
	CONTROL_Commutation();

	// Обработка мастер-запросов по интерфейсу
	DEVPROFILE_ProcessRequests();
	CONTROL_WatchDogUpdate();
}
//-----------------------------------------------

void CONTROL_SetDUTPosition(DUTPosition NewPosition, DUTPosition *LastPosition)
{
	static Int64U DelayCounter = 0;
	static bool Finished = false;

	if(NewPosition != *LastPosition && !DelayCounter)
	{
		Finished = false;
		LL_SetTopPosition(false);
		LL_SetBotPosition(false);

		DelayCounter = CONTROL_TimeCounter + CONTACTOR_DELAY;
	}
	else
	{
		if(CONTROL_TimeCounter >= DelayCounter)
		{
			if(!Finished)
			{
				(NewPosition == Top) ? LL_SetTopPosition(true) : LL_SetBotPosition(true);
				DelayCounter = CONTROL_TimeCounter + CONTACTOR_DELAY;
				Finished = true;
			}
			else
			{
				*LastPosition = NewPosition;
				DelayCounter = 0;
			}
		}
	}
}
//-----------------------------------------------

void CONTROL_SetInductance(Inductance Coil, Inductance *LastCoil)
{
	static Int64U DelayCounter = 0;

	if(Coil != *LastCoil && !DelayCounter)
	{
		if(Coil == L_300uH)
		{
			LL_SwitchCoil1(false);
			LL_SwitchCoil2(false);
		}
		else if(Coil == L_100uH)
		{
			LL_SwitchCoil1(true);
			LL_SwitchCoil2(false);
		}
		else if(Coil == L_30uH)
		{
			LL_SwitchCoil1(true);
			LL_SwitchCoil2(true);
		}

		DelayCounter = CONTROL_TimeCounter + CONTACTOR_DELAY;
	}
	else
	{
		if(CONTROL_TimeCounter >= DelayCounter)
			*LastCoil = Coil;
	}
}
//-----------------------------------------------

void CONTROL_Commutation()
{
	static Inductance LastInductance = L_300uH;
	static DUTPosition LastDUTPosition = Off;

	if(LastInductance != CachedInductance)
		CONTROL_SetInductance(CachedInductance, &LastInductance);
	else
		CONTROL_CheckInductance(LastInductance);

	if(LastDUTPosition != CachedDUTPosition)
		CONTROL_SetDUTPosition(CachedDUTPosition, &LastDUTPosition);
	else
		CONTROL_CheckDUTPosition(LastDUTPosition);
}
//-----------------------------------------------

void CONTROL_CheckInductance(Inductance Coil)
{
	switch(Coil)
	{
		case L_300uH:
			if(LL_CheckCoil1())
				CONTROL_SwitchToFault(DF_COIL1);

			if(LL_CheckCoil2())
				CONTROL_SwitchToFault(DF_COIL2);
			break;

		case L_100uH:
			if(!LL_CheckCoil1())
				CONTROL_SwitchToFault(DF_COIL1);

			if(LL_CheckCoil2())
				CONTROL_SwitchToFault(DF_COIL2);
			break;

		case L_30uH:
			if(LL_CheckCoil1())
				CONTROL_SwitchToFault(DF_COIL1);

			if(!LL_CheckCoil2())
				CONTROL_SwitchToFault(DF_COIL2);
			break;
	}
}

void CONTROL_CheckDUTPosition(DUTPosition Position)
{
	switch(Position)
	{
		case Off:
			if(LL_CheckTopPosition())
				CONTROL_SwitchToFault(DF_TOP_POSITION);

			if(LL_CheckBotPosition())
				CONTROL_SwitchToFault(DF_BOT_POSITION);
			break;

		case Top:
			if(!LL_CheckTopPosition())
				CONTROL_SwitchToFault(DF_TOP_POSITION);

			if(LL_CheckBotPosition())
				CONTROL_SwitchToFault(DF_BOT_POSITION);
			break;

		case Bot:
			if(LL_CheckTopPosition())
				CONTROL_SwitchToFault(DF_TOP_POSITION);

			if(!LL_CheckBotPosition())
				CONTROL_SwitchToFault(DF_BOT_POSITION);
			break;
	}
}
//-----------------------------------------------

void CONTROL_BatteryCharge()
{
	DataTable[REG_CAP_VOLTAGE] = LL_MeasureHV() * DataTable[REG_VCAP_K] + DataTable[REG_VCAP_B];

	if(CONTROL_State != DS_Ready && CONTROL_State != DS_InProcess)
	{
		if((DataTable[REG_CAP_VOLTAGE] - CachedCapVoltage) >= DataTable[REG_CHARGE_THRESHOLD])
			CapChargeState = ActiveDischarge;
		else if((DataTable[REG_CAP_VOLTAGE] - CachedCapVoltage) <= ((-1) * DataTable[REG_CHARGE_THRESHOLD]))
			CapChargeState = Charge;
		else
			CapChargeState = PassiveDischarge;

		switch(CapChargeState)
		{
			case PassiveDischarge:
				LL_Charge(false);
				LL_Discharge(false);
				break;

			case ActiveDischarge:
				LL_Charge(false);
				LL_Discharge(true);
				break;

			case Charge:
				LL_Charge(true);
				LL_Discharge(false);
				break;
		}
	}
	else
	{
		CapChargeState = ActiveDischarge;

		LL_Charge(false);
		LL_Discharge(true);
	}
}
//-----------------------------------------------

void CONTROL_CacheVariables()
{
	CachedCapVoltage = DataTable[REG_VOLTAGE];
	CachedDUTPosition = DataTable[REG_DUT_POSITION];
	CachedInductance = DataTable[REG_INDUCTANCE];
}

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_ResetToDefaults();
	
	CONTROL_SetDeviceState(DS_Fault);
	DataTable[REG_FAULT_REASON] = Reason;
}
//-----------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
}
//-----------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//-----------------------------------------------
