/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	selftest.h									    												*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef SELFTEST_H
#define SELFTEST_H


#define UART_SELFTEST       1
#define I2C_SELFTEST        2
#define TIMER_SELFTEST      3
#define PWM_SELFTEST        4
#define SEGLCD_SELFTEST     5
#define ADC_SELFTEST        6
#define COMP_SELFTEST       7

void System_Selftest(void);

#endif

//[] END OF FILE
