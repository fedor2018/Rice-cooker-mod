/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	pwm_pi.h																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef PWM_PI_H
#define PWM_PI_H


#define DEFAULT_COOK_TEMPERATURE 	80
#define DEFAULT_WARM_TEMPERATURE 	60

#define KP					        25
#define KI					        0.5

#define DEFAULT_COMPARE_VALUE	999			// PWM Duty Cycle = 50%

#define COMPARE_VALUE_MIN_WARM	199 		// PWM Duty Cycle = 90%
#define COMPARE_VALUE_MAX_WARM	1799 		// PWM Duty Cycle = 10%

#define COMPARE_VALUE_MIN_COOK	199			// PWM Duty Cycle = 90%
#define COMPARE_VALUE_MAX_COOK	1499		// PWM Duty Cycle = 25%
//
//#define COMPARE_VALUE_MIN_WARM	199 		// PWM Duty Cycle = 10%
//#define COMPARE_VALUE_MAX_WARM	1799 		// PWM Duty Cycle = 90%
//
//#define COMPARE_VALUE_MIN_COOK	499			// PWM Duty Cycle = 25%
//#define COMPARE_VALUE_MAX_COOK	1799		// PWM Duty Cycle = 90%


//#define PWM_CMP1_Value(x)	1999-20*(x)	

void PI_Temperature_Adjust(void);

void Pwm_Selftest(void);

#endif

//[] END OF FILE
