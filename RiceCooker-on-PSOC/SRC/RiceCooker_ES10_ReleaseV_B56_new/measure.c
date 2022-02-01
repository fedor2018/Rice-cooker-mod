/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	measure.c																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/* Global variable used to store the RTD Temperature */
static float rtd_temperature = 0;
/* Global variable used to store Bus Current vlaue, unit mA */
static uint16 buscurrent = 0;
/* flag of ADC Sample, interval is 40* Tpwm_tc_isr = 40mS */
extern CYBIT adc_sampleEnable_flag;
/* flag of first sample, use by IIR/4 software filter*/ 
static CYBIT firstSample_flag = TRUE;

/* Temp var used for IIR/16 fotware Filter */
/**************************************************************************/
/* Static variable to store the RTD channel Convert result */
static uint16 rtdresult = 0;
/* variables use to store the temp and result of IIR/4 software filter */
static float  rtdresult_filterTemp = 0, rtdresult_filterResult = 0;
/* Static variable to store the Bus Current channel Convert result */
static uint16 currentresult = 0;
/* variables use to store the temp and result of IIR/4 software filter */
static int16  currentresult_filterTemp = 0, currentresult_filterResult = 0;
/**************************************************************************/
	
/*******************************************************************************
* Function Name: Get_ADCMeasureResult
********************************************************************************
* Summary:
* 1. Measure RTD sensor and bus current using SARADC
* 2. Call PI algorithm each time to update PWM output dutycycle based on ADC result
* 3. Function will be called each 50mS by isr_50cycle
* Parameters:  
*   N/A
*
* Return: 
*  void
*
*******************************************************************************/
void Get_ADCMeasureResult(void)
{

    float rtd_voltage = 0;
    uint16 tx_data;
	
	/* if 40ms interval flag is set */
	if(TRUE == adc_sampleEnable_flag)
	{
		/* Clear flag */
		adc_sampleEnable_flag = FALSE;
//		/* Start Convert */
//        ADC_StartConvert();
//        /* Waiting for all enabled channels be converted completely */
//        ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
        /* Read result back, rtd sensor = 0/buscurrent = 1 channel */
        rtdresult = ADC_GetResult16(0);
        currentresult = ADC_GetResult16(1);
        
        rtdresult = rtdresult/4;
        currentresult = currentresult/4;
        
       
//        UART_SpiUartWriteTxData((uint8)(currentresult));
//        UART_SpiUartWriteTxData((uint8)(currentresult>>8));
//        UART_UartPutChar('\n');
// 	    UART_UartPutChar('\r');	

        
        /* If IIR4 software seitch is enabled */
        #if(IIR4 == IIR4_ENABLE)
        {
            if(TRUE == firstSample_flag)
    		{
    			rtdresult_filterResult = rtdresult;
    			currentresult_filterResult = currentresult;
    			
    			firstSample_flag = FALSE;
    		}
    		/* IIR4 Filter */
    		rtdresult_filterTemp = (float)((rtdresult - rtdresult_filterResult)/8);
    		rtdresult_filterResult += rtdresult_filterTemp;
    		
    		rtd_voltage = (float)(rtdresult_filterResult * 2.048)/4096;
    		rtd_temperature = RTD_RestoTemp((float)((10000 * rtd_voltage)/(ACC_ACTUALLY_VALUE - rtd_voltage)));
    		
    		
    		currentresult_filterTemp = (int16)((currentresult - currentresult_filterResult)/8);
    		currentresult_filterResult += currentresult_filterTemp;
    		
    		buscurrent = ADC_CountsTo_mVolts(1, (currentresult_filterResult/AMP_ACTUALLY_VALUE));

        }
        #else
        {
            rtd_voltage = (float)(rtdresult * 2.048)/4096;
            rtd_temperature = RTD_RestoTemp((float)((10000 * rtd_voltage)/(ACC_ACTUALLY_VALUE - rtd_voltage)));
            
            buscurrent = ADC_CountsTo_mVolts(1, (currentresult/AMP_ACTUALLY_VALUE));
        }
        #endif
    
        
        /* PI algorithm be executed one time to calcualte PWM*/      
		PI_Temperature_Adjust();
        Auto_Cooking_to_Warming(rtd_temperature);
        I2C_Communication();
    }
}

/*******************************************************************************
* Function Name: Get_RtdTemperature
********************************************************************************
* Summary:
*   Get current rtd temperature value
* Parameters:  
*   N/A
*
* Return: 
*  rtd_temperature
*
*******************************************************************************/
float Get_RtdTemperature(void)
{
    return(rtd_temperature);
}

/*******************************************************************************
* Function Name: Set_RtdTemperature(Only for debugging)
********************************************************************************
* Summary:
*   Set current rtd temperature value
* Parameters:  
*   N/A
*
* Return: 
*  rtd_temperature
*
*******************************************************************************/
uint8 Set_RtdTemperature(uint8 workmode, uint8 tempvalue)
{
    uint8 temp = 0;
    
    if(
        ((COOKING_MODE == workmode)&& \
         ((tempvalue >= DATA_COOK_TEMPERATURE_MIN)&& \
          (tempvalue <= DATA_COOK_TEMPERATURE_MAX) \
         ) \
        ) || \
        ((WARMING_MODE == workmode)&& \
         ((tempvalue >= DATA_WARM_TEMPERATURE_MIN)&& \
          (tempvalue <= DATA_WARM_TEMPERATURE_MAX)
         ) \
        )  \
      ) \
    {
        rtd_temperature = tempvalue;
        temp = CY_SUCCESS;
    }
    else 
    {
        temp = CY_FAIL;
    }
    
    return(temp);
}

/*******************************************************************************
* Function Name: Get_BusCurrent
********************************************************************************
* Summary:
*   Get current bus current value
* Parameters:  
*   N/A
*
* Return: 
*  buscurrent
*
*******************************************************************************/
uint16 Get_BusCurrent(void)
{
    return(buscurrent);
}


/*******************************************************************************
* Function Name: Set_BusCurrent(Only for debugging)
********************************************************************************
* Summary:
*   Get current bus current value
* Parameters:  
*   N/A
*
* Return: 
*  buscurrent
*
*******************************************************************************/
void Set_BusCurrent(uint8 curvalue)
{
    buscurrent = curvalue;
}


/*******************************************************************************
* Function Name: Adc_Selftest
********************************************************************************
* Summary:
*   SAR ADC selftest 
* Parameters:  
*   N/A
*
* Return: 
*  void
*
*******************************************************************************/
void Adc_Selftest(void)
{


}

/* [] END OF FILE */
