/*******************************************************************************
* File Name: `$INSTANCE_NAME`_UART_BOOT.c
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "`$INSTANCE_NAME`_SPI_UART.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED)


/***************************************
*    Bootloader Variables
***************************************/


/***************************************
*    Extern Bootloader Variables
***************************************/


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartCyBtldrCommStart
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
void `$INSTANCE_NAME`_UartCyBtldrCommStart(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartCyBtldrCommStop
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
*******************************************************************************/
void `$INSTANCE_NAME`_UartCyBtldrCommStop(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartCyBtldrCommReset
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
void `$INSTANCE_NAME`_UartCyBtldrCommReset(void)
{
    ;
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartCyBtldrCommRead
********************************************************************************
*
* Summary:
*  Receives the command from the Host.
*  All bytes are received by the Uart ISR and stored in internal Uart buffer. The
*  function checks status with timeout to detemine the end of transfer and
*  then copy data to bootloader buffer.
*  After exist this function the Uart ISR is able to receive more data.
*
* Parameters:
*  pData:     pointer to data buffer to store command.
*  Size:     maximum number of bytes which could to be passed back.
*  Count:    actual size of data was received.
*  TimeOut:  timeout value in tries of 10uS.
*
* Return:
*  Status of receive operation.
*
* Global variables:
*  `$INSTANCE_NAME`_slWriteBuf - used to store received command.
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_UartCyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartCyBtldrCommWrite
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
cystatus `$INSTANCE_NAME`_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    status = CYRET_BAD_PARAM;

    return(status);
}

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED) */


/* [] END OF FILE */
