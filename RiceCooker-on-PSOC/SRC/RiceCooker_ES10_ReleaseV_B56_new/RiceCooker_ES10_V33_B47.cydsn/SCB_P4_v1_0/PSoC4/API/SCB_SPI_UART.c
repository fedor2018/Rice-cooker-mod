/*******************************************************************************
* File Name: `$INSTANCE_NAME`_SPI_UART.c
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

/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartReadRxData
********************************************************************************
*
* Summary:
*  Returns data in RX Data register without checking status register to
*  determine if data is valid
*
* Parameters:
*  None
*
* Return:
*  Received data from RX register
*
* Global Variables:
*  `$INSTANCE_NAME`_rxBuffer - RAM buffer pointer for save received data.
*  `$INSTANCE_NAME`_rxBufferHead - cyclic index for write to rxBuffer,
*     checked to identify new data.
*  `$INSTANCE_NAME`_rxBufferTail - cyclic index for read from rxBuffer,
*     incremented after each byte has been read from buffer.
*  `$INSTANCE_NAME`_rxBufferLoopDetect - creared if loop condition was detected
*     in RX ISR.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartReadRxData(void)
{
    uint32 rxData;
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        if(`$INSTANCE_NAME`_rxBufferHead == `$INSTANCE_NAME`_rxBufferTail)
        {
            /* No data in the buffer: return 0x00 */
            rxData = 0u;
        }
        else
        {
            /* There is data in RX software buffer */

            /* Calculate index to read from */
            locTail = (`$INSTANCE_NAME`_rxBufferTail + 1u);

            if(`$INSTANCE_NAME`_RX_BUFFER_SIZE == locTail)
            {
                locTail = 0u;
            }

            /* Get data fron RX software buffer */
            rxData = `$INSTANCE_NAME`_GetWordFromRxBuffer(locTail);

            /* Change index in the buffer */
            `$INSTANCE_NAME`_rxBufferTail = locTail;
        }
    }
    `$Cond`else
    {
        rxData = `$INSTANCE_NAME`_RX_FIFO_RD_REG;
    }
    `$EndCond`

    return(rxData);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartGetRxBufferSize
********************************************************************************
*
* Summary:
*  Determine the amount of bytes left in the RX buffer and return the count in
*  bytes
*
* Parameters:
*  None
*
* Return:
*  : Integer count of the number of bytes left
*  in the RX buffer
*
* Global Variables:
*
* Theory:
*  Allows the user to find out how full the RX Buffer is.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartGetRxBufferSize(void)
{
    uint32 size;
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        locHead = `$INSTANCE_NAME`_rxBufferHead;

        if(locHead >= `$INSTANCE_NAME`_rxBufferTail)
        {
            size = (locHead - `$INSTANCE_NAME`_rxBufferTail);
        }
        else
        {
            size = (locHead + (`$INSTANCE_NAME`_RX_BUFFER_SIZE - `$INSTANCE_NAME`_rxBufferTail));
        }
    }
    `$Cond`else
    {
        size = `$INSTANCE_NAME`_GET_RX_FIFO_ENTRIES;
    }
    `$EndCond`

    return(size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartClearRxBuffer
********************************************************************************
*
* Summary:
*  Clears the RX RAM buffer by setting the read and write pointers both to zero.
*  Clears hardware RX FIFO.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_rxBufferHead - cleared to zero.
*  `$INSTANCE_NAME`_rxBufferTail - cleared to zero.
*
*
* Theory:
*  Setting the pointers to zero makes the system believe there is no data to
*  read and writing will resume at address 0 overwriting any data that may
*  have remained in the RAM.
*
* Side Effects:
*  Any received data not read from the RAM or FIFO buffer will be lost.
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiUartClearRxBuffer(void)
{
    #if(`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 intSourceMask;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_RX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_RX_SW_BUFFER)
    {
        intSourceMask = `$INSTANCE_NAME`_SpiUartDisableIntRx();

        `$INSTANCE_NAME`_CLEAR_RX_FIFO;

        /* Flush RX software buffer */
        `$INSTANCE_NAME`_rxBufferHead     = `$INSTANCE_NAME`_rxBufferTail;
        `$INSTANCE_NAME`_rxBufferOverflow = 0u;

        /* End RX transfer */
        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_ALL);

        `$INSTANCE_NAME`_SpiUartEnableIntRx(intSourceMask);
    }
    `$Cond`else
    {
        `$INSTANCE_NAME`_CLEAR_RX_FIFO;
    }
    `$EndCond`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartWriteTxData
********************************************************************************
*
* Summary:
*  Wait to send byte until TX register or buffer has room.
*
* Parameters:
*  txDataByte: The 8-bit data value to send across the UART.
*
* Return:
*  None
*
* Global Variables:
*  `$INSTANCE_NAME`_txBuffer - RAM buffer pointer for save data for transmission
*  `$INSTANCE_NAME`_txBufferHead - cyclic index for write to txBuffer,
*     checked to identify free space in txBuffer and incremented after each byte
*     saved to buffer.
*  `$INSTANCE_NAME`_txBufferTail - cyclic index for read from txBuffer,
*     checked to identify free space in txBuffer.
*  `$INSTANCE_NAME`_initVar - checked to identify that the component has been
*     initialized.
*
* Theory:
*  Allows the user to transmit any byte of data in a single transfer
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiUartWriteTxData(uint32 txDataByte)
{
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
        uint32 intSourceMask;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
    {
        /* Head index to put data */
        locHead = (`$INSTANCE_NAME`_txBufferHead + 1u);

        /* Adjust TX software buffer index */
        if(`$INSTANCE_NAME`_TX_BUFFER_SIZE == locHead)
        {
            locHead = 0u;
        }

        while(locHead == `$INSTANCE_NAME`_txBufferTail)
        {
            ; /* Wait for space in the TX software buffer */
        }

        /* The TX software buffer has at least one room */

        if((`$INSTANCE_NAME`_txBufferHead == `$INSTANCE_NAME`_txBufferTail) &&
           (`$INSTANCE_NAME`_FIFO_SIZE != `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES))
        {
            /* TX software buffer is empty: put data in TX FIFO */
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = txDataByte;
        }
        /* Put data in the TX software buffer */
        else
        {
            `$INSTANCE_NAME`_PutWordInTxBuffer(locHead, txDataByte);

            `$INSTANCE_NAME`_txBufferHead = locHead;

            /* Enable interrupt to transmit */
            intSourceMask  = `$INSTANCE_NAME`_INTR_TX_EMPTY;
            intSourceMask |= `$INSTANCE_NAME`_GetRxInterruptSource();
            `$INSTANCE_NAME`_SpiUartEnableIntTx(intSourceMask);
        }
    }
    `$Cond`else
    {
        while(`$INSTANCE_NAME`_FIFO_SIZE == `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES)
        {
            ; /* Block while TX FIFO is FULL */
        }

        `$INSTANCE_NAME`_TX_FIFO_WR_REG = txDataByte;
    }
    `$EndCond`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartPutArray
********************************************************************************
*
* Summary:
*  Write a Sequence of bytes on the Transmit line. Data comes from RAM or ROM.
*
* Parameters:
*  string: Address of the memory array residing in RAM or ROM.
*  byteCount: Number of Bytes to be transmitted.
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiUartPutArray(const `$BitWidthReplacementStringTx` wrBuf[], uint32 count)
{
    uint32 i;

    for(i=0; i < count; i++)
    {
        `$INSTANCE_NAME`_SpiUartWriteTxData(wrBuf[i]);
    }
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartGetTxBufferSize
********************************************************************************
*
* Summary:
*  Determine the amount of space left in the TX buffer and return the count in
*  bytes
*
* Parameters:
*  None
*
* Return:
*  Integer count of the number of bytes left in the TX buffer
*
* Global Variables:
*
* Theory:
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartGetTxBufferSize(void)
{
    uint32 size;
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
    {
        /* Get current Tail index */
        locTail = `$INSTANCE_NAME`_txBufferTail;

        if(`$INSTANCE_NAME`_txBufferHead >= locTail)
        {
            size = (`$INSTANCE_NAME`_txBufferHead - locTail);
        }
        else
        {
            size = (`$INSTANCE_NAME`_txBufferHead + (`$INSTANCE_NAME`_TX_BUFFER_SIZE - locTail));
        }
    }
    `$Cond`else
    {
        size = `$INSTANCE_NAME`_GET_TX_FIFO_ENTRIES;
    }
    `$EndCond`

    return(size);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartClearTxBuffer
********************************************************************************
*
* Summary:
*  Clears the TX RAM buffer by setting the read and write pointers both to zero.
*  Clears the hardware TX FIFO. Any data present in the FIFO will not be sent.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_SpiUartClearTxBuffer(void)
{
    #if(`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 intSourceMask;
    #endif /* (`$INSTANCE_NAME`_INTERNAL_TX_SW_BUFFER_CONST) */

    `$Cond`if(`$INSTANCE_NAME`_CHECK_TX_SW_BUFFER)
    {
        intSourceMask = `$INSTANCE_NAME`_SpiUartDisableIntTx();

        `$INSTANCE_NAME`_CLEAR_TX_FIFO;

        /* Flush TX software buffer */
        `$INSTANCE_NAME`_txBufferHead = `$INSTANCE_NAME`_txBufferTail;

        /* End TX transfer if it is in progress */
        intSourceMask &= (uint32) ~`$INSTANCE_NAME`_INTR_TX_EMPTY;

        `$INSTANCE_NAME`_SpiUartEnableIntTx(intSourceMask);
    }
    `$Cond`else
    {
        `$INSTANCE_NAME`_CLEAR_TX_FIFO;
    }
    `$EndCond`
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartEnableIntRx
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
void `$INSTANCE_NAME`_SpiUartEnableIntRx(uint32 intSourceMask)
{
    `$INSTANCE_NAME`_SetRxInterruptMode(intSourceMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartDisableIntRx
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
uint32 `$INSTANCE_NAME`_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = `$INSTANCE_NAME`_GetRxInterruptMode();

    `$INSTANCE_NAME`_SetRxInterruptMode(~`$INSTANCE_NAME`_INTR_RX_ALL);

    return(intSource);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartEnableIntTx
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
void `$INSTANCE_NAME`_SpiUartEnableIntTx(uint32 intSourceMask)
{
    `$INSTANCE_NAME`_SetTxInterruptMode(intSourceMask);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SpiUartDisableIntTx
********************************************************************************
*
* Summary:
*  Configure which status bits trigger an interrupt event
*
* Parameters:
*
* Return:
*  None
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = `$INSTANCE_NAME`_GetTxInterruptMode();

    `$INSTANCE_NAME`_SetTxInterruptMode(~`$INSTANCE_NAME`_INTR_TX_ALL);

    return(intSourceMask);
}


#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutWordInRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutWordInRxBuffer(uint32 index, uint32 rxDataByte)
    {
        uint32 databits;

        if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            /* Config SPI */
            databits = `$INSTANCE_NAME`_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, txDataBits);
        }
        else
        {
            /* Config UART */
            databits = `$INSTANCE_NAME`_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, dataBits);
        }

        /* Put data in the buffer */
        if(`$INSTANCE_NAME`_ONE_BYTE_WIDTH == databits)
        {
            `$INSTANCE_NAME`_rxBuffer[index] = ((uint8) rxDataByte);
        }
        else
        {
            `$INSTANCE_NAME`_rxBuffer[(uint32)(index << 1u)]      = LO8(LO16(rxDataByte));
            `$INSTANCE_NAME`_rxBuffer[(uint32)(index << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetWordFromRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetWordFromRxBuffer(uint32 index)
    {
        uint32 value;
        uint32 databits;

        if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            /* Config SPI */
            databits = `$INSTANCE_NAME`_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, txDataBits);
        }
        else
        {
            /* Config UART */
            databits = `$INSTANCE_NAME`_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, dataBits);
        }

        if(`$INSTANCE_NAME`_ONE_BYTE_WIDTH == databits)
        {
            value = `$INSTANCE_NAME`_rxBuffer[index];
        }
        else
        {
            value  = (uint32)  `$INSTANCE_NAME`_rxBuffer[(uint32)(index << 1u)];
            value |= (uint32) (`$INSTANCE_NAME`_rxBuffer[(uint32)(index << 1u) + 1u] << 8u);
        }

        return(value);
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_PutWordInTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_PutWordInTxBuffer(uint32 index, uint32 txDataByte)
    {
        uint32 databits;

        if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            /* Config SPI */
            databits = `$INSTANCE_NAME`_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, txDataBits);
        }
        else
        {
            /* Config UART */
            databits = `$INSTANCE_NAME`_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, dataBits);
        }

        /* Put data in the buffer */
        if(`$INSTANCE_NAME`_ONE_BYTE_WIDTH == databits)
        {
            `$INSTANCE_NAME`_txBuffer[index] = ((uint8) txDataByte);
        }
        else
        {
            `$INSTANCE_NAME`_txBuffer[(uint32)(index << 1u)]      = LO8(LO16(txDataByte));
            `$INSTANCE_NAME`_txBuffer[(uint32)(index << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_GetWordFromTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Configure which status bits trigger an interrupt event
    *
    * Parameters:
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    uint32 `$INSTANCE_NAME`_GetWordFromTxBuffer(uint32 index)
    {
        uint32 value;
        uint32 databits;

        if(`$INSTANCE_NAME`_SCB_MODE_SPI_RUNTM_CFG)
        {
            /* Config SPI */
            databits = `$INSTANCE_NAME`_SPI_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, txDataBits);
        }
        else
        {
            /* Config UART */
            databits = `$INSTANCE_NAME`_UART_INIT_ACCESS(`$INSTANCE_NAME`_scbCfg, dataBits);
        }

        if(`$INSTANCE_NAME`_ONE_BYTE_WIDTH == databits)
        {
            value = `$INSTANCE_NAME`_txBuffer[index];
        }
        else
        {
            value  = (uint32)  `$INSTANCE_NAME`_txBuffer[(uint32)(index << 1u)];
            value |= (uint32) (`$INSTANCE_NAME`_txBuffer[(uint32)(index << 1u) + 1u] << 8u);
        }

        return(value);
    }
#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */


/* [] END OF FILE */
