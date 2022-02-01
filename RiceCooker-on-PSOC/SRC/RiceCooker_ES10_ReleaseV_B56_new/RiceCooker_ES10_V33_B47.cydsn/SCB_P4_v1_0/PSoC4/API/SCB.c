/*******************************************************************************
* File Name: `$INSTANCE_NAME`.c
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

#include "`$INSTANCE_NAME`.h"

/**********************************
*      System variables
**********************************/

uint8 `$INSTANCE_NAME`_initVar = 0u;

#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    /* Stores internal component configuration for unconfigured mode */
    volatile uint32 `$INSTANCE_NAME`_scbMode;
    volatile void * `$INSTANCE_NAME`_scbCfg = NULL;

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */

void (* `$INSTANCE_NAME`_customIntrHandler) (void) = NULL;


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Init
********************************************************************************
*
* Summary:
*
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Init(void)
{
    #if(`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG)
        `$INSTANCE_NAME`_I2CInit((`$INSTANCE_NAME`_I2C_INIT_STRUCT *) &`$INSTANCE_NAME`_configI2C);

    #elif(`$INSTANCE_NAME`_SCB_MODE_SPI_CONST_CFG)
        `$INSTANCE_NAME`_SpiInit((`$INSTANCE_NAME`_SPI_INIT_STRUCT *) &`$INSTANCE_NAME`_configSpi);

    #elif(`$INSTANCE_NAME`_SCB_MODE_UART_CONST_CFG)
        `$INSTANCE_NAME`_UartInit((`$INSTANCE_NAME`_UART_INIT_STRUCT *) &`$INSTANCE_NAME`_configUart);

    #elif(`$INSTANCE_NAME`_SCB_MODE_EZI2C_CONST_CFG)
        `$INSTANCE_NAME`_EzI2CInit((`$INSTANCE_NAME`_EZI2C_INIT_STRUCT *) &`$INSTANCE_NAME`_configEzI2C);

    #elif(`$INSTANCE_NAME`_SCB_MODE_EZSPI_CONST_CFG)
        `$INSTANCE_NAME`_EzSpiInit((`$INSTANCE_NAME`_EZSPI_INIT_STRUCT *) &`$INSTANCE_NAME`_configEzSpi);

    #else
        /* The mode to enable is unknown */
        `$INSTANCE_NAME`_scbMode = `$INSTANCE_NAME`_SCB_MODE_UNCONFIG;
        `$INSTANCE_NAME`_scbCfg  = NULL;

    #endif /* (`$INSTANCE_NAME`_SCB_MODE_I2C_CONST_CFG) */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Enable
********************************************************************************
*
* Summary:
*
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Enable(void)
{
    `$INSTANCE_NAME`_CTRL_REG |= `$INSTANCE_NAME`_CTRL_ENABLED;  /* Enable SCB block */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Start
********************************************************************************
*
* Summary:
*
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  `$INSTANCE_NAME`_initVar - used to check initial configuration, modified
*  on first function call.
*
*******************************************************************************/
void `$INSTANCE_NAME`_Start(void)
{
    if(0u == `$INSTANCE_NAME`_initVar)
    {
        `$INSTANCE_NAME`_Init();       /* Initialize component */
        `$INSTANCE_NAME`_initVar = 1u; /* SCB was initialized  */
    }

    `$INSTANCE_NAME`_Enable();
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_Stop
********************************************************************************
*
* Summary:
*
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void `$INSTANCE_NAME`_Stop(void)
{
    `$INSTANCE_NAME`_CTRL_REG &= ~`$INSTANCE_NAME`_CTRL_ENABLED;  /* Disable SCB block */
}


/*******************************************************************************
* Function Name: `$INSTANCE_NAME`_SetCustomInterruptHandler
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
void `$INSTANCE_NAME`_SetCustomInterruptHandler(void (*func) (void))
{
    `$INSTANCE_NAME`_customIntrHandler = func;  /* Register interrupt handler */
}


#if(`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG)
    /*******************************************************************************
    * Function Name: `$INSTANCE_NAME`_SetPins
    ********************************************************************************
    *
    * Summary:
    *
    * Parameters:
    *
    *
    * Return:
    *  None
    *
    *******************************************************************************/
    void `$INSTANCE_NAME`_SetPins(uint32 mode, uint32 subMode, uint32 spiSsUartTxRx)
    {
        uint32 hsiomSel;
        uint8 pinsDm[`$INSTANCE_NAME`_SCB_PINS_NUMBER];
        uint32 i;

        /* Make all unused */
        for(i=0u; i<`$INSTANCE_NAME`_SCB_PINS_NUMBER; i++)
        {
            pinsDm[i] = PIN_DM_ALG_HIZ;
        }

        /* Choice the Dm and HSIOM */
        if((`$INSTANCE_NAME`_SCB_MODE_I2C   == mode) ||
           (`$INSTANCE_NAME`_SCB_MODE_EZI2C == mode))
        {
            hsiomSel  = `$INSTANCE_NAME`_HSIOM_I2C_SEL;

            pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX] = ((uint8) PIN_DM_OD_LO);
            pinsDm[`$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX] = ((uint8) PIN_DM_OD_LO);
        }
        else if((`$INSTANCE_NAME`_SCB_MODE_SPI   == mode) ||
                (`$INSTANCE_NAME`_SCB_MODE_EZSPI == mode))
        {
            hsiomSel =  `$INSTANCE_NAME`_HSIOM_SPI_SEL;

            if(`$INSTANCE_NAME`_SPI_SLAVE == subMode)
            {
                pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX] = ((uint8) PIN_DM_DIG_HIZ);
                pinsDm[`$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                pinsDm[`$INSTANCE_NAME`_SCLK_PIN_INDEX]        = ((uint8) PIN_DM_DIG_HIZ);
                pinsDm[`$INSTANCE_NAME`_SS0_PIN_INDEX]         = ((uint8) PIN_DM_DIG_HIZ);
            }
            else /* (Master) */
            {
                pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                pinsDm[`$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX] = ((uint8) PIN_DM_DIG_HIZ);
                pinsDm[`$INSTANCE_NAME`_SCLK_PIN_INDEX]        = ((uint8) PIN_DM_STRONG);

                if(0ul != spiSsUartTxRx)
                {
                    pinsDm[`$INSTANCE_NAME`_SS0_PIN_INDEX] = ((uint8) PIN_DM_STRONG);

                    if(spiSsUartTxRx > 1ul)
                    {
                        pinsDm[`$INSTANCE_NAME`_SS1_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                    }

                    if(spiSsUartTxRx > 2ul)
                    {
                        pinsDm[`$INSTANCE_NAME`_SS2_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                    }

                    if(spiSsUartTxRx > 3ul)
                    {
                        pinsDm[`$INSTANCE_NAME`_SS3_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                    }
                }
            }
        }
        else /* UART */
        {
            hsiomSel =  `$INSTANCE_NAME`_HSIOM_UART_SEL;

            if(`$INSTANCE_NAME`_UART_MODE_SMARTCARD == subMode)
            {
                pinsDm[`$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX] = ((uint8) PIN_DM_OD_LO);
            }
            else
            {
                if(0u != (`$INSTANCE_NAME`_UART_RX & spiSsUartTxRx))
                {
                    pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX] = ((uint8) PIN_DM_DIG_HIZ);
                }

                if(0u != (`$INSTANCE_NAME`_UART_TX & spiSsUartTxRx))
                {
                    pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX] = ((uint8) PIN_DM_STRONG);
                }
            }
        }

        /* Condfigure pins: set HSIOM and DM */

        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_REG, `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM__MASK,
                                           `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

        #if(`$INSTANCE_NAME`_MISO_SDA_TX_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_REG, `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM__MASK,
                                           `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

        #if(`$INSTANCE_NAME`_SCLK_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SCLK_HSIOM_REG, `$INSTANCE_NAME`_SCLK_HSIOM__MASK,
                                           `$INSTANCE_NAME`_SCLK_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_SCLK_PIN) */

        #if(`$INSTANCE_NAME`_SS0_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS0_HSIOM_REG, `$INSTANCE_NAME`_SS0_HSIOM__MASK,
                                           `$INSTANCE_NAME`_SS0_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

        #if(`$INSTANCE_NAME`_SS1_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS1_HSIOM_REG, `$INSTANCE_NAME`_SS1_HSIOM__MASK,
                                           `$INSTANCE_NAME`_SS1_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

        #if(`$INSTANCE_NAME`_SS2_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS2_HSIOM_REG, `$INSTANCE_NAME`_SS2_HSIOM__MASK,
                                           `$INSTANCE_NAME`_SS2_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

        #if(`$INSTANCE_NAME`_SS3_PIN)
            `$INSTANCE_NAME`_SET_HSIOM_SEL(`$INSTANCE_NAME`_SS3_HSIOM_REG,  `$INSTANCE_NAME`_SS3_HSIOM__MASK,
                                           `$INSTANCE_NAME`_SS3_HSIOM__POS, hsiomSel);
        #endif /* (`$INSTANCE_NAME`_SS3_PIN) */


        /******** Set DM ********/
        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
            `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake_SetDriveMode(pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_WAKE_INDEX]);

            /* Set interrupt on rising edge */
            `$INSTANCE_NAME`_SET_INCFG_TYPE(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_REG,
                                            `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE__MASK,
                                            `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE__POS,
                                            `$INSTANCE_NAME`_INTCFG_TYPE_RASING_EDGE);

        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

        #if(`$INSTANCE_NAME`_MOSI_SCL_RX_PIN)
            `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_SetDriveMode(pinsDm[`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

        #if(`$INSTANCE_NAME`_MISO_SDA_TX_PIN)
            `$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx_SetDriveMode(pinsDm[`$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */


        #if(`$INSTANCE_NAME`_SCLK_PIN)
            `$INSTANCE_NAME`_spi_clk_SetDriveMode(pinsDm[`$INSTANCE_NAME`_SCLK_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_SCLK_PIN) */

        #if(`$INSTANCE_NAME`_SS0_PIN)
            `$INSTANCE_NAME`_spi_ss0_SetDriveMode(pinsDm[`$INSTANCE_NAME`_SS0_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_SS0_PIN) */

        #if(`$INSTANCE_NAME`_SS1_PIN)
            `$INSTANCE_NAME`_spi_ss1_SetDriveMode(pinsDm[`$INSTANCE_NAME`_SS1_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_SS1_PIN) */

        #if(`$INSTANCE_NAME`_SS2_PIN)
            `$INSTANCE_NAME`_spi_ss2_SetDriveMode(pinsDm[`$INSTANCE_NAME`_SS2_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_SS2_PIN) */

        #if(`$INSTANCE_NAME`_SS3_PIN)
            `$INSTANCE_NAME`_spi_ss3_SetDriveMode(pinsDm[`$INSTANCE_NAME`_SS3_PIN_INDEX]);
        #endif /* (`$INSTANCE_NAME`_SS3_PIN) */
    }

#endif /* (`$INSTANCE_NAME`_SCB_MODE_UNCFG_CONST_CFG) */


/* [] END OF FILE */
