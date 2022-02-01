/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SPI.c
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

#include "`$INSTANCE_NAME`_SPI_UART_PVT.h"


/**********************************
*      System variables
**********************************/

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
    volatile uint8 * `$INSTANCE_NAME`_rxBuffer;
    volatile uint32  `$INSTANCE_NAME`_rxBufferHead;
    volatile uint32  `$INSTANCE_NAME`_rxBufferTail;
    volatile uint32  `$INSTANCE_NAME`_rxBufferOverflow;
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
    volatile uint8 * `$INSTANCE_NAME`_txBuffer;
    volatile uint32  `$INSTANCE_NAME`_txBufferHead;
    volatile uint32  `$INSTANCE_NAME`_txBufferTail;
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    volatile `$BitWidthReplacementStringRx` `$INSTANCE_NAME`_rxBufferInternal[`$INSTANCE_NAME`_RX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)
    volatile `$BitWidthReplacementStringTx` `$INSTANCE_NAME`_txBufferInternal[`$INSTANCE_NAME`_TX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER) */


/**********************************
*      Interrupt
**********************************/

CY_ISR_PROTO(`$INSTANCE_NAME`_SPI_WAKEUP_ISR);


/**********************************
*      Constant
**********************************/

const `$INSTANCE_NAME`_SPI_INIT_STRUCT `$INSTANCE_NAME`_configSpi =
{
    `$INSTANCE_NAME`_SPI_MODE,
    `$INSTANCE_NAME`_SPI_SUB_MODE,
    `$INSTANCE_NAME`_SPI_CLOCK_MODE,
    `$INSTANCE_NAME`_SPI_OVS_FACTOR,
    `$INSTANCE_NAME`_SPI_MEDIAN_FILTER_ENABLE,
    `$INSTANCE_NAME`_SPI_LATE_MISO_SAMPLE_ENABLE,
    `$INSTANCE_NAME`_SPI_WAKE_ENABLE,
    `$INSTANCE_NAME`_SPI_RX_DATA_BITS_NUM,
    `$INSTANCE_NAME`_SPI_TX_DATA_BITS_NUM,
    `$INSTANCE_NAME`_SPI_BITS_ORDER,
    `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATION,
    `$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE,
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
        (uint8 *) `$INSTANCE_NAME`_rxBufferInternal,
    #else
        NULL,
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER) */
    `$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE,
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)
        (uint8 *) `$INSTANCE_NAME`_txBufferInternal,
    #else
        NULL,
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER) */
    `$INSTANCE_NAME`_SPI_INTERRUPT_ENABLE,
    `$INSTANCE_NAME`_SPI_INTR_RX_MASK,
    `$INSTANCE_NAME`_SPI_RX_TRIGGER_LEVEL,
    `$INSTANCE_NAME`_SPI_INTR_TX_MASK,
    `$INSTANCE_NAME`_SPI_TX_TRIGGER_LEVEL
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiInit
********************************************************************************
*
* Summary:
*  Initializes SPIM registers with initial values provided from customizer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiInit(`$INSTANCE_NAME`_SPI_INIT_STRUCT *config)
{
    /* Configure SPI interface */
    `$INSTANCE_NAME`_CTRL_REG = `$INSTANCE_NAME`_GET_CTRL_OVS(config->oversample) |
                                `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(config->enableWake) |
                                `$INSTANCE_NAME`_CTRL_SPI;

    `$INSTANCE_NAME`_SPI_CTRL_REG = `$INSTANCE_NAME`_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                    `$INSTANCE_NAME`_GET_SPI_CTRL_SELECT_PRECEDE(config->submode)             |
                                    `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                    `$INSTANCE_NAME`_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                    `$INSTANCE_NAME`_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                    `$INSTANCE_NAME`_GET_SPI_CTRL_MASTER_MODE   (config->mode);

    /* Configure RX direction */
    `$INSTANCE_NAME`_RX_CTRL_REG = `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                   `$INSTANCE_NAME`_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                   `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                   `$INSTANCE_NAME`_SPI_RX_CTRL;

    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

    /* Configure TX direction */
    `$INSTANCE_NAME`_TX_CTRL_REG = `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                   `$INSTANCE_NAME`_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                   `$INSTANCE_NAME`_SPI_TX_CTRL;

    `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

    /* Configure interrupt source */
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_StartEx(&`$INSTANCE_NAME`_SPI_UART_ISR);

        if(0u == config->enableInterrupt)
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
        }
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

    /* Configure interrupt sources */
    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = (config->rxInterruptMask & `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR);
    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = (config->txInterruptMask & `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE);
    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_RX_MASK_REG     = (config->rxInterruptMask & ((uint32) ~`$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR));
    `$INSTANCE_NAME`_INTR_TX_MASK_REG     = (config->txInterruptMask & ((uint32) ~`$INSTANCE_NAME`_INTR_MASTER_SPI_DONE));


    /* Configure global veriables */
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_rxBufferHead     = 0u;
        `$INSTANCE_NAME`_rxBufferTail     = 0u;
        `$INSTANCE_NAME`_rxBufferOverflow = 0u;
        `$INSTANCE_NAME`_rxBuffer         = config->rxBuffer;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        `$INSTANCE_NAME`_txBufferHead = 0u;
        `$INSTANCE_NAME`_txBufferTail = 0u;
        `$INSTANCE_NAME`_txBuffer = config->txBuffer;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

    #if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
        /* Configure pins */
        `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_SPI, config->mode, config->mode); /* TBD nubmer of ss lines */

        /* Set internal configuration */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_SPI;
        `$INSTANCE_NAME`_scbCfg  = (void *) config;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetActiveSlaveSelect
********************************************************************************
*
* Summary:
*  Selects one of the four SPI slave select signals.
*  The component should be in one of the following states to change the active
*  slave select signal source correctly:
*   - the component is disabled
*   - the component has completed all transactions (TX FIFO is empty and the
*     SpiDone flag is set)
*  This function does not check that these conditions are met.
*  At initialization time the active slave select line is slave select 0.
*
* Parameters:
*  activeSS: The four lines available to utilize Slave Select function.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(uint32 activeSS)
{
    /* Clear bits of Slave Select */
    `$INSTANCE_NAME`_SPI_CTRL_REG &= ~`$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__MASK;

    `$INSTANCE_NAME`_SPI_CTRL_REG |= (activeSS << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiSaveConfig
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
void `$INSTANCE_NAME`_SpiSaveConfig(void)
{
    if( `$INSTANCE_NAME`_SPI_WAKEUP_ENABLE)
    {
        `$INSTANCE_NAME`_backup.enableState = 0u;   /* Keep SCB enabled */

        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_SPI_WAKEUP_ISR);
            `$INSTANCE_NAME`_SCB_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
        `$INSTANCE_NAME`_ENABLE_INTR_SPI_EC(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiRestoreConfig
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
void `$INSTANCE_NAME`_SpiRestoreConfig(void)
{
    if(`$INSTANCE_NAME`_SPI_WAKEUP_ENABLE)
    {
        #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
            `$INSTANCE_NAME`_SCB_IRQ_SetVector(&`$INSTANCE_NAME`_SPI_UART_ISR);
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
CY_ISR(`$INSTANCE_NAME`_SPI_WAKEUP_ISR)
{
    if(`$INSTANCE_NAME`_CHECK_INTR_SPI_EC_MASKED(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP))
    {
        `$INSTANCE_NAME`_DISABLE_INTR_SPI_EC(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
        `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP);
    }
    
    /* Wait for call `$INSTANCE_NAME`_SpiRestoreConfig to enable interrupt */
    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */
    
}


/* [] END OF FILE */
