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
DeviceSubState SUB_State = SS_None;

volatile Int64U CONTROL_TimeCounter = 0;

// Forward functions
static Boolean CONTROL_DispatchAction(Int16U ActionID, pInt16U pUserError);
void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState);
void CONTROL_ResetToDefaults();
void CONTROL_ResetData();
void CONTROL_ResetHardware();
void CONTROL_WatchDogUpdate();
void CONTROL_SetPosition(DUTPosition Position);
void CONTROL_SetInductance(Inductance Coil);

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

	CONTROL_SetDeviceState(DS_None, SS_None);
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
	LL_ClampAdapter(false);
	CONTROL_SetPosition(Off);
	CONTROL_SetInductance(L_300uH);
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
					CONTROL_SetDeviceState(DS_InProcess, SS_None);
				else if(CONTROL_State != DS_Ready)
					*pUserError = ERR_OPERATION_BLOCKED;
			}
			break;
			
		case ACT_DISABLE_POWER:
			{
				if(CONTROL_State == DS_Ready)
					CONTROL_SetDeviceState(DS_None, SS_None);
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

		default:
			return DIAG_HandleDiagnosticAction(ActionID, pUserError);
	}
	
	return true;
}
//-----------------------------------------------

void CONTROL_Idle()
{
	// Обработка мастер-запросов по интерфейсу
	DEVPROFILE_ProcessRequests();

	CONTROL_WatchDogUpdate();
}
//-----------------------------------------------

void CONTROL_SetPosition(DUTPosition Position)
{
	LL_SetTopPosition(false);
	LL_SetBotPosition(false);
	DELAY_MS(CONTACTOR_DELAY);

	if(Position == Top)
	{
		LL_SetTopPosition(true);
		DELAY_MS(CONTACTOR_DELAY);
	}

	if(Position == Bot)
	{
		LL_SetBotPosition(true);
		DELAY_MS(CONTACTOR_DELAY);
	}
}
//-----------------------------------------------

void CONTROL_SetInductance(Inductance Coil)
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

	DELAY_MS(CONTACTOR_DELAY);
}
//-----------------------------------------------

void CONTROL_SwitchToFault(Int16U Reason)
{
	CONTROL_ResetToDefaults();
	
	CONTROL_SetDeviceState(DS_Fault, SS_None);
	DataTable[REG_FAULT_REASON] = Reason;
}
//-----------------------------------------------

void CONTROL_SetDeviceState(DeviceState NewState, DeviceSubState NewSubState)
{
	CONTROL_State = NewState;
	DataTable[REG_DEV_STATE] = NewState;
	
	SUB_State = NewSubState;
	DataTable[REG_SUB_STATE] = NewSubState;
}
//-----------------------------------------------

void CONTROL_WatchDogUpdate()
{
	if(BOOT_LOADER_VARIABLE != BOOT_LOADER_REQUEST)
		IWDG_Refresh();
}
//-----------------------------------------------
