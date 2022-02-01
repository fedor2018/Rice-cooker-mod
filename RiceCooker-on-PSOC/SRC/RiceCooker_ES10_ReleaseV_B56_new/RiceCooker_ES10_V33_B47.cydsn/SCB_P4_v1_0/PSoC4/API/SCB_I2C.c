/*******************************************************************************
* File Name: `$INSTANCE_NAME`_I2C.c
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

#include "`$INSTANCE_NAME`_I2C_PVT.h"


/**********************************
*      Variables
**********************************/

volatile uint8 `$INSTANCE_NAME`_state;          /* Current state of I2C FSM         */
volatile uint8 `$INSTANCE_NAME`_wakeupSource;   /* Defines if I2C was wakeup source */


/**********************************
*      Constant
**********************************/

/* Constant configuration of I2C */
const `$INSTANCE_NAME`_I2C_INIT_STRUCT `$INSTANCE_NAME`_configI2C =
{
    `$INSTANCE_NAME`_I2C_MODE,
    `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW,
    `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH,
    `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE,
    `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS,
    `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK,
    `$INSTANCE_NAME`_I2C_ACCEPT_ADRESS,
    `$INSTANCE_NAME`_I2C_WAKE_ENABLE
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CInit
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
*******************************************************************************/
void `$INSTANCE_NAME`_I2CInit(`$INSTANCE_NAME`_I2C_INIT_STRUCT *config)
{
    /* Configure I2C interface */
    `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->acceptAddr) |
                                `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE (config->enableWake) |
                                `$INSTANCE_NAME`_CTRL_I2C;

    `$INSTANCE_NAME`_I2C_CTRL_REG = (`$INSTANCE_NAME`_GET_I2C_CTRL_HIGH_PHASE_OVS(config->oversampleHigh) |
                                     `$INSTANCE_NAME`_GET_I2C_CTRL_LOW_PHASE_OVS (config->oversampleLow)  |
                                     `$INSTANCE_NAME`_GET_I2C_CTRL_SLAVE_MODE    (config->mode)           |
                                     `$INSTANCE_NAME`_GET_I2C_CTRL_MASTER_MODE   (config->mode)           |
                                     `$INSTANCE_NAME`_I2C_CTRL);

    /* Set default address and mask */
    if(`$INSTANCE_NAME`_I2C_SLAVE)
    {
        `$INSTANCE_NAME`_RX_MATCH_REG = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(config->slaveAddr) |
                                        `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->slaveAddrMask);
    }

    /* Configure TX and RX direction */
    `$INSTANCE_NAME`_RX_CTRL_REG = `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(config->enableMedianFilter) |
                                   `$INSTANCE_NAME`_I2C_RX_CTRL;

    `$INSTANCE_NAME`_TX_CTRL_REG = `$INSTANCE_NAME`_I2C_TX_CTRL;

    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = 0u;
    `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = 0u;

    /* Configure interrupt sources */
    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_RX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_TX_MASK_REG     = `$INSTANCE_NAME`_NO_INTR_SOURCES;

    if(`$INSTANCE_NAME`_I2C_SLAVE)
    {
        `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK;
    }

    if(`$INSTANCE_NAME`_I2C_MASTER)
    {
        `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_I2C_INTR_MASTER_MASK;
    }

    /* Configure interrupt with I2C handler and enabled it */
    `$INSTANCE_NAME`_SCB_IRQ_StartEx(&`$INSTANCE_NAME`_I2C_ISR);

    /* Configure global veriables */
    `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

    #if(`$INSTANCE_NAME`_I2C_SLAVE_CONST)
        `$INSTANCE_NAME`_slStatus        = 0u;
        `$INSTANCE_NAME`_slRdBufIndex    = 0u;
        `$INSTANCE_NAME`_slWrBufIndex    = 0u;
        `$INSTANCE_NAME`_slOverFlowCount = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_SLAVE_CONST) */

    #if(`$INSTANCE_NAME`_I2C_MASTER_CONST)
        `$INSTANCE_NAME`_mstrStatus     = 0u;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
        `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    #endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */


    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        /* Configure pins */
        `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_I2C, 0u, 0u);

        /* Set internal configuration */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_I2C;
        `$INSTANCE_NAME`_scbCfg  = (void *) config;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CStop
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
*
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CStop(void)
{
    `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE; /* FSM State -> FSM_IDLE */
    `$INSTANCE_NAME`_SCB_IRQ_ClearPending();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CSaveConfig
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
*
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_I2C_WAKEUP_ISR);
void `$INSTANCE_NAME`_I2CSaveConfig(void)
{
    if(`$INSTANCE_NAME`_I2C_WAKEUP)
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;   /* Keep SCB enabled */

        /* Change interrupt handler to wakeup one */
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_I2C_WAKEUP_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CRestoreConfig
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
void `$INSTANCE_NAME`_I2CRestoreConfig(void)
{
    if(`$INSTANCE_NAME`_I2C_WAKEUP)
    {
        /* Change interrupt handler to common I2C */
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_I2C_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SPI_WAKEUP_ISR
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
CY_ISR(`$INSTANCE_NAME`_I2C_WAKEUP_ISR)
{
    if(`$INSTANCE_NAME`_CHECK_INTR_I2C_EC_MASKED(`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP))
    {
        /* Disable interrupt after wakeup. It will be cleared by I2C_ISR */
        `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(`$INSTANCE_NAME`_NO_INTR_SOURCES);
    }
    
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
}


/* [] END OF FILE */
