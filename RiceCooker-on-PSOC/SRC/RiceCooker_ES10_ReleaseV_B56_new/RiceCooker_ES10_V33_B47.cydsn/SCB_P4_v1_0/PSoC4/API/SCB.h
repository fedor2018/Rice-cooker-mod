/*******************************************************************************
* File Name: `$INSTANCE_NAME`.h
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

#if !defined(CY_SCB_`$INSTANCE_NAME`_H)
#define CY_SCB_`$INSTANCE_NAME`_H

#include "cydevice_trm.h"
#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"


/***************************************
*   Conditional compilation parameters
****************************************/

#define `$INSTANCE_NAME`_REMOVE_SCB_IRQ             (`$RemoveScbIrq`u)
#define `$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL    (0u == `$INSTANCE_NAME`_REMOVE_SCB_IRQ)

#define `$INSTANCE_NAME`_REMOVE_UART_RX_WAKAUP_IRQ  (`$RemoveUartRxWakeupIrq`u)
#define `$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ         (0u == `$INSTANCE_NAME`_REMOVE_UART_RX_WAKAUP_IRQ)

#define `$INSTANCE_NAME`_SCB_MODE           (`$ScbMode`u)

/* SCB modes enum */
#define `$INSTANCE_NAME`_SCB_MODE_I2C       (0x01u)
#define `$INSTANCE_NAME`_SCB_MODE_SPI       (0x02u)
#define `$INSTANCE_NAME`_SCB_MODE_UART      (0x04u)
#define `$INSTANCE_NAME`_SCB_MODE_EZI2C     (0x08u)
#define `$INSTANCE_NAME`_SCB_MODE_EZSPI     (0x10u)
#define `$INSTANCE_NAME`_SCB_MODE_UNCONFIG  (0x1Fu)

#define `$INSTANCE_NAME`_SCB_MODE_I2C_RUNTM_CFG    (`$INSTANCE_NAME`_SCB_MODE_I2C   == `$INSTANCE_NAME`_scbMode)
#define `$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG    (`$INSTANCE_NAME`_SCB_MODE_SPI   == `$INSTANCE_NAME`_scbMode)
#define `$INSTANCE_NAME`_SCB_MODE_UART_RUNTM_CFG   (`$INSTANCE_NAME`_SCB_MODE_UART  == `$INSTANCE_NAME`_scbMode)
#define `$INSTANCE_NAME`_SCB_MODE_EZI2C_RUNTM_CFG  (`$INSTANCE_NAME`_SCB_MODE_EZI2C == `$INSTANCE_NAME`_scbMode)
#define `$INSTANCE_NAME`_SCB_MODE_EZSPI_RUNTM_CFG  (`$INSTANCE_NAME`_SCB_MODE_EZSPI == `$INSTANCE_NAME`_scbMode)

#define `$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG    (0u != (`$INSTANCE_NAME`_SCB_MODE_I2C   & `$INSTANCE_NAME`_SCB_MODE))
#define `$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG    (0u != (`$INSTANCE_NAME`_SCB_MODE_SPI   & `$INSTANCE_NAME`_SCB_MODE))
#define `$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG   (0u != (`$INSTANCE_NAME`_SCB_MODE_UART  & `$INSTANCE_NAME`_SCB_MODE))
#define `$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG  (0u != (`$INSTANCE_NAME`_SCB_MODE_EZI2C & `$INSTANCE_NAME`_SCB_MODE))
#define `$INSTANCE_NAME`_SCB_MODE_EZSPI_CONST_CFG  (0u != (`$INSTANCE_NAME`_SCB_MODE_EZSPI & `$INSTANCE_NAME`_SCB_MODE))
#define `$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG  (`$INSTANCE_NAME`_SCB_MODE_UNCONFIG == `$INSTANCE_NAME`_SCB_MODE)

/* SCB interrupt enum */
#define `$INSTANCE_NAME`_SCB_INTR_MODE_NONE     (0u)
#define `$INSTANCE_NAME`_SCB_INTR_MODE_INTERNAL (1u)
#define `$INSTANCE_NAME`_SCB_INTR_MODE_EXTERNAL (2u)

/* Bootloader communication interface enable */
#define `$INSTANCE_NAME`_BTLDR_COMM_ENABLED ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                             (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))


/***************************************
*       inculdes
****************************************/

#if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
    #include "`$INSTANCE_NAME`_I2C.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */

#if(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG || `$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
    #include "`$INSTANCE_NAME`_SPI_UART.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG || `$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG) */

#if(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG || `$INSTANCE_NAME`_SCB_MODE_EZSPI_CONST_CFG)
    #include "`$INSTANCE_NAME`_EZ_MODE.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG || `$INSTANCE_NAME`_SCB_MODE_EZSPI_CONST_CFG) */

#if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
    #include "`$INSTANCE_NAME`_SCB_IRQ.h"
#endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

#if(`$INSTANCE_NAME`_UART_RX_WAKAUP_IRQ)
    #include "`$INSTANCE_NAME`_RX_WAKEUP_IRQ.h"
#endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    #include "`$INSTANCE_NAME`_PINS.h"
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */


/***************************************
*        Function Prototypes
***************************************/

/* Start and Stop APIs */
void `$INSTANCE_NAME`_Init(void);
void `$INSTANCE_NAME`_Enable(void);
void `$INSTANCE_NAME`_Start(void);
void `$INSTANCE_NAME`_Stop(void);

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    void `$INSTANCE_NAME`_SetPins(uint32 mode, uint32 subMode, uint32 spiSsUartTxRx);
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

/* Sleep and Wakeup APis */
void `$INSTANCE_NAME`_Sleep(void);
void `$INSTANCE_NAME`_Wakeup(void);

/* Customer interrupt handler */
void `$INSTANCE_NAME`_SetCustomInterruptHandler(void (*func) (void));

#if defined(CYDEV_BOOTLOADER_IO_COMP) && (`$INSTANCE_NAME`_BTLDR_COMM_ENABLED)

    /* Bootloader Physical layer functions */
    void `$INSTANCE_NAME`_CyBtldrCommStart(void);
    void `$INSTANCE_NAME`_CyBtldrCommStop (void);
    void `$INSTANCE_NAME`_CyBtldrCommReset(void);
    cystatus `$INSTANCE_NAME`_CyBtldrCommRead       (uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);
    cystatus `$INSTANCE_NAME`_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut);

    #if(CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`)
        #define CyBtldrCommStart    `$INSTANCE_NAME`_CyBtldrCommStart
        #define CyBtldrCommStop     `$INSTANCE_NAME`_CyBtldrCommStop
        #define CyBtldrCommReset    `$INSTANCE_NAME`_CyBtldrCommReset
        #define CyBtldrCommWrite    `$INSTANCE_NAME`_CyBtldrCommWrite
        #define CyBtldrCommRead     `$INSTANCE_NAME`_CyBtldrCommRead
    #endif /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) */

#endif /*defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_`$INSTANCE_NAME`) || \
                                                     (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface)) */

/* Interface to internal interrupt component */
#if(`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL)
    #define `$INSTANCE_NAME`_EnableInt()    `$INSTANCE_NAME`_SCB_IRQ_Enable()
    #define `$INSTANCE_NAME`_DisableInt()   `$INSTANCE_NAME`_SCB_IRQ_Disable()
#endif /* (`$INSTANCE_NAME`_INTERRUPT_MODE_INTERNAL) */

/* Get interrupt cause */
#define `$INSTANCE_NAME`_GetInterruptCause()    (`$INSTANCE_NAME`_INTR_CAUSE_REG)

/* APIs to service INTR_RX register */
#define `$INSTANCE_NAME`_SetRxInterruptMode(interruptMask)      `$INSTANCE_NAME`_WRITE_INTR_RX_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearRxInterruptSource(interruptMask)  `$INSTANCE_NAME`_CLEAR_INTR_RX(interruptMask)
#define `$INSTANCE_NAME`_SetRxInterrupt(interruptMask)          `$INSTANCE_NAME`_SET_INTR_RX(interruptMask)
#define `$INSTANCE_NAME`_GetRxInterruptSource()                 (`$INSTANCE_NAME`_INTR_RX_REG)
#define `$INSTANCE_NAME`_GetRxInterruptMode()                   (`$INSTANCE_NAME`_INTR_RX_MASK_REG)
#define `$INSTANCE_NAME`_GetRxInterruptSourceMasked()           (`$INSTANCE_NAME`_INTR_RX_MASKED_REG)

/* APIs to service INTR_TX register */
#define `$INSTANCE_NAME`_SetTxInterruptMode(interruptMask)      `$INSTANCE_NAME`_WRITE_INTR_TX_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearTxInterruptSource(interruptMask)  `$INSTANCE_NAME`_CLEAR_INTR_TX(interruptMask)
#define `$INSTANCE_NAME`_SetTxInterrupt(interruptMask)          `$INSTANCE_NAME`_SET_INTR_TX(interruptMask)
#define `$INSTANCE_NAME`_GetTxInterruptSource()                 (`$INSTANCE_NAME`_INTR_TX_REG)
#define `$INSTANCE_NAME`_GetTxInterruptMode()                   (`$INSTANCE_NAME`_INTR_TX_MASK_REG)
#define `$INSTANCE_NAME`_GetTxInterruptSourceMasked()           (`$INSTANCE_NAME`_INTR_TX_MASKED_REG)

/* APIs to service INTR_MASTER register */
#define `$INSTANCE_NAME`_SetMasterInterruptMode(interruptMask)      `$INSTANCE_NAME`_WRITE_INTR_MASTER_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearMasterInterruptSource(interruptMask)  `$INSTANCE_NAME`_CLEAR_INTR_MASTER(interruptMask)
#define `$INSTANCE_NAME`_SetMasterInterrupt(interruptMask)          `$INSTANCE_NAME`_SET_INTR_MASTER(interruptMask)
#define `$INSTANCE_NAME`_GetMasterInterruptSource()                 (`$INSTANCE_NAME`_INTR_MASTER_REG)
#define `$INSTANCE_NAME`_GetMasterInterruptMode()                   (`$INSTANCE_NAME`_INTR_MASTER_MASK_REG)
#define `$INSTANCE_NAME`_GetMasterInterruptSourceMasked()           (`$INSTANCE_NAME`_INTR_MASTER_MASKED_REG)

/* APIs to service INTR_SLAVE register */
#define `$INSTANCE_NAME`_SetSlaveInterruptMode(interruptMask)       `$INSTANCE_NAME`_WRITE_INTR_SLAVE_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearSlaveInterruptSource(interruptMask)   `$INSTANCE_NAME`_CLEAR_INTR_SLAVE(interruptMask)
#define `$INSTANCE_NAME`_SetSlaveInterrupt(interruptMask)           `$INSTANCE_NAME`_SET_INTR_SLAVE(interruptMask)
#define `$INSTANCE_NAME`_GetSlaveInterruptSource()                  (`$INSTANCE_NAME`_INTR_SLAVE_REG)
#define `$INSTANCE_NAME`_GetSlaveInterruptMode()                    (`$INSTANCE_NAME`_INTR_SLAVE_MASK_REG)
#define `$INSTANCE_NAME`_GetSlaveInterruptSourceMasked()            (`$INSTANCE_NAME`_INTR_SLAVE_MASKED_REG)

/* APIs to service INTR_I2C_EC register */
#define `$INSTANCE_NAME`_SetI2CExtClkInterruptMode(interruptMask)       `$INSTANCE_NAME`_WRITE_INTR_I2C_EC_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearI2CExtClkInterruptSource(interruptMask)   `$INSTANCE_NAME`_CLEAR_INTR_I2C_EC(interruptMask)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptSource()                  (`$INSTANCE_NAME`_INTR_I2C_EC_REG)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptMode()                    (`$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG)
#define `$INSTANCE_NAME`_GetI2CExtClkInterruptSourceMasked()            (`$INSTANCE_NAME`_INTR_I2C_EC_MASKED_REG)

/* APIs to service INTR_SPI_EC register */
#define `$INSTANCE_NAME`_SetSpiExtClkInterruptMode(interruptMask)       `$INSTANCE_NAME`_WRITE_INTR_SPI_EC_MASK(interruptMask)
#define `$INSTANCE_NAME`_ClearSpiExtClkInterruptSource(interruptMask)   `$INSTANCE_NAME`_CLEAR_INTR_SPI_EC(interruptMask)
#define `$INSTANCE_NAME`_GetExtSpiClkInterruptSource()                  (`$INSTANCE_NAME`_INTR_SPI_EC_REG)
#define `$INSTANCE_NAME`_GetExtSpiClkInterruptMode()                    (`$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG)
#define `$INSTANCE_NAME`_GetExtSpiClkInterruptSourceMasked()            (`$INSTANCE_NAME`_INTR_SPI_EC_MASKED_REG)

/* Internal component APIs: NOT intended for customer use */
#define `$INSTANCE_NAME`_EnableRxInterrupt(sourceMask)              `$INSTANCE_NAME`_ENABLE_INTR_RX(sourceMask)
#define `$INSTANCE_NAME`_EnableTxInterrupt(sourceMask)              `$INSTANCE_NAME`_ENABLE_INTR_TX(sourceMask)
#define `$INSTANCE_NAME`_EnableMasterInterrupt(sourceMask)          `$INSTANCE_NAME`_ENABLE_INTR_MASTER(sourceMask)
#define `$INSTANCE_NAME`_EnableSlaveInterrupt(sourceMask)           `$INSTANCE_NAME`_ENABLE_INTR_SLAVE(sourceMask)
#define `$INSTANCE_NAME`_EnableI2CExtClkInterrupt(sourceMask)       `$INSTANCE_NAME`_ENABLE_INTR_I2C_EC(sourceMask)
#define `$INSTANCE_NAME`_EnableSpiExtClkInterrupt(sourceMask)       `$INSTANCE_NAME`_ENABLE_INTR_SPI_EC(sourceMask)

#define `$INSTANCE_NAME`_DisableRxInterrupt(sourceMask)             `$INSTANCE_NAME`_DISABLE_INTR_RX(sourceMask)
#define `$INSTANCE_NAME`_DisableTxInterrupt(sourceMask)             `$INSTANCE_NAME`_DISABLE_INTR_TX(sourceMask)
#define `$INSTANCE_NAME`_DisableMasterInterrupt(sourceMask)         `$INSTANCE_NAME`_DISABLE_INTR_MASTER(sourceMask)
#define `$INSTANCE_NAME`_DisableSlaveInterrupt(sourceMask)          `$INSTANCE_NAME`_DISABLE_INTR_SLAVE(sourceMask)
#define `$INSTANCE_NAME`_DisableI2CExtClkInterruptMode(sourceMask)  `$INSTANCE_NAME`_DISABLE_INTR_I2C_EC(sourceMask)
#define `$INSTANCE_NAME`_DisableSpiExtClkInterrupt(sourceMask)      `$INSTANCE_NAME`_DISABLE_INTR_SPI_EC(sourceMask)


/***************************************
*       Type defines
***************************************/

/* Structure to save registers before go to sleep */
typedef struct
{
    uint8 enableState;

} `$INSTANCE_NAME`_BACKUP_STRUCT;


/**********************************
*      Global veriables
**********************************/

extern uint8 `$INSTANCE_NAME`_initVar;

extern volatile uint32 `$INSTANCE_NAME`_scbMode;
extern volatile void * `$INSTANCE_NAME`_scbCfg;
extern void (* `$INSTANCE_NAME`_customIntrHandler) (void);
extern `$INSTANCE_NAME`_BACKUP_STRUCT `$INSTANCE_NAME`_backup;


/***************************************
*              Registers
***************************************/

#define `$INSTANCE_NAME`_CTRL_REG               (*(reg32 *) `$INSTANCE_NAME`_SCB__CTRL)
#define `$INSTANCE_NAME`_CTRL_PTR               ( (reg32 *) `$INSTANCE_NAME`_SCB__CTRL)

#define `$INSTANCE_NAME`_STATUS_REG             (*(reg32 *) `$INSTANCE_NAME`_SCB__STATUS)
#define `$INSTANCE_NAME`_STATUS_PTR             ( (reg32 *) `$INSTANCE_NAME`_SCB__STATUS)

#define `$INSTANCE_NAME`_SPI_CTRL_REG           (*(reg32 *) `$INSTANCE_NAME`_SCB__SPI_CTRL)
#define `$INSTANCE_NAME`_SPI_CTRL_PTR           ( (reg32 *) `$INSTANCE_NAME`_SCB__SPI_CTRL)

#define `$INSTANCE_NAME`_SPI_STATUS_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__SPI_STATUS)
#define `$INSTANCE_NAME`_SPI_STATUS_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__SPI_STATUS)

#define `$INSTANCE_NAME`_UART_CTRL_REG          (*(reg32 *) `$INSTANCE_NAME`_SCB__UART_CTRL)
#define `$INSTANCE_NAME`_UART_CTRL_PTR          ( (reg32 *) `$INSTANCE_NAME`_SCB__UART_CTRL)

#define `$INSTANCE_NAME`_UART_TX_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__UART_TX_CTRL)
#define `$INSTANCE_NAME`_UART_TX_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__UART_RX_CTRL)

#define `$INSTANCE_NAME`_UART_RX_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__UART_RX_CTRL)
#define `$INSTANCE_NAME`_UART_RX_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__UART_RX_CTRL)

#define `$INSTANCE_NAME`_UART_RX_STATUS_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__UART_RX_STATUS)
#define `$INSTANCE_NAME`_UART_RX_STATUS_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__UART_RX_STATUS)

#define `$INSTANCE_NAME`_I2C_CTRL_REG           (*(reg32 *) `$INSTANCE_NAME`_SCB__I2C_CTRL)
#define `$INSTANCE_NAME`_I2C_CTRL_PTR           ( (reg32 *) `$INSTANCE_NAME`_SCB__I2C_CTRL)

#define `$INSTANCE_NAME`_I2C_STATUS_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__I2C_STATUS)
#define `$INSTANCE_NAME`_I2C_STATUS_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__I2C_STATUS)

#define `$INSTANCE_NAME`_I2C_MASTER_CMD_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__I2C_M_CMD)
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__I2C_M_CMD)

#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_REG      (*(reg32 *) `$INSTANCE_NAME`_SCB__I2C_S_CMD)
#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_PTR      ( (reg32 *) `$INSTANCE_NAME`_SCB__I2C_S_CMD)

#define `$INSTANCE_NAME`_I2C_CFG_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__I2C_CFG)
#define `$INSTANCE_NAME`_I2C_CFG_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__I2C_CFG)

#define `$INSTANCE_NAME`_TX_CTRL_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__TX_CTRL)
#define `$INSTANCE_NAME`_TX_CTRL_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__TX_CTRL)

#define `$INSTANCE_NAME`_TX_FIFO_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_CTRL)
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_CTRL)

#define `$INSTANCE_NAME`_TX_FIFO_STATUS_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_STATUS)
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_STATUS)

#define `$INSTANCE_NAME`_TX_FIFO_WR_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_WR)
#define `$INSTANCE_NAME`_TX_FIFO_WR_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__TX_FIFO_WR)

#define `$INSTANCE_NAME`_RX_CTRL_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_CTRL)
#define `$INSTANCE_NAME`_RX_CTRL_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_CTRL)

#define `$INSTANCE_NAME`_RX_FIFO_CTRL_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_CTRL)
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_CTRL)

#define `$INSTANCE_NAME`_RX_FIFO_STATUS_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_STATUS)
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_STATUS)

#define `$INSTANCE_NAME`_RX_MATCH_REG           (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_MATCH)
#define `$INSTANCE_NAME`_RX_MATCH_PTR           ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_MATCH)

#define `$INSTANCE_NAME`_RX_FIFO_RD_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_RD)
#define `$INSTANCE_NAME`_RX_FIFO_RD_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_RD)

#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT_REG  (*(reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_RD_SILENT)
#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT_PTR  ( (reg32 *) `$INSTANCE_NAME`_SCB__RX_FIFO_RD_SILENT)

#define `$INSTANCE_NAME`_EZ_DATA_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__EZ_DATA00)
#define `$INSTANCE_NAME`_EZ_DATA_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__EZ_DATA00)

#define `$INSTANCE_NAME`_INTR_CAUSE_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_CAUSE)
#define `$INSTANCE_NAME`_INTR_CAUSE_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_CAUSE)

#define `$INSTANCE_NAME`_INTR_I2C_EC_REG        (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC)
#define `$INSTANCE_NAME`_INTR_I2C_EC_PTR        ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC)

#define `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG   (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC_MASK)
#define `$INSTANCE_NAME`_INTR_I2C_EC_MASK_PTR   ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC_MASK)

#define `$INSTANCE_NAME`_INTR_I2C_EC_MASKED_REG (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC_MASKED)
#define `$INSTANCE_NAME`_INTR_I2C_EC_MASKED_PTR ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_I2C_EC_MASKED)

#define `$INSTANCE_NAME`_INTR_SPI_EC_REG        (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC)
#define `$INSTANCE_NAME`_INTR_SPI_EC_PTR        ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC)

#define `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG   (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC_MASK)
#define `$INSTANCE_NAME`_INTR_SPI_EC_MASK_PTR   ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC_MASK)

#define `$INSTANCE_NAME`_INTR_SPI_EC_MASKED_REG (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC_MASKED)
#define `$INSTANCE_NAME`_INTR_SPI_EC_MASKED_PTR ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_SPI_EC_MASKED)

#define `$INSTANCE_NAME`_INTR_MASTER_REG        (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_M)
#define `$INSTANCE_NAME`_INTR_MASTER_PTR        ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_M)

#define `$INSTANCE_NAME`_INTR_MASTER_SET_REG    (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_SET)
#define `$INSTANCE_NAME`_INTR_MASTER_SET_PTR    ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_SET)

#define `$INSTANCE_NAME`_INTR_MASTER_MASK_REG   (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_MASK)
#define `$INSTANCE_NAME`_INTR_MASTER_MASK_PTR   ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_MASK)

#define `$INSTANCE_NAME`_INTR_MASTER_MASKED_REG (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_MASKED)
#define `$INSTANCE_NAME`_INTR_MASTER_MASKED_PTR ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_M_MASKED)

#define `$INSTANCE_NAME`_INTR_SLAVE_REG         (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_S)
#define `$INSTANCE_NAME`_INTR_SLAVE_PTR         ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_S)

#define `$INSTANCE_NAME`_INTR_SLAVE_SET_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_SET)
#define `$INSTANCE_NAME`_INTR_SLAVE_SET_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_SET)

#define `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG    (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_MASK)
#define `$INSTANCE_NAME`_INTR_SLAVE_MASK_PTR    ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_MASK)

#define `$INSTANCE_NAME`_INTR_SLAVE_MASKED_REG  (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_MASKED)
#define `$INSTANCE_NAME`_INTR_SLAVE_MASKED_PTR  ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_S_MASKED)

#define `$INSTANCE_NAME`_INTR_TX_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX)
#define `$INSTANCE_NAME`_INTR_TX_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX)

#define `$INSTANCE_NAME`_INTR_TX_SET_REG        (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_SET)
#define `$INSTANCE_NAME`_INTR_TX_SET_PTR        ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_SET)

#define `$INSTANCE_NAME`_INTR_TX_MASK_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_MASK)
#define `$INSTANCE_NAME`_INTR_TX_MASK_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_MASK)

#define `$INSTANCE_NAME`_INTR_TX_MASKED_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_MASKED)
#define `$INSTANCE_NAME`_INTR_TX_MASKED_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_TX_MASKED)

#define `$INSTANCE_NAME`_INTR_RX_REG            (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX)
#define `$INSTANCE_NAME`_INTR_RX_PTR            ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX)

#define `$INSTANCE_NAME`_INTR_RX_SET_REG        (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_SET)
#define `$INSTANCE_NAME`_INTR_RX_SET_PTR        ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_SET)

#define `$INSTANCE_NAME`_INTR_RX_MASK_REG       (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_MASK)
#define `$INSTANCE_NAME`_INTR_RX_MASK_PTR       ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_MASK)

#define `$INSTANCE_NAME`_INTR_RX_MASKED_REG     (*(reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_MASKED)
#define `$INSTANCE_NAME`_INTR_RX_MASKED_PTR     ( (reg32 *) `$INSTANCE_NAME`_SCB__INTR_RX_MASKED)


/***************************************
*        Registers Constants
***************************************/

/* `$INSTANCE_NAME`_CTRL */
#define `$INSTANCE_NAME`_CTRL_OVS__POS          (0u)  /* [3:0]   Oversampling factor                 */
#define `$INSTANCE_NAME`_CTRL_EC_AM_MODE__POS   (8u)  /* [8]     Externally clocked address match    */
#define `$INSTANCE_NAME`_CTRL_EC_OP_MODE__POS   (9u)  /* [9]     Externally clocked operation mode   */
#define `$INSTANCE_NAME`_CTRL_EZ_MODE__POS      (10u) /* [10]    EZ buffer is enabled                */
#define `$INSTANCE_NAME`_CTRL_ADDR_ACCEPT__POS  (16u) /* [16]    Put matched address in RX FIFO      */
#define `$INSTANCE_NAME`_CTRL_BLOCK__POS        (17u) /* [17]    Ext and Int logic to resolve colide */
#define `$INSTANCE_NAME`_CTRL_MODE__POS         (24u) /* [25:24] Operation mode                      */
#define `$INSTANCE_NAME`_CTRL_ENABLED__POS      (31u) /* [31]    Enable SCB block                    */
#define `$INSTANCE_NAME`_CTRL_OVS__MASK         ((uint32) (0x0Fu << `$INSTANCE_NAME`_CTRL_OVS__POS))
#define `$INSTANCE_NAME`_CTRL_EC_AM_MODE        ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_EC_AM_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_EC_OP_MODE        ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_EC_OP_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_EZ_MODE           ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_EZ_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_ADDR_ACCEPT       ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_ADDR_ACCEPT__POS))
#define `$INSTANCE_NAME`_CTRL_BLOCK             ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_BLOCK__POS))
#define `$INSTANCE_NAME`_CTRL_MODE__MASK        ((uint32) (0x03u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_MODE_I2C          ((uint32) (0x00u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_MODE_SPI          ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_MODE_UART         ((uint32) (0x02u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_CTRL_ENABLED           ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_ENABLED__POS))


/* `$INSTANCE_NAME`_STATUS_REG */
#define `$INSTANCE_NAME`_STATUS_EC_BUSY__POS    (0u)  /* [0] Bus busy. Externaly clocked loigc access to EZ memory */
#define `$INSTANCE_NAME`_STATUS_EC_BUSY         ((uint32) (0x0Fu << `$INSTANCE_NAME`_STATUS_EC_BUSY__POS))


/* `$INSTANCE_NAME`_SPI_CTRL_REG  */
#define `$INSTANCE_NAME`_SPI_CTRL_CONTINUOUS__POS       (0u)  /* [0]     Continuous or Separated SPI data transfers */
#define `$INSTANCE_NAME`_SPI_CTRL_SELECT_PRECEDE__POS   (1u)  /* [1]     Precedes or coincides start of data frame  */
#define `$INSTANCE_NAME`_SPI_CTRL_CPHA__POS             (2u)  /* [2]     SCLK phase                                 */
#define `$INSTANCE_NAME`_SPI_CTRL_CPOL__POS             (3u)  /* [3]     SCLK polarity                              */
#define `$INSTANCE_NAME`_SPI_CTRL_LATE_MISO_SAMPLE__POS (4u)  /* [4]     Late MISO sample enabled                   */
#define `$INSTANCE_NAME`_SPI_CTRL_LOOPBACK__POS         (16u) /* [16]    Local loopback control enabled             */
#define `$INSTANCE_NAME`_SPI_CTRL_MODE__POS             (24u) /* [25:24] Submode of SPI operation                   */
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS     (26u) /* [27:26] Selects SPI SS signal                      */
#define `$INSTANCE_NAME`_SPI_CTRL_MASTER_MODE__POS      (31u) /* [31]    Master mode enabled                        */
#define `$INSTANCE_NAME`_SPI_CTRL_CONTINUOUS            ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_CONTINUOUS__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SELECT_PRECEDE        ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_SELECT_PRECEDE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_CPHA                  ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_CPHA__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_CPOL                  ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_CPOL__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_LATE_MISO_SAMPLE      ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_LATE_MISO_SAMPLE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_LOOPBACK              ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_LOOPBACK__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_MODE__MASK            ((uint32) (0x03u << `$INSTANCE_NAME`_SPI_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_MODE_MOTOROLA         ((uint32) (0x00u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_MODE_TI               ((uint32) (0x01u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_MODE_NS               ((uint32) (0x02u << `$INSTANCE_NAME`_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__MASK    ((uint32) (0x03u << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT0         ((uint32) (0x00u << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT1         ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT2         ((uint32) (0x02u << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT3         ((uint32) (0x03u << `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_MASTER                ((uint32) (0x01u << `$INSTANCE_NAME`_SPI_CTRL_MASTER_MODE__POS))
#define `$INSTANCE_NAME`_SPI_CTRL_SLAVE                 ((uint32) (0x00u << `$INSTANCE_NAME`_SPI_CTRL_MASTER_MODE__POS))


/* `$INSTANCE_NAME`_SPI_STATUS_REG  */
#define `$INSTANCE_NAME`_SPI_STATUS_BUS_BUSY__POS   (0u)  /* [0]    Bus busy - slave selected */
#define `$INSTANCE_NAME`_SPI_STATUS_EZ_ADDR__POS    (8u)  /* [15:8] EzAddress                 */

#define `$INSTANCE_NAME`_SPI_STATUS_BUS_BUSY        ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY__POS))
#define `$INSTANCE_NAME`_SPI_STATUS_EZ_ADDR__MASK   ((uint32) (0xFFu << `$INSTANCE_NAME`_I2C_STATUS_EZ_ADDR__POS))


/* `$INSTANCE_NAME`_UART_CTRL */
#define `$INSTANCE_NAME`_UART_CTRL_LOOPBACK__POS    (16u) /* [16] Loopback     */
#define `$INSTANCE_NAME`_UART_CTRL_MODE__POS        (24u) /* [24] UART subMode */

#define `$INSTANCE_NAME`_UART_CTRL_LOOPBACK             ((uint32) (0x01u << `$INSTANCE_NAME`_UART_CTRL_LOOPBACK__POS))
#define `$INSTANCE_NAME`_UART_CTRL_MODE_UART_STD        ((uint32) (0x00u << `$INSTANCE_NAME`_UART_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_UART_CTRL_MODE_UART_SMARTCARD  ((uint32) (0x01u << `$INSTANCE_NAME`_UART_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_UART_CTRL_MODE_UART_IRDA       ((uint32) (0x02u << `$INSTANCE_NAME`_UART_CTRL_MODE__POS))
#define `$INSTANCE_NAME`_UART_CTRL_MODE__MASK           ((uint32) (0x03u << `$INSTANCE_NAME`_UART_CTRL_MODE__POS))


/* `$INSTANCE_NAME`_UART_TX_CTRL */
#define `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS        (0u)  /* Stop bits: (Stop bits + 1) * 0.5 period */
#define `$INSTANCE_NAME`_UART_TX_CTRL_PARITY__POS           (4u)  /* Parity bit                              */
#define `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED__POS   (5u)  /* Parity enable                           */
#define `$INSTANCE_NAME`_UART_TX_CTRL_RETRY_ON_NACK__POS    (8u)  /* Smart Card: re-send frame on NACK       */
#define `$INSTANCE_NAME`_UART_TX_CTRL_ONE_STOP_BIT          ((uint32) (0x01u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_ONE_HALF_STOP_BITS    ((uint32) (0x02u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_TWO_STOP_BITS         ((uint32) (0x03u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__MASK       ((uint32) (0x07u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_PARITY                ((uint32) (0x01u << `$INSTANCE_NAME`_UART_TX_CTRL_PARITY__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED        ((uint32) (0x01u << `$INSTANCE_NAME`_UART_TX_CTRL_PARITY_ENABLED__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_RETRY_ON_NACK         ((uint32) (0x01u << `$INSTANCE_NAME`_UART_TX_CTRL_RETRY_ON_NACK__POS))


/* `$INSTANCE_NAME`_UART_RX_CTRL */
#define `$INSTANCE_NAME`_UART_RX_CTRL_STOP_BITS__POS            (0u)  /* Stop bits: (Stop bits + 1) * 0.5 period     */
#define `$INSTANCE_NAME`_UART_RX_CTRL_PARITY__POS               (4u)  /* Parity bit                                  */
#define `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED__POS       (5u)  /* Parity enable                               */
#define `$INSTANCE_NAME`_UART_RX_CTRL_POLARITY__POS             (6u)  /* IrDA: inverts polarity of incomming signal  */
#define `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_PARITY_ERR__POS   (8u)  /* Drop and lost RX FIFO on parity error       */
#define `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_FRAME_ERR__POS    (9u)  /* Drop and lost RX FIFO on frame error        */
#define `$INSTANCE_NAME`_UART_RX_CTRL_MP_MODE__POS              (10u) /* Multi-processor mode                        */
#define `$INSTANCE_NAME`_UART_RX_CTRL_LIN_MODE__POS             (12u) /* Lin mode: only applicable for UART Standart */
#define `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START__POS           (13u) /* Skip start not: only for UART Standart      */
#define `$INSTANCE_NAME`_UART_RX_CTRL_BREAK_WIDTH__POS          (16u) /* Break width: (Break width + 1)              */
#define `$INSTANCE_NAME`_UART_TX_CTRL_ONE_STOP_BIT              ((uint32) (0x01u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_ONE_HALF_STOP_BITS        ((uint32) (0x02u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_TX_CTRL_TWO_STOP_BITS             ((uint32) (0x03u << `$INSTANCE_NAME`_UART_TX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_STOP_BITS__MASK           ((uint32) (0x07u << `$INSTANCE_NAME`_UART_RX_CTRL_STOP_BITS__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_PARITY                    ((uint32) (0x01u << `$INSTANCE_NAME`_UART_RX_CTRL_PARITY__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED            ((uint32) (0x01u << \
                                                                  `$INSTANCE_NAME`_UART_RX_CTRL_PARITY_ENABLED__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_POLARITY                  ((uint32) (0x01u << `$INSTANCE_NAME`_UART_RX_CTRL_POLARITY__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_PARITY_ERR        ((uint32) (0x01u << \
                                                                  `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_PARITY_ERR__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_FRAME_ERR         ((uint32) (0x01u << \
                                                                  `$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_FRAME_ERR__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_MP_MODE                   ((uint32) (0x01u << `$INSTANCE_NAME`_UART_RX_CTRL_MP_MODE__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_LIN_MODE                  ((uint32) (0x01u << `$INSTANCE_NAME`_UART_RX_CTRL_LIN_MODE__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START                ((uint32) (0x01u << \
                                                                  `$INSTANCE_NAME`_UART_RX_CTRL_SKIP_START__POS))
#define `$INSTANCE_NAME`_UART_RX_CTRL_BREAK_WIDTH__MASK         ((uint32) (0x0Fu << \
                                                                  `$INSTANCE_NAME`_UART_RX_CTRL_BREAK_WIDTH__POS))

/* `$INSTANCE_NAME`_UART_RX_STATUS_REG */
#define `$INSTANCE_NAME`_UART_RX_STATUS_BR_COUNTER__POS     (0u)  /* Baute Rate counter */
#define `$INSTANCE_NAME`_UART_RX_STATUS_BR_COUNTER__MASK    ((uint32) (0xFFFu << `$INSTANCE_NAME`_UART_RX_CTRL_BREAK_WIDTH__POS))


/* `$INSTANCE_NAME`_I2C_CTRL */
#define `$INSTANCE_NAME`_I2C_CTRL_HIGH_PHASE_OVS__POS           (0u)   /* [3:0] Oversampling factor high: masrer only */
#define `$INSTANCE_NAME`_I2C_CTRL_LOW_PHASE_OVS__POS            (4u)   /* [7:4] Oversampling factor low:  masrer only */
#define `$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK__POS         (8u)   /* [8]   Master ACKs data wgile RX FIFO != FULL*/
#define `$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK__POS    (9u)   /* [9]   Master NACKs data if RX FIFO ==  FULL */
#define `$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE__POS         (11u)  /* [11]  Slave ignores General call            */
#define `$INSTANCE_NAME`_I2C_CTRL_S_READY_ADDR_ACK__POS         (12u)  /* [12]  Slave ACKs Address if RX FIFO != FULL */
#define `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK__POS         (13u)  /* [13]  Slave ACKs data while RX FIFO == FULL */
#define `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK__POS    (14u)  /* [14]  Slave NACKs address if RX FIFO == FULL*/
#define `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK__POS    (15u)  /* [15]  Slave NACKs data if RX FIFO is  FULL  */
#define `$INSTANCE_NAME`_I2C_CTRL_LOOPBACK__POS                 (16u)  /* [16]  Loopback                              */
#define `$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE__POS               (30u)  /* [30]  Slave mode enabled                    */
#define `$INSTANCE_NAME`_I2C_CTRL_MASTER_MODE__POS              (31u)  /* [31]  Master mode enabled                   */
#define `$INSTANCE_NAME`_I2C_CTRL_HIGH_PHASE_OVS__MASK          ((uint32) (0x0Fu << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_HIGH_PHASE_OVS__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_LOW_PHASE_OVS__MASK           ((uint32) (0x0Fu << `$INSTANCE_NAME`_I2C_CTRL_LOW_PHASE_OVS__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK              ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK         ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE              ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_GENERAL_IGNORE__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_S_READY_ADDR_ACK              ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_READY_ADDR_ACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK              ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK         ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK         ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_LOOPBACK                      ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_CTRL_LOOPBACK__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE                    ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE__POS))
#define `$INSTANCE_NAME`_I2C_CTRL_MASTER_MODE                   ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_CTRL_MASTER_MODE__POS))


/* `$INSTANCE_NAME`_I2C_STATUS_REG  */
#define `$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY__POS   (0u)  /* [0]    Bus busy: internally clocked */
#define `$INSTANCE_NAME`_I2C_STATUS_S_READ__POS     (4u)  /* [4]    Slave is read by master      */
#define `$INSTANCE_NAME`_I2C_STATUS_M_READ__POS     (5u)  /* [5]    Master reads Slave           */
#define `$INSTANCE_NAME`_I2C_STATUS_EZ_ADDR__POS    (8u)  /* [15:8] EZAddress                    */
#define `$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY        ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY__POS))
#define `$INSTANCE_NAME`_I2C_STATUS_S_READ          ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_STATUS_S_READ__POS))
#define `$INSTANCE_NAME`_I2C_STATUS_M_READ          ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_STATUS_M_READ__POS))
#define `$INSTANCE_NAME`_I2C_STATUS_EZ_ADDR__MASK   ((uint32) (0xFFu << `$INSTANCE_NAME`_I2C_STATUS_EZ_ADDR__POS))


/* `$INSTANCE_NAME`_I2C_MASTER_CMD_REG */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START__POS            (0u)  /* [0] Master generate Start                */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE__POS    (1u)  /* [1] Master generate Start if bus is free */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_ACK__POS              (2u)  /* [2] Master generate ACK                  */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK__POS             (3u)  /* [3] Master generate NACK                 */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_STOP__POS             (4u)  /* [4] Master generate Stop                 */
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START                 ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START__POS))
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE         ((uint32) (0x01u << \
                                                                   `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE__POS))
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_ACK                   ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_MASTER_CMD_M_ACK__POS))
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK                  ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK__POS))
#define `$INSTANCE_NAME`_I2C_MASTER_CMD_M_STOP                  ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_MASTER_CMD_M_STOP__POS))


/* `$INSTANCE_NAME`_I2C_SLAVE_CMD_REG  */
#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_ACK__POS   (0u)  /* [0] Slave generate ACK  */
#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_NACK__POS  (1u)  /* [1] Slave generate NACK */
#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_ACK        ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_ACK__POS))
#define `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_NACK       ((uint32) (0x01u << `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_NACK__POS))


/* `$INSTANCE_NAME`_TX_CTRL_REG */
#define `$INSTANCE_NAME`_TX_CTRL_DATA_WIDTH__POS    (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST__POS     (8u)  /* [8]   MSB first shifter-out             */
#define `$INSTANCE_NAME`_TX_CTRL_ENABLED__POS       (31u) /* [31]  Transmitter enabled               */
#define `$INSTANCE_NAME`_TX_CTRL_DATA_WIDTH_MASK    ((uint32) (0x0Fu << `$INSTANCE_NAME`_TX_CTRL_DATA_WIDTH__POS))
#define `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST          ((uint32) (0x01u << `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST__POS))
#define `$INSTANCE_NAME`_TX_CTRL_LSB_FIRST          ((uint32) (0x00u << `$INSTANCE_NAME`_TX_CTRL_MSB_FIRST__POS))
#define `$INSTANCE_NAME`_TX_CTRL_ENABLED            ((uint32) (0x01u << `$INSTANCE_NAME`_TX_CTRL_ENABLED__POS))


/* `$INSTANCE_NAME`_TX_CTRL_FIFO_REG */
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_TRIGGER_LEVEL__POS    (0u)  /* [2:0] Trigger level                              */
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_CLEAR__POS            (16u) /* [16]  Clear TX FIFO: claared after set           */
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_FREEZE__POS           (17u) /* [17]  Freeze TX FIFO: HW do not inc read pointer */
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_TX_FIFO_CTRL_TRIGGER_LEVEL__POS))
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_CLEAR                 ((uint32) (0x01u << `$INSTANCE_NAME`_TX_FIFO_CTRL_CLEAR__POS))
#define `$INSTANCE_NAME`_TX_FIFO_CTRL_FREEZE                ((uint32) (0x01u << `$INSTANCE_NAME`_TX_FIFO_CTRL_FREEZE__POS))


/* `$INSTANCE_NAME`_TX_FIFO_STATUS_REG */
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_USED__POS       (0u)  /* [3:0]   Amount of entries in TX FIFO */
#define `$INSTANCE_NAME`_TX_FIFO_SR_VALID__POS          (15u) /* [15]    Shifter status of TX FIFO    */
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_RD_PTR__POS     (16u) /* [18:16] TX FIFO read pointer         */
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_WR_PTR__POS     (24u) /* [26:24] TX FIFO write pointer        */
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_USED__MASK      ((uint32) (0x0Fu << `$INSTANCE_NAME`_TX_FIFO_STATUS_USED__POS))
#define `$INSTANCE_NAME`_TX_FIFO_SR_VALID               ((uint32) (0x01u << `$INSTANCE_NAME`_TX_FIFO_SR_VALID__POS))
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_RD_PTR__MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_TX_FIFO_STATUS_RD_PTR__POS))
#define `$INSTANCE_NAME`_TX_FIFO_STATUS_WR_PTR__MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_TX_FIFO_STATUS_WR_PTR__POS))


/* `$INSTANCE_NAME`_TX_FIFO_WR_REG */
#define `$INSTANCE_NAME`_TX_FIFO_WR__POS    (0u)  /* [15:0] Data written into TX FIFO */
#define `$INSTANCE_NAME`_TX_FIFO_WR__MASK   ((uint32) (0xFFu << `$INSTANCE_NAME`_TX_FIFO_WR__POS))


/* `$INSTANCE_NAME`_RX_CTRL_REG */
#define `$INSTANCE_NAME`_RX_CTRL_DATA_WIDTH__POS    (0u)  /* [3:0] Dataframe width: (Data width - 1) */
#define `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST__POS     (8u)  /* [8]   MSB first shifter-out             */
#define `$INSTANCE_NAME`_RX_CTRL_MEDIAN__POS        (9u)  /* [9]   Median filter                     */
#define `$INSTANCE_NAME`_RX_CTRL_ENABLED__POS       (31u) /* [31]  Receiver enabled                  */
#define `$INSTANCE_NAME`_RX_CTRL_DATA_WIDTH__MASK   ((uint32) (0x0Fu << `$INSTANCE_NAME`_RX_CTRL_DATA_WIDTH__POS))
#define `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST          ((uint32) (0x01u << `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST__POS))
#define `$INSTANCE_NAME`_RX_CTRL_LSB_FIRST          ((uint32) (0x00u << `$INSTANCE_NAME`_RX_CTRL_MSB_FIRST__POS))
#define `$INSTANCE_NAME`_RX_CTRL_MEDIAN             ((uint32) (0x01u << `$INSTANCE_NAME`_RX_CTRL_MEDIAN__POS))
#define `$INSTANCE_NAME`_RX_CTRL_ENABLED            ((uint32) (0x01u << `$INSTANCE_NAME`_RX_CTRL_ENABLED__POS))


/* `$INSTANCE_NAME`_RX_FIFO_CTRL_REG */
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_TRIGGER_LEVEL__POS    (0u)   /* [2:0] Trigger level                            */
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_CLEAR__POS            (16u)  /* [16]  Clear RX FIFO: claar after set           */
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_FREEZE__POS           (17u)  /* [17]  Freeze RX FIFO: HW writes has not effect */
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_TRIGGER_LEVEL_MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_RX_FIFO_CTRL_TRIGGER_LEVEL__POS))
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_CLEAR                 ((uint32) (0x01u << `$INSTANCE_NAME`_RX_FIFO_CTRL_CLEAR__POS))
#define `$INSTANCE_NAME`_RX_FIFO_CTRL_FREEZE                ((uint32) (0x01u << `$INSTANCE_NAME`_RX_FIFO_CTRL_FREEZE__POS))


/* `$INSTANCE_NAME`_RX_FIFO_STATUS_REG */
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_USED__POS       (0u)   /* [3:0]   Amount of entries in RX FIFO */
#define `$INSTANCE_NAME`_RX_FIFO_SR_VALID__POS          (15u)  /* [15]    Shifter status of RX FIFO    */
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_RD_PTR__POS     (16u)  /* [18:16] RX FIFO read pointer         */
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_WR_PTR__POS     (24u)  /* [26:24] RX FIFO write pointer        */
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_USED__MASK      ((uint32) (0x0Fu << `$INSTANCE_NAME`_RX_FIFO_STATUS_USED__POS))
#define `$INSTANCE_NAME`_RX_FIFO_SR_VALID               ((uint32) (0x01u << `$INSTANCE_NAME`_RX_FIFO_SR_VALID__POS))
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_RD_PTR__MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_RX_FIFO_STATUS_RD_PTR__POS))
#define `$INSTANCE_NAME`_RX_FIFO_STATUS_WR_PTR__MASK    ((uint32) (0x07u << `$INSTANCE_NAME`_RX_FIFO_STATUS_WR_PTR__POS))


/* `$INSTANCE_NAME`_RX_MATCH_REG */
#define `$INSTANCE_NAME`_RX_MATCH_ADDR__POS     (0u)  /* [7:0]   Slave address                        */
#define `$INSTANCE_NAME`_RX_MATCH_MASK__POS     (16u) /* [23:16] Slave address mask: 0 - doesn't care */
#define `$INSTANCE_NAME`_RX_MATCH_ADDR__MASK    ((uint32) (0xFFu << `$INSTANCE_NAME`_RX_MATCH_ADDR__POS))
#define `$INSTANCE_NAME`_RX_MATCH_MASK__MASK    ((uint32) (0xFFu << `$INSTANCE_NAME`_RX_MATCH_MASK__POS))


/* `$INSTANCE_NAME`_RX_FIFO_WR_REG */
#define `$INSTANCE_NAME`_RX_FIFO_RD__POS    (0u)  /* [15:0] Data read from RX FIFO */
#define `$INSTANCE_NAME`_RX_FIFO_RD__MASK   ((uint32) (0xFFu << `$INSTANCE_NAME`_RX_FIFO_RD__POS))


/* `$INSTANCE_NAME`_RX_FIFO_RD_SILENT_REG */
#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__MASK    ((uint32) (0xFFu << `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__POS))

/* `$INSTANCE_NAME`_RX_FIFO_RD_SILENT_REG */
#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__POS     (0u)  /* [15:0] Data read from RX FIFO: not remove data from FIFO */
#define `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__MASK    ((uint32) (0xFFu << `$INSTANCE_NAME`_RX_FIFO_RD_SILENT__POS))

/* `$INSTANCE_NAME`_EZ_DATA_REG */
#define `$INSTANCE_NAME`_EZ_DATA__POS   (0u)  /* [7:0] Data from Ez Memory */
#define `$INSTANCE_NAME`_EZ_DATA__MASK  ((uint32) (0xFFu << `$INSTANCE_NAME`_EZ_DATA__POS))

/*  `$INSTANCE_NAME`_INTR_CAUSE_REG */
#define `$INSTANCE_NAME`_INTR_CAUSE_MASTER__POS (0u)  /* [0] Master interrupt active                 */
#define `$INSTANCE_NAME`_INTR_CAUSE_SLAVE__POS  (1u)  /* [1] Slave interrupt active                  */
#define `$INSTANCE_NAME`_INTR_CAUSE_TX__POS     (2u)  /* [2] Transmitter interrupt active            */
#define `$INSTANCE_NAME`_INTR_CAUSE_RX__POS     (3u)  /* [3] Receiver interrupt active               */
#define `$INSTANCE_NAME`_INTR_CAUSE_I2C_EC__POS (4u)  /* [4] Externally clock I2C interrupt active   */
#define `$INSTANCE_NAME`_INTR_CAUSE_SPI_EC__POS (5u)  /* [5] Externally clocked SPI interrupt active */
#define `$INSTANCE_NAME`_INTR_CAUSE_MASTER      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_MASTER__POS))
#define `$INSTANCE_NAME`_INTR_CAUSE_SLAVE       ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_SLAVE__POS))
#define `$INSTANCE_NAME`_INTR_CAUSE_TX          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_TX__POS))
#define `$INSTANCE_NAME`_INTR_CAUSE_RX          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_RX__POS))
#define `$INSTANCE_NAME`_INTR_CAUSE_I2C_EC      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_I2C_EC__POS))
#define `$INSTANCE_NAME`_INTR_CAUSE_SPI_EC      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_CAUSE_SPI_EC__POS))


/* `$INSTANCE_NAME`_INTR_SPI_EC_REG, `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG, `$INSTANCE_NAME`_INTR_SPI_EC_MASKED_REG */
#define `$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP__POS       (0u)  /* [0] Address match: triggers wakeup of chip */
#define `$INSTANCE_NAME`_INTR_SPI_EC_EZ_STOP__POS       (1u)  /* [1] Externally clocked Stop detected       */
#define `$INSTANCE_NAME`_INTR_SPI_EC_EZ_WRITE_STOP__POS (2u)  /* [2] Externally clocked Write Stop detected */
#define `$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP__POS))
#define `$INSTANCE_NAME`_INTR_SPI_EC_EZ_STOP            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SPI_EC_EZ_STOP__POS))
#define `$INSTANCE_NAME`_INTR_SPI_EC_EZ_WRITE_STOP      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SPI_EC_EZ_WRITE_STOP__POS))


/* `$INSTANCE_NAME`_INTR_I2C_EC, `$INSTANCE_NAME`_INTR_I2C_EC_MASK, `$INSTANCE_NAME`_INTR_I2C_EC_MASKED */
#define `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP__POS       (0u)  /* [0] Address match: triggers wakeup of chip */
#define `$INSTANCE_NAME`_INTR_I2C_EC_EZ_STOP__POS       (1u)  /* [1] Externally clocked Stop detected       */
#define `$INSTANCE_NAME`_INTR_I2C_EC_EZ_WRITE_STOP__POS (2u)  /* [2] Externally clocked Write Stop detected */
#define `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP__POS))
#define `$INSTANCE_NAME`_INTR_I2C_EC_EZ_STOP            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_I2C_EC_EZ_STOP__POS))
#define `$INSTANCE_NAME`_INTR_I2C_EC_EZ_WRITE_STOP      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_I2C_EC_EZ_WRITE_STOP__POS))


/* `$INSTANCE_NAME`_INTR_MASTER, `$INSTANCE_NAME`_INTR_MASTER_SET,
   `$INSTANCE_NAME`_INTR_MASTER_MASK, `$INSTANCE_NAME`_INTR_MASTER_MASKED */
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST__POS  (0u)  /* [0] Master lost arbitration                          */
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK__POS      (1u)  /* [1] Master receives NACK: address or write to slave  */
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_ACK__POS       (2u)  /* [2] Master receives NACK: address or write to slave  */
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP__POS      (4u)  /* [4] Master detects the Stop: only self generated Stop*/
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR__POS (8u)  /* [8] Master detects bus error: misplaced Start or Stop*/
#define `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE__POS      (9u)  /* [9] Master complete trasfer: Only for SPI            */
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST       ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST__POS))
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK__POS))
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_ACK            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_I2C_ACK__POS))
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP__POS))
#define `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR__POS))
#define `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE__POS))

/* `$INSTANCE_NAME`_INTR_SLAVE, `$INSTANCE_NAME`_INTR_SLAVE_SET,
   `$INSTANCE_NAME`_INTR_SLAVE_MASK, `$INSTANCE_NAME`_INTR_SLAVE_MASKED */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST__POS       (0u)  /* [0]  Slave lost arbitration                   */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK__POS           (1u)  /* [1]  Slave receives NACK: master reads data   */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ACK__POS            (2u)  /* [2]  Slave receives ACK: master reads data    */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP__POS     (3u)  /* [3]  Slave detects end of write transaction   */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP__POS           (4u)  /* [4]  Slave detects end of transaction intened */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_START__POS          (5u)  /* [5]  Slave detects Start                      */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH__POS     (6u)  /* [6]  Slave address matches                    */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_GENERAL__POS        (7u)  /* [7]  General call received                    */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR__POS      (8u)  /* [8]  Slave detects bus error                  */
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_WRITE_STOP__POS  (9u)  /* [9]  Slave write complete: Only for SPI       */
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_STOP__POS        (10u) /* [10] Slave end of transaciton: Only for SPI   */
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR__POS      (11u) /* [11] Slave detects bus error: Only for SPI    */
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK                ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ACK                 ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_ACK__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP                ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_START               ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_START__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_GENERAL             ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_GENERAL__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_WRITE_STOP       ((uint32) (0x01u << \
                                                                `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_WRITE_STOP__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_STOP             ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_STOP__POS))
#define `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR__POS))


/* `$INSTANCE_NAME`_INTR_TX, `$INSTANCE_NAME`_INTR_TX_SET,
   `$INSTANCE_NAME`_INTR_TX_MASK, `$INSTANCE_NAME`_INTR_TX_MASKED */
#define `$INSTANCE_NAME`_INTR_TX_TRIGGER__POS       (0u)  /* [0]  Trigger on TX FIFO entires                       */
#define `$INSTANCE_NAME`_INTR_TX_NOT_FULL__POS      (1u)  /* [1]  TX FIFO is not full                              */
#define `$INSTANCE_NAME`_INTR_TX_EMPTY__POS         (4u)  /* [4]  TX FIFO is empty                                 */
#define `$INSTANCE_NAME`_INTR_TX_OVERFLOW__POS      (5u)  /* [5]  Attempt to write to a full TX FIFO               */
#define `$INSTANCE_NAME`_INTR_TX_UNDERFLOW__POS     (6u)  /* [6]  Attempt to read from an empty TX FIFO            */
#define `$INSTANCE_NAME`_INTR_TX_BLOCKED__POS       (7u)  /* [7]  No access to the EZ memory                       */
#define `$INSTANCE_NAME`_INTR_TX_UART_NACK__POS     (8u)  /* [8]  UART transmitter received a NACK: SmartCard mode */
#define `$INSTANCE_NAME`_INTR_TX_UART_DONE__POS     (9u)  /* [9]  UART transmitter done even                       */
#define `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST__POS (10u) /* [10] UART lost arbitration: LIN or SmartCard          */
#define `$INSTANCE_NAME`_INTR_TX_TRIGGER            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_TRIGGER__POS))
#define `$INSTANCE_NAME`_INTR_TX_NOT_FULL           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_NOT_FULL__POS))
#define `$INSTANCE_NAME`_INTR_TX_EMPTY              ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_EMPTY__POS))
#define `$INSTANCE_NAME`_INTR_TX_OVERFLOW           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_OVERFLOW__POS))
#define `$INSTANCE_NAME`_INTR_TX_UNDERFLOW          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_UNDERFLOW__POS))
#define `$INSTANCE_NAME`_INTR_TX_BLOCKED            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_BLOCKED__POS))
#define `$INSTANCE_NAME`_INTR_TX_UART_NACK          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_UART_NACK__POS))
#define `$INSTANCE_NAME`_INTR_TX_UART_DONE          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_UART_DONE__POS))
#define `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST      ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST__POS))


/* `$INSTANCE_NAME`_INTR_RX, `$INSTANCE_NAME`_INTR_RX_SET,
   `$INSTANCE_NAME`_INTR_RX_MASK, `$INSTANCE_NAME`_INTR_RX_MASKED */
#define `$INSTANCE_NAME`_INTR_RX_TRIGGER__POS       (0u)   /* [0]  Trigger on RX FIFO entires            */
#define `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY__POS     (2u)   /* [2]  RX FIFO is not empty                  */
#define `$INSTANCE_NAME`_INTR_RX_FULL__POS          (3u)   /* [3]  RX FIFO is full                       */
#define `$INSTANCE_NAME`_INTR_RX_OVERFLOW__POS      (5u)   /* [5]  Attempt to write to a full RX FIFO    */
#define `$INSTANCE_NAME`_INTR_RX_UNDERFLOW__POS     (6u)   /* [6]  Attempt to read from an empty RX FIFO */
#define `$INSTANCE_NAME`_INTR_RX_BLOCKED__POS       (7u)   /* [7]  No access to the EZ memory            */
#define `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR__POS   (8u)   /* [8]  Frame error in received data frame    */
#define `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR__POS  (9u)   /* [9]  Parity error in received data frame   */
#define `$INSTANCE_NAME`_INTR_RX_BAUD_DETECT__POS   (10u)  /* [10] LIN baudrate detection is completed   */
#define `$INSTANCE_NAME`_INTR_RX_BREAK_DETECT__POS  (11u)  /* [11] Break detection is successful         */
#define `$INSTANCE_NAME`_INTR_RX_TRIGGER            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_TRIGGER__POS))
#define `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY__POS))
#define `$INSTANCE_NAME`_INTR_RX_FULL               ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_FULL__POS))
#define `$INSTANCE_NAME`_INTR_RX_OVERFLOW           ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_OVERFLOW__POS))
#define `$INSTANCE_NAME`_INTR_RX_UNDERFLOW          ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_UNDERFLOW__POS))
#define `$INSTANCE_NAME`_INTR_RX_BLOCKED            ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_BLOCKED__POS))
#define `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR        ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR__POS))
#define `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR       ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR__POS))
#define `$INSTANCE_NAME`_INTR_RX_BAUD_DETECT        ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_BAUD_DETECT__POS))
#define `$INSTANCE_NAME`_INTR_RX_BREAK_DETECT       ((uint32) (0x01u << `$INSTANCE_NAME`_INTR_RX_BREAK_DETECT__POS))


/* Define all interupt soureces */
#define `$INSTANCE_NAME`_INTR_I2C_EC_ALL    (`$INSTANCE_NAME`_INTR_I2C_EC_WAKE_UP | \
                                             `$INSTANCE_NAME`_INTR_I2C_EC_EZ_STOP | \
                                             `$INSTANCE_NAME`_INTR_I2C_EC_EZ_WRITE_STOP)

#define `$INSTANCE_NAME`_INTR_SPI_EC_ALL    (`$INSTANCE_NAME`_INTR_SPI_EC_WAKE_UP | \
                                             `$INSTANCE_NAME`_INTR_SPI_EC_EZ_STOP | \
                                             `$INSTANCE_NAME`_INTR_SPI_EC_EZ_WRITE_STOP)

#define `$INSTANCE_NAME`_INTR_MASTER_ALL    (`$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST  | \
                                             `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK      | \
                                             `$INSTANCE_NAME`_INTR_MASTER_I2C_ACK       | \
                                             `$INSTANCE_NAME`_INTR_MASTER_I2C_STOP      | \
                                             `$INSTANCE_NAME`_INTR_MASTER_I2C_BUS_ERROR | \
                                             `$INSTANCE_NAME`_INTR_MASTER_SPI_DONE )

#define `$INSTANCE_NAME`_INTR_SLAVE_ALL     (`$INSTANCE_NAME`_INTR_SLAVE_I2C_ARB_LOST      | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_NACK          | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_ACK           | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_WRITE_STOP    | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_STOP          | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_START         | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_ADDR_MATCH    | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_GENERAL       | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_I2C_BUS_ERROR     | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_WRITE_STOP | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_SPI_EZ_STOP       | \
                                             `$INSTANCE_NAME`_INTR_SLAVE_SPI_BUS_ERROR)

#define `$INSTANCE_NAME`_INTR_TX_ALL        (`$INSTANCE_NAME`_INTR_TX_TRIGGER   | \
                                             `$INSTANCE_NAME`_INTR_TX_NOT_FULL  | \
                                             `$INSTANCE_NAME`_INTR_TX_EMPTY     | \
                                             `$INSTANCE_NAME`_INTR_TX_OVERFLOW  | \
                                             `$INSTANCE_NAME`_INTR_TX_UNDERFLOW | \
                                             `$INSTANCE_NAME`_INTR_TX_BLOCKED   | \
                                             `$INSTANCE_NAME`_INTR_TX_UART_NACK | \
                                             `$INSTANCE_NAME`_INTR_TX_UART_DONE | \
                                             `$INSTANCE_NAME`_INTR_TX_UART_ARB_LOST)

#define `$INSTANCE_NAME`_INTR_RX_ALL        (`$INSTANCE_NAME`_INTR_RX_TRIGGER      | \
                                             `$INSTANCE_NAME`_INTR_RX_NOT_EMPTY    | \
                                             `$INSTANCE_NAME`_INTR_RX_FULL         | \
                                             `$INSTANCE_NAME`_INTR_RX_OVERFLOW     | \
                                             `$INSTANCE_NAME`_INTR_RX_UNDERFLOW    | \
                                             `$INSTANCE_NAME`_INTR_RX_BLOCKED      | \
                                             `$INSTANCE_NAME`_INTR_RX_FRAME_ERROR  | \
                                             `$INSTANCE_NAME`_INTR_RX_PARITY_ERROR | \
                                             `$INSTANCE_NAME`_INTR_RX_BAUD_DETECT  | \
                                             `$INSTANCE_NAME`_INTR_RX_BREAK_DETECT)
                
/* General usege HW definitions */
#define `$INSTANCE_NAME`_ONE_BYTE_WIDTH (8u)   /* Number of bits in one byte */
#define `$INSTANCE_NAME`_FIFO_SIZE      (8u)   /* Size of TX or RX FIFO: defined by HW */
#define `$INSTANCE_NAME`_BUFFER_SIZE    (32u)  /* EZ Buffer size: defined by HW        */

/* I2C and EZI2C slave address defines */
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDR__POS    (0x01u)    /* 7-bit address shift */
#define `$INSTANCE_NAME`_I2C_SLAVE_ADDR__MASK   (0xFEu)    /* 8-bit address mask */

/* OVS constants for IrDA Low Power operation */
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16     (0x00u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS32     (0x01u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS48     (0x02u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS96     (0x03u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS192    (0x04u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS768    (0x05u)
#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS1536   (0x06u)

#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS16     (16u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS32     (32u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS48     (48u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS96     (96u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS192    (192u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS768    (768u)
#define `$INSTANCE_NAME`_UART_IRDA_LP_OVS1536   (1536u)

#define `$INSTANCE_NAME`_CTRL_OVS_IRDA_OVS      (`$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16)


/***************************************
*       Common SCB Macro Definition
***************************************/

/* TX FIFO macro */
#define `$INSTANCE_NAME`_CLEAR_TX_FIFO  \
                            do{         \
                                `$INSTANCE_NAME`_TX_FIFO_CTRL_REG |=  `$INSTANCE_NAME`_TX_FIFO_CTRL_CLEAR; \
                                `$INSTANCE_NAME`_TX_FIFO_CTRL_REG &= ~`$INSTANCE_NAME`_TX_FIFO_CTRL_CLEAR; \
                            }while(0)

#define `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES    (`$INSTANCE_NAME`_TX_FIFO_STATUS_REG & \
                                                 `$INSTANCE_NAME`_TX_FIFO_STATUS_USED__MASK)

#define `$INSTANCE_NAME`_GET_TX_FIFO_SR_VALID   ((0u != (`$INSTANCE_NAME`_TX_FIFO_STATUS_REG & \
                                                         `$INSTANCE_NAME`_TX_FIFO_SR_VALID)) ? (1u) : (0u))

/* RX FIFO macro */
#define `$INSTANCE_NAME`_CLEAR_RX_FIFO  \
                                do{     \
                                    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG |=  `$INSTANCE_NAME`_RX_FIFO_CTRL_CLEAR; \
                                    `$INSTANCE_NAME`_RX_FIFO_CTRL_REG &= ~`$INSTANCE_NAME`_RX_FIFO_CTRL_CLEAR; \
                                }while(0)

#define `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES    (`$INSTANCE_NAME`_RX_FIFO_STATUS_REG & \
                                                    `$INSTANCE_NAME`_RX_FIFO_STATUS_USED__MASK)

#define `$INSTANCE_NAME`_GET_RX_FIFO_SR_VALID   ((0u != (`$INSTANCE_NAME`_RX_FIFO_STATUS_REG & \
                                                         `$INSTANCE_NAME`_RX_FIFO_SR_VALID)) ? (1u) : (0u))

/* Enable interrupt source: set sourceMask bits in `$INSTANCE_NAME`_INTR_X_MASK_REG */
#define `$INSTANCE_NAME`_WRITE_INTR_I2C_EC_MASK(sourceMask) \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG = (sourceMask); \
                                                }while(0)

#define `$INSTANCE_NAME`_WRITE_INTR_SPI_EC_MASK(sourceMask) \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_WRITE_INTR_MASTER_MASK(sourceMask) \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_WRITE_INTR_SLAVE_MASK(sourceMask)  \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_WRITE_INTR_TX_MASK(sourceMask)     \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_TX_MASK_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_WRITE_INTR_RX_MASK(sourceMask)     \
                                                do{         \
                                                    `$INSTANCE_NAME`_INTR_RX_MASK_REG = (sourceMask); \
                                                }while(0)

#define `$INSTANCE_NAME`_ENABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG |= (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_ENABLE_INTR_SPI_EC(sourceMask) \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG |= (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_ENABLE_INTR_MASTER(sourceMask) \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_MASTER_MASK_REG |= (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_ENABLE_INTR_SLAVE(sourceMask)  \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG |= (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_ENABLE_INTR_TX(sourceMask)     \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_TX_MASK_REG |= (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_ENABLE_INTR_RX(sourceMask)     \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_RX_MASK_REG |= (sourceMask); \
                                                }while(0)

/* Disable interrupt source: clear sourceMask bits in `$INSTANCE_NAME`_INTR_X_MASK_REG */
#define `$INSTANCE_NAME`_DISABLE_INTR_I2C_EC(sourceMask) \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_I2C_EC_MASK_REG &= ~(sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_DISABLE_INTR_SPI_EC(sourceMask) \
                                                do{      \
                                                    `$INSTANCE_NAME`_INTR_SPI_EC_MASK_REG &= ~(sourceMask); \
                                                 }while(0)
                                                 
#define `$INSTANCE_NAME`_DISABLE_INTR_MASTER(sourceMask) \
                                                do{      \
                                                `$INSTANCE_NAME`_INTR_MASTER_MASK_REG &= ~(sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_DISABLE_INTR_SLAVE(sourceMask) \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SLAVE_MASK_REG &= ~(sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_DISABLE_INTR_TX(sourceMask)    \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_TX_MASK_REG &= ~(sourceMask); \
                                                 }while(0)
                                                 
#define `$INSTANCE_NAME`_DISABLE_INTR_RX(sourceMask)    \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_RX_MASK_REG &= ~(sourceMask); \
                                                }while(0)

/* Set interrupt sources: write sourceMask bits in `$INSTANCE_NAME`_INTR_X_SET_REG */
#define `$INSTANCE_NAME`_SET_INTR_I2C_EC(sourceMask)    \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_I2C_EC_SET_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_SET_INTR_SPI_EC(sourceMask)    \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SPI_EC_SET_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_SET_INTR_MASTER(sourceMask)    \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_MASTER_SET_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_SET_INTR_SLAVE(sourceMask) \
                                                do{ \
                                                    `$INSTANCE_NAME`_INTR_SLAVE_SET_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_SET_INTR_TX(sourceMask)    \
                                                do{ \
                                                    `$INSTANCE_NAME`_INTR_TX_SET_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_SET_INTR_RX(sourceMask)    \
                                                do{ \
                                                    `$INSTANCE_NAME`_INTR_RX_SET_REG = (sourceMask); \
                                                }while(0)

/* Clear interrupt sources: write sourceMask bits in `$INSTANCE_NAME`_INTR_X_REG */
#define `$INSTANCE_NAME`_CLEAR_INTR_I2C_EC(sourceMask)  \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_I2C_EC_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_CLEAR_INTR_SPI_EC(sourceMask)  \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SPI_EC_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_CLEAR_INTR_MASTER(sourceMask)  \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_MASTER_REG = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_CLEAR_INTR_SLAVE(sourceMask)   \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_SLAVE_REG  = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_CLEAR_INTR_TX(sourceMask)      \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_TX_REG     = (sourceMask); \
                                                }while(0)
                                                
#define `$INSTANCE_NAME`_CLEAR_INTR_RX(sourceMask)      \
                                                do{     \
                                                    `$INSTANCE_NAME`_INTR_RX_REG     = (sourceMask); \
                                                }while(0)

/* Return TRUE if sourceMask is set in `$INSTANCE_NAME`_INTR_CAUSE_REG */
#define `$INSTANCE_NAME`_CHECK_CAUSE_INTR(sourceMask)    (0u != (`$INSTANCE_NAME`_INTR_CAUSE_REG & (sourceMask))

/* Return TRUE if sourceMask is set in  INTR_X_MASKED_REG */
#define `$INSTANCE_NAME`_CHECK_INTR_EC_I2C(sourceMask)  (0u != (`$INSTANCE_NAME`_INTR_I2C_EC_REG & (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_EC_SPI(sourceMask)  (0u != (`$INSTANCE_NAME`_INTR_SPI_EC_REG & (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_MASTER(sourceMask)  (0u != (`$INSTANCE_NAME`_INTR_MASTER_REG & (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_SLAVE(sourceMask)   (0u != (`$INSTANCE_NAME`_INTR_SLAVE_REG  & (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_TX(sourceMask)      (0u != (`$INSTANCE_NAME`_INTR_TX_REG     & (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_RX(sourceMask)      (0u != (`$INSTANCE_NAME`_INTR_RX_REG     & (sourceMask)))

/* Return TRUE if sourceMask is set in `$INSTANCE_NAME`_INTR_X_MASKED_REG */
#define `$INSTANCE_NAME`_CHECK_INTR_I2C_EC_MASKED(sourceMask)   (0u != (`$INSTANCE_NAME`_INTR_I2C_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_SPI_EC_MASKED(sourceMask)   (0u != (`$INSTANCE_NAME`_INTR_SPI_EC_MASKED_REG & \
                                                                       (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_MASTER_MASKED(sourceMask)   (0u != (`$INSTANCE_NAME`_INTR_MASTER_MASKED_REG & \
                                                                       (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_SLAVE_MASKED(sourceMask)    (0u != (`$INSTANCE_NAME`_INTR_SLAVE_MASKED_REG  & \
                                                                       (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_TX_MASKED(sourceMask)       (0u != (`$INSTANCE_NAME`_INTR_TX_MASKED_REG     & \
                                                                       (sourceMask)))
#define `$INSTANCE_NAME`_CHECK_INTR_RX_MASKED(sourceMask)       (0u != (`$INSTANCE_NAME`_INTR_RX_MASKED_REG     & \
                                                                       (sourceMask)))

/* Return TRUE if sourceMask is set in `$INSTANCE_NAME`_CTRL_REG: generaly is used to check enable bit */
#define `$INSTANCE_NAME`_GET_CTRL_ENABLED    (0u != (`$INSTANCE_NAME`_CTRL_REG & `$INSTANCE_NAME`_CTRL_ENABLED))

#define `$INSTANCE_NAME`_CHECK_SLAVE_AUTO_ADDR_NACK     (0u != (`$INSTANCE_NAME`_I2C_CTRL_REG & \
                                                                `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK))


/***************************************
*      I2C Macro Definition
***************************************/

/* Enable auto ACK/NACK */
#define `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_ADDR_NACK    \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_ACK     \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA_NACK    \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define `$INSTANCE_NAME`_ENABLE_MASTER_AUTO_DATA_ACK    \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_ENABLE_MASTER_AUTO_DATA_NACK   \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= `$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Disable auto ACK/NACK */
#define `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_ADDR_NACK   \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA_ACK    \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA_NACK   \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK; \
                            }while(0)

#define `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA_ACK   \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA_NACK  \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~`$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK; \
                            }while(0)

/* Enable Slave autoACK/NACK Data */
#define `$INSTANCE_NAME`_ENABLE_SLAVE_AUTO_DATA     \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_CTRL_REG |= (`$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK |       \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Slave autoACK/NACK Data */
#define `$INSTANCE_NAME`_DISABLE_SLAVE_AUTO_DATA    \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~(`$INSTANCE_NAME`_I2C_CTRL_S_READY_DATA_ACK |      \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_DATA_NACK); \
                            }while(0)

/* Disable Master autoACK/NACK Data */
#define `$INSTANCE_NAME`_DISABLE_MASTER_AUTO_DATA   \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_CTRL_REG &= ~(`$INSTANCE_NAME`_I2C_CTRL_M_READY_DATA_ACK |      \
                                                                   `$INSTANCE_NAME`_I2C_CTRL_M_NOT_READY_DATA_NACK); \
                            }while(0)

/* Master commands */
#define `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START  \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_START_ON_IDLE; \
                            }while(0)

#define `$INSTANCE_NAME`_I2C_MASTER_CLEAR_START     \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG =  0u; \
                            }while(0)

#define `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART    \
                            do{                         \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG =                                            \
                                    (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START |                                   \
                                        (`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_M_READ) ? \
                                                    (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK) : (0u)));       \
                           }while(0)

#define `$INSTANCE_NAME`_I2C_MASTER_GENERATE_STOP   \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG =                                            \
                                    (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_STOP |                                    \
                                        (`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_M_READ) ? \
                                            (`$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK) : (0u)));               \
                            }while(0)

#define `$INSTANCE_NAME`_I2C_MASTER_GENERATE_ACK    \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_I2C_MASTER_GENERATE_NACK   \
                            do{                     \
                                `$INSTANCE_NAME`_I2C_MASTER_CMD_REG = `$INSTANCE_NAME`_I2C_MASTER_CMD_M_NACK; \
                            }while(0)

/* Slave comamnds */
#define `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_ACK     \
                            do{             \
                                `$INSTANCE_NAME`_I2C_SLAVE_CMD_REG = `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_ACK; \
                            }while(0)

#define `$INSTANCE_NAME`_I2C_SLAVE_GENERATE_NACK    \
                            do{             \
                                `$INSTANCE_NAME`_I2C_SLAVE_CMD_REG = `$INSTANCE_NAME`_I2C_SLAVE_CMD_S_NACK; \
                            }while(0)

/* Return 8-bit address. The input address should be 7-bits */
#define `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(addr) (((uint32) (addr) << `$INSTANCE_NAME`_I2C_SLAVE_ADDR__POS) & \
                                                                         `$INSTANCE_NAME`_I2C_SLAVE_ADDR__MASK)


/***************************************
*      EzI2C Macro Definition
***************************************/

/* Returns I2C EzAddress */
#define `$INSTANCE_NAME`_GET_I2C_STATUS_EZ_ADDRESS      (`$INSTANCE_NAME`_I2C_STATUS_REG >> \
                                                            `$INSTANCE_NAME`_I2C_STATUS_EZ_ADDR__POS)

/* Returns true if bit is set in `$INSTANCE_NAME`_I2C_STATUS_REG */
#define `$INSTANCE_NAME`_CHECK_I2C_STATUS(sourceMask)   (0u != (`$INSTANCE_NAME`_I2C_STATUS_REG & (sourceMask)))


/***************************************
*      EzSpi Macro Definition
***************************************/

/* Returns SPI EzAddress */
#define `$INSTANCE_NAME`_GET_SPI_STATUS_EZ_ADDRESS      (`$INSTANCE_NAME`_SPI_STATUS_REG >> \
                                                            `$INSTANCE_NAME`_SPI_STATUS_EZ_ADDR__POS)

/* Returns true if bit is set in `$INSTANCE_NAME`_SPI_STATUS_REG */
#define `$INSTANCE_NAME`_CHECK_SPI_STATUS(sourceMask)   (0u != (`$INSTANCE_NAME`_SPI_STATUS_REG & (sourceMask)))


/***************************************
*   Gets defualt config bits
***************************************/

/* `$INSTANCE_NAME`_CTRL */
#define `$INSTANCE_NAME`_GET_CTRL_OVS(oversample)   ((uint32) ((oversample) - 1u))

#define `$INSTANCE_NAME`_GET_CTRL_OVS_IRDA_LP(oversample)   \
            ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS16   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16 : \
             ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS32   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS32 : \
              ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS48   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS48 : \
               ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS96   == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS96 : \
                ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS192  == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS192 : \
                 ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS768  == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS768 : \
                  ((`$INSTANCE_NAME`_UART_IRDA_LP_OVS1536 == (oversample)) ? `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS1536 : \
                                                                              `$INSTANCE_NAME`_CTRL_OVS_IRDA_LP_OVS16)))))))

#define `$INSTANCE_NAME`_GET_CTRL_EC_OP_MODE(opMode)        ((0u != (opMode)) ? \
                                                                (`$INSTANCE_NAME`_CTRL_EC_OP_MODE)  : (0u))

#define `$INSTANCE_NAME`_GET_CTRL_EC_AM_MODE(amMode)        ((0u != (amMode)) ? \
                                                                (`$INSTANCE_NAME`_CTRL_EC_AM_MODE)  : (0u))

#define `$INSTANCE_NAME`_GET_CTRL_BLOCK(block)              ((0u != (block))  ? \
                                                                (`$INSTANCE_NAME`_CTRL_BLOCK)       : (0u))

#define `$INSTANCE_NAME`_GET_CTRL_ADDR_ACCEPT(acceptAddr)   ((0u != (acceptAddr)) ? \
                                                                (`$INSTANCE_NAME`_CTRL_ADDR_ACCEPT) : (0u))

/* `$INSTANCE_NAME`_I2C_CTRL */
#define `$INSTANCE_NAME`_GET_I2C_CTRL_HIGH_PHASE_OVS(oversampleHigh) ((uint32) ((oversampleHigh) - 1u))

#define `$INSTANCE_NAME`_GET_I2C_CTRL_LOW_PHASE_OVS(oversampleLow)   ((uint32) (((oversampleLow)  - 1u) << \
                                                                        `$INSTANCE_NAME`_I2C_CTRL_LOW_PHASE_OVS__POS))

#define `$INSTANCE_NAME`_GET_I2C_CTRL_S_NOT_READY_ADDR_NACK(wakeNack) ((0u != (wakeNack)) ? \
                                                            (`$INSTANCE_NAME`_I2C_CTRL_S_NOT_READY_ADDR_NACK) : (0u))

#define `$INSTANCE_NAME`_GET_I2C_CTRL_SLAVE_MODE(mode)  ((0u != ((mode) & `$INSTANCE_NAME`_I2C_MODE_SLAVE))  ? \
                                                            (`$INSTANCE_NAME`_I2C_CTRL_SLAVE_MODE)  : (0u))

#define `$INSTANCE_NAME`_GET_I2C_CTRL_MASTER_MODE(mode) ((0u != ((mode) & `$INSTANCE_NAME`_I2C_MODE_MASTER)) ? \
                                                            (`$INSTANCE_NAME`_I2C_CTRL_MASTER_MODE) : (0u))

/* `$INSTANCE_NAME`_SPI_CTRL */
#define `$INSTANCE_NAME`_GET_SPI_CTRL_CONTINUOUS(separate)  ((0u != (separate)) ? \
                                                                (`$INSTANCE_NAME`_SPI_CTRL_CONTINUOUS) : (0u))
#define `$INSTANCE_NAME`_GET_SPI_CTRL_SELECT_PRECEDE(mode)  \
                                                   ((0u != ((mode) & `$INSTANCE_NAME`_SPI_MODE_TI_PRECEDES_MASK)) ? \
                                                                (`$INSTANCE_NAME`_SPI_CTRL_SELECT_PRECEDE) : (0u))

#define `$INSTANCE_NAME`_GET_SPI_CTRL_SCLK_MODE(mode)       ((uint32) ((mode) << `$INSTANCE_NAME`_SPI_CTRL_CPHA__POS))

#define `$INSTANCE_NAME`_GET_SPI_CTRL_LATE_MISO_SAMPLE(lateMiso) ((0u != (lateMiso)) ? \
                                                                (`$INSTANCE_NAME`_SPI_CTRL_LATE_MISO_SAMPLE) : (0u))

#define `$INSTANCE_NAME`_GET_SPI_CTRL_SUB_MODE(mode)        ((uint32) ((mode) & `$INSTANCE_NAME`_SPI_MODE_MASK) << \
                                                                `$INSTANCE_NAME`_SPI_CTRL_MODE__POS)

#define `$INSTANCE_NAME`_GET_SPI_CTRL_SLAVE_SELECT(select)  ((uint32) ((select) & \
                                                                `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__MASK)<< \
                                                                `$INSTANCE_NAME`_SPI_CTRL_SLAVE_SELECT__POS)

#define `$INSTANCE_NAME`_GET_SPI_CTRL_MASTER_MODE(mode)     ((0u != (mode)) ? \
                                                                (`$INSTANCE_NAME`_SPI_CTRL_MASTER) : (0u))

/* `$INSTANCE_NAME`_UART_CTRL */
#define `$INSTANCE_NAME`_GET_UART_CTRL_MODE(mode)           ((uint32) ((mode) << `$INSTANCE_NAME`_UART_CTRL_MODE__POS))

/* `$INSTANCE_NAME`_UART_RX_CTRL */
#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_MODE(stopBits)    ((uint32) ((stopBits) - 1u))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_PARITY(parity)    ((0u != (parity))   ? \
                                                                    (`$INSTANCE_NAME`_UART_RX_CTRL_PARITY) : (0u))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_POLARITY(polarity)    ((0u != (polarity)) ? \
                                                                    (`$INSTANCE_NAME`_UART_RX_CTRL_POLARITY) : (0u))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_PARITY_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (`$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_PARITY_ERR) : (0u))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_DROP_ON_FRAME_ERR(dropErr) ((0u != (dropErr)) ? \
                                                        (`$INSTANCE_NAME`_UART_RX_CTRL_DROP_ON_FRAME_ERR) : (0u))

#define `$INSTANCE_NAME`_GET_UART_RX_CTRL_MP_MODE(mpMode)   ((0u != (mpMode)) ? \
                                                        (`$INSTANCE_NAME`_UART_RX_CTRL_MP_MODE)  : (0u))

/* `$INSTANCE_NAME`_UART_TX_CTRL */
#define `$INSTANCE_NAME`_GET_UART_TX_CTRL_MODE(stopBits)    ((uint32) ((stopBits) - 1u))

#define `$INSTANCE_NAME`_GET_UART_TX_CTRL_PARITY(parity)    ((0u != (parity)) ? \
                                                               (`$INSTANCE_NAME`_UART_TX_CTRL_PARITY) : (0u))

#define `$INSTANCE_NAME`_GET_UART_TX_CTRL_RETRY_NACK(nack)  ((0u != (nack)) ? \
                                                               (`$INSTANCE_NAME`_UART_TX_CTRL_RETRY_ON_NACK) : (0u))

/* `$INSTANCE_NAME`_RX_CTRL */
#define `$INSTANCE_NAME`_GET_RX_CTRL_DATA_WIDTH(dataWidth)  ((uint32) ((dataWidth) - 1u))

#define `$INSTANCE_NAME`_GET_RX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (`$INSTANCE_NAME`_RX_CTRL_MSB_FIRST) : (0u))

#define `$INSTANCE_NAME`_GET_RX_CTRL_MEDIAN(filterEn)       ((0u != (filterEn)) ? \
                                                                (`$INSTANCE_NAME`_RX_CTRL_MEDIAN) : (0u))

/* `$INSTANCE_NAME`_RX_MATCH */
#define `$INSTANCE_NAME`_GET_RX_MATCH_ADDR(addr)    ((uint32) (addr))
#define `$INSTANCE_NAME`_GET_RX_MATCH_MASK(mask)    ((uint32) ((mask) << `$INSTANCE_NAME`_RX_MATCH_MASK__POS))

/* `$INSTANCE_NAME`_RX_FIFO_CTRL */
#define `$INSTANCE_NAME`_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level))

/* `$INSTANCE_NAME`_TX_CTRL */
#define `$INSTANCE_NAME`_GET_TX_CTRL_DATA_WIDTH(dataWidth)  ((uint32) ((dataWidth) - 1u))

#define `$INSTANCE_NAME`_GET_TX_CTRL_BIT_ORDER(bitOrder)    ((0u != (bitOrder)) ? \
                                                                (`$INSTANCE_NAME`_TX_CTRL_MSB_FIRST) : (0u))

/* `$INSTANCE_NAME`_TX_FIFO_CTRL */
#define `$INSTANCE_NAME`_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(level)  ((uint32) (level))

#define `$INSTANCE_NAME`_NO_INTR_SOURCES    (0u)

#endif /* (CY_SCB_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
