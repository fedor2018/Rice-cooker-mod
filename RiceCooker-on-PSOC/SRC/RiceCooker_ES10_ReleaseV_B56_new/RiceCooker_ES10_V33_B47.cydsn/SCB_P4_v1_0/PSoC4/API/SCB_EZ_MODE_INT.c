/*******************************************************************************
* File Name: `$INSTANCE_NAME`_EZ_MODE_INT.c
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

#include "`$INSTANCE_NAME`_EZ_MODE.h"


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_EZ_MODE_ISR
********************************************************************************
*
* Summary:
*  Handle Interrupt Service Routine.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
CY_ISR(`$INSTANCE_NAME`_EZ_MODE_ISR)
{
    if(NULL != `$INSTANCE_NAME`_customIntrHandler)
    {
        `$INSTANCE_NAME`_customIntrHandler();    /* Call customer routine if needed */
    }
}


/* [] END OF FILE */
