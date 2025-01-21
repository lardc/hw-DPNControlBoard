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
