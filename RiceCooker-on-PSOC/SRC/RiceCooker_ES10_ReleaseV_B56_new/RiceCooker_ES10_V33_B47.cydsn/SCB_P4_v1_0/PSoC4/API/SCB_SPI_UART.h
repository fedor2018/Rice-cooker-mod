/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SPI_UART.h
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

#if !defined(CY_SCB_SPI_UART_`$INSTANCE_NAME`_H)
#define CY_SCB_SPI_UART_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*       Type defines
***************************************/

typedef struct
{
    uint32 mode;
    uint32 submode;
    uint32 sclkMode;
    uint32 oversample;
    uint32 enableMedianFilter;
    uint32 enableLateSampling;
    uint32 enableWake;
    uint32 rxDataBits;
    uint32 txDataBits;
    uint32 bitOrder;
    uint32 transferSeperation;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} `$INSTANCE_NAME`_SPI_INIT_STRUCT;


typedef struct
{
    uint32 mode;
    uint32 direction;
    uint32 dataBits;
    uint32 parity;
    uint32 stopBits;
    uint32 oversample;
    uint32 enableIrdaLowPower;
    uint32 enableMedianFilter;
    uint32 enableRetryNack;
    uint32 enableInvertedRx;
    uint32 dropOnParityErr;
    uint32 dropOnFrameErr;
    uint32 enableWake;
    uint32 rxBufferSize;
    uint8* rxBuffer;
    uint32 txBufferSize;
    uint8* txBuffer;
    uint32 enableMultiproc;
    uint32 multiprocAcceptAddr;
    uint32 multiprocAddr;
    uint32 multiprocAddrMask;
    uint32 enableInterrupt;
    uint32 rxInterruptMask;
    uint32 rxTriggerLevel;
    uint32 txInterruptMask;
    uint32 txTriggerLevel;
} `$INSTANCE_NAME`_UART_INIT_STRUCT;


/***************************************
*       Global components vars
***************************************/

extern const `$INSTANCE_NAME`_SPI_INIT_STRUCT  `$INSTANCE_NAME`_configSpi;
extern const `$INSTANCE_NAME`_UART_INIT_STRUCT `$INSTANCE_NAME`_configUart;


/***************************************
*   Parameters from customizer
****************************************/

#define `$INSTANCE_NAME`_SPI_MODE                   (`$SpiMode`u)
#define `$INSTANCE_NAME`_SPI_SUB_MODE               (`$SpiSubMode`u)
#define `$INSTANCE_NAME`_SPI_CLOCK_MODE             (`$SpiSclkMode`u)
#define `$INSTANCE_NAME`_SPI_OVS_FACTOR             (`$SpiOvsFactor`u)
#define `$INSTANCE_NAME`_SPI_MEDIAN_FILTER_ENABLE   (`$SpiMedianFilterEnable`u)
#define `$INSTANCE_NAME`_SPI_LATE_MISO_SAMPLE_ENABLE (`$SpiLateMisoSampleEnable`u)
#define `$INSTANCE_NAME`_SPI_RX_DATA_BITS_NUM       (`$SpiNumberOfRxDataBits`u)
#define `$INSTANCE_NAME`_SPI_TX_DATA_BITS_NUM       (`$SpiNumberOfTxDataBits`u)
#define `$INSTANCE_NAME`_SPI_WAKE_ENABLE            (`$SpiWakeEnable`u)
#define `$INSTANCE_NAME`_SPI_BITS_ORDER             (`$SpiBitsOrder`u)
#define `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATION    (`$SpiTransferSeparation`u)
#define `$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE         (`$SpiRxBufferSize`u)
#define `$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE         (`$SpiTxBufferSize`u)

#define `$INSTANCE_NAME`_SPI_RX_TRIGGER_LEVEL       (`$SpiRxTriggerLevel`u)

#define `$INSTANCE_NAME`_SPI_INTR_RX_TRIGGER        ((0u != `$SpiIntrRxTrigger`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_TRIGGER) : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_RX_NOT_EMPTY      ((0u != `$SpiIntrRxNotEmpty`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY) : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_RX_FULL           ((0u != `$SpiIntrRxFull`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_FULL) : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_RX_OVERFLOW       ((0u != `$SpiIntrRxOverflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_OVERFLOW) : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_RX_UNDERFLOW      ((0u != `$SpiIntrRxUnderflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_UNDERFLOW) : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_SLAVE_BUS_ERR     ((0u != `$SpiIntrSlaveBusError`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR) : (0u))

#define `$INSTANCE_NAME`_SPI_TX_TRIGGER_LEVEL       (`$SpiTxTriggerLevel`u)

#define `$INSTANCE_NAME`_SPI_INTR_TX_TRIGGER        ((0u != `$SpiIntrTxTrigger`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_TRIGGER)      : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_TX_NOT_FULL       ((0u != `$SpiIntrTxNotFull`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_NOT_FULL)     : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_TX_EMPTY          ((0u != `$SpiIntrTxEmpty`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_EMPTY)        : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_TX_OVERFLOW       ((0u != `$SpiIntrTxOverflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_OVERFLOW)     : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_TX_UNDERFLOW      ((0u != `$SpiIntrTxUnderflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_UNDERFLOW)    : (0u))

#define `$INSTANCE_NAME`_SPI_INTR_MASTER_SPI_DONE   ((0u != `$SpiIntrMasterSpiDone`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_MASTER_SPI_DONE) : (0u))

/* `$INSTANCE_NAME`_INTR_RX_MASK */
#define `$INSTANCE_NAME`_SPI_INTR_RX_MASK   (`$INSTANCE_NAME`_SPI_INTR_RX_TRIGGER   | \
                                             `$INSTANCE_NAME`_SPI_INTR_RX_NOT_EMPTY | \
                                             `$INSTANCE_NAME`_SPI_INTR_RX_FULL      | \
                                             `$INSTANCE_NAME`_SPI_INTR_RX_OVERFLOW  | \
                                             `$INSTANCE_NAME`_SPI_INTR_RX_UNDERFLOW | \
                                             `$INSTANCE_NAME`_SPI_INTR_SLAVE_BUS_ERR)

/* `$INSTANCE_NAME`_INTR_TX_MASK */
#define `$INSTANCE_NAME`_SPI_INTR_TX_MASK   (`$INSTANCE_NAME`_SPI_INTR_TX_TRIGGER   | \
                                             `$INSTANCE_NAME`_SPI_INTR_TX_NOT_FULL  | \
                                             `$INSTANCE_NAME`_SPI_INTR_TX_EMPTY     | \
                                             `$INSTANCE_NAME`_SPI_INTR_TX_OVERFLOW  | \
                                             `$INSTANCE_NAME`_SPI_INTR_TX_UNDERFLOW | \
                                             `$INSTANCE_NAME`_SPI_INTR_MASTER_SPI_DONE)


/***************************************
*   Parameters from customizer
****************************************/

#define `$INSTANCE_NAME`_UART_SUB_MODE              (`$UartSubMode`u)
#define `$INSTANCE_NAME`_UART_DIRECTION             (`$UartDirection`u)
#define `$INSTANCE_NAME`_UART_DATA_BITS_NUM         (`$UartNumberOfDataBits`u)
#define `$INSTANCE_NAME`_UART_PARITY_TYPE           (`$UartParityType`u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_NUM         (`$UartNumberOfStopBits`u)
#define `$INSTANCE_NAME`_UART_OVS_FACTOR            (`$UartOvsFactor`u)
#define `$INSTANCE_NAME`_UART_IRDA_LOW_POWER        (`$UartIrdaLowPower`u)
#define `$INSTANCE_NAME`_UART_MEDIAN_FILTER_ENABLE  (`$UartMedianFilterEnable`u)
#define `$INSTANCE_NAME`_UART_RETRY_ON_NACK         (`$UartSmCardRetryOnNack`u)
#define `$INSTANCE_NAME`_UART_IRDA_POLARITY         (`$UartIrdaPolarity`u)
#define `$INSTANCE_NAME`_UART_DROP_ON_FRAME_ERR     (`$UartDropOnFrameErr`u)
#define `$INSTANCE_NAME`_UART_DROP_ON_PARITY_ERR    (`$UartDropOnParityErr`u)
#define `$INSTANCE_NAME`_UART_WAKE_ENABLE           (`$UartWakeEnable`u)
#define `$INSTANCE_NAME`_UART_RX_BUFFER_SIZE        (`$UartRxBufferSize`u)
#define `$INSTANCE_NAME`_UART_TX_BUFFER_SIZE        (`$UartTxBufferSize`u)
#define `$INSTANCE_NAME`_UART_MP_MODE_ENABLE        (`$UartMpEnable`u)
#define `$INSTANCE_NAME`_UART_MP_ACCEPT_ADDRESS     (`$UartMpRxAcceptAddress`u)
#define `$INSTANCE_NAME`_UART_MP_RX_ADDRESS         (`$UartMpRxAddress`u)
#define `$INSTANCE_NAME`_UART_MP_RX_ADDRESS_MASK    (`$UartMpRxAddressMask`u)

#define `$INSTANCE_NAME`_UART_RX_TRIGGER_LEVEL      (`$UartRxTriggerLevel`u)

#define `$INSTANCE_NAME`_UART_INTR_RX_TRIGGER       ((0u != `$UartIntrRxTrigger`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_TRIGGER) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY     ((0u != `$UartIntrRxNotEmpty`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_FULL          ((0u != `$UartIntrRxFull`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_FULL) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_OVERFLOW      ((0u != `$UartIntrRxOverflow`u)  ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_OVERFLOW) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_UNDERFLOW     ((0u != `$UartIntrRxUnderflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_UNDERFLOW) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_FRAME_ERR     ((0u != `$UartIntrRxFrameErr`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_FRAME_ERROR) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_RX_PARITY_ERR    ((0u != `$UartIntrRxParityErr`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_RX_PARITY_ERROR) : (0u))

#define `$INSTANCE_NAME`_UART_TX_TRIGGER_LEVEL      (`$UartTxTriggerLevel`u)

#define `$INSTANCE_NAME`_UART_INTR_TX_TRIGGER       ((0u != `$UartIntrTxTrigger`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_TRIGGER) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL      ((0u != `$UartIntrTxNotFull`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_NOT_FULL) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_EMPTY         ((0u != `$UartIntrTxEmpty`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_EMPTY) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_OVERFLOW      ((0u != `$UartIntrTxOverflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_OVERFLOW) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_UNDERFLOW     ((0u != `$UartIntrTxUnderflow`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_UNDERFLOW) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_UART_NACK     ((0u != `$UartIntrTxUartNack`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_UART_NACK) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_UART_DONE     ((0u != `$UartIntrTxUartDone`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_UART_DONE) : (0u))

#define `$INSTANCE_NAME`_UART_INTR_TX_UART_ARB_LOST ((0u != `$UartIntrTxUartLostArb`u) ? \
                                                        (`$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST) : (0u))

/* `$INSTANCE_NAME`_INTR_RX_MASK */
#define `$INSTANCE_NAME`_UART_INTR_RX_MASK  (`$INSTANCE_NAME`_UART_INTR_RX_TRIGGER   | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_NOT_EMPTY | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_FULL      | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_OVERFLOW  | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_UNDERFLOW | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_FRAME_ERR | \
                                             `$INSTANCE_NAME`_UART_INTR_RX_PARITY_ERR)

/* `$INSTANCE_NAME`_INTR_TX_MASK */
#define `$INSTANCE_NAME`_UART_INTR_TX_MASK  (`$INSTANCE_NAME`_UART_INTR_TX_TRIGGER   | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_NOT_FULL  | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_EMPTY     | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_OVERFLOW  | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_UNDERFLOW | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_UART_NACK | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_UART_DONE | \
                                             `$INSTANCE_NAME`_UART_INTR_TX_UART_ARB_LOST)

/* All source of RX errors */
#define `$INSTANCE_NAME`_INTR_RX_ERR        (`$INSTANCE_NAME`_INTR_RX_OVERFLOW    | \
                                             `$INSTANCE_NAME`_INTR_RX_UNDERFLOW   | \
                                             `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR | \
                                             `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR)


/***************************************
*   Access to SPI and UART struct
****************************************/

#define `$INSTANCE_NAME`_SPI_INIT_ACCESS(ptr, field)    (((`$INSTANCE_NAME`_SPI_INIT_STRUCT  *) (ptr))->field)
#define `$INSTANCE_NAME`_UART_INIT_ACCESS(ptr, field)   (((`$INSTANCE_NAME`_UART_INIT_STRUCT *) (ptr))->field)

#define `$INSTANCE_NAME`_SPI_UART_INIT_ACCESS(ptr, field)((`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG) ?          \
                                                                `$INSTANCE_NAME`_SPI_INIT_ACCESS(ptr, field) : \
                                                                `$INSTANCE_NAME`_UART_INIT_ACCESS(ptr, field))


/***************************************
* Conditional compilation parameters
****************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)

    /* Interrupt is disabled for uncofigured mode */
    #define `$INSTANCE_NAME`_SPI_INTERRUPT_ENABLE   (0u)
    #define `$INSTANCE_NAME`_UART_INTERRUPT_ENABLE  (0u)

    /* Only external RX and TX buffer for uncofigured mode */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER   (0u)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER   (0u)

    /* Get RX and TX buffer size */
    #define `$INSTANCE_NAME`_RX_BUFFER_SIZE (`$INSTANCE_NAME`_SPI_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, rxBufferSize))
    #define `$INSTANCE_NAME`_TX_BUFFER_SIZE (`$INSTANCE_NAME`_SPI_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, rxBufferSize))

    /* Return true if buffer is provided */
    #define `$INSTANCE_NAME`_CHECK_RX_SW_BUFFER (NULL != `$INSTANCE_NAME`_rxBuffer)
    #define `$INSTANCE_NAME`_CHECK_TX_SW_BUFFER (NULL != `$INSTANCE_NAME`_txBuffer)

    /* Alwasy provde global variables to support RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST    (1u)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST    (1u)

    /* Get wakeup enable option */
    #define `$INSTANCE_NAME`_SPI_WAKEUP_ENABLE  \
                                    (0u != `$INSTANCE_NAME`_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWake))
    #define `$INSTANCE_NAME`_UART_WAKEUP_ENABLE \
                                    (0u != `$INSTANCE_NAME`_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWake))

#else

    /* Enable SPI mode interrupt */
    #define `$INSTANCE_NAME`_SPI_INTERRUPT_ENABLE   ((`$SpiInterruptMode`u == \
                                                        `$INSTANCE_NAME`_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))

    /* Enable UART mode interrupt */
    #define `$INSTANCE_NAME`_UART_INTERRUPT_ENABLE  ((`$UartInterruptMode`u == \
                                                        `$INSTANCE_NAME`_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))

    /* SPI internal RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_SPI_RX_SW_BUFFER  (`$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE > \
                                                                                            `$INSTANCE_NAME`_FIFO_SIZE)
    #define `$INSTANCE_NAME`_INTERNAL_SPI_TX_SW_BUFFER  (`$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE > \
                                                                                            `$INSTANCE_NAME`_FIFO_SIZE)

    /* UART internal RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_UART_RX_SW_BUFFER  (`$INSTANCE_NAME`_UART_RX_BUFFER_SIZE > \
                                                                                            `$INSTANCE_NAME`_FIFO_SIZE)
    #define `$INSTANCE_NAME`_INTERNAL_UART_TX_SW_BUFFER  (`$INSTANCE_NAME`_UART_TX_BUFFER_SIZE > \
                                                                                            `$INSTANCE_NAME`_FIFO_SIZE)

    /* Internal RX and TX buffer: for SPI or UART */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER  ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ?      \
                                                        (`$INSTANCE_NAME`_INTERNAL_SPI_RX_SW_BUFFER) : \
                                                        (`$INSTANCE_NAME`_INTERNAL_UART_RX_SW_BUFFER))

    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER  ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ?       \
                                                        (`$INSTANCE_NAME`_INTERNAL_SPI_TX_SW_BUFFER) : \
                                                        (`$INSTANCE_NAME`_INTERNAL_UART_TX_SW_BUFFER))

    /* Internal RX and TX buffer size: for SPI or UART */
    #define `$INSTANCE_NAME`_RX_BUFFER_SIZE         ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ? \
                                                       (`$INSTANCE_NAME`_SPI_RX_BUFFER_SIZE) :   \
                                                       (`$INSTANCE_NAME`_UART_RX_BUFFER_SIZE))

    #define `$INSTANCE_NAME`_TX_BUFFER_SIZE         ((`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG) ? \
                                                       (`$INSTANCE_NAME`_SPI_TX_BUFFER_SIZE) :   \
                                                       (`$INSTANCE_NAME`_UART_TX_BUFFER_SIZE))

    /* Internal RX and TX buffer: for SPI or UART. Used in conditional compilation check */
    #define `$INSTANCE_NAME`_CHECK_RX_SW_BUFFER (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    #define `$INSTANCE_NAME`_CHECK_TX_SW_BUFFER (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)

    /* Provde global variables to support RX and TX buffers */
    #define `$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST    (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    #define `$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST    (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)

    /* Get wakeup enable option */
    #define `$INSTANCE_NAME`_SPI_WAKEUP_ENABLE  (0u != `$INSTANCE_NAME`_SPI_WAKE_ENABLE)
    #define `$INSTANCE_NAME`_UART_WAKEUP_ENABLE (0u != `$INSTANCE_NAME`_UART_WAKE_ENABLE)

#endif /* End (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define `$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
                                                     
#define `$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                    (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*        Function Prototypes
***************************************/

/* SPI common APIs */
void `$INSTANCE_NAME`_SpiInit(`$INSTANCE_NAME`_SPI_INIT_STRUCT *config);
void `$INSTANCE_NAME`_SpiSetActiveSlaveSelect(uint32 activeSS);
void `$INSTANCE_NAME`_SpiSaveConfig(void);
void `$INSTANCE_NAME`_SpiRestoreConfig(void);

/* UART common APIs */
void `$INSTANCE_NAME`_UartInit(`$INSTANCE_NAME`_UART_INIT_STRUCT *config);
void `$INSTANCE_NAME`_UartSaveConfig(void);
void `$INSTANCE_NAME`_UartRestoreConfig(void);

/* UART only TX and RX direction APIs */
#define `$INSTANCE_NAME`_UartPutChar(ch)    `$INSTANCE_NAME`_SpiUartWriteTxData((uint32)(ch))
void `$INSTANCE_NAME`_UartPutString(const char8 string[]);
void `$INSTANCE_NAME`_UartPutCRLF(uint32 txDataByte);

uint32 `$INSTANCE_NAME`_UartGetChar(void);
uint32 `$INSTANCE_NAME`_UartGetByte(void);

void `$INSTANCE_NAME`_UartSetRxAddress(uint32 address);
void `$INSTANCE_NAME`_UartSetRxAddressMask(uint32 addressMask);

/* Common APIs Tx direction */
void   `$INSTANCE_NAME`_SpiUartWriteTxData(uint32 txDataByte);
void   `$INSTANCE_NAME`_SpiUartPutArray(const `$BitWidthReplacementStringTx` wrBuf[], uint32 count);
void   `$INSTANCE_NAME`_SpiUartClearTxBuffer(void);
uint32 `$INSTANCE_NAME`_SpiUartGetTxBufferSize(void);

/* Common APIs Rx direction */
uint32 `$INSTANCE_NAME`_SpiUartReadRxData(void);
uint32 `$INSTANCE_NAME`_SpiUartGetRxBufferSize(void);
void   `$INSTANCE_NAME`_SpiUartClearRxBuffer(void);

CY_ISR_PROTO(`$INSTANCE_NAME`_SPI_UART_ISR);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED)
    /* SPI Bootloader physical layer functions */
    void `$INSTANCE_NAME`_SpiCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_SpiCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_SpiCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_SpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_SpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_SPI_BTLDR_COMM_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED)
    /* UART Bootloader physical layer functions */
    void `$INSTANCE_NAME`_UartCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_UartCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_UartCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_UartCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_UartCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_UART_BTLDR_COMM_ENABLED) */


#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    /* RX direction */
    void `$INSTANCE_NAME`_PutWordInRxBuffer    (uint32 index, uint32 rxDataByte);
    uint32 `$INSTANCE_NAME`_GetWordFromRxBuffer(uint32 index);

    /* TX direction */
    void `$INSTANCE_NAME`_PutWordInTxBuffer    (uint32 index, uint32 txDataByte);
    uint32 `$INSTANCE_NAME`_GetWordFromTxBuffer(uint32 index);

#else

    /* RX direction */
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        #define `$INSTANCE_NAME`_PutWordInRxBuffer(index, rxDataByte) \
                do{                                               \
                    `$INSTANCE_NAME`_rxBufferInternal[(index)] = ((`$BitWidthReplacementStringRx`) (rxDataByte)); \
                }while(0u)

        #define `$INSTANCE_NAME`_GetWordFromRxBuffer(index) `$INSTANCE_NAME`_rxBufferInternal[(index)]

    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    /* TX direction */
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        #define `$INSTANCE_NAME`_PutWordInTxBuffer(index, txDataByte) \
                    do{                                               \
                        `$INSTANCE_NAME`_txBufferInternal[(index)] = ((`$BitWidthReplacementStringRx`) (txDataByte)); \
                    }while(0u)

        #define `$INSTANCE_NAME`_GetWordFromTxBuffer(index) `$INSTANCE_NAME`_txBufferInternal[(index)]

    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#endif /* (`$INSTANCE_NAME`_TX_SW_BUFFER_ENABLE) */


/***************************************
*            API Constants SPI
***************************************/

/* SPI mode enum */
#define `$INSTANCE_NAME`_SPI_SLAVE  (0u)
#define `$INSTANCE_NAME`_SPI_MASTER (1u)

/* SPI sub mode enum */
#define `$INSTANCE_NAME`_SPI_MODE_MOTOROLA      (0x00u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_COINCIDES  (0x01u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES   (0x11u)
#define `$INSTANCE_NAME`_SPI_MODE_NATIONAL      (0x02u)
#define `$INSTANCE_NAME`_SPI_MODE_MASK          (0x03u)
#define `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES_MASK  (0x10u)

/* SPI phase and polarity mode enum */
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL0   (0x00u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA0_CPOL1   (0x02u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL0   (0x01u)
#define `$INSTANCE_NAME`_SPI_SCLK_CPHA1_CPOL1   (0x03u)

/* SPI bits order enum */
#define `$INSTANCE_NAME`_BITS_ORDER_LSB_FIRST   (0u)
#define `$INSTANCE_NAME`_BITS_ORDER_MSB_FIRST   (1u)

/* SPI transfer separation enum */
#define `$INSTANCE_NAME`_SPI_TRANSFER_SEPARATED     (0u)
#define `$INSTANCE_NAME`_SPI_TRANSFER_CONTINUOUS    (1u)

/* "activeSS" constants for SpiSetActiveSlaveSelect() function */
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS0    (0x00u)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS1    (0x01u)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS2    (0x02u)
#define `$INSTANCE_NAME`_SPIM_ACTIVE_SS3    (0x03u)


/***************************************
*            API Constants UART
***************************************/

/* UART sub-modes enum */
#define `$INSTANCE_NAME`_UART_MODE_STD          (0u)
#define `$INSTANCE_NAME`_UART_MODE_SMARTCARD    (1u)
#define `$INSTANCE_NAME`_UART_MODE_IRDA         (2u)

/* UART direction enum */
#define `$INSTANCE_NAME`_UART_TX_RX (3u)
#define `$INSTANCE_NAME`_UART_RX    (1u)
#define `$INSTANCE_NAME`_UART_TX    (2u)

/* UART parity enum */
#define `$INSTANCE_NAME`_UART_PARITY_EVEN   (0u)
#define `$INSTANCE_NAME`_UART_PARITY_ODD    (1u)
#define `$INSTANCE_NAME`_UART_PARITY_NONE   (2u)

/* UART stop bits enum */
#define `$INSTANCE_NAME`_UART_STOP_BITS_1   (1u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_1_5 (2u)
#define `$INSTANCE_NAME`_UART_STOP_BITS_2   (3u)

/* UART IrDA low power OVS enum */
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS16     (16u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS32     (32u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS48     (48u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS96     (96u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS192    (192u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS768    (768u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS1536   (1536u)


/***************************************
*      Default register settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_SPI      (`$INSTANCE_NAME`_CTRL_MODE_SPI)

#define `$INSTANCE_NAME`_SPI_RX_CTRL   (`$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_SPI_TX_CTRL   (`$INSTANCE_NAME`_TX_CTRL_ENABLED)


/***************************************
*      Default register settings UART
***************************************/

#define `$INSTANCE_NAME`_CTRL_UART      (`$INSTANCE_NAME`_CTRL_MODE_UART)

#define `$INSTANCE_NAME`_UART_RX_CTRL   (`$INSTANCE_NAME`_RX_CTRL_LSB_FIRST | \
                                         `$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_UART_TX_CTRL   (`$INSTANCE_NAME`_TX_CTRL_LSB_FIRST | \
                                         `$INSTANCE_NAME`_TX_CTRL_ENABLED)

#endif /* CY_SCB_SPI_UART_`$INSTANCE_NAME`_H */


/* [] END OF FILE */
