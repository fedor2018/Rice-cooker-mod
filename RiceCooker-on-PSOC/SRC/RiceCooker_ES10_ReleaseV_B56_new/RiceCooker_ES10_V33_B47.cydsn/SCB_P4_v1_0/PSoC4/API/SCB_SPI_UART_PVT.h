/*******************************************************************************
* File Name: `$INSTANCE_NAME_PVT`.h
* Version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
*
* Description:
*  This file provides private constants and parameter values for the I2C
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_`$INSTANCE_NAME`_H)
#define CY_SCB_SPI_UART_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_SPI_UART.h"


/**********************************
*      Internal functions
**********************************/

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint8 * `$INSTANCE_NAME`_rxBuffer;
    extern volatile uint32  `$INSTANCE_NAME`_rxBufferHead;
    extern volatile uint32  `$INSTANCE_NAME`_rxBufferTail;
    extern volatile uint32  `$INSTANCE_NAME`_rxBufferOverflow;
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint8 * `$INSTANCE_NAME`_txBuffer;
    extern volatile uint32  `$INSTANCE_NAME`_txBufferHead;
    extern volatile uint32  `$INSTANCE_NAME`_txBufferTail;
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

#if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER)
    extern volatile `$BitWidthReplacementStringRx` `$INSTANCE_NAME`_rxBufferInternal[`$INSTANCE_NAME`_RX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER) */

#if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER)
    extern volatile `$BitWidthReplacementStringTx` `$INSTANCE_NAME`_txBufferInternal[`$INSTANCE_NAME`_TX_BUFFER_SIZE];
#endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER) */


/**********************************
*      Internal functions
**********************************/

void   `$INSTANCE_NAME`_SpiUartEnableIntRx(uint32 intSourceMask);
void   `$INSTANCE_NAME`_SpiUartEnableIntTx(uint32 intSourceMask);
uint32 `$INSTANCE_NAME`_SpiUartDisableIntRx(void);
uint32 `$INSTANCE_NAME`_SpiUartDisableIntTx(void);

#endif /* (CY_SCB_SPI_UART_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
