/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZSPI.c
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
*      Interrupt
**********************************/

CY_ISR_PROTO(`$INSTANCE_NAME`_EZSPI_WAKEUP_ISR);


/**********************************
*      Constant
**********************************/

const `$INSTANCE_NAME`_EZSPI_INIT_STRUCT `$INSTANCE_NAME`_configEzSpi =
{
    `$INSTANCE_NAME`_EZSPI_OPERATION_MODE,
    `$INSTANCE_NAME`_EZSPI_MEDIAN_FILTER_ENABLE,
    `$INSTANCE_NAME`_EZSPI_WAIT_STATES_ENABLE,
    `$INSTANCE_NAME`_EZSPI_WAKE_ENABLE,
    `$INSTANCE_NAME`_EZSPI_INTERRUPT_ENABLE,
    `$INSTANCE_NAME`_EZSPI_INTR_MASK,
    `$INSTANCE_NAME`_EZSPI_INTR_RX_MASK,
    `$INSTANCE_NAME`_EZSPI_INTR_TX_MASK,
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EZSPIInit
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
void `$INSTANCE_NAME`_EzSpiInit(`$INSTANCE_NAME`_EZSPI_INIT_STRUCT *config)
{
    /* Configure EZSPI interface */
    `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_GET_CTRL_EC_OP_MODE(config->operationMode) |
                                `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(config->operationMode  |
                                                                     config->enableWake)    |
                                `$INSTANCE_NAME`_GET_CTRL_BLOCK(config->enableWaitStates)   |
                                `$INSTANCE_NAME`_CTRL_EZSPI;

    `$INSTANCE_NAME`_SPI_CTRL_REG = `$INSTANCE_NAME`_EZSPI_SPI_CTRL;

    /* Configure RX direction */
    `$INSTANCE_NAME`_RX_CTRL_REG = `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                   `$INSTANCE_NAME`_EZ_RX_CTRL;

    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = 0u;

    /* Configure RX direction */
    `$INSTANCE_NAME`_TX_CTRL_REG = `$INSTANCE_NAME`_EZ_TX_CTRL;

    `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = 0u;

    /* Configure interrupt sources */
    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_RX_MASK_REG     = config->rxInterruptMask;
    `$INSTANCE_NAME`_INTR_TX_MASK_REG     = config->txInterruptMask;

    if(`$INSTANCE_NAME`_EZ_INTERNALLY_CLOCKED == config->operationMode)
    {
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = config->ezInterruptMask;
    }
    else
    {
        `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = config->ezInterruptMask;
    }

    /* Configure interrupt with I2C handler and enabled it */
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_StartEx(&`$INSTANCE_NAME`_EZ_MODE_ISR);

        if(0u == config->enableInterrupt)
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
        }
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        /* Configure pins */
        `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_EZSPI, 0u, 1u);

        /* Set internal configuration */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_EZSPI;
        `$INSTANCE_NAME`_scbCfg  = (void *) config;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiSaveConfig
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
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzSpiSaveConfig(void)
{

    if(`$INSTANCE_NAME`_EZSPI_WAKEUP_ENABLE)
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;   /* Keep SCB enabled */
    
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_EZ_MODE_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
        `$INSTANCE_NAME`_ENABLE_INTR_SPI_EC(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzSpiRestoreConfig
********************************************************************************
*
* Summary:
*  Initializes I2C registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_EzSpiRestoreConfig(void)
{
    /* TBD */
    if(`$INSTANCE_NAME`_EZSPI_WAKEUP_ENABLE)
    {
        `$INSTANCE_NAME`_CTRL_REG &= ~`$INSTANCE_NAME`_CTRL_EC_AM_MODE;

        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_EZ_MODE_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EZSPI_WAKEUP_ISR
********************************************************************************
*
* Summary:
*  Empty interrupt handler to trigger after wakeup.
*
* Parameters:
*  void
*
* Return:
*  void
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_EZSPI_WAKEUP_ISR)
{
    if(`$INSTANCE_NAME`_CHECK_INTR_SPI_EC_MASKED(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP))
    {
        `$INSTANCE_NAME`_DISABLE_INTR_SPI_EC(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }

    /* Wait for call `$INSTANCE_NAME`_EzSpiRestoreConfig to enable interrupt */
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
}


/* [] END OF FILE */
