// Header
#include "InitConfig.h"

// Includes
#include "Board.h"
#include "SysConfig.h"
#include "BCCIxParams.h"
#include "Global.h"
#include "LowLevel.h"
// Functions
//
void INITCFG_ConfigSystemClock()
{
	RCC_PLL_HSE_Config(QUARTZ_FREQUENCY, PREDIV_4, PLL_14);
	RCC_SysCfg_Clk_EN();
}
//------------------------------------

void INITCFG_ConfigGPIO()
{
	// Включение тактирования портов
	RCC_GPIO_Clk_EN(PORTA);
	RCC_GPIO_Clk_EN(PORTB);
	RCC_GPIO_Clk_EN(PORTC);
	
	// Аналоговые входы
	GPIO_InitAnalog(GPIO_MSR_HV);
	GPIO_InitAnalog(GPIO_MSR_PRESSURE);
	
	// Выходы
	GPIO_InitPushPullOutput(GPIO_LED);
	GPIO_InitPushPullOutput(GPIO_CONT1);
	GPIO_InitPushPullOutput(GPIO_CONT2);
	GPIO_InitPushPullOutput(GPIO_CONT3);
	GPIO_InitPushPullOutput(GPIO_CONT4);
	GPIO_InitPushPullOutput(GPIO_CHARGE);
	GPIO_InitPushPullOutput(GPIO_DISCHARGE);

	// Начальная установка состояний
	GPIO_SetState(GPIO_LED, false);
	GPIO_SetState(GPIO_CONT1, false);
	GPIO_SetState(GPIO_CONT2, false);
	GPIO_SetState(GPIO_CONT3, false);
	GPIO_SetState(GPIO_CONT4, false);
	GPIO_SetState(GPIO_CHARGE, false);
	GPIO_SetState(GPIO_DISCHARGE, false);
	
	// Альтернативные функции
	GPIO_InitAltFunction(GPIO_ALT_CAN_RX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_CAN_TX, AltFn_9);
	GPIO_InitAltFunction(GPIO_ALT_UART_RX, AltFn_7);
	GPIO_InitAltFunction(GPIO_ALT_UART_TX, AltFn_7);
}
//------------------------------------

void INITCFG_ConfigCAN()
{
	RCC_CAN_Clk_EN(CAN_1_ClkEN);
	NCAN_Init(SYSCLK, CAN_BAUDRATE, false);
	NCAN_FIFOInterrupt(true);
	NCAN_FilterInit(0, CAN_SLAVE_FILTER_ID, CAN_SLAVE_NID_MASK);
	NCAN_FilterInit(1, CAN_MASTER_FILTER_ID, CAN_MASTER_NID_MASK);
}
//------------------------------------

void INITCFG_ConfigUART()
{
	USART_Init(USART1, SYSCLK, USART_BAUDRATE);
	USART_Recieve_Interupt(USART1, 0, true);
}
//------------------------------------

void INITCFG_ConfigADC()
{
	RCC_ADC_Clk_EN(ADC_12_ClkEN);

	// ADC1
	ADC_Calibration(ADC1);
	ADC_SoftTrigConfig(ADC1);
	ADC_ChannelSeqReset(ADC1);
	ADC_Enable(ADC1);
	ADC_SamplingStart(ADC1);
}
//------------------------------------

void INITCFG_ConfigTimer3()
{
	TIM_Clock_En(TIM_3);
	TIM_Config(TIM3, SYSCLK, TIMER3_uS);
	TIM_Interupt(TIM3, 0, true);
	TIM_Start(TIM3);
}
//------------------------------------

void INITCFG_ConfigWatchDog()
{
	IWDG_Config();
	IWDG_ConfigureFastUpdate();
}
//------------------------------------
