#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Includes
#include "stdinc.h"
#include "Global.h"

// Types
typedef enum __DeviceState
{
	DS_None				= 0,
	DS_Fault			= 1,
	DS_Disabled			= 2,
	DS_Ready			= 3,
	DS_InProcess		= 4,
	DS_SafetyTrig		= 5,
	DS_InSelfTest		= 6
} DeviceState;

typedef enum __DUTPosition
{
	Off					= POSITION_OFF,
	Top					= POSITION_TOP,
	Bot					= POSITION_BOT
} DUTPosition;

typedef enum __Inductance
{
	L_300uH				= 300,
	L_100uH				= 100,
	L_30uH				= 30
}Inductance;

typedef enum __ChargeState
{
	PassiveDischarge	= 0,
	ActiveDischarge		= 1,
	Charge				= 2
}ChargeState;

// Variables
//
extern volatile Int64U CONTROL_TimeCounter;
extern DeviceState CONTROL_State;
extern Inductance CachedInductance;
extern Inductance LastInductance;
extern DUTPosition CachedDUTPosition;
extern DUTPosition LastDUTPosition;


// Functions
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SwitchToFault(Int16U Reason);
void CONTROL_SetDUTPosition(DUTPosition NewPosition, DUTPosition *LastPosition);
void CONTROL_SetInductance(Inductance Coil, Inductance *LastCoil);
bool CONTROL_CheckInductance(Inductance Coil);
bool CONTROL_CheckDUTPosition(DUTPosition Position);
void CONTROL_SetDeviceState(DeviceState NewState);

#endif // __CONTROLLER_H
