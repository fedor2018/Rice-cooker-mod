/*******************************************************************************
* File Name: `$INSTANCE_NAME`_I2C_MASTER.c
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


#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)

/**********************************
*      System variables
**********************************/

/* Master variables */
volatile uint16 `$INSTANCE_NAME`_mstrStatus;        /* Master Status byte            */
volatile uint8  `$INSTANCE_NAME`_mstrControl;       /* Master Control byte           */

/* Transmit buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrRdBufPtr;     /* Pointer to Master Read buffer  */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufSize;    /* Master Read buffer size        */
volatile uint32  `$INSTANCE_NAME`_mstrRdBufIndex;   /* Master Read buffer Index       */

/* Receive buffer variables */
volatile uint8 * `$INSTANCE_NAME`_mstrWrBufPtr;     /* Pointer to Master Write buffer */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufSize;    /* Master Write buffer size       */
volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndex;   /* Master Write buffer Index      */


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteBuf
********************************************************************************
*
* Summary:
*  Automatically writes an entire buffer of data to a slave device. Once the
*  data transfer is initiated by this function, further data transfer is handled
*  by the included ISR in byte by byte mode.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer of data to be sent.
*  cnt:       Size of buffer to send.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  The included ISR will start transfer after start or restart condition will
*  be generated.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrWrBufPtr - used to store pointer to master write buffer.
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*  `$INSTANCE_NAME`_mstrWrBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteBuf(uint32 slaveAddress, uint8 * wrData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != wrData)  /* Check buffer pointer */
    {
        /* Check FSM state and bus before generate Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable();

            /* Check the bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT;
                              errStatus  =  `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }


    /* Check if the Master is ready to start  */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        /* Setup write transcation */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_ADDR;
        `$INSTANCE_NAME`_mstrWrBufIndex = 0ul;
        `$INSTANCE_NAME`_mstrWrBufSize  = cnt;
        `$INSTANCE_NAME`_mstrWrBufPtr   = (volatile uint8 *) wrData;
        `$INSTANCE_NAME`_mstrControl    = mode;

        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        `$INSTANCE_NAME`_mstrStatus &= ((uint32) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT);

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* The TX and RX FIFO have to be EMPTY */

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }

         /* Catch when address will be sent */
        `$INSTANCE_NAME`_ClearTxInterruptSource(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
        `$INSTANCE_NAME`_SetTxInterruptMode(`$INSTANCE_NAME`_INTR_TX_UNDERFLOW);
    }

    `$INSTANCE_NAME`_SCB_IRQ_Enable();

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadBuf
********************************************************************************
*
* Summary:
*  Automatically writes an entire buffer of data to a slave device. Once the
*  data transfer is initiated by this function, further data transfer is handled
*  by the included ISR in byte by byte mode.
*
* Parameters:
*  slaveAddr: 7-bit slave address.
*  xferData:  Pointer to buffer where to put data from slave.
*  cnt:       Size of buffer to read.
*  mode:      Transfer mode defines: start or restart condition generation at
*             begin of the transfer and complete the transfer or halt before
*             generating a stop.
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  The included ISR will start transfer after start or restart condition will
*  be generated.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus  - used to store current status of I2C Master.
*  `$INSTANCE_NAME`_state       - used to store current state of software FSM.
*  `$INSTANCE_NAME`_mstrControl - used to control master end of transaction with
*  or without the Stop generation.
*  `$INSTANCE_NAME`_mstrRdBufPtr - used to store pointer to master write buffer.
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master write
*  buffer.
*  `$INSTANCE_NAME`_mstrRdBufSize - used to store master write buffer size.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadBuf(uint32 slaveAddress, uint8 * rdData, uint32 cnt, uint32 mode)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    if(NULL != rdData)
    {
        /* Check FSM state and bus before generate Start/ReStart condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable();

            /* Check the bus state */
            errStatus = `$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY) ?
                            `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY : `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_I2C_FSM_HALT)
        {
            `$INSTANCE_NAME`_mstrStatus &= ((uint32) ~`$INSTANCE_NAME`_I2C_MSTAT_XFER_HALT);
                              errStatus  =  `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else
        {
            /* Unexpected FSM state: exit */
        }
    }

    /* Check the Master ready to proceed */
    if(`$INSTANCE_NAME`_I2C_MSTR_NO_ERROR == errStatus) /* No error proceed */
    {
        /* Setup read transfer */
        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_ADDR;
        `$INSTANCE_NAME`_mstrRdBufIndex = 0ul;
        `$INSTANCE_NAME`_mstrRdBufSize  = cnt;
        `$INSTANCE_NAME`_mstrRdBufPtr   = (volatile uint8 *) rdData;
        `$INSTANCE_NAME`_mstrControl    = mode;

        slaveAddress = (`$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress) | `$INSTANCE_NAME`_I2C_READ_FLAG);

        `$INSTANCE_NAME`_mstrStatus &= ((uint32) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT);

        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* The TX and RX FIFO have to be EMPTY */

        /* Generate Start or ReStart */
        if(`$INSTANCE_NAME`_CHECK_I2C_MODE_RESTART(mode))
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
        }
        else
        {
            `$INSTANCE_NAME`_TX_FIFO_WR_REG = (slaveAddress);
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;
        }

        /* Prepare reaing */
        if(`$INSTANCE_NAME`_mstrRdBufSize < `$INSTANCE_NAME`_I2C_FIFO_SIZE) /* Reading byte-by-byte */
        {
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);
        }
        else /* Reading use RX FIFO */
        {
            `$INSTANCE_NAME`_ENABLE_MASTER_AUTO_DATA_ACK;
            `$INSTANCE_NAME`_SetRxInterruptMode(`$INSTANCE_NAME`_INTR_RX_FULL);
        }
    }

    `$INSTANCE_NAME`_SCB_IRQ_Enable();

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStart
********************************************************************************
*
* Summary:
*  Generates Start condition and sends slave address with read/write bit.
*
* Parameters:
*  slaveAddress:  7-bit slave address.
*  R_nW:          Zero, send write command, non-zero send read command.
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  This function is entered without a 'byte complete' bit set in the I2C_CSR
*  register. It does not exit until it will be set.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStart(uint32 slaveAddress, uint32 R_nW)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generate Start condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_FSM_IDLE)
    {
        /* If bus is free, generate Start condition */
        if(`$INSTANCE_NAME`_CHECK_I2C_STATUS(`$INSTANCE_NAME`_I2C_STATUS_BUS_BUSY))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_BUS_BUSY;
        }
        else
        {
            `$INSTANCE_NAME`_SCB_IRQ_Disable(); /* Disable interrupt: the manual APIs don't require it */

            slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

            if(0u == R_nW) /* Write direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
            }
            else /* Read direction */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                         slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
            }

            /* The TX and RX FIFO have to be EMPTY */

            `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress; /* Put address in TX FIFO */
            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_START;


            while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                      `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
            {
                /* Wait until address will be transfered */
            }

            /* Check results of address phase */
            if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
            }
            else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
            {
                errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
            }
            else /* INTR_MASTER_I2C_ARB_LOST  */
            {
                `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
            }

            `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                        `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST);
        }
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendRestart
********************************************************************************
*
* Summary:
*  Generates ReStart condition and sends slave address with read/write bit.
*
* Parameters:
*  slaveAddress:  7-bit slave address.
*  R_nW:          Zero, send write command, non-zero send read command.
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  This function is entered without a 'byte complete' bit set in the I2C_CSR
*  register. It does not exit until it will be set.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendRestart(uint32 slaveAddress, uint32 R_nW)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generate ReStart condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        slaveAddress = `$INSTANCE_NAME`_GET_I2C_8BIT_ADDRESS(slaveAddress);

        if(0u == R_nW) /* Write direction */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_WR_DATA;
        }
        else  /* Read direction */
        {
            `$INSTANCE_NAME`_state  = `$INSTANCE_NAME`_I2C_FSM_MSTR_RD_DATA;
                      slaveAddress |= `$INSTANCE_NAME`_I2C_READ_FLAG;
        }

        /* The TX and RX FIFO have to be EMPTY */

        /* Clean-up interrupt status */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_ALL);

        /* Generates a START - the restart should be set first and then address need to be put,
         * Because on write the the byte in TX FIFO treated as DATA byte. ReStart will not be generated */
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_RESTART;

        while(`$INSTANCE_NAME`_CHECK_I2C_MASTER_CMD(`$INSTANCE_NAME`_I2C_MASTER_CMD_M_START))
        {
            /* Wait until ReStart will be generated */
        }

        /* Put address into TX FIFO */
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = slaveAddress;

        /* Wait for the address to be transfered */
        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            /* Wait until address will be transfered */
        }

        /* Check results of address phase */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
             errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else /* INTR_MASTER_I2C_ARB_LOST */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
        }

        /* Clean-up interrupt status */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST);
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterSendStop
********************************************************************************
*
* Summary:
*  Generates I2C Stop condition on bus. Function do nothing if Start or Restart
*  condition was failed before call this function.
*
* Parameters:
*  None
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  The Stop generation is required to complete transaction.
*  This function does not wait while Stop condition will be generated.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterSendStop(void)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before generate Stop condition */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        `$INSTANCE_NAME`_I2C_MASTER_GENERATE_STOP;

        /* Wait NACK and Stop generation: but while NACK generation the lost arbitrage is possible */
        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            /* Wait until Stop will be generated */
        }


        /* Check what was actually generated */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP))
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else /* `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST */
        {
            errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
        }

        `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;

        /* Clean-up interrupt status */
        /* NACK is not captured by end of read: valid only for TX direction */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_STOP |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST);
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterWriteByte
********************************************************************************
*
* Summary:
*  Sends one byte to a slave. A valid Start or ReStart condition must be
*  generated before this call this function. Function do nothing if Start or
*  Restart condition was failed before call this function.
*
* Parameters:
*  data:  The data byte to send to the slave.
*
* Return:
*  Status error - zero means no errors.
*
* Side Effects:
*  This function is entered without a 'byte complete' bit set in the I2C_CSR
*  register. It does not exit until it will be set.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterWriteByte(uint32 theByte)
{
    uint32 errStatus;

    errStatus = `$INSTANCE_NAME`_I2C_MSTR_NOT_READY;

    /* Check FSM state before write byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        `$INSTANCE_NAME`_TX_FIFO_WR_REG = theByte;

        while(!`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                  `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST))
        {
            /* Wait unitl byte will be transfered */
        }

        /* Check results after byte was sent */
        if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_NO_ERROR;
        }
        else if(`$INSTANCE_NAME`_CHECK_INTR_MASTER(`$INSTANCE_NAME`_INTR_MASTER_I2C_NACK))
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_LB_NAK;
        }
        else /* INTR_MASTER_I2C_ARB_LOST */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_IDLE;
                         errStatus = `$INSTANCE_NAME`_I2C_MSTR_ERR_ARB_LOST;
        }

        /* Clean-up interrupt status */
        `$INSTANCE_NAME`_ClearMasterInterruptSource(`$INSTANCE_NAME`_INTR_MASTER_I2C_ACK  |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_NACK |
                                                    `$INSTANCE_NAME`_INTR_MASTER_I2C_ARB_LOST);
    }

    return(errStatus);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterReadByte
********************************************************************************
*
* Summary:
*  Reads one byte from a slave and ACK or NACK the transfer. A valid Start or
*  ReStart condition must be generated before this call this function. Function
*  do nothing if Start or Restart condition was failed before call this
*  function.
*
* Parameters:
*  acknNack:  Zero, response with NACK, if non-zero response with ACK.
*
* Return:
*  Byte read from slave.
*
* Side Effects:
*  This function is entered without a 'byte complete' bit set in the I2C_CSR
*  register. It does not exit until it will be set.
*
* Global variables:
*  `$INSTANCE_NAME`_state - used to store current state of software FSM.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterReadByte(uint32 ackNack)
{
    uint32 theByte;

    theByte = 0u;

    /* Check FSM state before read byte */
    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        while(0u == `$INSTANCE_NAME`_CHECK_INTR_RX(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY))
        {
            /* Wait until byte will be received */
        }

        theByte = `$INSTANCE_NAME`_RX_FIFO_RD_REG;

        `$INSTANCE_NAME`_ClearRxInterruptSource(`$INSTANCE_NAME`_INTR_RX_NOT_EMPTY);

        /* ACK  - generates directly by master CMD.
         * NACK - does nothing. The NACK and STOP are generated by MasterSendStop() */
        if(0u == ackNack)  /* Do ACK */
        {
            `$INSTANCE_NAME`_I2C_MASTER_GENERATE_ACK;
        }
        else /* Do nothing */
        {
            `$INSTANCE_NAME`_state = `$INSTANCE_NAME`_I2C_FSM_MSTR_HALT;
        }
    }

    return(theByte);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetReadBufSize
********************************************************************************
*
* Summary:
*  Returns the amount of bytes that has been transferred with an
*  I2C_MasterReadBuf command.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it will return
*  the byte count transferred so far.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetReadBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrRdBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterGetWriteBufSize
********************************************************************************
*
* Summary:
*  Returns the amount of bytes that has been transferred with an
*  I2C_MasterWriteBuf command.
*
* Parameters:
*  None
*
* Return:
*  Byte count of transfer. If the transfer is not yet complete, it will return
*  the byte count transferred so far.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrWrBufIndex - used to current index within master write
*  buffer.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterGetWriteBufSize(void)
{
    return(`$INSTANCE_NAME`_mstrWrBufIndex);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearReadBuf
********************************************************************************
*
* Summary:
*  Resets the read buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearReadBuf(void)
{
    `$INSTANCE_NAME`_mstrRdBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= ((uint32) ~`$INSTANCE_NAME`_I2C_MSTAT_RD_CMPLT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearWriteBuf
********************************************************************************
*
* Summary:
*  Resets the write buffer pointer back to the first byte in the buffer.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_mstrRdBufIndex - used to current index within master read
*   buffer.
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
void `$INSTANCE_NAME`_I2CMasterClearWriteBuf(void)
{
    `$INSTANCE_NAME`_mstrWrBufIndex = 0u;
    `$INSTANCE_NAME`_mstrStatus    &= ((uint32) ~`$INSTANCE_NAME`_I2C_MSTAT_WR_CMPLT);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterStatus
********************************************************************************
*
* Summary:
*  Returns the master's communication status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterStatus(void)
{
    uint32 status;

    status = `$INSTANCE_NAME`_mstrStatus;

    if(`$INSTANCE_NAME`_CHECK_I2C_MASTER_ACTIVE)
    {
        /* Add status of master pending tranaction: MSTAT_XFER_INP */
        status |= `$INSTANCE_NAME`_I2C_MSTAT_XFER_INP;
    }

    return(status);
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_I2CMasterClearStatus
********************************************************************************
*
* Summary:
*  Clears all status flags and returns the master status.
*
* Parameters:
*  None
*
* Return:
*  Current status of I2C master.
*
* Global variables:
*  `$INSTANCE_NAME`_mstrStatus - used to store current status of I2C Master.
*
*******************************************************************************/
uint32 `$INSTANCE_NAME`_I2CMasterClearStatus(void)
{
    uint32 status;

    /* Read and clear master status */
    status = `$INSTANCE_NAME`_mstrStatus;
    `$INSTANCE_NAME`_mstrStatus = `$INSTANCE_NAME`_I2C_MSTAT_CLEAR;

    return(status);
}

#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */


/* [] END OF FILE */
