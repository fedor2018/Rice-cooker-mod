/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	timing.c																					*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

extern CYBIT flag_IsAny_Cmd_Executed;

static uint32 timing_counter = 0x00u;

extern CYBIT flag_1s;


/*******************************************************************************
* Function Name: Timing_Management
********************************************************************************
* Summary:
*   Management function of Timing Subsystem of Rice Cooker
* Parameters:  
*
* Return: 
*   
*
*******************************************************************************/
void Timing_Management(void)
{
	if(TRUE == flag_1s)
	{
		flag_1s = FALSE;
		
		/* if work mode is switched to another mode */
		if((TRUE == flag_IsAny_Cmd_Executed) || (TRUE == Get_AutoModeSwitchflag()))
		{
			timing_counter = 0;
			flag_IsAny_Cmd_Executed = FALSE;
            Set_AutoModeSwitchflag(FALSE);
		}
		else
		{
			timing_counter++;
			
			if((TIMING_MODE == Get_CurrentMode()) && ((Get_Timing2Cooking_Interval()*INTERVAL_UINT) == timing_counter))
			{
				Timing_to_Cooking();
				
				UART_UartPutString("Timing1 End, Enter Cook Mode!"); 
				UART_UartPutChar('\n');
				UART_UartPutChar('\r');


			}
            
			else if ((LOWPOWER_MODE == Get_CurrentMode()) && ((Get_LP2DP_Interval()*INTERVAL_UINT) == timing_counter))
			{
				LowPower_to_DeepSleep();
				
				UART_UartPutString("Timing3 End, Enter DP Mode!"); 
				UART_UartPutChar('\n');
				UART_UartPutChar('\r');
			}
            
			else if((STOP_MODE == Get_CurrentMode()) && ((Get_Stop2LP_Interval()*INTERVAL_UINT) == timing_counter))
			{
				Stop_to_LowPower();
				
				UART_UartPutString("Timing2 End, Enter LP Mode!"); 
				UART_UartPutChar('\n');
				UART_UartPutChar('\r');
                
			}

			
		}
        
	}

}

/*******************************************************************************
* Function Name: Get_TimingCounterValue
********************************************************************************
* Summary:
*   Get_TimingCounterValue
* Parameters:  
*
* Return: 
*   
*
*******************************************************************************/
uint32 Get_TimingCounterValue(void)
{
    return(timing_counter);
}

/*******************************************************************************
* Function Name: Set_TimingCounterValue
********************************************************************************
* Summary:
*   Set_TimingCounterValue
* Parameters:  
*
* Return: 
*   
*
*******************************************************************************/
void Set_TimingCounterValue(uint16 num)
{
    timing_counter = num;
}

void Timer_Selftest(void)
{;}

/* [] END OF FILE */
