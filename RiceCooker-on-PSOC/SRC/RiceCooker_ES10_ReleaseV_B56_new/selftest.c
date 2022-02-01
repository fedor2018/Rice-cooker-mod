/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	selftest.c									    												*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
#include <device.h>

extern uint8 selftest_item;

/* var used to record which test is done
    0x01 -- UART Self Test
    0x02 -- I2C Self Test
    0x04 -- Timer Self Test
    0x08 -- PWM Self Test
    0x10 -- SegLCD Self Test
    0x20 -- SARADC Self Test
    0x40 -- Comp Self Test
    0x80 -- All Tests Complete
*/    
static uint8 selftest_seq = 0x00;

/*******************************************************************************
* Function Name: System_Selftest
********************************************************************************
* Summary:
*  system self test function.  
*
* Parameters:  
*  None
*
* Return: 
*  None 
*  
*******************************************************************************/
void System_Selftest(void)
{
    if(0x80 != (selftest_seq&0x80))
    {
        do{
            if(UART_SELFTEST == selftest_item)
            {
                Uart_Selftest();
                selftest_seq |= 0x01;
            }
            else if(I2C_SELFTEST == selftest_item)
            {
                I2C_Selftest();
                selftest_seq |= 0x02;
            }
            else if(TIMER_SELFTEST == selftest_item)
            {
                Timer_Selftest();
                selftest_seq |= 0x04;
            }
            else if(PWM_SELFTEST == selftest_item)
            {
                Pwm_Selftest();
                selftest_seq |= 0x80;
            }
            else if(SEGLCD_SELFTEST == selftest_item)
            {
                Seglcd_Selftest();
                selftest_seq |= 0x10;
            }
            else if(ADC_SELFTEST == selftest_item)
            {
                Adc_Selftest();
                selftest_seq |= 0x20;
            }
            else if(COMP_SELFTEST == selftest_item)
            {
                //Comp_Selftest();
                selftest_seq |= 0x40;
            }
        }while(0x7F != (selftest_seq&0x7F));
        
        UART_UartPutString("SelfTest Complete!"); 
        UART_UartPutChar('\n');
        UART_UartPutChar('\r');	
        
        selftest_seq |= 0x80;
    }
}

/* [] END OF FILE */
