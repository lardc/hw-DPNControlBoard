#ifndef CONTROLLER_SELFTEST_H_
#define CONTROLLER_SELFTEST_H_

// Types
//
typedef enum __SelfTestState
{
	STS_None			= 0,
	STS_Charge			= 1,
	STS_Discharge		= 2,
	STS_CheckCoil_300uH	= 3,
	STS_CheckCoil_100uH	= 4,
	STS_CheckCoil_30uH	= 5,
	STS_CheckTopPos		= 6,
	STS_CheckBotPos		= 7,
	STS_CheckOffPos		= 8
}SelfTestState;

// Functions
//
void SELFTEST_Process();

#endif /* CONTROLLER_SELFTEST_H_ */
