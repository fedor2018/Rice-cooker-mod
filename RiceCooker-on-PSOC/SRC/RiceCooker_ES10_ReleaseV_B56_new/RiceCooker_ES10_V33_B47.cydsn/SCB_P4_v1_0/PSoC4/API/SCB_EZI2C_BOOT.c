/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZI2C_BOOT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_EZ_MODE.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED)

/***************************************
*    Bootloader Variables
***************************************/


/***************************************
*    Extern Bootloader Variables
***************************************/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CCyBtldrCommStart
********************************************************************************
*
* Summary:
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*
* Global variables:
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CCyBtldrCommStart(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CCyBtldrCommStop
********************************************************************************
*
* Summary:
*  Disables the communication component and disables the interrupt.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CCyBtldrCommStop(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CCyBtldrCommReset
********************************************************************************
*
* Summary:
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzI2CCyBtldrCommReset(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CCyBtldrCommRead
********************************************************************************
*
* Summary:
*
* Parameters:
*  pData:    pointer to data buffer to store command.
*  Size:     maximum number of bytes which could to be passed back.
*  Count:    actual size of data was received.
*  TimeOut:  timeout value in tries of 10uS.
*
* Return:

*
* Global variables:
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite
********************************************************************************
*
* Summary:
*
* Parameters:
*  pData:    pointer to data buffer with response command.
*  Size:     number of bytes required to be transmitted.
*  Count:    actual size of data was transmitted.
*  TimeOut:  timeout value in tries of 10uS.
*
* Return:
*  Status of transmit operation.
*
* Global variables:
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    return(status);
}

#endif /* #if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
