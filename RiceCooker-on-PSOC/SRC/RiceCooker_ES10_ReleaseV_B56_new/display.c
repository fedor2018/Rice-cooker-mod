/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	display.c																							*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

extern CYBIT seglcd_refresh_flag;


/*******************************************************************************
* Function Name: UartDisplay
********************************************************************************
* Summary:
*   API use to send RTD temperature or bus current to PC COM tool when checking
*   command is recieved
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void UartDisplay(uint8 display_type)
{

/*    
	char	readout_data[2];
    uint8   str1;
    
    str1 = (uint8) Get_RtdTemperature();
    
	hex2char_byte(readout_data, str1);
    
	UART_UartPutString(readout_data);
	UART_UartPutChar('\n');
	UART_UartPutChar('\r');	
}
*/

	char tempstr[8]={'\0'};
	char currentstr[8]={'\0'};
    float temp;
    
    temp = Get_RtdTemperature();
    
	if(DISPLAY_TEMPERATURE == display_type)
	{
//		sprintf(tempstr,"%4.1f",temp);
        ftoa(temp, tempstr);
		if((temp) >= 100.0)
		{
			if( (tempstr[4] == '0') || \
				(tempstr[4] == '1') || \
				(tempstr[4] == '2') || \
				(tempstr[4] == '3') || \
				(tempstr[4] == '4')
			  )
			{
				tempstr[4] = '0';
			}
			else
			{
				tempstr[4] = '5';	
			}
			tempstr[5] = '\0';
		}
		else
		{
			if( (tempstr[3] == '0') || \
				(tempstr[3] == '1') || \
				(tempstr[3] == '2') || \
				(tempstr[3] == '3') || \
				(tempstr[3] == '4')
			  )
			{
				tempstr[3] = '0';
			}
			else
			{
				tempstr[3] = '5';	
			}
			tempstr[4] = '\0';
		}
		UART_UartPutString("Heat Plate Temperature:  ");
		UART_UartPutString(tempstr);
		UART_UartPutString("dg");
		UART_UartPutChar('\n');
		UART_UartPutChar('\r');
	}
	else if(DISPLAY_BUSCURRENT == display_type)
	{
		UART_UartPutString("Bus Current:  ");
//		sprintf(currentstr,"%3d", Get_BusCurrent());
//      ftoa((float)Get_BusCurrent(), currentstr);
        itoa(Get_BusCurrent(), currentstr, 10);
        currentstr[4] = '\0';
		UART_UartPutString(currentstr);
		UART_UartPutString("mV");
		UART_UartPutChar('\n');
		UART_UartPutChar('\r');
	}

}

/*******************************************************************************
* Function Name: SeglcdDisplay
********************************************************************************
* Summary:
*   Segment LCD display API
*   Occur cycle is 200ms
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void SeglcdDisplay(uint8 work_mode, uint32 timing_countervalue)
{
    if(TRUE == seglcd_refresh_flag)
    {
    	/* Display the work mode */
    	LCD_Seg_Write7SegNumber_0(work_mode,0,1); 
    	/* Diaplay the dot */
    	LCD_Seg_WritePixel(LCD_Seg_HBAR0,1);
    	/* Display the run time, timing_countervalue is the global counter value, the format is covert to time format*/
    	LCD_Seg_Write7SegNumber_1(((timing_countervalue/60)*100 + timing_countervalue%60),0,1);  
        
        seglcd_refresh_flag = FALSE;
    }
}

/* seglcd self test function */
void Seglcd_Selftest(void)
{;}





/* [] END OF FILE */
