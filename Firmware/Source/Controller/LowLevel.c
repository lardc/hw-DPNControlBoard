// Header
#include "LowLevel.h"

// Include
#include "Board.h"
#include "Global.h"

// Functions
//
void LL_ToggleBoardLED()
{
	GPIO_Toggle(GPIO_LED);
}
//------------------------------------

void LL_SetTopPosition(bool State)
{
	GPIO_SetState(GPIO_CONT1, State);
}
//------------------------------------

void LL_SetBotPosition(bool State)
{
	GPIO_SetState(GPIO_CONT2, State);
}
//------------------------------------

void LL_SwitchCoil1(bool State)
{
	GPIO_SetState(GPIO_CONT3, State);
}
//------------------------------------

void LL_SwitchCoil2(bool State)
{
	GPIO_SetState(GPIO_CONT4, State);
}
//------------------------------------

void LL_Charge(bool State)
{
	GPIO_SetState(GPIO_CHARGE, State);
}
//------------------------------------

void LL_Discharge(bool State)
{
	GPIO_SetState(GPIO_DISCHARGE, State);
}
//------------------------------------

bool LL_CheckTopPosition()
{
	return GPIO_GetState(GPIO_CONT1);
}
//------------------------------------

bool LL_CheckBotPosition()
{
	return GPIO_GetState(GPIO_CONT2);
}
//------------------------------------

bool LL_CheckCoil1()
{
	return GPIO_GetState(GPIO_CONT3);
}
//------------------------------------

bool LL_CheckCoil2()
{
	return GPIO_GetState(GPIO_CONT4);
}
//------------------------------------

Int16U LL_MeasureHV()
{
	return ADC_Measure(ADC1, ADC_HV_CHANNEL);
}
//------------------------------------

Int16U LL_MeasurePressure()
{
	return ADC_Measure(ADC1, ADC_PRESSURE_CHANNEL);
}
//------------------------------------
