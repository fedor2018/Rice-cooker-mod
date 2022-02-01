/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	state_machine.c																					*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/* power on defualt mode is N/A */
static uint8 current_mode = NA_MODE;


static CYBIT modeswitch_success_flag = FALSE;

void Set_AutoModeSwitchflag(CYBIT flag)
{
     modeswitch_success_flag = flag;
}
CYBIT Get_AutoModeSwitchflag(void)
{
    return(modeswitch_success_flag);
}

/*******************************************************************************
* Function Name: Get_CurrentMode
********************************************************************************
* Summary:
* Get current work mode of Rice Cooker
* Parameters:  
*   N/A
*
* Return: 
*  current work mode
*
*******************************************************************************/
uint8 Get_CurrentMode(void)
{
    return(current_mode);
}

/*******************************************************************************
* Function Name: Set_CurrentMode
********************************************************************************
* Summary:
* Set work mode for Rice Cooker
* Parameters:  
*   mode 
*
* Return: 
*
*******************************************************************************/
void  Set_CurrentMode(uint8 mode)
{
    current_mode = mode;
}

/*******************************************************************************
* Function Name: PowerOn_to_Stop
********************************************************************************
* Summary:
* After ststem power on, rice cooker enter into stop mode automatically by execute
* this function
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void PowerOn_to_Stop(void)
{
    /* Timing timer start will record time */
    isr_200ms_Start();
    isr_1000ms_Start();

  
    LCD_Seg_Start();
    
    Timer_Start();
    Timer_TriggerCommand(Timer_MASK, Timer_CMD_START);

 	UART_UartPutString("Enter Stop Mode Automatically!"); 
    UART_UartPutChar('\n');
 	UART_UartPutChar('\r');	
    
	Set_CurrentMode(STOP_MODE);

}


/*******************************************************************************
* Function Name: Stop_to_Stop
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_Stop(void)
{
	Set_CurrentMode(STOP_MODE);
}

/*******************************************************************************
* Function Name: Stop_to_Timing
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_Timing(void)
{
	Set_CurrentMode(TIMING_MODE);
}

/*******************************************************************************
* Function Name: Stop_to_Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_Cooking(void)
{
    
    isr_50ms_Start();

	ADC_Start();
	Opamp_Start();
	Comp_Start();
    
	PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);
    
    I2C_Start();
    
	Set_CurrentMode(COOKING_MODE);
}

/*******************************************************************************
* Function Name: Stop_to_Warming
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_Warming(void)
{

    isr_50ms_Start();

	ADC_Start();
	Opamp_Start();
	Comp_Start();
	PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);
    I2C_Start();
    
	Set_CurrentMode(WARMING_MODE);
}

/*******************************************************************************
* Function Name: Stop_to_LowPower
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_LowPower(void)
{
   
	Set_CurrentMode(LOWPOWER_MODE);
    
    Set_AutoModeSwitchflag(TRUE);
    
    Set_LPFlag_Status(TRUE);
}

/*******************************************************************************
* Function Name: Stop_to_DeepSleep
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Stop_to_DeepSleep(void)
{

	Set_CurrentMode(DEEPSLEEP_MODE);

    Set_DPFlag_Status(TRUE);
}

/*******************************************************************************
* Function Name: Timing_to_STOP
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Timing_to_Stop(void)
{	
	Set_CurrentMode(STOP_MODE);
}

/*******************************************************************************
* Function Name: Timing_to_Timing
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Timing_to_Timing(void)
{
	Set_CurrentMode(TIMING_MODE);
}

/*******************************************************************************
* Function Name: Timing_to_Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Timing_to_Cooking(void)
{
    isr_50ms_Start();

	ADC_Start();
	Opamp_Start();
	Comp_Start();
	PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);

    I2C_Start();
    
	Set_CurrentMode(COOKING_MODE);
    
    Set_AutoModeSwitchflag(TRUE);
}

/*******************************************************************************
* Function Name: Timing_to_Pause
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Timing_to_Pause(void)
{
    isr_1000ms_Disable();
    Timer_Stop();
    Set_CurrentMode(PAUSE_MODE);
}

/*******************************************************************************
* Function Name: Cooking_to_Stop
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Cooking_to_stop(void)
{	
	isr_50ms_Disable();

    I2C_Stop();
    PWM_Stop();
    
	ADC_Stop();
	Opamp_Stop();
	Comp_Stop();

	Set_CurrentMode(STOP_MODE);
}

/*******************************************************************************
* Function Name: Cooking_to_Timing
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Cooking_to_Timing(void)
{
	isr_50ms_Disable();

    I2C_Stop();
    PWM_Stop();
    
	ADC_Stop();
	Opamp_Stop();
	Comp_Stop();
    
	Set_CurrentMode(TIMING_MODE);
}
    
/*******************************************************************************
* Function Name: Cooking_to_Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Cooking_to_Cooking(void)
{
	Set_CurrentMode(COOKING_MODE);
}

/*******************************************************************************
* Function Name: Cooking_to_Warming
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Cooking_to_Warming(void)
{
	Set_CurrentMode(WARMING_MODE);
}

/*******************************************************************************
* Function Name: Cooking_to_Pause
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Cooking_to_Pause(void)
{
    isr_1000ms_Disable();
    Timer_Stop();
    I2C_Stop();
    PWM_Stop();
    
    Set_CurrentMode(PAUSE_MODE);
}

/*******************************************************************************
* Function Name: Warming_to_Stop
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Warming_to_Stop(void)
{	
	isr_50ms_Disable();

    I2C_Stop();
    PWM_Stop();
    
	ADC_Stop();
	Opamp_Stop();
	Comp_Stop();
    
	Set_CurrentMode(STOP_MODE);
}

/*******************************************************************************
* Function Name: Warming_to_Timing
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Warming_to_Timing(void)
{
	isr_50ms_Disable();

    I2C_Stop();
    PWM_Stop();
    
	ADC_Stop();
	Opamp_Stop();
	Comp_Stop();
    
	Set_CurrentMode(TIMING_MODE);
}

/*******************************************************************************
* Function Name: Warming_to_Warming
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Warming_to_Warming(void)
{
	Set_CurrentMode(WARMING_MODE);
}

/*******************************************************************************
* Function Name: Warming_to_Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Warming_to_Cooking(void)
{
	Set_CurrentMode(COOKING_MODE);
}

/*******************************************************************************
* Function Name: Warming_to_Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Warming_to_Pause(void)
{
    isr_1000ms_Disable();
    Timer_Stop();
    I2C_Stop();
    PWM_Stop();

    Set_CurrentMode(PAUSE_MODE);
}

/*******************************************************************************
* Function Name: LP_to_Stop
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void LowPower_to_Stop(void)
{	
	Set_LPFlag_Status(FALSE);

	Set_CurrentMode(STOP_MODE);
}

/*******************************************************************************
* Function Name: LP_to_DeepSleep
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void LowPower_to_DeepSleep(void)
{
	Set_CurrentMode(DEEPSLEEP_MODE);
    Set_AutoModeSwitchflag(TRUE);
    
    Set_LPFlag_Status(FALSE);
	Set_DPFlag_Status(TRUE);	
}

/*******************************************************************************
* Function Name: DP_to_STOP
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void DeepSleep_to_Stop(void)
{	
	Set_CurrentMode(STOP_MODE);
    
    Set_DPFlag_Status(FALSE);	
}

/*******************************************************************************
* Function Name: Pause to timing
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Pause_to_Timing(void)
{
    isr_1000ms_Enable();
    Timer_Start();
    Timer_TriggerCommand(Timer_MASK,Timer_CMD_START);
    Set_CurrentMode(TIMING_MODE);
}

/*******************************************************************************
* Function Name: Pause to Cooking
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Pause_to_Cooking(void)
{
    isr_1000ms_Enable();
    Timer_Start();
    Timer_TriggerCommand(Timer_MASK,Timer_CMD_START);
    I2C_Start();
    PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);
    
    Set_CurrentMode(COOKING_MODE);
}

/*******************************************************************************
* Function Name: Pause to Warming
********************************************************************************
* Summary:
*   mode switch api 
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void Pause_to_Warming(void)
{
    isr_1000ms_Enable();
    Timer_Start();
    Timer_TriggerCommand(Timer_MASK,Timer_CMD_START);
    I2C_Start();
    PWM_Start();
    PWM_TriggerCommand(PWM_MASK, PWM_CMD_START);
    
    Set_CurrentMode(WARMING_MODE);
}

/* Mode Transition Jump Table */
uint32 (* ApiArray[7][7])() = 
{
    {
        /*Stop to xx */
        &Stop_to_Stop,          /*[0][0]*/
        &Stop_to_Timing,        /*[0][1]*/
        &Stop_to_Cooking,       /*[0][2]*/
        &Stop_to_Warming,       /*[0][3]*/
        &Stop_to_LowPower,      /*[0][4]*/
        &Stop_to_DeepSleep,     /*[0][5]*/
        0                       /*[0][6]*/
    },
    {   
        /*Timing to xx */
        &Timing_to_Stop,        /*[1][0]*/
        &Timing_to_Timing,      /*[1][1]*/
        &Timing_to_Cooking,     /*[1][2]*/
        0,                      /*[1][3]*/
        0,                      /*[1][4]*/
        0,                      /*[1][5]*/
        &Timing_to_Pause        /*[1][6]*/
    },
    {
        /*Cooking to xx */
        &Cooking_to_stop,       /*[2][0]*/    
        &Cooking_to_Timing,     /*[2][1]*/
        &Cooking_to_Cooking,    /*[2][2]*/
        &Cooking_to_Warming,    /*[2][3]*/
        0,                      /*[2][4]*/
        0,                      /*[2][5]*/
        &Cooking_to_Pause       /*[2][6]*/
    },
    {
        /*Warming to xx */
        &Warming_to_Stop,       /*[3][0]*/ 
        &Warming_to_Timing,     /*[3][1]*/ 
        &Warming_to_Cooking,    /*[3][2]*/ 
        &Warming_to_Warming,    /*[3][3]*/ 
        0,                      /*[3][4]*/ 
        0,                      /*[3][5]*/ 
        &Warming_to_Pause       /*[3][6]*/ 
    },
    {
        /*Lowpower to xx */
        &LowPower_to_Stop,      /*[4][0]*/ 
        0,                      /*[4][1]*/ 
        0,                      /*[4][2]*/ 
        0,                      /*[4][3]*/ 
        0,                      /*[4][4]*/ 
        &LowPower_to_DeepSleep, /*[4][5]*/ 
        0                       /*[4][6]*/ 
    },
    {
        /* DeepSleep to xx */
        &DeepSleep_to_Stop,     /*[5][0]*/ 
        0,                      /*[5][1]*/
        0,                      /*[5][2]*/
        0,                      /*[5][3]*/
        0,                      /*[5][4]*/
        0,                      /*[5][5]*/
        0                       /*[5][6]*/
    },
    {
        0,                      /*[6][0]*/
        &Pause_to_Timing,       /*[6][1]*/
        &Pause_to_Cooking,      /*[6][2]*/
        &Pause_to_Warming,      /*[6][3]*/
        0,                      /*[6][4]*/
        0,                      /*[6][5]*/
        0                       /*[6][6]*/
    }
};

/*******************************************************************************
* Function Name: Mode_Switching
********************************************************************************
* Summary:
*   Mode transition API 
* Parameters:  
*
* Return: 
*   cy_success/cy_fail
*******************************************************************************/
uint8 Mode_Switching(uint8 cur_mode, uint8 sw_mode)
{
    uint8 temp = CY_SUCCESS;
    if(0 == (ApiArray[cur_mode][sw_mode]))
    {
        temp = CY_FAIL;
    }
    else
    {
        ApiArray[cur_mode][sw_mode]();
       
    }
    
    return(temp);
}



/* [] END OF FILE */
