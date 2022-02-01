/*******************************************************************************
* File Name: `$INSTANCE_NAME`_UART.c
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

#if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
    #include "`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)*/

#if(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
    #include "`$INSTANCE_NAME`_rx_wake.h"
#endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */


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

CY_ISR_PROTO(`$INSTANCE_NAME`_UART_WAKEUP_ISR);


/**********************************
*      Constants
**********************************/

const `$INSTANCE_NAME`_UART_INIT_STRUCT `$INSTANCE_NAME`_configUart =
{
    `$INSTANCE_NAME`_UART_SUB_MODE,
    `$INSTANCE_NAME`_UART_DIRECTION,
    `$INSTANCE_NAME`_UART_DATA_BITS_NUM,
    `$INSTANCE_NAME`_UART_PARITY_TYPE,
    `$INSTANCE_NAME`_UART_STOP_BITS_NUM,
    `$INSTANCE_NAME`_UART_OVS_FACTOR,
    `$INSTANCE_NAME`_UART_IRDA_LOW_POWER,
    `$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE,
    `$INSTANCE_NAME`_UART_RETRY_ON_NACK,
    `$INSTANCE_NAME`_UART_IRDA_POLARITY,
    `$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR,
    `$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR,
    `$INSTANCE_NAME`_UART_WAKE_ENABLE,
    `$INSTANCE_NAME`_UART_RX_BUFFER_SIZE,
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
        (uint8 *) `$INSTANCE_NAME`_rxBufferInternal,
    #else
        NULL,
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER) */
    `$INSTANCE_NAME`_UART_TX_BUFFER_SIZE,
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)
        (uint8 *) `$INSTANCE_NAME`_txBufferInternal,
    #else
        NULL,
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER) */
    `$INSTANCE_NAME`_UART_MP_MODE_ENABLE,
    `$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS,
    `$INSTANCE_NAME`_UART_MP_RX_ADDRESS,
    `$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK,
    `$INSTANCE_NAME`_UART_INTERRUPT_ENABLE,
    `$INSTANCE_NAME`_UART_INTR_RX_MASK,
    `$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL,
    `$INSTANCE_NAME`_UART_INTR_TX_MASK,
    `$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL
};


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartInit
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
void `$INSTANCE_NAME`_UartInit(`$INSTANCE_NAME`_UART_INIT_STRUCT *config)
{
    uint32 defReg;

    /* Configure UART interface */
    if(`$INSTANCE_NAME`_UART_MODE_IRDA == config->mode)
    {
        if(0u != config->enableIrdaLowPower)
        {
            defReg = `$INSTANCE_NAME`_GET_CTRL_OVS_IRDA_LP(config->oversample);
        }
        else
        {
            defReg = `$INSTANCE_NAME`_CTRL_OVS_IRDA_OVS;
        }
    }
    else
    {
        defReg  = `$INSTANCE_NAME`_GET_CTRL_OVS(config->oversample);
    }

    if(0u != (config->enableMultiproc))
    {
        defReg |= `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(config->multiprocAcceptAddr);
    }

    `$INSTANCE_NAME`_CTRL_REG       = `$INSTANCE_NAME`_CTRL_UART | defReg;
    `$INSTANCE_NAME`_UART_CTRL_REG  = `$INSTANCE_NAME`_GET_UART_CTRL_MODE(config->mode);


    /* Configure RX direction */
    if(0u != (`$INSTANCE_NAME`_UART_RX & config->direction))
    {
        /* Set `$INSTANCE_NAME`_UART_RX_CTRL_REG */
        defReg = `$INSTANCE_NAME`_GET_UART_RX_CTRL_MODE(config->stopBits);

        if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
        {
           defReg |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_PARITY(config->parity);
           defReg |= `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED;
        }

        defReg |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_POLARITY(config->enableInvertedRx);
        defReg |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_MP_MODE(config->enableMultiproc);

        defReg |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(config->dropOnParityErr);
        defReg |= `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(config->dropOnFrameErr);

        `$INSTANCE_NAME`_UART_RX_CTRL_REG = defReg;


        /* Set `$INSTANCE_NAME`_RX_CTRL_REG */
        defReg  = `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(config->dataBits);
        defReg |= `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter);
        defReg |= `$INSTANCE_NAME`_UART_RX_CTRL;

        `$INSTANCE_NAME`_RX_CTRL_REG = defReg;


        /* Set `$INSTANCE_NAME`_RX_FIFO_CTRL_REG */
        `$INSTANCE_NAME`_RX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);


        /* Set `$INSTANCE_NAME`_RX_MATCH_REG */
        if(0u != (config->enableMultiproc))
        {
            defReg  = `$INSTANCE_NAME`_GET_RX_MATCH_ADDR(config->multiprocAddr);
            defReg |= `$INSTANCE_NAME`_GET_RX_MATCH_MASK(config->multiprocAddrMask);

            `$INSTANCE_NAME`_RX_MATCH_REG = defReg;
        }
    }

    /* Configure TX direction */
    if(0u != (`$INSTANCE_NAME`_UART_TX & config->direction))
    {
        /* Set `$INSTANCE_NAME`_UART_TX_CTRL_REG */
        defReg  = `$INSTANCE_NAME`_GET_UART_TX_CTRL_MODE      (config->stopBits);
        defReg |= `$INSTANCE_NAME`_GET_UART_TX_CTRL_RETRY_NACK(config->enableRetryNack);

        if(`$INSTANCE_NAME`_UART_PARITY_NONE != config->parity)
        {
           defReg |= `$INSTANCE_NAME`_GET_UART_TX_CTRL_PARITY(config->parity);
           defReg |= `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED;
        }

        `$INSTANCE_NAME`_UART_TX_CTRL_REG = defReg;


        /* Set `$INSTANCE_NAME`_TX_CTRL_REG */
        defReg  = `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(config->dataBits);
        defReg |= `$INSTANCE_NAME`_UART_TX_CTRL;

        `$INSTANCE_NAME`_TX_CTRL_REG = defReg;


        /* Set `$INSTANCE_NAME`_TX_FIFO_CTRL_REG */
        `$INSTANCE_NAME`_TX_FIFO_CTRL_REG = `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);
    }

    #if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
        `$INSTANCE_NAME`_SCB_IRQ_StartEx(&`$INSTANCE_NAME`_SPI_UART_ISR);

        if(0u == config->enableInterrupt)
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable();
        }
    #endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

    /* Configure interrupt sources */
    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG  = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = `$INSTANCE_NAME`_NO_INTR_SOURCES;
    `$INSTANCE_NAME`_INTR_RX_MASK_REG     = config->rxInterruptMask;
    `$INSTANCE_NAME`_INTR_TX_MASK_REG     = config->txInterruptMask;

    /* Configure WAKE interrupt */
    #if(`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ)
        `$INSTANCE_NAME`_RX_WAKEUP_IRQ_StartEx(&`$INSTANCE_NAME`_UART_WAKEUP_ISR);
        `$INSTANCE_NAME`_RX_WAKEUP_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ) */

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
        `$INSTANCE_NAME`_SetPins(`$INSTANCE_NAME`_SCB_MODE_UART, config->mode, config->direction);

        /* Set internal configuration */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_UART;
        `$INSTANCE_NAME`_scbCfg  = (void *) config;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartPutString
********************************************************************************
*
* Summary:
*  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
*
* Parameters:
*  string: char pointer to character string of Data to Send.
*
* Return:
*  None.
*
* Global Variables:
*  `$INSTANCE_NAME`_initVar - checked to identify that the component has been
*     initialized.
*
*
* Theory:
*  This function will block if there is not enough memory to place the whole
*  string, it will block until the entire string has been written to the
*  transmit buffer.
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartPutString(const char8 string[])
{
    uint16 bufIndex;

    bufIndex = 0u;

    /* Blocks the control flow until all data will be sent */
    while(string[bufIndex] != ((char8) 0))
    {
        `$INSTANCE_NAME`_UartPutChar((uint32) string[bufIndex]);
        bufIndex++;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartPutCRLF
********************************************************************************
*
* Summary:
*  Write a character and then carriage return and line feed
*
* Parameters:
*  txDataByte: uint8 Character to send
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartPutCRLF(uint32 txDataByte)
{
    `$INSTANCE_NAME`_UartPutChar(txDataByte);  /* Blocks the control flow until all data will be sent */
    `$INSTANCE_NAME`_UartPutChar(0x0Du);       /* Blocks the control flow until all data will be sent */
    `$INSTANCE_NAME`_UartPutChar(0x0Au);       /* Blocks the control flow until all data will be sent */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartGetChar
********************************************************************************
*
* Summary:
*  Reads UART RX buffer immediately, if data is not available or an error
*  condition exists, zero is returned; otherwise, character is read and
*  returned.
*
* Parameters:
*  None.
*
* Return:
*  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
*  A returned zero signifies an error condition or no data available.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_UartGetChar(void)
{
    uint32 rxData;

    `$Cond`if(`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        /* RX software buffer enabled */
        rxData = `$INSTANCE_NAME`_SpiUartReadRxData();

        if(0u != `$INSTANCE_NAME`_rxBufferOverflow)
        {
            rxData = 0u; /* RX software buffer overflow */
        }
    }
    `$Cond`else
    {
        if(0u != `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES)
        {
            rxData = `$INSTANCE_NAME`_RX_FIFO_RD_REG; /* Read data from RX FIFO */
        }
        else
        {
            rxData = 0u; /* Nothing in RX FIFO */
        }
    }
    `$EndCond`

    if(`$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_ERR))
    {
        rxData = 0u; /* Error occured */
    }

    return(rxData);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartGetByte
********************************************************************************
*
* Summary:
*  Wiats for byte in UART RX buffer and read it. The bits 15-7 contians error
*  condtions if these bits are 0. The read byte is valid.
*
* Parameters:
*  None.
*
* Return:
*  Bits 15-8 contains status and bits 7-0 contains the next data element from
*  receive buffer. If the bits 15-8 are nonzero, an error has occurred.
*
* Side Effects:
*  In case of software buffer the error condition is applied to last recieved
*  byte. It may not match with currently reading byte.
*  The `$INSTANCE_NAME`_INTR_RX_OVERFLOW is not possible when RX software buffer
*  is used. The `$INSTANCE_NAME`_rxBufferOverflow variable is used instead.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_UartGetByte(void)
{
    uint32 rxData;
    uint32 tmpStatus;

    while(0u == `$INSTANCE_NAME`_SpiUartGetRxBufferSize())
    {
        /* Wait for byte in the RX buffer */
    }

    /* Get received data */
    rxData = `$INSTANCE_NAME`_SpiUartReadRxData();

    /* Get status and mask required bits */
    tmpStatus = (`$INSTANCE_NAME`_GetRxInterruptSource() & `$INSTANCE_NAME`_INTR_RX_ERR);
    
    `$Cond`if(`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        /* Get overflow status */
        tmpStatus |= `$INSTANCE_NAME`_rxBufferOverflow;
    }
    `$EndCond`

    /* Put together data and error status */
    rxData |= ((uint32) (tmpStatus << 8u));
    
    return(rxData);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddress
********************************************************************************
*
* Summary:
*  Sets the I2C slave address.
*
* Parameters:
*  address: I2C slave address for the primary device. This value may be any
*  address between 0 and 127.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_UartSetRxAddress(uint32 address)
{
    /* Clear address mask bits */
    `$INSTANCE_NAME`_RX_MATCH_REG &= ~`$INSTANCE_NAME`_RX_MATCH_ADDR__MASK;

    /* Set address */
    `$INSTANCE_NAME`_RX_MATCH_REG |= (address & `$INSTANCE_NAME`_RX_MATCH_ADDR__MASK);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSetRxAddressMask
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
void `$INSTANCE_NAME`_UartSetRxAddressMask(uint32 addressMask)
{
    /* Clear address mask bits */
    `$INSTANCE_NAME`_RX_MATCH_REG &= ~`$INSTANCE_NAME`_RX_MATCH_MASK__MASK;

    /* Set address mask */
    `$INSTANCE_NAME`_RX_MATCH_REG |= (addressMask << `$INSTANCE_NAME`_RX_MATCH_MASK__POS);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartSaveConfig
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
void `$INSTANCE_NAME`_UartSaveConfig(void)
{
    if(`$INSTANCE_NAME`_UART_WAKEUP_ENABLE)
    {
        /* Clear any pending interrupts */

        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)*/

        #if(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
            (void) `$INSTANCE_NAME`_rx_wake_ClearInterrupt();
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */

        /* Enable to skip start */
        `$INSTANCE_NAME`_UART_RX_CTRL_REG |= `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;

        #if(`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ)
            `$INSTANCE_NAME`_RX_WAKEUP_IRQ_ClearPending();
            `$INSTANCE_NAME`_RX_WAKEUP_IRQ_Enable();
        #endif /* (`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ) */

        `$INSTANCE_NAME`_backup.enableState = 0u;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UartRestoreConfig
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
void `$INSTANCE_NAME`_UartRestoreConfig(void)
{
    if(`$INSTANCE_NAME`_UART_WAKEUP_ENABLE)
    {
        /* Disable to skip start */
        `$INSTANCE_NAME`_UART_RX_CTRL_REG &= ~`$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START;
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_UART_WAKEUP_ISR
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
CY_ISR(`$INSTANCE_NAME`_UART_WAKEUP_ISR)
{
    #if(`$INSTANCE_NAME`_UART_RX_WAKE_PIN)
        (void) `$INSTANCE_NAME`_rx_wake_ClearInterrupt();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKE_PIN) */

    #if(`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ)
        `$INSTANCE_NAME`_RX_WAKEUP_IRQ_Disable();
    #endif /* (`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ) */
}


/* [] END OF FILE */
