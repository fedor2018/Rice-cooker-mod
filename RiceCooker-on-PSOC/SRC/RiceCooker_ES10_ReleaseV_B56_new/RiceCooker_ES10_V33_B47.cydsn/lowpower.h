/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	lowpower.h									    												*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef LOWPOWER_H
#define LOWPOWER_H


void LowPower_Management(void);

CYBIT Get_LPFlag_Status(void);
void  Set_LPFlag_Status(CYBIT status);

CYBIT Get_DPFlag_Status(void);
void  Set_DPFlag_Status(CYBIT status);

#endif
//[] END OF FILE
