#ifndef __LOWLEVEL_H
#define __LOWLEVEL_H

// Include
#include "stdinc.h"

// Functions
//
void LL_ToggleBoardLED();
void LL_ClampAdapter(bool State);
void LL_SetTopPosition(bool State);
void LL_SetBotPosition(bool State);
void LL_SwitchCoil1(bool State);
void LL_SwitchCoil2(bool State);
void LL_Charge(bool State);
void LL_Discharge(bool State);
bool LL_CheckAdapter();
bool LL_CheckTopPosition();
bool LL_CheckBotPosition();
bool LL_CheckCoil1();
bool LL_CheckCoil2();
Int16U LL_MeasureHV();
Int16U LL_MeasurePressure();

#endif // __LOWLEVEL_H
