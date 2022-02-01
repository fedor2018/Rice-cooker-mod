/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PM.c
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

`$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup =
{
    0u, /* enableState */
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Sleep
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
void `$INSTANCE_NAME`_Sleep(void)
{
    `$INSTANCE_NAME`_backup.enableState = (uint8) `$INSTANCE_NAME`_GET_CTRL_ENABLED;

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)

        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CSaveConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzSpiSaveConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            `$INSTANCE_NAME`_I2CSaveConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            `$INSTANCE_NAME`_SpiSaveConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            `$INSTANCE_NAME`_UartSaveConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            `$INSTANCE_NAME`_EzI2CSaveConfig();

        #else
            `$INSTANCE_NAME`_EzSpiSaveConfig();

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */


    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Stop();
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Wakeup
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
void `$INSTANCE_NAME`_Wakeup(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)

        if(`$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_I2CRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_SpiRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_UartRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzI2CRestoreConfig();
        }
        else if(`$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG)
        {
            `$INSTANCE_NAME`_EzSpiRestoreConfig();
        }
        else
        {
            /* Unknown mode: do nothing */
        }

    #else

        #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
            `$INSTANCE_NAME`_I2CRestoreConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
            `$INSTANCE_NAME`_SpiRestoreConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
            `$INSTANCE_NAME`_UartRestoreConfig();

        #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
            `$INSTANCE_NAME`_EzI2CRestoreConfig();

        #else
            `$INSTANCE_NAME`_EzSpiRestoreConfig();

        #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

    if(0u != `$INSTANCE_NAME`_backup.enableState)
    {
        `$INSTANCE_NAME`_Enable();
    }
}


/* [] END OF FILE */
