/*******************************************************************************
* File Name: `$INSTANCE_NAME`_PINS.h
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

#if !defined(CY_SCB_PINS_`$INSTANCE_NAME`_H)
#define CY_SCB_PINS_`$INSTANCE_NAME`_H

/***************************************
*   Conditional compilation parameters
****************************************/

#define `$INSTANCE_NAME`_REMOVE_UART_RX_WAKE_PIN        (`$RemoveUartRxWake`u)
#define `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_WAKE_PIN    (`$RemoveMosiSclRxWake`u)
#define `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_PIN         (`$RemoveMosiSclRx`u)
#define `$INSTANCE_NAME`_REMOVE_MISO_SDA_TX_PIN         (`$RemoveMisoSdaTx`u)
#define `$INSTANCE_NAME`_REMOVE_SCLK_PIN                (`$RemoveSpiSclk`u)
#define `$INSTANCE_NAME`_REMOVE_SS0_PIN                 (`$RemoveSpiSs0`u)
#define `$INSTANCE_NAME`_REMOVE_SS1_PIN                 (`$RemoveSpiSs1`u)
#define `$INSTANCE_NAME`_REMOVE_SS2_PIN                 (`$RemoveSpiSs2`u)
#define `$INSTANCE_NAME`_REMOVE_SS3_PIN                 (`$RemoveSpiSs3`u)

#define `$INSTANCE_NAME`_UART_RX_WAKE_PIN       (0u == `$INSTANCE_NAME`_REMOVE_UART_RX_WAKE_PIN)

#define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN   (0u == `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_WAKE_PIN)
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN        (0u == `$INSTANCE_NAME`_REMOVE_MOSI_SCL_RX_PIN)
#define `$INSTANCE_NAME`_MISO_SDA_TX_PIN        (0u == `$INSTANCE_NAME`_REMOVE_MISO_SDA_TX_PIN)
#define `$INSTANCE_NAME`_SCLK_PIN               (0u == `$INSTANCE_NAME`_REMOVE_SCLK_PIN)
#define `$INSTANCE_NAME`_SS0_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS0_PIN)
#define `$INSTANCE_NAME`_SS1_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS1_PIN)
#define `$INSTANCE_NAME`_SS2_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS2_PIN)
#define `$INSTANCE_NAME`_SS3_PIN                (0u == `$INSTANCE_NAME`_REMOVE_SS3_PIN)


/***************************************
*   Includes
****************************************/

#if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
    #include "`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake.h"
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN) */

#if(`$INSTANCE_NAME`_MOSI_SCL_RX_PIN)
    #include "`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx.h"
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

#if(`$INSTANCE_NAME`_MISO_SDA_TX_PIN)
    #include "`$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx.h"
#endif /* (`$INSTANCE_NAME`_MISO_SDA_TX_PIN_PIN) */

#if(`$INSTANCE_NAME`_SCLK_PIN)
    #include "`$INSTANCE_NAME`_spi_clk.h"
#endif /* (`$INSTANCE_NAME`_SCLK_PIN) */

#if(`$INSTANCE_NAME`_SS0_PIN)
    #include "`$INSTANCE_NAME`_spi_ss0.h"
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if(`$INSTANCE_NAME`_SS1_PIN)
    #include "`$INSTANCE_NAME`_spi_ss1.h"
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if(`$INSTANCE_NAME`_SS2_PIN)
    #include "`$INSTANCE_NAME`_spi_ss2.h"
#endif /* (`$INSTANCE_NAME`_SS2_PIN) */

#if(`$INSTANCE_NAME`_SS3_PIN)
    #include "`$INSTANCE_NAME`_spi_ss3.h"
#endif /* (`$INSTANCE_NAME`_SS3_PIN) */


/***************************************
*              Registers
***************************************/

#if(`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_REG     \
                                                (*(reg32 *) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM_PTR     \
                                                ( (reg32 *) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM__MASK   \
                                                (`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_HSIOM__POS    \
                                                (`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__HSIOM_SHIFT)

    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_REG    (*(reg32 *) \
                                                              `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_PTR    ( (reg32 *) \
                                                              `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__0__INTCFG)

    #define `$INSTANCE_NAME`_INTCFG_TYPE__MASK                  (0x03u)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE__POS  (`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx_wake__SHIFT)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE__MASK (`$INSTANCE_NAME`_INTCFG_TYPE__MASK << \
                                                                    `$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_INTCFG_TYPE__POS)

#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_WAKE_PIN) */

#if(`$INSTANCE_NAME`_MOSI_SCL_RX_PIN)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx__0__HSIOM)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM__MASK    (`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MOSI_SCL_RX_HSIOM__POS     (`$INSTANCE_NAME`_spi_mosi_i2c_scl_uart_rx__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN) */

#if(`$INSTANCE_NAME`_MISO_SDA_TX_PIN)
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx__0__HSIOM)
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM__MASK    (`$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_MISO_SDA_TX_HSIOM__POS     (`$INSTANCE_NAME`_spi_miso_i2c_sda_uart_tx__0__HSIOM_SHIFT)

#endif /* (`$INSTANCE_NAME`_MISO_SDA_TX_PIN_PIN) */

#if(`$INSTANCE_NAME`_SCLK_PIN)
    #define `$INSTANCE_NAME`_SCLK_HSIOM_REG     (*(reg32 *) `$INSTANCE_NAME`_spi_clk__0__HSIOM)
    #define `$INSTANCE_NAME`_SCLK_HSIOM_PTR     ( (reg32 *) `$INSTANCE_NAME`_spi_clk__0__HSIOM)
    #define `$INSTANCE_NAME`_SCLK_HSIOM__MASK   (`$INSTANCE_NAME`_spi_clk__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SCLK_HSIOM__POS    (`$INSTANCE_NAME`_spi_clk__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_SCLK_PIN) */

#if(`$INSTANCE_NAME`_SS0_PIN)
    #define `$INSTANCE_NAME`_SS0_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_ss0__0__HSIOM)
    #define `$INSTANCE_NAME`_SS0_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_ss0__0__HSIOM)
    #define `$INSTANCE_NAME`_SS0_HSIOM__MASK    (`$INSTANCE_NAME`_spi_ss0__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS0_HSIOM__POS     (`$INSTANCE_NAME`_spi_ss0__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if(`$INSTANCE_NAME`_SS1_PIN)
    #define `$INSTANCE_NAME`_SS1_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_ss1__0__HSIOM)
    #define `$INSTANCE_NAME`_SS1_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_ss1__0__HSIOM)
    #define `$INSTANCE_NAME`_SS1_HSIOM__MASK    (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS1_HSIOM__POS     (`$INSTANCE_NAME`_spi_ss1__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_SS1_PIN) */

#if(`$INSTANCE_NAME`_SS2_PIN)
    #define `$INSTANCE_NAME`_SS2_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_ss2__0__HSIOM)
    #define `$INSTANCE_NAME`_SS2_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_ss2__0__HSIOM)
    #define `$INSTANCE_NAME`_SS2_HSIOM__MASK    (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS2_HSIOM__POS     (`$INSTANCE_NAME`_spi_ss2__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_SS2_PIN) */

#if(`$INSTANCE_NAME`_SS3_PIN)
    #define `$INSTANCE_NAME`_SS3_HSIOM_REG      (*(reg32 *) `$INSTANCE_NAME`_spi_ss3__0__HSIOM)
    #define `$INSTANCE_NAME`_SS3_HSIOM_PTR      ( (reg32 *) `$INSTANCE_NAME`_spi_ss3__0__HSIOM)
    #define `$INSTANCE_NAME`_SS3_HSIOM__MASK    (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_MASK)
    #define `$INSTANCE_NAME`_SS3_HSIOM__POS     (`$INSTANCE_NAME`_spi_ss3__0__HSIOM_SHIFT)
#endif /* (`$INSTANCE_NAME`_SS3_PIN) */


/***************************************
*        Registers Constants
***************************************/

/* Pins constanst */
#define `$INSTANCE_NAME`_HSIOM_DEF_SEL      (0x00u)
#define `$INSTANCE_NAME`_HSIOM_UART_SEL     (0x09u)
#define `$INSTANCE_NAME`_HSIOM_I2C_SEL      (0x0Eu)
#define `$INSTANCE_NAME`_HSIOM_SPI_SEL      (0x0Fu)

#define `$INSTANCE_NAME`_SCB_PINS_NUMBER        (7u)
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX  (0u)
#define `$INSTANCE_NAME`_MISO_SDA_TX_PIN_INDEX  (1u)
#define `$INSTANCE_NAME`_SCLK_PIN_INDEX         (2u)
#define `$INSTANCE_NAME`_SS0_PIN_INDEX          (3u)
#define `$INSTANCE_NAME`_SS1_PIN_INDEX          (4u)
#define `$INSTANCE_NAME`_SS2_PIN_INDEX          (5u)
#define `$INSTANCE_NAME`_SS3_PIN_INDEX          (6u)
#define `$INSTANCE_NAME`_MOSI_SCL_RX_PIN_WAKE_INDEX (`$INSTANCE_NAME`_MOSI_SCL_RX_PIN_INDEX)

#define `$INSTANCE_NAME`_INTCFG_TYPE_RASING_EDGE    (0x02u)

/* Pin DM defines */
#define PIN_DM_ALG_HIZ          (0u)
#define PIN_DM_DIG_HIZ          (1u)
#define PIN_DM_OD_LO            (4u)
#define PIN_DM_STRONG           (6u)


/***************************************
*          Macros
***************************************/

#define `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, mode)    ((reg) = (((reg) & ((uint32)(~(mask)))) | ((uint32)((mode) << (pos)))))

#define `$INSTANCE_NAME`_SET_HSIOM_SEL(reg, mask, pos, sel) `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, sel)
#define `$INSTANCE_NAME`_SET_INCFG_TYPE(reg, mask, pos, intType)    \
                                                        `$INSTANCE_NAME`_SET_REGISTER_BITS(reg, mask, pos, intType)

#define `$INSTANCE_NAME`_CLEAR_INSTAT(reg, mask)    {reg = mask;}

#endif /* (CY_SCB_PINS_`$INSTANCE_NAME`_H) */


/* [] END OF FILE */
