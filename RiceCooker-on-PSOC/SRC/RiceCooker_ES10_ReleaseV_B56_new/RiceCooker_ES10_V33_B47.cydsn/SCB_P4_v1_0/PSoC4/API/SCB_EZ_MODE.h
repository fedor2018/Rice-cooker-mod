/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZ_MODE.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the I2C_P4_FF component.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EZ_MODE_`$INSTANCE_NAME`_H)
#define CY_EZ_MODE_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*       Type defines
***************************************/

typedef struct
{
    uint32 operationMode;
    uint32 enableMedianFilter;
    uint32 enableWaitStates;
    uint32 slaveAddr;
    uint32 slaveAddrMask;
    uint32 enableWake;
    uint32 wakeAction;
    uint32 enableInterrupt;
    uint32 ezInterruptMask;
    uint32 rxInterruptMask;
    uint32 txInterruptMask;
} `$INSTANCE_NAME`_EZI2C_INIT_STRUCT;


typedef struct
{
    uint32 operationMode;
    uint32 enableMedianFilter;
    uint32 enableWaitStates;
    uint32 enableWake;
    uint32 enableInterrupt;
    uint32 ezInterruptMask;
    uint32 rxInterruptMask;
    uint32 txInterruptMask;
} `$INSTANCE_NAME`_EZSPI_INIT_STRUCT;


/***************************************
*       Global components vars
***************************************/

extern const `$INSTANCE_NAME`_EZI2C_INIT_STRUCT `$INSTANCE_NAME`_configEzI2C;
extern const `$INSTANCE_NAME`_EZSPI_INIT_STRUCT `$INSTANCE_NAME`_configEzSpi;


/***************************************
*       Conditional compilation
***************************************/

/* EZI2C struct init constants */
#define `$INSTANCE_NAME`_EZ_INTERNALLY_CLOCKED  (0u)
#define `$INSTANCE_NAME`_EZ_EXTERNALLY_CLOCKED  (1u)

#define `$INSTANCE_NAME`_EZI2C_WAKE_CLOCK_STRETCH   (0u)
#define `$INSTANCE_NAME`_EZI2C_WAKE_ADDRESS_NACK    (1u)


/***************************************
*   Parameters from customizer EzI2C
****************************************/

#define `$INSTANCE_NAME`_EZI2C_OPERATION_MODE       (`$EzI2cOperationMode`u)
#define `$INSTANCE_NAME`_EZI2C_MEDIAN_FILTER_ENABLE (`$EzI2cMedianFilterEnable`u)
#define `$INSTANCE_NAME`_EZI2C_SLAVE_ADDRESS        (`$EzI2cSlaveAddress`u)
#define `$INSTANCE_NAME`_EZI2C_SLAVE_ADDRESS_MASK   (`$EzI2cSlaveAddressMask`u)
#define `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE          (`$EzI2cWakeEnable`u)
#define `$INSTANCE_NAME`_EZI2C_WAKE_ACTION          (`$EzI2cWakeAction`u)

#define `$INSTANCE_NAME`_EZI2C_INTR_WAKE            ((0u != `$EzI2cIntrWake`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP) : (0u))
#define `$INSTANCE_NAME`_EZI2C_INTR_RX_MASK         ((0u != `$EzI2cIntrRxBlocked`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_RX_BLOCKED) : (0u))
#define `$INSTANCE_NAME`_EZI2C_INTR_TX_MASK         ((0u != `$EzI2cIntrTxBlocked`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_TX_BLOCKED) : (0u))


#if(`$INSTANCE_NAME`_EZ_EXTERNALLY_CLOCKED == `$INSTANCE_NAME`_EZI2C_OPERATION_MODE)
    /* Externally clocked Operation Mode */
    #define `$INSTANCE_NAME`_EZI2C_WAIT_STATES_ENABLE   (`$EzI2cWaitStatesEnable`u)
    #define `$INSTANCE_NAME`_EZI2C_INTR_STOP            ((0u != `$EzI2cIntrStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_I2C_EC_EZ_STOP) : (0u))
    #define `$INSTANCE_NAME`_EZI2C_INTR_WRITE_STOP      ((0u != `$EzI2cIntrWriteStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_I2C_EC_EZ_WRITE_STOP) : (0u))
#else
    /* Internally clocked Operation Mode */
    #define `$INSTANCE_NAME`_EZI2C_WAIT_STATES_ENABLE   (0u)
    #define `$INSTANCE_NAME`_EZI2C_INTR_STOP            ((0u != `$EzI2cIntrStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP) : (0u))
    #define `$INSTANCE_NAME`_EZI2C_INTR_WRITE_STOP      ((0u != `$EzI2cIntrWriteStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP) : (0u))
#endif /* (`$INSTANCE_NAME`_EZ_EXTERNALLY_CLOCKED == `$INSTANCE_NAME`_EZI2C_OPERATION_MODE) */

/* `$INSTANCE_NAME`_EZI2C_INTR_MASK */
#define `$INSTANCE_NAME`_EZI2C_INTR_MASK                (`$INSTANCE_NAME`_EZI2C_INTR_WAKE | \
                                                         `$INSTANCE_NAME`_EZI2C_INTR_STOP | \
                                                         `$INSTANCE_NAME`_EZI2C_INTR_WRITE_STOP)


/***************************************
*   Parameters from customizer EzSpi
****************************************/

#define `$INSTANCE_NAME`_EZSPI_OPERATION_MODE       (`$EzSpiOperationMode`u)
#define `$INSTANCE_NAME`_EZSPI_MEDIAN_FILTER_ENABLE (`$EzSpiMedianFilterEnable`u)
#define `$INSTANCE_NAME`_EZSPI_WAKE_ENABLE          (`$EzSpiWakeEnable`u)
#define `$INSTANCE_NAME`_EZSPI_INTR_WAKE            ((0u != `$EzSpiIntrWake`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP) : (0u))
#define `$INSTANCE_NAME`_EZSPI_INTR_RX_MASK         ((0u != `$EzSpiIntrRxBlocked`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_RX_BLOCKED) : (0u))
#define `$INSTANCE_NAME`_EZSPI_INTR_TX_MASK         ((0u != `$EzSpiIntrTxBlocked`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_TX_BLOCKED) : (0u))

#if(`$INSTANCE_NAME`_EZ_EXTERNALLY_CLOCKED == `$INSTANCE_NAME`_EZSPI_OPERATION_MODE)
    /* Externally clocked Operation Mode */
    #define `$INSTANCE_NAME`_EZSPI_WAIT_STATES_ENABLE   (`$EzSpiWaitStatesEnable`u)
    #define `$INSTANCE_NAME`_EZSPI_INTR_STOP            ((0u != `$EzSpiIntrStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SPI_EC_EZ_STOP) : (0u))
    #define `$INSTANCE_NAME`_EZSPI_INTR_WRITE_STOP      ((0u != `$EzSpiIntrWriteStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SPI_EC_EZ_WRITE_STOP) : (0u))

#else
    /* Internally clocked Operation Mode */
    #define `$INSTANCE_NAME`_EZSPI_WAIT_STATES_ENABLE   (0u)
    #define `$INSTANCE_NAME`_EZSPI_INTR_STOP            ((0u != `$EzSpiIntrStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_STOP) : (0u))
    #define `$INSTANCE_NAME`_EZSPI_INTR_WRITE_STOP      ((0u != `$EzSpiIntrWriteStop`u) ? \
                                                            (`$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_WRITE_STOP) : (0u))

#endif /* (`$INSTANCE_NAME`_EZ_EXTERNALLY_CLOCKED == `$INSTANCE_NAME`_EZI2C_OPERATION_MODE) */

/* `$INSTANCE_NAME`_EZSPI_INTR_MASK */
#define `$INSTANCE_NAME`_EZSPI_INTR_MASK                (`$INSTANCE_NAME`_EZSPI_INTR_WAKE | \
                                                         `$INSTANCE_NAME`_EZSPI_INTR_STOP | \
                                                         `$INSTANCE_NAME`_EZSPI_INTR_WRITE_STOP)


/***************************************
*   Access to EZI2C and EZSPI struct
****************************************/

#define `$INSTANCE_NAME`_EZI2C_INIT_ACCESS(ptr, field)   (((`$INSTANCE_NAME`_EZI2C_INIT_STRUCT *) (ptr))->field)
#define `$INSTANCE_NAME`_EZSPI_INIT_ACCESS(ptr, field)   (((`$INSTANCE_NAME`_EZSPI_INIT_STRUCT *) (ptr))->field)

#define `$INSTANCE_NAME`_EZI2C_SPI_INIT_ACCESS(ptr, field)  ((`$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG) ? \
                                                                `$INSTANCE_NAME`_EZI2C_INIT_ACCESS(ptr, field) : \
                                                                `$INSTANCE_NAME`_EZSPI_INIT_ACCESS(ptr, field))


/***************************************
*   RunTime configuration choice
****************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)

    /* Enable internal interrpt */
    #define `$INSTANCE_NAME`_EZI2C_INTERRUPT_ENABLE (0u)
    #define `$INSTANCE_NAME`_EZSPI_INTERRUPT_ENABLE (0u)

    /* Insert wait states */
    #define `$INSTANCE_NAME`_WAIT_STATES_INSERTED   \
                            (0u != `$INSTANCE_NAME`_EZI2C_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWaitStates))

    /* EZI2C configuration */
    #define `$INSTANCE_NAME`_CHECK_SCB_MODE_EZI2C_CFG   `$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG

    /* EZI2C wakeup */
    #define `$INSTANCE_NAME`_EZI2C_WAKEUP_ENABLE    \
                            (0u != `$INSTANCE_NAME`_EZI2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWake))

    #define `$INSTANCE_NAME`_EZI2C_WAKEUP_ADDR_NACK \
                            (0u != `$INSTANCE_NAME`_EZI2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, wakeAction))

    /* EZSPI wakeup */
    #define `$INSTANCE_NAME`_EZSPI_WAKEUP_ENABLE    \
                            (0u != `$INSTANCE_NAME`_EZSPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWake))

#else

    /* Enable internal interrpt */
    #define `$INSTANCE_NAME`_EZI2C_INTERRUPT_ENABLE     ((`$EzI2cInterruptMode`u == \
                                                            `$INSTANCE_NAME`_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))

    #define `$INSTANCE_NAME`_EZSPI_INTERRUPT_ENABLE     ((`$EzSpiInterruptMode`u == \
                                                            `$INSTANCE_NAME`_SCB_INTR_MODE_INTERNAL) ? (1u) : (0u))
    /* Insert wait states */
    #define `$INSTANCE_NAME`_WAIT_STATES_INSERTED   ((`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG) ?    \
                                                        (`$INSTANCE_NAME`_EZI2C_WAIT_STATES_ENABLE) : \
                                                        (`$INSTANCE_NAME`_EZSPI_WAIT_STATES_ENABLE))
    /* EZI2C configuration */
    #define `$INSTANCE_NAME`_CHECK_SCB_MODE_EZI2C_CFG   `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG

    /* EZI2C wakeup */
    #define `$INSTANCE_NAME`_EZI2C_WAKEUP_ENABLE    (0u != `$INSTANCE_NAME`_EZI2C_WAKE_ENABLE)

    #define `$INSTANCE_NAME`_EZI2C_WAKEUP_ADDR_NACK (0u != `$INSTANCE_NAME`_EZI2C_WAKE_ACTION)

    /* EZSPI wakeup */
    #define `$INSTANCE_NAME`_EZSPI_WAKEUP_ENABLE    (0u != `$INSTANCE_NAME`_EZSPI_WAKE_ENABLE)

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

/* Bootloader communication interface enable: NOT supported yet */
#define `$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#define `$INSTANCE_NAME`_EZSPI_BTLDR_COMM_ENABLED   ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*        Function Prototypes
***************************************/

/* EZI2C specific functions */
void `$INSTANCE_NAME`_EzI2CInit(`$INSTANCE_NAME`_EZI2C_INIT_STRUCT *config);
void `$INSTANCE_NAME`_EzI2CSaveConfig(void);
void `$INSTANCE_NAME`_EzI2CRestoreConfig(void);

/* EZSPI specific functions */
void `$INSTANCE_NAME`_EzSpiInit(`$INSTANCE_NAME`_EZSPI_INIT_STRUCT *config);
void `$INSTANCE_NAME`_EzSpiSaveConfig(void);
void `$INSTANCE_NAME`_EzSpiRestoreConfig(void);

/* Data processing */
uint32 `$INSTANCE_NAME`_EzWriteByte(uint32 addr, uint32 dataByte);
uint32 `$INSTANCE_NAME`_EzReadByte(uint32 addr);

/* Service functions */
uint32 `$INSTANCE_NAME`_EzGetEzAddress(void);
uint32 `$INSTANCE_NAME`_EzIsBusBusy(void);

CY_ISR_PROTO(`$INSTANCE_NAME`_EZ_MODE_ISR);

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BTLDR_COMM_ENABLED)
    /* EZI2C Bootloader physical layer functions */
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_EzI2CCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_EzI2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZI2C_BOOTLOADER_INTERFACE_ENABLED) */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZSPI_BTLDR_COMM_ENABLED)
    /* EZSPI Bootloader physical layer functions */
    void `$INSTANCE_NAME`_EzSpiCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_EzSpiCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_EzSpiCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_EzSpiCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_EzSpiCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_EZSPI_BOOTLOADER_INTERFACE_ENABLED) */


/**********************************
*      External linkage
**********************************/

extern uint32 volatile * const `$INSTANCE_NAME`_hwBuffer;


/***************************************
*      Default EZ registers
***************************************/

#define `$INSTANCE_NAME`_EZ_RX_CTRL    ((`$INSTANCE_NAME`_FIFO_SIZE - 1u)  | \
                                        `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST | \
                                        `$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_EZ_TX_CTRL    ((`$INSTANCE_NAME`_FIFO_SIZE - 1u)  | \
                                        `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST | \
                                        `$INSTANCE_NAME`_TX_CTRL_ENABLED)


/***************************************
*    Default register settings EzI2C
***************************************/

#define `$INSTANCE_NAME`_CTRL_EZI2C     (`$INSTANCE_NAME`_CTRL_EZ_MODE | \
                                         `$INSTANCE_NAME`_CTRL_MODE_I2C)

#define `$INSTANCE_NAME`_EZI2C_I2C_CTRL (`$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE | \
                                         `$INSTANCE_NAME`_I2C_CTRL_S_READY_ADDR_ACK | \
                                         `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK | \
                                         `$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE)


/***************************************
*   Default register settings EzSpi
***************************************/

#define `$INSTANCE_NAME`_CTRL_EZSPI     (`$INSTANCE_NAME`_CTRL_EZ_MODE | \
                                         `$INSTANCE_NAME`_CTRL_MODE_SPI)


#define `$INSTANCE_NAME`_EZSPI_SPI_CTRL (`$INSTANCE_NAME`_SPI_CTRL_MODE_MOTOROLA | \
                                         `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT0 | \
                                         `$INSTANCE_NAME`_SPI_CTRL_SLAVE)



#endif /* (CY_EZ_MODE_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
