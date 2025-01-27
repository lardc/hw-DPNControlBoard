// Header
#include "Diagnostic.h"

// Include
#include "Delay.h"
#include "LowLevel.h"
#include "DataTable.h"
#include "DeviceObjectDictionary.h"
#include "Controller.h"
#include "Global.h"

// Functions
//
bool DIAG_HandleDiagnosticAction(Int16U ActionID, Int16U *pUserError)
{
	switch (ActionID)
	{
		case ACT_DBG_SET_TOP_POSITION:
			LL_SetTopPosition(DataTable[REG_DBG]);
			DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
			DataTable[REG_DBG] = LL_CheckTopPosition();
			break;

		case ACT_DBG_SET_BOT_POSITION:
			LL_SetBotPosition(DataTable[REG_DBG]);
			DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
			DataTable[REG_DBG] = LL_CheckBotPosition();
			break;

		case ACT_DBG_SET_COIL:
			if(DataTable[REG_DBG])
			{
				if(DataTable[REG_DBG] == 1)
				{
					LL_SwitchCoil2(false);
					DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
					LL_SwitchCoil1(true);
					DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
				}

				if(DataTable[REG_DBG] == 2)
				{
					LL_SwitchCoil1(false);
					DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
					LL_SwitchCoil2(true);
					DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
				}
			}
			else
			{
				LL_SwitchCoil1(false);
				LL_SwitchCoil2(false);
			}

			DELAY_MS(DataTable[REG_CONTACTOR_DELAY]);
			DataTable[REG_DBG] = (Int16U)(LL_CheckCoil1() | LL_CheckCoil2() << 1);
			 break;

		case ACT_DBG_CHARGE:
			LL_Charge(DataTable[REG_DBG]);
			break;

		case ACT_DBG_DISCHARGE:
			LL_Discharge(DataTable[REG_DBG]);
			break;

		case ACT_DBG_HV_MEASURE:
			DataTable[REG_DBG] = LL_MeasureHV();
			break;

		case ACT_DBG_PRESSURE_MEASURE:
			DataTable[REG_DBG] = LL_MeasurePressure();
			break;

		case ACT_DBG_SAFETY:
			DataTable[REG_DBG] = LL_SafetyCheck();
			break;

		default:
			return false;
	}
	
	return true;
}
//-----------------------------
