#ifndef __BOARD_H
#define __BOARD_H

#include "stm32f30x.h"

#include "ZwRCC.h"
#include "ZwGPIO.h"
#include "ZwNCAN.h"
#include "ZwTIM.h"
#include "ZwDAC.h"
#include "ZwDMA.h"
#include "ZwADC.h"
#include "ZwEXTI.h"
#include "ZwSCI.h"
#include "ZwSPI.h"
#include "ZwIWDG.h"
#include "ZwNFLASH.h"

// Определения для аналоговых портов
GPIO_PortPinSettingMacro GPIO_MSR_HV 			= {GPIOA, Pin_0};
GPIO_PortPinSettingMacro GPIO_MSR_PRESSURE		= {GPIOA, Pin_1};

// Определения для выходных портов
GPIO_PortPinSettingMacro GPIO_LED 					= {GPIOB, Pin_12};
GPIO_PortPinSettingMacro GPIO_CONT1					= {GPIOA, Pin_15};
GPIO_PortPinSettingMacro GPIO_CONT2					= {GPIOB, Pin_4};
GPIO_PortPinSettingMacro GPIO_CONT3					= {GPIOB, Pin_6};
GPIO_PortPinSettingMacro GPIO_CONT4					= {GPIOB, Pin_8};
GPIO_PortPinSettingMacro GPIO_CONT5					= {GPIOC, Pin_13};
GPIO_PortPinSettingMacro GPIO_CHARGE				= {GPIOB, Pin_15};
GPIO_PortPinSettingMacro GPIO_DISCHARGE				= {GPIOB, Pin_14};

// Определения для входных портов
GPIO_PortPinSettingMacro GPIO_SAFETY				= {GPIOA, Pin_8};
GPIO_PortPinSettingMacro GPIO_CONT_SENS1			= {GPIOB, Pin_3};
GPIO_PortPinSettingMacro GPIO_CONT_SENS2			= {GPIOB, Pin_5};
GPIO_PortPinSettingMacro GPIO_CONT_SENS3			= {GPIOB, Pin_7};
GPIO_PortPinSettingMacro GPIO_CONT_SENS4			= {GPIOB, Pin_9};
GPIO_PortPinSettingMacro GPIO_CONT_SENS5			= {GPIOC, Pin_14};

// Определения для портов альтернативных функций
GPIO_PortPinSettingMacro GPIO_ALT_CAN_RX 			= {GPIOA, Pin_11};
GPIO_PortPinSettingMacro GPIO_ALT_CAN_TX 			= {GPIOA, Pin_12};
GPIO_PortPinSettingMacro GPIO_ALT_UART_RX 			= {GPIOA, Pin_10};
GPIO_PortPinSettingMacro GPIO_ALT_UART_TX 			= {GPIOA, Pin_9};

#endif // __BOARD_H
