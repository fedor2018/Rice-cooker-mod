/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	lowpower.c									    												*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

CYBIT lp_enter_flag = FALSE;
CYBIT dp_enter_flag = FALSE;
extern CYBIT Wakeup_Flag;

CYBIT Get_LPFlag_Status(void)
{
    return(lp_enter_flag);
}
void  Set_LPFlag_Status(CYBIT status)
{
    lp_enter_flag = status;
}

CYBIT Get_DPFlag_Status(void)
{
    return(dp_enter_flag);
}
void  Set_DPFlag_Status(CYBIT status)
{
    dp_enter_flag = status;
}

void LowPower_Management(void)
{
    if((TRUE == Get_LPFlag_Status()) || (TRUE == Get_DPFlag_Status()))
    {
        LCD_Seg_Sleep();
        I2C_Sleep();
        PWM_Sleep();
        Timer_Sleep();
        Comp_Sleep();
        Opamp_Sleep();
        ADC_Sleep();
        
        UART_Sleep();
        
        ST_Switch_SetDriveMode(ST_Switch_DM_ALG_HIZ);
        I2C_scl_SetDriveMode(I2C_scl_DM_ALG_HIZ);
        I2C_sda_SetDriveMode(I2C_sda_DM_ALG_HIZ);
        
        isr_50ms_ClearPending();
        isr_200ms_ClearPending();
        isr_1000ms_ClearPending();
        UART_SCB_IRQ_ClearPending();
        UART_RX_WAKEUP_IRQ_Start();
        
        if(Get_LPFlag_Status())
        {
            Set_LPFlag_Status(FALSE);
            CySysPmSleep();
            
        }
        else
        {
            Set_DPFlag_Status(FALSE);
            CySysPmDeepSleep();
        }
        
    }

    if(TRUE == Wakeup_Flag)
    {
        isr_50ms_ClearPending();
        isr_200ms_ClearPending();
        isr_1000ms_ClearPending();
        UART_SCB_IRQ_ClearPending();
        
        UART_RX_WAKEUP_IRQ_Stop();
        UART_WakeUp();
        
        ST_Switch_SetDriveMode(ST_Switch_DM_RES_UP);
        I2C_scl_SetDriveMode(I2C_scl_DM_OD_LO);
        I2C_sda_SetDriveMode(I2C_sda_DM_OD_LO);
        
        ADC_Wakeup();         
        Comp_WakeUp();
        Opamp_WakeUp();
         
        Timer_WakeUp();         
        PWM_WakeUp();
        I2C_Sleep();
        LCD_Seg_WakeUp();

        Wakeup_Flag = FALSE;
        
        PowerOn_to_Stop();

    }
}
/* [] END OF FILE */
