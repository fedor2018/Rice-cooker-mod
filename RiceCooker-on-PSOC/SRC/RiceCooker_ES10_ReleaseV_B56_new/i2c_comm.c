/**************************************START OF THE FILE*************************************************************/
/********************************************************************************************************************/
/*																													*/
/*	Copyright (C) 2013 Cypress Semiconductor Technology(Shanghai) Co., LTD.											*/
/*																													*/
/*	System Name	:	Rice Cooker 																					*/
/*	Module Name	:																									*/
/*	File   Name	:	i2c_comm.c		    																			*/
/*	Revision	:	1.00																							*/
/*	Author		:	VisonZhang(XZNG)																				*/
/*	Date		:	2013/1/9																						*/
/*------------------------------------------------------------------------------------------------------------------*/
/*	History		:																									*/
/*------------------------------------------------------------------------------------------------------------------*/
/********************************************************************************************************************/
#include <device.h>

static uint8 bSensor[1];
static uint8 bWriteBuffer[1];
static uint8 bReadBuffer[2];

static uint8 SensorRaw[2] = {123, 45};
static uint8 pluscounter = 0;

/*******************************************************************************
* Function Name: I2C_Communication
********************************************************************************
* Summary:
* I2C Communication function, upload data to I2C BRIDGE PAANEL software
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void I2C_Communication(void)
{
    
    I2C_Updatebuffer();
}

void I2CBufferInit(void)
{
    I2C_I2CSlaveInitWriteBuf(bWriteBuffer,1);
    I2C_I2CSlaveInitReadBuf(bReadBuffer,2);
}

/*******************************************************************************
* Function Name: I2C_Selftest
********************************************************************************
* Summary:
* Parameters:  
*
* Return: 
*
*******************************************************************************/
void I2C_Selftest(void)
{
    I2C_Start();
    I2C_I2CSlaveInitWriteBuf(bWriteBuffer,1);
    I2C_I2CSlaveInitReadBuf(bWriteBuffer,2);
    I2C_Updatebuffer();
    
}

void I2C_Updatebuffer(void)
{
	/* Wait for I2C master to complete a write */ 
	if(0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_WR_CMPLT)) 
	{ 
	    I2C_I2CSlaveClearWriteStatus(); 
	    bSensor[0] = bWriteBuffer[0]; /* Transfer data */ 
	    I2C_I2CSlaveClearWriteBuf(); 
	} 
	if(0u != (I2C_I2CSlaveStatus() & I2C_I2C_SSTAT_RD_CMPLT))
	{
		I2C_I2CSlaveClearReadStatus();
		
		//Store Sensor Raw Count into I2C buffer
		bReadBuffer[0] = SensorRaw[bSensor[0]];
		bReadBuffer[1] = pluscounter++;
        
		I2C_I2CSlaveClearReadBuf(); 
	}
	if(pluscounter >=255) pluscounter = 0;
}
//[] END OF FILE

