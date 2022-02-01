/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	uart_command.h																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/
#ifndef UART_COMMAND_H
#define UART_COMMAND_H

/* Command package length is 6 bytes */
#define COMMAND_PACKAGE_SIZE			0x06u

/* Package start/stop byte */
#define PACKAGE_START					0xFFu
#define PACKAGE_STOP					0xFEu
#define PACHAGE_CHECKSUM_DEBUG			0xFDu

/* The definition of pakcage format */
#define COMMAND_START_BYTE				0x00u
#define COMMAND_LENGTH_BYTE				0x01u
#define COMMAND_TYPE_BYTE				0x02u
#define COMMAND_DATA_BYTE				0x03u
#define COMMAND_CHECKSUM_BYTE			0x04u
#define COMMAND_STOP_BYTE				0x05u

/* Command Type Definition */
#define TYPE_MODE_SWITCH				0x11u
#define TYPE_COOK_TEMPERATURE_SET		0x21u
#define TYPE_WARM_TEMPERATURE_SET		0x22u
#define TYPE_COOK_TIMING_SET			0x31u
#define TYPE_LP_TIMING_SET				0x32u
#define TYPE_DP_TIMING_SET				0x33u

/*Only used for Debugging, when sar is not available*/
#define SAR_RTD_TEMP_SET                0x41u
#define SAR_BUS_CURRENT_SET             0x42u


/* Special Command */
#define TYPE_GET_CURRENT_MODE			0xAAu
#define TYPE_GET_TEMPERATURE			0xBBu
#define TYPE_GET_BUSCURRENT				0xCCu


/* Command Data Definition */
/* Mode Transition */
#define DATA_STOP_MODE_ENTER			0x00u
#define DATA_TIMING_MODE_ENTER			0x01u
#define DATA_Cooking_MODE_ENTER			0x02u
#define DATA_WARMING_MODE_ENTER			0x03u
#define DATA_LP_MODE_ENTER				0x04u
#define DATA_DP_MODE_ENTER				0x05u
#define DATA_PAUSE_MODE_ENTER           0x06u



/* Cooking Tempwrature Range, 80dg to 90 dg */
#define DATA_COOK_TEMPERATURE_MIN		0x50u
#define DATA_COOK_TEMPERATURE_MAX		0x5Au

/* Warming Tempwrature Range, 50dg to 70 dg */
#define DATA_WARM_TEMPERATURE_MIN		0x32u
#define DATA_WARM_TEMPERATURE_MAX		0x46u

/* Timing Range */
#define DATA_TIMING_MIN					0x01u
#define DATA_TIMING_MAX					0xFAu

uint8 Get_CookingTemperature(void);
uint8 Set_CookingTemperature(uint8 temperature);

uint8 Get_WarmingTemperature(void);
uint8 Set_WarmingTemperature(uint8 temperature);

uint8 Get_Timing2Cooking_Interval(void);
uint8 Set_Timing2Cooking_Interval(uint8 interval);

uint8 Get_Stop2LP_Interval(void);
uint8 Set_Stop2LP_Interval(uint8 interval);

uint8 Get_LP2DP_Interval(void);
uint8 Set_LP2DP_Interval(uint8 interval);

/* Function to check the format of received command package and decode */
uint8 IsCommandDecodePass(void);
/* Finction to execute the received command */
uint8 Command_Execute(uint8 cmdtype, uint8 cmddata);
/* Function to clear command buffer */
void  Command_Buffer_Clear(void);
/* Integrate Above four functions together */
void  Command_Management(void);

void Uart_Selftest(void);

void Auto_Cooking_to_Warming(float temper);

#endif
//[] END OF FILE
