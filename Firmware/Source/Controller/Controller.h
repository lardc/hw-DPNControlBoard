#ifndef __CONTROLLER_H
#define __CONTROLLER_H

// Includes
#include "stdinc.h"

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
	Off					= 0,
	Top					= 1,
	Bot					= 2
} DUTPosition;

typedef enum __Inductance
{
	L_300uH				= 0,
	L_100uH				= 1,
	L_30uH				= 2
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


// Functions
void CONTROL_Init();
void CONTROL_Idle();
void CONTROL_SwitchToFault(Int16U Reason);

#endif // __CONTROLLER_H
