/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	measure.h																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef MEASURE_H
#define MEASURE_H


#define ACC_ACTUALLY_VALUE   3.286
#define AMP_ACTUALLY_VALUE   4

/* Software Switch for SAR */
#define SAR_SWITCH       SAR_DISABLE 

#define SAR_ENABLE 	     0x01u
#define SAR_DISABLE      0x02u

#define IIR4             IIR4_ENABLE


/* Software Switch for IIR16 filter */
#define IIR4_ENABLE 	 0x01u
#define IIR4_DISABLE     0x02u

#define IIR4             IIR4_ENABLE


void Get_ADCMeasureResult(void);

float Get_RtdTemperature(void);
uint8 Set_RtdTemperature(uint8 workmode, uint8 tempvalue);

uint16 Get_BusCurrent(void);
void  Set_BusCurrent(uint8 curvalue);

void   Adc_Selftest(void);

#endif
//[] END OF FILE
