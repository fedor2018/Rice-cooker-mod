/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	state_machine.h																					*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


void Set_AutoModeSwitchflag(CYBIT flag);
CYBIT Get_AutoModeSwitchflag(void);

uint32 (* ApiArray[7][7])();
uint8 Mode_Switching(uint8 cur_mode, uint8 sw_mode);

uint8 Get_CurrentMode(void);
void  Set_CurrentMode(uint8 mode);

void PowerOn_to_Stop(void);

/* Mode Switching APIS */
void Stop_to_Stop(void);
void Stop_to_Timing(void);
void Stop_to_Cooking(void);
void Stop_to_Warming(void);
void Stop_to_LowPower(void);
void Stop_to_DeepSleep(void);

void Timing_to_Stop(void);
void Timing_to_Timing(void);
void Timing_to_Cooking(void);
void Timing_to_Pause(void);

void Cooking_to_stop(void);
void Cooking_to_Timing(void);
void Cooking_to_Cooking(void);
void Cooking_to_Warming(void);
void Cooking_to_Pause(void);

void Warming_to_Stop(void);
void Warming_to_Timing(void);
void Warming_to_Cooking(void);
void Warming_to_Warming(void);
void Warming_to_Pause(void);

void LowPower_to_Stop(void);
void LowPower_to_DeepSleep(void);

void DeepSleep_to_Stop(void);

void Pause_to_Timing(void);
void Pause_to_Cooking(void);
void Pause_to_Warming(void);



#endif
//[] END OF FILE
