/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZI2C.c
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

CY_ISR_PROTO(`$INSTANCE_NAME`_EZI2C_WAKEUP_ISR);


/**********************************
*      Constant
**********************************/

const `$INSTANCE_NAME`_EZI2C_INIT_STRUCT `$INSTANCE_NAME`_configEzI2C =
{
    `$INSTANCE_NAME`_EZI2C_OPERATION_MODE,
    `$INSTANCE_NAME`_EZI2C_MEDIAN_FILTER_ENABLE,
    `$INSTANCE_NAME`_EZI2C_WAIT_STATES_ENABLE,
    `$INSTANCE_NAME`_EZI2C_SLAVE_ADDRESS,
    `$INSTANCE_NAME`_EZI2C_SLAVE_ADDRESS_MASK,
    `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE,
    `$INSTANCE_NAME`_EZI2C_WAKE_ACTION,
    `$INSTANCE_NAME`_EZI2C_INTERRUPT_ENABLE,
    `$INSTANCE_NAME`_EZI2C_INTR_MASK,
    `$INSTANCE_NAME`_EZI2C_INTR_RX_MASK,
    `$INSTANCE_NAME`_EZI2C_INTR_TX_MASK,
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EZI2CInit
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
void `$INSTANCE_NAME`_EzI2CInit(`$INSTANCE_NAME`_EZI2C_INIT_STRUCT *config)
{
    /* Configure EZI2C interface */
    `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_GET_CTRL_EC_OP_MODE(config->operationMode) |
                                `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(config->operationMode  | 
                                                                     config->enableWake)    |
                                `$INSTANCE_NAME`_GET_CTRL_BLOCK(config->enableWaitStates)   |
                                `$INSTANCE_NAME`_CTRL_EZI2C;

    `$INSTANCE_NAME`_I2C_CTRL_REG = `$INSTANCE_NAME`_EZI2C_I2C_CTRL;

    /* Configure slave address */
    `$INSTANCE_NAME`_RX_MATCH_REG = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                    `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->slaveAddrMask);

    /* Configure RX direction */
    `$INSTANCE_NAME`_RX_CTRL_REG = `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                   `$INSTANCE_NAME`_EZ_RX_CTRL;

    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = 0u;

    /* Configure TX direction */
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
        `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = config->ezInterruptMask;
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
        `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_EZI2C, 0u, 0u);

        /* Set internal configuration */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_EZI2C;
        `$INSTANCE_NAME`_scbCfg  = (void *) config;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CSaveConfig
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
void `$INSTANCE_NAME`_EzI2CSaveConfig(void)
{
    if(`$INSTANCE_NAME`_EZI2C_WAKEUP_ENABLE)
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;

        /* Change interrupt vector for wakeup */
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_EZI2C_WAKEUP_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

        /* Enable NACK */
        if(`$INSTANCE_NAME`_EZI2C_WAKEUP_ADDR_NACK)
        {
            `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK;
        }
        
        `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
        `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);
        `$INSTANCE_NAME`_ENABLE_INTR_I2C_EC(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EzI2CRestoreConfig
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
void `$INSTANCE_NAME`_EzI2CRestoreConfig(void)
{
    if(`$INSTANCE_NAME`_EZI2C_WAKEUP_ENABLE)
    {
        if(!`$INSTANCE_NAME`_EZI2C_WAKEUP_ADDR_NACK)
        {
            while(0u == (`$INSTANCE_NAME`_GetSlaveInterruptSource() & `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH))
            {
                /* Work-around: wake need to be cleared after I2C_ADDR_MATCH */
            }
        }
        
        `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
        `$INSTANCE_NAME`_ClearSlaveInterruptSource(`$INSTANCE_NAME`_INTR_SLAVE_ALL);
        
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_EZ_MODE_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EZI2C_WAKEUP_ISR
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
CY_ISR(`$INSTANCE_NAME`_EZI2C_WAKEUP_ISR)
{
    if(`$INSTANCE_NAME`_CHECK_INTR_I2C_EC_MASKED(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
    {
        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
        
        if(`$INSTANCE_NAME`_EZI2C_WAKEUP_ADDR_NACK)
        {
            /* Work-around: wake need to be cleared before ReStart or Stop accordingly to BROS.
             * Clear the INTR_I2C_EC_WAKE_UP here as not other events.
             */
            
            `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
            `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK;
        }
    }

    /* Wait for call `$INSTANCE_NAME`_EzI2CRestoreConfig to enable interrupt */
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
}


/* [] END OF FILE */
