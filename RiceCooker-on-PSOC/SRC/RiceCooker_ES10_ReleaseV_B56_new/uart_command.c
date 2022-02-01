/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	uart_command.c																						*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/

#include <device.h>

/* extern var */
extern uint8 UART_Rx_Buffer[8];
extern CYBIT flag_IsPackageReceived;

static uint8 cooking_temperature = DEFAULT_COOK_TEMPERATURE;
static uint8 warming_temperature = DEFAULT_WARM_TEMPERATURE;

static uint8 timing2cooking_interval = COOKING_TIMING_VALUE;
static uint8 stop2lp_interval = LP_TIMING_VALUE;
static uint8 lp2dp_interval = DP_TIMING_VALUE;

/* use for timing record clear */
CYBIT	flag_IsAny_Cmd_Executed = FALSE;

CYBIT   flag_print = FALSE;
static uint8 rev_command_data, rev_command_data_backup;
static uint8 rev_command_type, rev_command_type_backup;


/*******************************************************************************
* Function Name: Get_CookingTemperature
********************************************************************************
* Summary:
* Get Rice Cooker work temperatur of Cooking Mode
* Parameters:  
*   N/A
*
* Return: 
*  cooking_temperature
*
*******************************************************************************/
uint8 Get_CookingTemperature(void)
{
    return(cooking_temperature);
}

/*******************************************************************************
* Function Name: Set_CookingTemperature
********************************************************************************
* Summary:
* Set Rice Cooker work temperatur of Cooking Mode
* Parameters:  
*   temperature, value within [0x50,0x5A](80dg to 90 dg)
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
uint8 Set_CookingTemperature(uint8 temperature)
{
    uint8 temp;
    if((temperature >= DATA_COOK_TEMPERATURE_MIN)&&(temperature <= DATA_COOK_TEMPERATURE_MAX))
    {
        cooking_temperature = temperature;
        temp = CY_SUCCESS;
    }
    else
    {
        UART_UartPutString("Invalid, Range out of 0x50~0x5A"); 
 	    UART_UartPutChar('\n');
 	    UART_UartPutChar('\r');
        
        temp = CY_FAIL;
    }
    return(temp);
}

/*******************************************************************************
* Function Name: Get_WarmingTemperature
********************************************************************************
* Summary:
* Get Rice Cooker work temperatur of Warming Mode
* Parameters:  
*   
*
* Return: 
*  warm temperature
*
*******************************************************************************/
uint8 Get_WarmingTemperature(void)
{
    return(warming_temperature);
}

/*******************************************************************************
* Function Name: Set_WarmingTemperature
********************************************************************************
* Summary:
* Set Rice Cooker work temperatur of Warming Mode
* Parameters:  
*   Temperature value, should be within [0x32,0x46](50dg to 70 dg)
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
uint8 Set_WarmingTemperature(uint8 temperature)
{
    uint8 temp;
    if((temperature >= DATA_WARM_TEMPERATURE_MIN)&&(temperature <= DATA_WARM_TEMPERATURE_MAX))
    {
        warming_temperature = temperature;
        temp = CY_SUCCESS;
    }
    else
    {
        UART_UartPutString("Invalid, Range out of 0x32~0x46"); 
 	    UART_UartPutChar('\n');
 	    UART_UartPutChar('\r');	
        
        temp = CY_FAIL;
    }
    return(temp);
    
}

/*******************************************************************************
* Function Name: Get_Timing2Cooking_Interval
********************************************************************************
* Summary:
*   Get timing record value from timing mode to cooking mode 
* Parameters:  
*   
*
* Return: 
*  timing2cooking_interval
*
*******************************************************************************/
uint8 Get_Timing2Cooking_Interval(void)
{
    return(timing2cooking_interval);
}

/*******************************************************************************
* Function Name: Set_Timing2Cooking_Interval
********************************************************************************
* Summary:
*   Set timing record value from timing mode to cooking mode 
* Parameters:  
*   interval bettween 0x01~0xFA ()
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
uint8  Set_Timing2Cooking_Interval(uint8 interval)
{
    uint8 temp;
    
    if((interval >= DATA_TIMING_MIN) && (interval <= DATA_TIMING_MAX))
    {
        timing2cooking_interval = interval;
        temp = CY_SUCCESS;
    }
    else
    {
        UART_UartPutString("Invalid, Range out of 0x01~0xFA"); 
 	    UART_UartPutChar('\n');
 	    UART_UartPutChar('\r');	
        
        temp = CY_FAIL;
    }
    return(temp);
}

/*******************************************************************************
* Function Name: Get_Stop2LP_Interval
********************************************************************************
* Summary:
*   Get timing record value from Stop mode to LP mode 
* Parameters:  
*   
*
* Return: 
*  stop2lp_interval
*
*******************************************************************************/
uint8 Get_Stop2LP_Interval(void)
{
    return(stop2lp_interval);
}

/*******************************************************************************
* Function Name: Set_Stop2LP_Interval
********************************************************************************
* Summary:
*   Set timing record value from Stop mode to LP mode 
* Parameters:  
*   interval bettween 0x01~0xFA ()
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
uint8  Set_Stop2LP_Interval(uint8 interval)
{
    uint8 temp;
    
    if((interval >= DATA_TIMING_MIN) && (interval <= DATA_TIMING_MAX))
    {
        stop2lp_interval = interval;
        temp = CY_SUCCESS;
    }
    else
    {
        UART_UartPutString("Invalid, Range out of 0x01~0xFA"); 
 	    UART_UartPutChar('\n');
 	    UART_UartPutChar('\r');	
        
        temp = CY_FAIL;
    }
    return(temp);
}

/*******************************************************************************
* Function Name: Get_LP2DP_Interval
********************************************************************************
* Summary:
*   Get timing record value from LP mode to DPSleep mode 
* Parameters:  
*   
*
* Return: 
*  lp2dp_interval
*
*******************************************************************************/
uint8 Get_LP2DP_Interval(void)
{
    return(lp2dp_interval);
   
}

/*******************************************************************************
* Function Name: Set_LP2DP_Interval
********************************************************************************
* Summary:
*   Set timing record value from LP mode to DPSleep mode 
* Parameters:  
*   interval bettween 0x01~0xFA ()
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
uint8  Set_LP2DP_Interval(uint8 interval)
{
    uint8 temp;
    
    if((interval >= DATA_TIMING_MIN) && (interval <= DATA_TIMING_MAX))
    {
        lp2dp_interval = interval;
        temp = CY_SUCCESS;
    }
    else
    {
        UART_UartPutString("Invalid, Range out of 0x01~0xFA"); 
 	    UART_UartPutChar('\n');
 	    UART_UartPutChar('\r');	
        
        temp = CY_FAIL;
    }
    return(temp);
}

/*******************************************************************************
* Function Name: IsCommandDecodePass
********************************************************************************
* Summary:
* Function to check the format of received command package and decode 
* Parameters:  
*   
*
* Return: 
*  CY_SUCCESS/CY_FAIL
*
*******************************************************************************/

uint8 IsCommandDecodePass(void)
{
	uint8 temp;
	uint8 i;
	uint8 cmd_length = 0, cmd_checksum = 0;
	
    /* if a complete package is received */
	if(TRUE == flag_IsPackageReceived)
	{
		/* Calculate the checksum Command first*/
		cmd_checksum = UART_Rx_Buffer[COMMAND_LENGTH_BYTE] + \
					  UART_Rx_Buffer[COMMAND_TYPE_BYTE] + \
					  UART_Rx_Buffer[COMMAND_DATA_BYTE];
		
		/* calculate the lengh of cmd package */
		for(i = 0; i < 8; i++)
		{
			if(PACKAGE_STOP == UART_Rx_Buffer[i])
			{
				cmd_length = i+1;
				break;
			}
		}
		/* Check the package length is correct */
		if((UART_Rx_Buffer[COMMAND_LENGTH_BYTE] == cmd_length) && (COMMAND_PACKAGE_SIZE == UART_Rx_Buffer[COMMAND_LENGTH_BYTE]))
		{
			/*checksum verification*/
			if((UART_Rx_Buffer[COMMAND_CHECKSUM_BYTE] == cmd_checksum) || (UART_Rx_Buffer[COMMAND_CHECKSUM_BYTE] == PACHAGE_CHECKSUM_DEBUG))
			{
				/* Command type&data verification */
				if( ( (TYPE_MODE_SWITCH         == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) && \
					  ((DATA_STOP_MODE_ENTER    == UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
					   (DATA_TIMING_MODE_ENTER  == UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
					   (DATA_Cooking_MODE_ENTER == UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
					   (DATA_WARMING_MODE_ENTER == UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
					   (DATA_LP_MODE_ENTER  	== UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
                       (DATA_DP_MODE_ENTER	    == UART_Rx_Buffer[COMMAND_DATA_BYTE]) || \
					   (DATA_PAUSE_MODE_ENTER   == UART_Rx_Buffer[COMMAND_DATA_BYTE])	 \
					  )		\
					) ||	\			
					( (TYPE_COOK_TEMPERATURE_SET == UART_Rx_Buffer[COMMAND_TYPE_BYTE])&& \
					  ((UART_Rx_Buffer[COMMAND_DATA_BYTE] >= DATA_COOK_TEMPERATURE_MIN) && (UART_Rx_Buffer[COMMAND_DATA_BYTE] <= DATA_COOK_TEMPERATURE_MAX))	\
					) ||	\
					( (TYPE_WARM_TEMPERATURE_SET == UART_Rx_Buffer[COMMAND_TYPE_BYTE])&& \
					  ((UART_Rx_Buffer[COMMAND_DATA_BYTE] >= DATA_WARM_TEMPERATURE_MIN) && (UART_Rx_Buffer[COMMAND_DATA_BYTE] <= DATA_WARM_TEMPERATURE_MAX))	\
					) ||	\
					( ((TYPE_COOK_TIMING_SET == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) || (TYPE_LP_TIMING_SET == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) || (TYPE_DP_TIMING_SET == UART_Rx_Buffer[COMMAND_TYPE_BYTE])) && \
					  ((UART_Rx_Buffer[COMMAND_DATA_BYTE] >= DATA_TIMING_MIN) && (UART_Rx_Buffer[COMMAND_DATA_BYTE] <= DATA_TIMING_MAX))	\
					) ||	\
                    (
                      (SAR_RTD_TEMP_SET      == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) || \
                      (SAR_BUS_CURRENT_SET   == UART_Rx_Buffer[COMMAND_TYPE_BYTE])    \
                    ) ||    \
					( (TYPE_GET_CURRENT_MODE == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) || \
					  (TYPE_GET_TEMPERATURE  == UART_Rx_Buffer[COMMAND_TYPE_BYTE]) || \
					  (TYPE_GET_BUSCURRENT   == UART_Rx_Buffer[COMMAND_TYPE_BYTE])    \
					) 		\
				 )
				 {
				 	rev_command_data_backup = rev_command_type;
					rev_command_type_backup = rev_command_type;
					
					rev_command_type = UART_Rx_Buffer[COMMAND_TYPE_BYTE];					
					rev_command_data = UART_Rx_Buffer[COMMAND_DATA_BYTE];
					
					temp = CY_SUCCESS;
				 }
				 else
				 {
				 	temp = CY_FAIL;
				 }
				
			}
			else
			{
				temp = CY_FAIL;
			}
		}
		else
		{
			temp = CY_FAIL;
		}
	}
	else
	{
		temp = CY_FAIL;
	}
	
	return(temp);
}

/*******************************************************************************
* Function Name: Command_Buffer_Clear
********************************************************************************
* Summary:
*   Function to clear command buffer 
* Parameters:  
*   
*
* Return: 
*  
*
*******************************************************************************/

void  Command_Buffer_Clear(void)
{
	uint8 i;
	for(i=0; i<8; i++)
	{
		UART_Rx_Buffer[i] = 0;
	}
}


/*******************************************************************************
* Function Name: Command_Execute
********************************************************************************
* Summary:
*   Finction to execute the received command 
* Parameters:  
*   cmdtype - Type of received Command 
*   cmddata - Data of received Command
* Return: 
*   CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
/*  */
uint8 Command_Execute(uint8 cmdtype, uint8 cmddata)
{
	uint8 temp = CY_SUCCESS;
	
	switch(cmdtype)
	{
		case TYPE_MODE_SWITCH:
		{
			switch(cmddata)
			{
				case DATA_STOP_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), STOP_MODE))
					{
						UART_UartPutString("Stop Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				case DATA_TIMING_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), TIMING_MODE))
					{
						UART_UartPutString("Timing Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				case DATA_Cooking_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), COOKING_MODE))
					{
						UART_UartPutString("Cooking Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				case DATA_WARMING_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), WARMING_MODE))
					{
						UART_UartPutString("Warming Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				case DATA_LP_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), LOWPOWER_MODE))
					{
						UART_UartPutString("LowPower Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				case DATA_DP_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), DEEPSLEEP_MODE))
					{
						UART_UartPutString("DeepSleep Mode Enter!"); 
					}
					else
					{   
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
                case DATA_PAUSE_MODE_ENTER:
				{
					if(CY_SUCCESS == Mode_Switching(Get_CurrentMode(), PAUSE_MODE))
					{
						UART_UartPutString("PAUSE Mode Enter!"); 
					}
					else
					{
                        temp = CY_FAIL;
						UART_UartPutString("Invalid Mode Transition!"); 
					}
					break;
				}
				default:
				{
					temp = CY_FAIL;
					UART_UartPutString("Invalid Mode Transition!"); 
					break;
				}
			}
			break;
		}
		case TYPE_COOK_TEMPERATURE_SET:
		{
			if(CY_SUCCESS == Set_CookingTemperature(cmddata)) 
            {
                UART_UartPutString("Cooking Temperature is set!"); 
            }
            else 
            {
                temp = CY_FAIL;
            }
			break;
		}
		case TYPE_WARM_TEMPERATURE_SET:
		{
			if(CY_SUCCESS == Set_WarmingTemperature(cmddata)) 
            {
                UART_UartPutString("Warming Temperature is set!"); ; 
            }
            else 
            {
                temp = CY_FAIL;
            }
			break;
		}
		case TYPE_COOK_TIMING_SET:
		{
			if(CY_SUCCESS == Set_Timing2Cooking_Interval(cmddata)) 
            {
                UART_UartPutString("Cook Enter Timing is set!"); 
            }
            else 
            {
                temp = CY_FAIL;
            }
			break;
		}
		case TYPE_LP_TIMING_SET:
		{
			if(CY_SUCCESS == Set_Stop2LP_Interval(cmddata)) 
            {
                UART_UartPutString("LP Enter Timing is set!"); 
            }
            else 
            {
                temp = CY_FAIL;
            }
			break;
		}
		case TYPE_DP_TIMING_SET:
		{
			if(CY_SUCCESS == Set_LP2DP_Interval(cmddata)) 
            {
                UART_UartPutString("DP Enter Timing is set!"); 
            }
            else 
            {
                temp = CY_FAIL;
            }
			break;
		}
		case TYPE_GET_CURRENT_MODE:
		{
			UART_UartPutString("Current Mode is: "); 
			switch(Get_CurrentMode())
			{
				case STOP_MODE:
				{
					UART_UartPutString("Stop Mode"); 
					break;
				}
				case TIMING_MODE:
				{
					UART_UartPutString("Timing Mode");
					break;
				}
				case COOKING_MODE:
				{
					UART_UartPutString("Cooking Mode");
					break;
				}
				case WARMING_MODE:
				{
					UART_UartPutString("Warming Mode");
					break;
				}
				case LOWPOWER_MODE:
				{
					UART_UartPutString("LowPower Mode");
					break;
				}
				case DEEPSLEEP_MODE:
				{
					UART_UartPutString("DeepSleep Mode");
					break;
				}
				case PAUSE_MODE:
				{
					UART_UartPutString("Pause Mode");
					break;
				}
				default:
				{
					UART_UartPutString("NaN");
					temp = CY_FAIL;
					break;
				}
			}
			break;
		}
		case TYPE_GET_TEMPERATURE:
		{
            //flag_print = TRUE;
			UartDisplay(DISPLAY_TEMPERATURE);
			break;
		}
        case SAR_RTD_TEMP_SET:
        {
            if(CY_SUCCESS == Set_RtdTemperature(Get_CurrentMode(), cmddata))
            {
                UART_UartPutString("RTD Tmeprature is set!");
            }
            else
            {
                UART_UartPutString("Invalid CMD");
                temp = CY_FAIL;
            }
            break;
        }
		case TYPE_GET_BUSCURRENT:
		{

			UartDisplay(DISPLAY_BUSCURRENT);
			break;
		}
        case SAR_BUS_CURRENT_SET:
        {
            Set_BusCurrent(cmddata);
            UART_UartPutString("Bus Current Value is set!");
            break;
        }
		default:
		{
			temp = CY_FAIL;
			break;
		}
	}
    
	UART_UartPutChar('\n');
	UART_UartPutChar('\r');	
	
	return (temp);
}

/*******************************************************************************
* Function Name: Command_Management
********************************************************************************
* Summary:
*   function to integrated command decode, command execute functions together
* Parameters:  
*
* Return: 
*   CY_SUCCESS/CY_FAIL
*
*******************************************************************************/
void  Command_Management(void)
{ 
	/* If Complete Command Package is received */
	if(TRUE == flag_IsPackageReceived)
	{
		/* If format of Command package is correct */
		if(CY_SUCCESS == IsCommandDecodePass())
		{
			if(CY_SUCCESS == Command_Execute(rev_command_type, rev_command_data))
            {
                
                flag_IsAny_Cmd_Executed = TRUE;
            }
            else
            {
                UART_UartPutString("Command Execute Fail, Try Again!");
                UART_UartPutChar('\n');
	            UART_UartPutChar('\r');	
            }
		}
		/* If Command Length or Checksum is not correct */
		else
		{
    		UART_UartPutString("Invalid Command!"); 
    		UART_UartPutChar('\n');
    		UART_UartPutChar('\r');
		}
        /* Clear command buffer */
		Command_Buffer_Clear();
        /* clear flag */
		flag_IsPackageReceived = FALSE;
	}

}

/*******************************************************************************
* Function Name: Uart_Selftest
********************************************************************************
* Summary:
*   uart self test function
* Parameters:  
*
* Return: 
*   
*
*******************************************************************************/
void Uart_Selftest(void)
{;}


void Auto_Cooking_to_Warming(float temper )
{
   
    if(temper >= cooking_temperature)
    {
        Cooking_to_Warming();
    }
}

/* [] END OF FILE */
