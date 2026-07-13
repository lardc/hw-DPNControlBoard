// Header
//
#include "SelfTest.h"

// Include
//
#include "LowLevel.h"
#include "Board.h"
#include "Controller.h"
#include "Global.h"
#include "DataTable.h"
#include "Constraints.h"

// Variables
//
SelfTestState State = STS_None;
Int64U Timeout = 0;

// Functions
//
void SELFTEST_Reset()
{
	State = STS_None;
	Timeout = 0;
}
//------------------------------

void SELFTEST_Process()
{
	if(CONTROL_State == DS_InSelfTest)
	{
		switch(State)
		{
			case STS_None:
				DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_NONE;
				Timeout = CONTROL_TimeCounter + DataTable[REG_CHARGE_TIMEOUT];
				LL_Discharge(false);
				LL_Charge(true);
				State = STS_Charge;
				break;

			case STS_Charge:
				if(DataTable[REG_CAP_VOLTAGE] >= VOLTAGE_MAX)
				{
					LL_Charge(false);
					LL_Discharge(true);
					Timeout = CONTROL_TimeCounter + DataTable[REG_DISCHARGE_TIMEOUT];

					State = STS_Discharge;
				}
				else
				{
					if(CONTROL_TimeCounter >= Timeout)
						CONTROL_SwitchToFault(DF_CHARGE);
				}
				break;

			case STS_Discharge:
				if(DataTable[REG_CAP_VOLTAGE] <= VOLTAGE_MIN)
				{
					CachedInductance = L_30uH;
					State = STS_CheckCoil_30uH;
				}
				else
				{
					if(CONTROL_TimeCounter >= Timeout)
						CONTROL_SwitchToFault(DF_DISCHARGE);
				}
				break;

			case STS_CheckCoil_30uH:
				if(LastInductance != CachedInductance)
					CONTROL_SetInductance(CachedInductance, &LastInductance);
				else
					if(CONTROL_CheckInductance(LastInductance))
					{
						CachedInductance = L_100uH;
						State = STS_CheckCoil_100uH;
					}
				break;

			case STS_CheckCoil_100uH:
				if(LastInductance != CachedInductance)
					CONTROL_SetInductance(CachedInductance, &LastInductance);
				else
					if(CONTROL_CheckInductance(LastInductance))
					{
						CachedInductance = L_300uH;
						State = STS_CheckCoil_300uH;
					}
				break;

			case STS_CheckCoil_300uH:
				if(LastInductance != CachedInductance)
					CONTROL_SetInductance(CachedInductance, &LastInductance);
				else
					if(CONTROL_CheckInductance(LastInductance))
					{
						CachedInductance = L_300uH;
						CachedDUTPosition = Top;

						State = STS_CheckTopPos;
					}
				break;

			case STS_CheckTopPos:
				if(LastDUTPosition != CachedDUTPosition)
					CONTROL_SetDUTPosition(CachedDUTPosition, &LastDUTPosition);
				else
					if(CONTROL_CheckDUTPosition(LastDUTPosition))
					{
						CachedDUTPosition = Bot;
						State = STS_CheckBotPos;
					}
				break;

			case STS_CheckBotPos:
				if(LastDUTPosition != CachedDUTPosition)
					CONTROL_SetDUTPosition(CachedDUTPosition, &LastDUTPosition);
				else
					if(CONTROL_CheckDUTPosition(LastDUTPosition))
					{
						CachedDUTPosition = Off;
						State = STS_CheckOffPos;
					}
				break;

			case STS_CheckOffPos:
				if(LastDUTPosition != CachedDUTPosition)
					CONTROL_SetDUTPosition(CachedDUTPosition, &LastDUTPosition);
				else
					if(CONTROL_CheckDUTPosition(LastDUTPosition))
					{
						State = STS_None;
						DataTable[REG_SELF_TEST_OP_RESULT] = OPRESULT_OK;
						CONTROL_SetDeviceState(DS_Ready);
					}
				break;
		}
	}
}
//------------------------------
