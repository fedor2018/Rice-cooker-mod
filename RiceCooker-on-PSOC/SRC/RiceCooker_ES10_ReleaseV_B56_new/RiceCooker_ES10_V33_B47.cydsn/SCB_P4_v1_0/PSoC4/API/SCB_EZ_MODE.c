/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZ_MODE.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*
*
*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_EZ_MODE.h"


/**********************************
*      System variables
**********************************/

uint32 volatile * const `$INSTANCE_NAME`_hwBuffer = `$INSTANCE_NAME`_EZ_DATA_PTR;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_WriteByte
********************************************************************************
*
* Summary:
*  Sets the I2C slave address mask.
*
* Parameters:
*  address: I2C slave address mask for the primary device. This value may be any
*  address between 0 and 127.
*
* Return:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzWriteByte(uint32 addr, uint32 dataByte)
{
    uint32 result;

    if(`$INSTANCE_NAME`_WAIT_STATES_INSERTED)
    {
        result = 0u;
        `$INSTANCE_NAME`_hwBuffer[addr] = dataByte;
    }
    else
    {
        `$INSTANCE_NAME`_hwBuffer[addr] = dataByte;

        result = (uint32) `$INSTANCE_NAME`_CHECK_INTR_TX(`$INSTANCE_NAME`_INTR_TX_BLOCKED);
    }

    return(result);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_ReadByte
********************************************************************************
*
* Summary:
*
* Parameters:
*
* Return:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzReadByte(uint32 addr)
{
    return(`$INSTANCE_NAME`_hwBuffer[addr]);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzGetEzAddress
********************************************************************************
*
* Summary:
*
* Parameters:
*  None
* Return:
*  
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzGetEzAddress(void)
{
    uint32 status;

    if(`$INSTANCE_NAME`_CHECK_SCB_MODE_EZI2C_CFG)
    {
        status = `$INSTANCE_NAME`_GET_I2C_STATUS_EZ_ADDRESS;
    }
    else
    {
        status = `$INSTANCE_NAME`_GET_SPI_STATUS_EZ_ADDRESS;
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzIsBusBusy
********************************************************************************
*
* Summary:
*  Sets the I2C slave address mask.
*
* Parameters:
*  address: I2C slave address mask for the primary device. This value may be any
*  address between 0 and 127.
*
* Return:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_EzIsBusBusy(void)
{
    uint32 status;

    if(`$INSTANCE_NAME`_CHECK_SCB_MODE_EZI2C_CFG)
    {
        status = (uint32) `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY);
    }
    else
    {
        status = (uint32) `$INSTANCE_NAME`_CHECK_SPI_STATUS(`$INSTANCE_NAME`_SPI_STATUS_BUS_BUSY);
    }

    return(status);
}


/* [] END OF FILE */
