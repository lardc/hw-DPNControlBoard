#ifndef __CONSTRAINTS_H
#define __CONSTRAINTS_H

// Include
#include "stdinc.h"
#include "DataTable.h"
#include "Global.h"

// Definitions
//
#define COEF_P2_MIN					-INT16S_MAX
#define COEF_P2_MAX					INT16S_MAX
#define COEF_P2_DEF					0
//
#define COEF_P1_MIN					-INT16S_MAX
#define COEF_P1_MAX					INT16S_MAX
#define COEF_P1_DEF					1
//
#define COEF_P0_MIN					-INT16S_MAX
#define COEF_P0_MAX					INT16S_MAX
#define COEF_P0_DEF					0
//
#define COEF_K_MIN					-INT16S_MAX
#define COEF_K_MAX					INT16S_MAX
//
#define COEF_B_MIN					-INT16S_MAX
#define COEF_B_MAX					INT16S_MAX
//
#define VCAP_K_DEF					1.0
#define VCAP_B_DEF					0
//
#define CHARGE_THRESHOLD_MIN		1.0
#define CHARGE_THRESHOLD_MAX		10
#define CHARGE_THRESHOLD_DEF		5
//
#define VOLTAGE_MIN					100
#define VOLTAGE_MAX					1800
#define VOLTAGE_DEF					1000
//
#define PRESSURE_K_DEF				1
#define PRESSURE_B_DEF				0
#define PRESSURE_LOW_MIN			2
#define PRESSURE_LOW_MAX			8
#define PRESSURE_LOW_DEF			5
//
#define PRESSURE_CHECK_MIN			0
#define PRESSURE_CHECK_MAX			1000
#define PRESSURE_CHECK_DEF			500
//
#define CONTACTOR_DELAY_MIN			0
#define CONTACTOR_DELAY_MAX			1000
#define CONTACTOR_DELAY_DEF			500
//
#define CHARGE_TIMEOUT_MIN			10000
#define CHARGE_TIMEOUT_MAX			60000
#define CHARGE_TIMEOUT_DEF			40000
//
#define DISCHARGE_TIMEOUT_MIN		1000
#define DISCHARGE_TIMEOUT_MAX		10000
#define DISCHARGE_TIMEOUT_DEF		5000
//
#define CURRENT_MIN					30
#define CURRENT_MAX					900
#define CURRENT_DEF					100
//
#define DURATION_MIN				10
#define DURATION_MAX				200
#define DURATION_DEF				100


// Types
typedef struct __TableItemConstraint
{
	float Min;
	float Max;
	float Default;
} TableItemConstraint;

// Variables
extern const TableItemConstraint Constraint[];

#endif // __CONSTRAINTS_H
