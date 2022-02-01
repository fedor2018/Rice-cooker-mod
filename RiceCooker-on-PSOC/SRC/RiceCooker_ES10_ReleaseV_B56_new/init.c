/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	init.c																							*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/*******************************************************************************
* Function Name: System_Init
********************************************************************************
* Summary:
* This function initialize the Components Setting and print init message to PC;
*
* Parameters:  
*   N/A
*
* Return: 
*  void
*
*******************************************************************************/
void System_Init(void)
{
    /* Initlize UART Component and sent start initialize message to PC */
	UART_Start();
    UART_SCB_IRQ_Start();
    UART_RX_WAKEUP_IRQ_Disable();
    
	UART_UartPutString("System Init..."); 
 	UART_UartPutChar('\n');
 	UART_UartPutChar('\r');	
	
//    /* Initalize Analog Components */
	ADC_Start();
    ADC_IRQ_Disable();
//    ADC_IRQ_Enable();
    ADC_Stop();

	Opamp_Start();
	Opamp_Stop();

	Comp_Start();
	Comp_Stop();

//    PWM_Out_SetDriveMode(PWM_Out_DM_DIG_HIZ); //Set PWM Output Pin as HIGH-Z to Prevent Output Wave before Init is Complete
	PWM_Start();
	PWM_Stop();
	
	
	Timer_Start();
	Timer_Stop();
    
    I2C_Start();
    I2CBufferInit();
    I2C_Stop();
    
    /* LCD show 8 00:00. 8 represent Off mode. 00:00 represent Time */
    LCD_Seg_Start();
    LCD_Seg_ClearDisplay();
    LCD_Seg_Write7SegNumber_0(Get_CurrentMode(),0,1);
    LCD_Seg_Write7SegNumber_1(Get_TimingCounterValue(),0,1);
    LCD_Seg_WritePixel(LCD_Seg_HBAR0,1);
    CyDelay(3000);
    LCD_Seg_Stop();
    
//    PWM_Out_SetDriveMode(PWM_Out_DM_STRONG);
    
    CY_SET_REG32(0x400b0108,(CY_GET_REG32(0x400b0108) | 0x2000000));
    
    CyGlobalIntEnable;  /* Uncomment this line to enable global interrupts. */

	UART_UartPutString("Init Completed!"); 
 	UART_UartPutChar('\n');
 	UART_UartPutChar('\r');	
    
}


/* [] END OF FILE */
