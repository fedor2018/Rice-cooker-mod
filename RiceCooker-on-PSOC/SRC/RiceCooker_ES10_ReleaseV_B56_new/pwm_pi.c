/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	pwm_pi.c																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/* The calculated result of PI algorithm */
static float uk;
/* The differential between Set value and measured value */
static float ek;
/* The ek value of last time */
static float ek_1;
static float ek_2;
static int16 pwm_compValue = DEFAULT_COMPARE_VALUE;

void PI_Temperature_Adjust(void)
{
	if(COOKING_MODE == Get_CurrentMode()) 
	{	
		ek = (Get_CookingTemperature() - Get_RtdTemperature());
		
		ek_2 = ek - ek_1;
		uk =  KP* ek_2 + KI*ek;	
		ek_1 = ek;

		pwm_compValue -= (int16)uk * 20;
		
		if(pwm_compValue > COMPARE_VALUE_MAX_COOK) 
		{
			pwm_compValue = COMPARE_VALUE_MAX_COOK;
		}
		else if(pwm_compValue < COMPARE_VALUE_MIN_COOK)
		{
			pwm_compValue = COMPARE_VALUE_MIN_COOK;
		}

	}
	else if(WARMING_MODE == Get_CurrentMode()) 
	{	
		ek = (Get_WarmingTemperature() - Get_RtdTemperature());
		
		ek_2 = ek - ek_1;
		uk =  KP* ek_2 + KI*ek;	
		ek_1 = ek;

		pwm_compValue -= (int16)uk * 20;
		
		if(pwm_compValue > COMPARE_VALUE_MAX_WARM) 
		{
			pwm_compValue = COMPARE_VALUE_MAX_WARM;
		}
		else if(pwm_compValue < COMPARE_VALUE_MIN_WARM)
		{
			pwm_compValue = COMPARE_VALUE_MIN_WARM;
		}
	}
    PWM_WriteCompare(pwm_compValue);
}

void Pwm_Selftest(void)
{
   
    PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);

    PWM_WriteCompare(199);
    CyDelay(2000);
    PWM_WriteCompare(499);
    CyDelay(2000);
    PWM_WriteCompare(899);
    CyDelay(2000);
    PWM_WriteCompare(1699);
    CyDelay(2000);
}
/* [] END OF FILE */
