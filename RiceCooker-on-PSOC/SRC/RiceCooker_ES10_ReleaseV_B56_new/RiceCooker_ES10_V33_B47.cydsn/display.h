/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	display																							*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H


#define DISPLAY_TEMPERATURE	    0x00u
#define DISPLAY_BUSCURRENT	    0x01u

/* function used for debugging */
void UartDisplay(uint8 display_type);
/* function to diaplay workmode and time on SegLCD */
void SeglcdDisplay(uint8 work_mode, uint32 timing_countervalue);

/* seglcd self test function */
void Seglcd_Selftest(void);


#endif

//[] END OF FILE