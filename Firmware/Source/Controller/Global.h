// ----------------------------------------
// Global definitions
// ----------------------------------------

#ifndef __GLOBAL_H
#define __GLOBAL_H

#include "SysConfig.h"

// Параметры интерфейсов
#define	SCCI_TIMEOUT_TICKS			1000			// Таймаут протоколоа SCCI (в мс)
#define	BCCIM_TIMEOUT_TICKS			50				// Таймаут протоколоа мастер BCCI (в мс)
#define EP_WRITE_COUNT				0				// Количество массивов для записи
#define EP_COUNT					0				// Количество массивов для чтения
#define FEP_COUNT					0				// Количество массивов для чтения типа float
#define ENABLE_LOCKING				FALSE			// Защита паролем

// Временные параметры
#define TIME_LED_BLINK				500				// Период моргания светодиода на плате (в мс)

// Параметры аналоговой подсистемы
#define ADC_REF_VOLTAGE				3300.0f			// Опорное напряжение (в мВ)
#define ADC_RESOLUTION				4095

#endif // __GLOBAL_H
