/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	timing.h									    												*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef TIMING_H
#define TIMING_H

/* Default Cooking mode enter timing value is 1 minute */
#define COOKING_TIMING_VALUE	0x05u
/* Default low power mode enter timing value is 2 minute */
#define LP_TIMING_VALUE			0x01u
/* Default deep sleep mode enter timing value is 2 minute(from LP) */
#define DP_TIMING_VALUE			0xFFu

/* 60 second per uint */
#define INTERVAL_UINT           60

void   Timing_Management(void);

uint32 Get_TimingCounterValue(void);
void   Set_TimingCounterValue(uint16 num);
void   Timer_Selftest(void);


#endif
//[] END OF FILE
