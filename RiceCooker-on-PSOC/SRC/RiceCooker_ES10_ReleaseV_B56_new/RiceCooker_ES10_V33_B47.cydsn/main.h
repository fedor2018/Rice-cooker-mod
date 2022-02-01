/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	main.h																							*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/
#ifndef MAIN_H
#define MAIN_H


#define RELEASE 	    0x01u
#define SELFTEST        0x02u

#define VERSION         RELEASE

#define TRUE			1
#define FALSE			0

#define ON				1
#define OFF				0

#define CY_SUCCESS		0x01u
#define CY_FAIL			0x00u

/* WorKIng Mode definition */
#define STOP_MODE		0x00u
#define TIMING_MODE		0x01u
#define COOKING_MODE	0x02u
#define WARMING_MODE	0x03u
#define LOWPOWER_MODE	0x04u
#define DEEPSLEEP_MODE	0x05u
#define PAUSE_MODE      0x06u

#define NA_MODE         0x08u


#endif

//[] END OF FILE
