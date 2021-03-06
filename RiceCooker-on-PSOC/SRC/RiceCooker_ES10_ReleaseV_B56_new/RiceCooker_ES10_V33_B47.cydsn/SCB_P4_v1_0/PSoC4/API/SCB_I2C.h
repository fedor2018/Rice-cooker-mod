/*******************************************************************************
* File Name: `$INSTANCE_NAME`_I2C.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides constants and parameter values for the SCB component.
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_I2C_`$INSTANCE_NAME`_H)
#define CY_SCB_I2C_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`.h"


/***************************************
*       Type defines
***************************************/

typedef struct
{
    uint32 mode;
    uint32 oversampleLow;
    uint32 oversampleHigh;
    uint32 enableMedianFilter;
    uint32 slaveAddr;
    uint32 slaveAddrMask;
    uint32 acceptAddr;
    uint32 enableWake;
} `$INSTANCE_NAME`_I2C_INIT_STRUCT;


/***************************************
*       Global components vars
***************************************/

extern const `$INSTANCE_NAME`_I2C_INIT_STRUCT `$INSTANCE_NAME`_configI2C;


/***************************************
*   Parameters from customizer
****************************************/

#define `$INSTANCE_NAME`_I2C_MODE                   (`$I2cMode`u)
#define `$INSTANCE_NAME`_I2C_OVS_FACTOR_LOW         (`$I2cOvsFactorLow`u)
#define `$INSTANCE_NAME`_I2C_OVS_FACTOR_HIGH        (`$I2cOvsFactorHigh`u)
#define `$INSTANCE_NAME`_I2C_MEDIAN_FILTER_ENABLE   (`$I2cMedianFilterEnable`u)
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS          (`$I2cSlaveAddress`u)
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDRESS_MASK     (`$I2cSlaveAddressMask`u)
#define `$INSTANCE_NAME`_I2C_ACCEPT_ADRESS          (`$I2cAcceptAddress`u)
#define `$INSTANCE_NAME`_I2C_WAKE_ENABLE            (`$I2cWakeEnable`u)
#define `$INSTANCE_NAME`_I2C_WAKE_ACTION            (`$I2cWakeAction`u)
#define `$INSTANCE_NAME`_I2C_DATA_RATE              (`$I2cDataRate`u)


/***************************************
*   Access to I2C config structure
****************************************/

#define `$INSTANCE_NAME`_I2C_INIT_ACCESS(ptr, field)  (((`$INSTANCE_NAME`_I2C_INIT_STRUCT *) (ptr))->field)


/***************************************
*   Condition compilation parameters
****************************************/

/* I2C sub mode enum */
#define `$INSTANCE_NAME`_I2C_MODE_SLAVE              (0x01u)
#define `$INSTANCE_NAME`_I2C_MODE_MASTER             (0x02u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER       (0x06u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE (0x07u)
#define `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_MASK  (0x04u)

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)

    /* Returns true if slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_SLAVE   (0u != (`$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, mode) & \
                                                 `$INSTANCE_NAME`_I2C_MODE_SLAVE))

    /* Returns true if master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MASTER  (0u != (`$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, mode) & \
                                                 `$INSTANCE_NAME`_I2C_MODE_MASTER))

    /* Returns true if multi-master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER \
                                    (0u != (`$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, mode) & \
                                            `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER))

    /* Returns true if multi-master-slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE \
                                    (0u != (`$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, mode) & \
                                            `$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE))

    /* Returns true if address accepts in RX FIFO */
    #define `$INSTANCE_NAME`_I2C_ACCEPT_ADDR \
                                    (0u != `$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, acceptAddr))

    /* Returns true if wakeup on address match is enabled */
    #define `$INSTANCE_NAME`_I2C_WAKEUP \
                                    (0u != `$INSTANCE_NAME`_I2C_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, enableWake))

    #define `$INSTANCE_NAME`_I2C_SLAVE_CONST        (1u)
    #define `$INSTANCE_NAME`_I2C_MASTER_CONST       (1u)
    #define `$INSTANCE_NAME`_I2C_ACCEPT_ADDR_CONST  (1u)

    #define `$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))

#else

    /* Returns true if slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_SLAVE   (0u != (`$INSTANCE_NAME`_I2C_MODE_SLAVE & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MASTER  (0u != (`$INSTANCE_NAME`_I2C_MODE_MASTER & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if multi-master mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER \
                                    (0u != (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if multi-master-slave mode is enabled */
    #define `$INSTANCE_NAME`_I2C_MULTI_MASTER_SLAVE \
                                    (0u != (`$INSTANCE_NAME`_I2C_MODE_MULTI_MASTER_SLAVE & `$INSTANCE_NAME`_I2C_MODE))

    /* Returns true if address accepts in RX FIFO */
    #define `$INSTANCE_NAME`_I2C_ACCEPT_ADDR     (0u != `$INSTANCE_NAME`_I2C_ACCEPT_ADRESS)

    /* Returns true if wakeup on address match is enabled */
    #define `$INSTANCE_NAME`_I2C_WAKEUP          (0u != `$INSTANCE_NAME`_I2C_WAKE_ENABLE)


    #define `$INSTANCE_NAME`_I2C_SLAVE_CONST        (`$INSTANCE_NAME`_I2C_SLAVE)
    #define `$INSTANCE_NAME`_I2C_MASTER_CONST       (`$INSTANCE_NAME`_I2C_MASTER)
    #define `$INSTANCE_NAME`_I2C_ACCEPT_ADDR_CONST  (`$INSTANCE_NAME`_I2C_ACCEPT_ADDR)

    #define `$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED     (`$INSTANCE_NAME`_I2C_SLAVE_CONST && \
                                                          ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                           (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)))

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */


/***************************************
*        Function Prototypes
***************************************/

/* Common functions */
void `$INSTANCE_NAME`_I2CInit(`$INSTANCE_NAME`_I2C_INIT_STRUCT *config);

/* Internal functions for external linking */
void `$INSTANCE_NAME`_I2CStop(void);
void `$INSTANCE_NAME`_I2CSaveConfig(void);
void `$INSTANCE_NAME`_I2CRestoreConfig(void);

/* I2C Master functions prototypes */
#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)
    /* Read and Clear status functions */
    uint32 `$INSTANCE_NAME`_I2CMasterStatus(void);
    uint32 `$INSTANCE_NAME`_I2CMasterClearStatus(void);

    /* Interrupt based operation functions */
    uint32 `$INSTANCE_NAME`_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode);
    uint32 `$INSTANCE_NAME`_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode);
    uint32 `$INSTANCE_NAME`_I2CMasterGetReadBufSize(void);
    uint32 `$INSTANCE_NAME`_I2CMasterGetWriteBufSize(void);
    void   `$INSTANCE_NAME`_I2CMasterClearReadBuf(void);
    void   `$INSTANCE_NAME`_I2CMasterClearWriteBuf(void);

    /* Manual operation functions */
    uint32 `$INSTANCE_NAME`_I2CMasterSendStart(uint32 slaveAddress, uint32 R_nW);
    uint32 `$INSTANCE_NAME`_I2CMasterSendRestart(uint32 slaveAddress, uint32 R_nW);
    uint32 `$INSTANCE_NAME`_I2CMasterSendStop(void);
    uint32 `$INSTANCE_NAME`_I2CMasterWriteByte(uint32 theByte);
    uint32 `$INSTANCE_NAME`_I2CMasterReadByte(uint32 ackNack);
#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */

/* I2C Slave functions prototypes */
#if(`$INSTANCE_NAME`_I2C_SLAVE_CONST)
    /* Read and Clear status functions */
    uint32 `$INSTANCE_NAME`_I2CSlaveStatus(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveClearReadStatus(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveClearWriteStatus(void);

    /* Set Slave address and mask */
    void   `$INSTANCE_NAME`_I2CSlaveSetAddress(uint32 address);
    void   `$INSTANCE_NAME`_I2CSlaveSetAddressMask(uint32 mask);

    /* Interrupt based operation functions */
    void   `$INSTANCE_NAME`_I2CSlaveInitReadBuf(uint8 * rdBuf, uint32 bufSize);
    void   `$INSTANCE_NAME`_I2CSlaveInitWriteBuf(uint8 * wrBuf, uint32 bufSize);
    uint32 `$INSTANCE_NAME`_I2CSlaveGetReadBufSize(void);
    uint32 `$INSTANCE_NAME`_I2CSlaveGetWriteBufSize(void);
    void   `$INSTANCE_NAME`_I2CSlaveClearReadBuf(void);
    void   `$INSTANCE_NAME`_I2CSlaveClearWriteBuf(void);
#endif /* (`$INSTANCE_NAME`_I2C_SLAVE_CONST) */

CY_ISR_PROTO(`$INSTANCE_NAME`_I2C_ISR); /* Interrupt handler */

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED)

    /* Bootloader physical layer functions */
    void `$INSTANCE_NAME`_I2CCyBtldrCommStart(void);
    void `$INSTANCE_NAME`_I2CCyBtldrCommStop (void);
    void `$INSTANCE_NAME`_I2CCyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_I2CCyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_I2CCyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    /* Size of Read/Write buffers for I2C bootloader  */
    #define `$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_READ_BUFFER   (64u)
    #define `$INSTANCE_NAME`_I2C_BTLDR_SIZEOF_WRITE_BUFFER  (64u)
    #define `$INSTANCE_NAME`_I2C_MIN_UINT16(a, b)           ( ((uint16)(a) < (b)) ? ((uint16) (a)) : ((uint16) (b)) )
    #define `$INSTANCE_NAME`_WAIT_1_MS                      (1u)

#endif /* defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_I2C_BTLDR_COMM_ENABLED) */


/***************************************
*            API Constants
***************************************/

/* EZI2C struct init constants */
#define `$INSTANCE_NAME`_I2C_WAKE_CLOCK_STRETCH (0u)
#define `$INSTANCE_NAME`_I2C_WAKE_ADDRESS_NACK  (1u)

/* General I2C constants */
#define `$INSTANCE_NAME`_I2C_READ_FLAG          (0x01u) /* Read flag of the Address */
#define `$INSTANCE_NAME`_I2C_FIFO_SIZE          (8u)    /* Max FIFO entries for I2C */
#define `$INSTANCE_NAME`_I2C_SLAVE_OVFL_RETURN  (0xFFu) /* Return by slave when overflow */

/* Master/Slave control constants */
#define `$INSTANCE_NAME`_I2C_WRITE_XFER_MODE    (0u)    /* Write    */
#define `$INSTANCE_NAME`_I2C_READ_XFER_MODE     (1u)    /* Read     */
#define `$INSTANCE_NAME`_I2C_ACK_DATA           (0u)    /* Send ACK */
#define `$INSTANCE_NAME`_I2C_NAK_DATA           (1u)    /* Send NAK */

/* "Mode" constants for MasterWriteBuf() or MasterReadBuf() function */
#define `$INSTANCE_NAME`_I2C_MODE_COMPLETE_XFER     (0x00u)    /* Full transfer with Start and Stop       */
#define `$INSTANCE_NAME`_I2C_MODE_REPEAT_START      (0x01u)    /* Begin with a ReStart instead of a Start */
#define `$INSTANCE_NAME`_I2C_MODE_NO_STOP           (0x02u)    /* Complete the transfer without a Stop    */

/* Master status */
#define `$INSTANCE_NAME`_I2C_MSTAT_CLEAR            (0x00u)    /* Clear (init) status value */

#define `$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT         (0x01u)    /* Read complete               */
#define `$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT         (0x02u)    /* Write complete              */
#define `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP         (0x04u)    /* Master transfer in progress */
#define `$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT        (0x08u)    /* Transfer is halted          */

#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_MASK         (0x3F0u)   /* Mask for all errors                                    */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_SHORT_XFER   (0x010u)   /* Master NAKed before end of packet                      */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_ADDR_NAK     (0x020u)   /* Slave did not ACK                                      */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_ARB_LOST     (0x040u)   /* Master lost arbitration during communication           */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_START_ABORT  (0x080u)   /* The Slave was addressed before the Start was generated */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_BUS_ERROR    (0x100u)   /* The misplaced Start or Stop is happen on the bus       */
#define `$INSTANCE_NAME`_I2C_MSTAT_ERR_XFER         (0x200u)   /* Error during transfer                                  */

/* Master API returns */
#define `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR          (0x00u)    /* Function complete without error                               */
#define `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY          (0x01u)    /* Bus is busy, process not started                              */
#define `$INSTANCE_NAME`_I2C_MSTR_NOT_READY         (0x02u)    /* Master not Master on the bus or Slave operation in progress   */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK        (0x03u)    /* Last Byte Naked                                               */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST      (0x04u)    /* Master lost arbitration during communication                  */
#define `$INSTANCE_NAME`_I2C_MSTR_ERR_ABORT_START_GEN  (0x05u) /* Master did not generate Start, the Slave was addressed before */

/* Slave Status Constants */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_CMPLT         (0x01u)    /* Read transfer complete                       */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_BUSY          (0x02u)    /* Read transfer in progress                    */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_ERR_OVFL      (0x04u)    /* Read overflow Error                          */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_ERR           (0x08u)    /* Read was interrupted by misplaced Start/Stop */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_MASK          (0x0Fu)    /* Read Status Mask                             */
#define `$INSTANCE_NAME`_I2C_SSTAT_RD_NO_ERR        (0x00u)    /* Read no Error                                */

#define `$INSTANCE_NAME`_I2C_SSTAT_WR_CMPLT         (0x10u)    /* Write transfer complete                       */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_BUSY          (0x20u)    /* Write transfer in progress                    */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_ERR_OVFL      (0x40u)    /* Write overflow Error                          */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_ERR           (0x80u)    /* Write was interrupted by misplaced Start/Stop */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_MASK          (0xF0u)    /* Write Status Mask                             */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_NO_ERR        (0x00u)    /* Write no Error                                */

#define `$INSTANCE_NAME`_I2C_SSTAT_RD_CLEAR         (0x0Fu)    /* Read Status clear  */
#define `$INSTANCE_NAME`_I2C_SSTAT_WR_CLEAR         (0xF0u)    /* Write Status Clear */


/***************************************
*           I2C FSM states
***************************************/

#define `$INSTANCE_NAME`_I2C_FSM_EXIT_IDLE      (0x00u) /* Master and Slave are not active, need to exit to IDLE */

/* Slave mode FSM states */
#define `$INSTANCE_NAME`_I2C_FSM_IDLE           (0x10u) /* Idle I2C state                */
#define `$INSTANCE_NAME`_I2C_FSM_SLAVE          (0x10u) /* Slave mask for all its states */

#define `$INSTANCE_NAME`_I2C_FSM_SL_WR          (0x11u) /* Slave write states */
#define `$INSTANCE_NAME`_I2C_FSM_SL_RD          (0x12u) /* Slave read  states */

/* Master mode FSM states */
#define `$INSTANCE_NAME`_I2C_FSM_MASTER         (0x20u) /* Master mask for all its states */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_ADDR      (0x08u) /* Master address phase           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_DATA      (0x04u) /* Master data phase              */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD        (0x01u) /* Master read phase              */

#define `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_ADDR   (0x28u) /* FSM master transmit address with write          */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_ADDR   (0x29u) /* FSM master transmit address with read           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA   (0x24u) /* FSM master writes data into the slave           */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA   (0x25u) /* FSM master reads data from the slave            */
#define `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT      (0x60u) /* FSM master halt state: wait for Stop or ReStart */

/* Request to complete any on-going transfer */
#define `$INSTANCE_NAME`_CMPLT_ANY_TRANSFER     (0x01u)

/* Returns true if FSM is in any Master state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER   (0u != (`$INSTANCE_NAME`_I2C_FSM_MASTER & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in any Slave state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_SLAVE    (0u != (`$INSTANCE_NAME`_I2C_FSM_SLAVE  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in Master send address state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_ADDR (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_ADDR & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in Master send or receive data state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_DATA (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_DATA  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in any of read states: applied for Slave and Master */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_RD   (0u != (`$INSTANCE_NAME`_I2C_FSM_MSTR_RD  & `$INSTANCE_NAME`_state))

/* Returns true if FSM is in IDLE state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE (`$INSTANCE_NAME`_I2C_FSM_IDLE == `$INSTANCE_NAME`_state)

/* Returns true if FSM is HALT state */
#define `$INSTANCE_NAME`_CHECK_I2C_FSM_HALT (`$INSTANCE_NAME`_I2C_FSM_MSTR_HALT == `$INSTANCE_NAME`_state)

/* Set Master read or write completion depends on state */
#define `$INSTANCE_NAME`_GET_I2C_MSTAT_CMPLT (`$INSTANCE_NAME`_CHECK_I2C_FSM_RD ?           \
                                                    (`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT) : \
                                                    (`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT))


/***************************************
*       Macro Definitions
***************************************/

/* Return TRUE if sourceMask is set in `$INSTANCE_NAME`_I2C_MASTER_CMD_REG: used to check if Start was generated */
#define `$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(sourceMask)   (0u != (`$INSTANCE_NAME`_I2C_MASTER_CMD_REG & (sourceMask)))

/* Return TRUE if `$INSTANCE_NAME`_MODE_NO_STOP is set in `$INSTANCE_NAME`_mstrControl: used to detect NoStop condition */
#define `$INSTANCE_NAME`_CHECK_I2C_MODE_NO_STOP(mode)   (0u != (`$INSTANCE_NAME`_I2C_MODE_NO_STOP & (mode)))

/* Return TRUE if `$INSTANCE_NAME`_MODE_REPEAT_START is set: used to detect when generate ReStart condition */
#define `$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode)   (0u != (`$INSTANCE_NAME`_I2C_MODE_REPEAT_START  & (mode)))

/* Return TRUE if `$INSTANCE_NAME`_state is in one of master states */
#define `$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE    (`$INSTANCE_NAME`_CHECK_I2C_FSM_MASTER)


/***************************************
*      Default register settings
***************************************/

#define `$INSTANCE_NAME`_CTRL_I2C       (`$INSTANCE_NAME`_CTRL_MODE_I2C)

#define `$INSTANCE_NAME`_I2C_CTRL       (`$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE)

#define `$INSTANCE_NAME`_I2C_RX_CTRL    ((`$INSTANCE_NAME`_FIFO_SIZE - 1u) | \
                                         `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST | \
                                         `$INSTANCE_NAME`_RX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_I2C_TX_CTRL    ((`$INSTANCE_NAME`_FIFO_SIZE - 1u) | \
                                         `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST | \
                                         `$INSTANCE_NAME`_TX_CTRL_ENABLED)

#define `$INSTANCE_NAME`_I2C_INTR_SLAVE_MASK    (`$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK       | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP | \
                                                 `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR)

#define `$INSTANCE_NAME`_I2C_INTR_MASTER_MASK   (`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK     | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP     | \
                                                 `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR)

#endif /* (CY_SCB_I2C_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
