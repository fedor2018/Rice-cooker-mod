/*******************************************************************************
* File Name: `$INSTANCE_NAME`_BOOT.c
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

#include "`$INSTANCE_NAME`.h"

#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStart
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
void `$INSTANCE_NAME`_CyBtldrCommStart(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CCyBtldrCommStart();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiCyBtldrCommStart();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartCyBtldrCommStart();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CCyBtldrCommStart();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzSpiCyBtldrCommStart();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            `$INSTANCE_NAME`_I2CCyBtldrCommStart();

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            `$INSTANCE_NAME`_SpiCyBtldrCommStart();

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            `$INSTANCE_NAME`_UartCyBtldrCommStart();

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            `$INSTANCE_NAME`_EzI2CCyBtldrCommStart();

        #else
            `$INSTANCE_NAME`_EzSpiCyBtldrCommStart();

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommStop
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
void `$INSTANCE_NAME`_CyBtldrCommStop(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CCyBtldrCommStop();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiCyBtldrCommStop();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartCyBtldrCommStop();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CCyBtldrCommStop();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzSpiCyBtldrCommStop();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            `$INSTANCE_NAME`_I2CCyBtldrCommStop();

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            `$INSTANCE_NAME`_SpiCyBtldrCommStop();

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            `$INSTANCE_NAME`_UartCyBtldrCommStop();

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            `$INSTANCE_NAME`_EzI2CCyBtldrCommStop();

        #else
            `$INSTANCE_NAME`_EzSpiCyBtldrCommStop();

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommReset
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
void `$INSTANCE_NAME`_CyBtldrCommReset(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CCyBtldrCommReset();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiCyBtldrCommReset();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartCyBtldrCommReset();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CCyBtldrCommReset();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzSpiCyBtldrCommReset();
        }
        else
        {
            /* Unknown mode: do nothing */
        }
    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            `$INSTANCE_NAME`_I2CCyBtldrCommReset();

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            `$INSTANCE_NAME`_SpiCyBtldrCommReset();

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            `$INSTANCE_NAME`_UartCyBtldrCommReset();

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            `$INSTANCE_NAME`_EzI2CCyBtldrCommReset();

        #else
            `$INSTANCE_NAME`_EzSpiCyBtldrCommReset();

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommRead
********************************************************************************
*
* Summary:
*
* Parameters:
*  pData:    pointer to pData buffer with response command.
*  Size:     number of bytes required to be transmitted.
*  Count:    actual size of pData was transmitted.
*  TimeOut:  timeout value in tries of 10uS.
*
* Return:
*  Status of transmit operation.
*
* Global variables:
*
*******************************************************************************/
cystatus `$INSTANCE_NAME`_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_I2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_SpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_UartCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_EzI2CCyBtldrCommRead(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_EzSpiCyBtldrCommRead(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            status = `$INSTANCE_NAME`_I2CCyBtldrCommRead(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            status = `$INSTANCE_NAME`_SpiCyBtldrCommRead(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            status = `$INSTANCE_NAME`_UartCyBtldrCommRead(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            status = `$INSTANCE_NAME`_EzI2CCyBtldrCommRead(pData, size, count, timeOut);

        #else
           status = `$INSTANCE_NAME`_EzSpiCyBtldrCommRead(pData, size, count, timeOut);

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_CyBtldrCommWrite
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
cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut)
{
    cystatus status;

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_I2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_SpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_UartCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            status = `$INSTANCE_NAME`_EzSpiCyBtldrCommWrite(pData, size, count, timeOut);
        }
        else
        {
            status = CYRET_INVALID_STATE; /* Unknown mode: return status */
        }
    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            status = `$INSTANCE_NAME`_I2CCyBtldrCommWrite(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            status = `$INSTANCE_NAME`_SpiCyBtldrCommWrite(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            status = `$INSTANCE_NAME`_UartCyBtldrCommWrite(pData, size, count, timeOut);

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            status = `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(pData, size, count, timeOut);

        #else
           status = `$INSTANCE_NAME`_EzSpiCyBtldrCommWrite(pData, size, count, timeOut);

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

    return(status);
}


#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */


/* [] END OF FILE */
