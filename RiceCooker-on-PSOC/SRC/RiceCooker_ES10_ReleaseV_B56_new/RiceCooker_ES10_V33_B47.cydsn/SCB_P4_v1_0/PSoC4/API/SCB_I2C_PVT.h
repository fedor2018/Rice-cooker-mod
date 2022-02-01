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

#if !defined(CY_SCB_I2C_PVT_`$INSTANCE_NAME`_H)
#define CY_SCB_I2C_PVT_`$INSTANCE_NAME`_H

#include "`$INSTANCE_NAME`_I2C.h"

extern volatile uint8 `$INSTANCE_NAME`_state;          /* Current state of I2C FSM         */
extern volatile uint8 `$INSTANCE_NAME`_wakeupSource;   /* Defines if I2C was wakeup source */

/* Master variables */
#if(`$INSTANCE_NAME`_I2C_MASTER_CONST)
    extern volatile uint16 `$INSTANCE_NAME`_mstrStatus;        /* Master Status byte            */
    extern volatile uint8  `$INSTANCE_NAME`_mstrControl;       /* Master Control byte           */

    /* Transmit buffer variables */
    extern volatile uint8 * `$INSTANCE_NAME`_mstrRdBufPtr;     /* Pointer to Master Read buffer  */
    extern volatile uint32  `$INSTANCE_NAME`_mstrRdBufSize;    /* Master Read buffer size        */
    extern volatile uint32  `$INSTANCE_NAME`_mstrRdBufIndex;   /* Master Read buffer Index       */

    /* Receive buffer variables */
    extern volatile uint8 * `$INSTANCE_NAME`_mstrWrBufPtr;     /* Pointer to Master Write buffer */
    extern volatile uint32  `$INSTANCE_NAME`_mstrWrBufSize;    /* Master Write buffer size       */
    extern volatile uint32  `$INSTANCE_NAME`_mstrWrBufIndex;   /* Master Write buffer Index      */
#endif /* (`$INSTANCE_NAME`_I2C_MASTER_CONST) */

#if(`$INSTANCE_NAME`_I2C_SLAVE_CONST)
    extern volatile uint8 `$INSTANCE_NAME`_slStatus;       /* Slave Status                */

    /* Transmit buffer variables */
    extern volatile uint8 * `$INSTANCE_NAME`_slRdBufPtr;   /* Pointer to Transmit buffer  */
    extern volatile uint32  `$INSTANCE_NAME`_slRdBufSize;  /* Slave Transmit buffer size  */
    extern volatile uint32  `$INSTANCE_NAME`_slRdBufIndex; /* Slave Transmit buffer Index */

    /* Receive buffer variables */
    extern volatile uint8 * `$INSTANCE_NAME`_slWrBufPtr;   /* Pointer to Receive buffer   */
    extern volatile uint32  `$INSTANCE_NAME`_slWrBufSize;  /* Slave Receive buffer size   */
    extern volatile uint32  `$INSTANCE_NAME`_slWrBufIndex; /* Slave Receive buffer Index  */
    extern volatile uint32  `$INSTANCE_NAME`_slOverFlowCount;  /* Slave Transmit Overflow counter */
#endif /* (`$INSTANCE_NAME`_I2C_SLAVE_CONST) */

#endif /* (CY_SCB_I2C_PVT_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
