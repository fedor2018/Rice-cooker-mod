/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZSPI_BOOT.c
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

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZSPI_BTLDR_COMM_ENABLED)

/***************************************
*    Bootloader Variables
***************************************/


/***************************************
*    Extern Bootloader Variables
***************************************/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiCyBtldrCommStart
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
void `$INSTANCE_NAME`_EzSpiCyBtldrCommStart(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiCyBtldrCommStop
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
void `$INSTANCE_NAME`_EzSpiCyBtldrCommStop(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiCyBtldrCommReset
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
void `$INSTANCE_NAME`_EzSpiCyBtldrCommReset(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiCyBtldrCommRead
********************************************************************************
*
* Summary:
*
* Parameters:
*  pData:     pointer to data buffer to store command.
*  Size:     maximum number of bytes which could to be passed back.
*  Count:    actual size of data was received.
*  TimeOut:  timeout value in tries of 10uS.
*
* Return:

*
* Global variables:
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_EzSpiCyBtldrCommRead(uint8 * pData, uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    status = CYRET_BAD_PARAM;
    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiCyBtldrCommWrite
********************************************************************************
*
* Summary:
*
* Parameters:
*  pData:     pointer to data buffer with response command.
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
cystatus `$INSTANCE_NAME`_EzSpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;
    status = CYRET_BAD_PARAM;
    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZSPI_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
