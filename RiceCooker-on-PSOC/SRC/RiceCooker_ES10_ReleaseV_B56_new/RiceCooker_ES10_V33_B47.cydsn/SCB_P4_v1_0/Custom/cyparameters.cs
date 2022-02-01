/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;
using System.ComponentModel;
using System.Reflection;
using System.Windows.Forms;

namespace SCB_P4_v1_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string SCB_MODE = "ScbMode";
        public const string SCB_MOSI_SCL_RX_ENABLED = "ScbMosiSclRxEnable";
        public const string SCB_SCL_KENABLED = "ScbSclkEnable";
        public const string SCB_RX_WAKE = "ScbRxWakeIrqEnable";
        public const string SCB_SS0_ENABLED = "ScbSs0Enable";
        public const string SCB_SS1_ENABLED = "ScbSs1Enable";
        public const string SCB_SS2_ENABLED = "ScbSs2Enable";
        public const string SCB_SS3_ENABLED = "ScbSs3Enable";
        public const string SCB_MISO_SDA_TX_ENABLED = "ScbMisoSdaTxEnable";
    }
    #endregion

    #region Enums
    public enum CyESCBMode
    {
        [Description("EZI2C")]
        EZI2C = 8,
        [Description("I2C")]
        I2C = 1,
        [Description("UART")]
        UART = 4,
        [Description("SPI")]
        SPI = 2,
        [Description("EZSPI")]
        EZSPI = 16,
        [Description("Unconfigured SCB")]
        UNCONFIG = 31
    }

    public enum CyEInterruptModeType { INTERNAL = 1, EXTERNAL = 2, INTERRUPT_NONE = 0 }
    #endregion

    public partial class CyParamRanges
    {
        public const double MIN_CLK_VALUE = 0.0000001;
        public const double MAX_CLK_VALUE = 1000;
        private const double KHZ_DEVIDER = 1000;
    }

    public partial class CyParameters
    {
        #region Clock data
        public const string SCB_CLOCK_SCBCLK = "or_sclk";
        public const string SCB_CLOCK_TERM = "clock";
        private const double KHZ_DIVIDER = 1000;
        #endregion

        public ICyInstQuery_v1 m_inst;
        public ICyTabbedParamEditor m_editor = null;
        public ICyTerminalQuery_v1 m_term;

        // During first getting of parameters this variable is false, what means that assigning
        // values to form controls will not immediatly overwrite parameters with the same values.
        private bool m_bGlobalEditMode = false;

        public bool GlobalEditMode
        {
            get { return m_bGlobalEditMode; }
            set { m_bGlobalEditMode = value; }
        }

        // References to tabs used in the customizer
        public CyGeneralTab m_generalTab;
        public CySCBTab m_scbTab;
        public CyEZI2CTab m_ezI2CTab;
        public CyEZI2CAdvancedTab m_ezI2CAdvancedTab;
        public CyEZSPITab m_ezSPITab;
        public CyEZSPIAdvancedTab m_ezSPIAdvancedTab;
        public CyI2CTab m_i2cTab;
        public CyUARTConfigureTab m_uartConfigTab;
        public CyUARTAdvancedTab m_uartAdvancedTab;
        public CySPIBasicTab m_spiBasicTab;
        public CySPIAdvancedTab m_spiAdvancedTab;

        #region Constructor(s)
        public CyParameters(ICyInstQuery_v1 inst)
        {
            m_inst = inst;
        }
        #endregion

        #region Getting Parameters
        private T GetValue<T>(string paramName)
        {
            T value;
            CyCustErr err = m_inst.GetCommittedParam(paramName).TryGetValueAs<T>(out value);
            if (err != null && err.IsOK)
            {
                return value;
            }
            else
            {
                return default(T);
            }
        }
        #endregion

        #region Setting Parameters
        private void SetValue<T>(string paramName, T value)
        {
            if (m_bGlobalEditMode)
            {
                if ((m_inst is ICyInstEdit_v1) == false) return;

                string valueToSet = value.ToString();
                if (value is bool)
                    valueToSet = valueToSet.ToLower();
                if ((m_inst as ICyInstEdit_v1).SetParamExpr(paramName, valueToSet.ToString()))
                {
                    (m_inst as ICyInstEdit_v1).CommitParamExprs();
                }
            }
        }
        #endregion

        #region Class properties
        public CyESCBMode SCBMode
        {
            get { return GetValue<CyESCBMode>(CyParamNames.SCB_MODE); }
            set { SetValue(CyParamNames.SCB_MODE, value); }
        }

        public bool SCB_MosiSclRxEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_MOSI_SCL_RX_ENABLED); }
            set { SetValue(CyParamNames.SCB_MOSI_SCL_RX_ENABLED, value); }
        }

        public bool SCB_SclkEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SCL_KENABLED); }
            set { SetValue(CyParamNames.SCB_SCL_KENABLED, value); }
        }

        public bool SCB_RxWake
        {
            get { return GetValue<bool>(CyParamNames.SCB_RX_WAKE); }
            set { SetValue(CyParamNames.SCB_RX_WAKE, value); }
        }

        public bool SCB_Ss0Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS0_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS0_ENABLED, value); }
        }

        public bool SCB_Ss1Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS1_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS1_ENABLED, value); }
        }

        public bool SCB_Ss2Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS2_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS2_ENABLED, value); }
        }

        public bool SCB_Ss3Enabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_SS3_ENABLED); }
            set { SetValue(CyParamNames.SCB_SS3_ENABLED, value); }
        }

        public bool SCB_MisoSdaTxEnabled
        {
            get { return GetValue<bool>(CyParamNames.SCB_MISO_SDA_TX_ENABLED); }
            set { SetValue(CyParamNames.SCB_MISO_SDA_TX_ENABLED, value); }
        }
        #endregion

        #region Service functions
        /// <summary>
        /// Show/hide tabs depending on the configuration
        /// </summary>
        public void UpdateTabVisibility()
        {
            if ((m_editor == null) || (m_scbTab == null) || (m_i2cTab == null) || (m_ezI2CTab == null) ||
                (m_ezSPITab == null) || (m_uartConfigTab == null) || (m_uartAdvancedTab == null) ||
                (m_spiBasicTab == null) || (m_spiAdvancedTab == null) )
            {
                return;
            }

            m_editor.ShowCustomPage(Resources.SCBTabDisplayName);
            m_editor.ShowCustomPage(Resources.I2CTabDisplayName);
            m_editor.ShowCustomPage(Resources.SPIBasicTabDisplayName);
            m_editor.ShowCustomPage(Resources.SPIAdvancedTabDisplayName);
            m_editor.ShowCustomPage(Resources.UARTConfigTabDisplayName);
            m_editor.ShowCustomPage(Resources.UARTAdvancedTabDisplayName);
            m_editor.ShowCustomPage(Resources.EZI2CBasicTabDisplayName);
            m_editor.ShowCustomPage(Resources.EZI2CAdvancedTabDisplayName);
            m_editor.ShowCustomPage(Resources.EZSPIBasicTabDisplayName);
            m_editor.ShowCustomPage(Resources.EZSPIAdvancedTabDisplayName);

            switch (SCBMode)
            {
                case CyESCBMode.UNCONFIG:
                    m_editor.HideCustomPage(Resources.I2CTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTConfigTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIAdvancedTabDisplayName);
                    break;
                case CyESCBMode.EZSPI:
                    m_editor.HideCustomPage(Resources.SCBTabDisplayName);
                    m_editor.HideCustomPage(Resources.I2CTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTConfigTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CAdvancedTabDisplayName);
                    break;
                case CyESCBMode.EZI2C:
                    m_editor.HideCustomPage(Resources.SCBTabDisplayName);
                    m_editor.HideCustomPage(Resources.I2CTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTConfigTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIAdvancedTabDisplayName);
                    break;
                case CyESCBMode.I2C:
                    m_editor.HideCustomPage(Resources.SCBTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTConfigTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIAdvancedTabDisplayName);
                    break;
                case CyESCBMode.UART:
                    m_editor.HideCustomPage(Resources.SCBTabDisplayName);
                    m_editor.HideCustomPage(Resources.I2CTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.SPIAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIAdvancedTabDisplayName);
                    break;
                case CyESCBMode.SPI:
                    m_editor.HideCustomPage(Resources.SCBTabDisplayName);
                    m_editor.HideCustomPage(Resources.I2CTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTConfigTabDisplayName);
                    m_editor.HideCustomPage(Resources.UARTAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZI2CAdvancedTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIBasicTabDisplayName);
                    m_editor.HideCustomPage(Resources.EZSPIAdvancedTabDisplayName);
                    break;
            }
        }

        public void UpdateDesigns(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery)
        {
            if (m_i2cTab != null)
                m_i2cTab.UpdateClock();
            if (m_spiBasicTab != null)
                m_spiBasicTab.UpdateClock();
            if (m_uartConfigTab != null)
                m_uartConfigTab.UpdateClock();
            if (m_ezI2CTab != null)
                m_ezI2CTab.UpdateClock();
            if (m_ezSPITab != null)
                m_ezSPITab.UpdateClock();
        }

        /// <summary>
        /// Returns internal clock value
        /// </summary>
        public static double GetInternalClock(ICyTerminalQuery_v1 termQuery)
        {
            return GetInternalClock(termQuery, SCB_CLOCK_SCBCLK);
        }

        public static double GetExternalClock(ICyTerminalQuery_v1 termQuery)
        {
            List<CyClockData> clkdata = termQuery.GetClockData(SCB_CLOCK_TERM, 0);
            if (clkdata.Count > 0)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);                    
                }
            }
            return (-1);
        }

        public static double GetInternalClock(ICyTerminalQuery_v1 termQuery, string clock)
        {
            List<CyClockData> clkdata = new List<CyClockData>();

            clkdata = termQuery.GetClockData(clock, "term1", 0);

            if (clkdata.Count == 1)
            {
                if (clkdata[0].IsFrequencyKnown)
                {
                    return clkdata[0].Frequency * Math.Pow(10, clkdata[0].UnitAsExponent - 3);
                }
            }
            return -1;
        }
        #endregion Service functions

        #region Get descriptions list
        /// <summary>
        /// This method returns array of strings - descriptions of the enumeration that is a type of the parameter with
        /// name specified in paramName.
        /// </summary>
        /// <param name="paramName">Name of the parameter. The parameters should be enum type</param>
        /// <returns>List of the enumeration descriptions</returns>
        public string[] GetEnumDescriptions(string paramName)
        {
            return new List<string>(m_inst.GetPossibleEnumValues(paramName)).ToArray();
        }

        /// <summary>
        /// Get the description for the parameter with name <b><i>paramName</i></b> and <b><i>value</i></b>.
        /// </summary>
        /// <param name="paramName">Parameter name</param>
        /// <param name="value">Value. It should be enumeration type item ID</param>
        /// <returns>The description of the item. If the item ID cannot be resolved, returns string representation of
        /// the <b><i>value</i></b></returns>
        public string GetValueDescription(string paramName, object value)
        {
            return m_inst.ResolveEnumIdToDisplay(paramName, value.ToString());
        }

        /// <summary>
        /// Get the enum item value by parameter name and enum item description.
        /// </summary>
        /// <typeparam name="T">Type of the enumeration, that is a C# type equivalent to the symbol's enumeration.
        /// </typeparam>
        /// <param name="paramName">Name of the parameter</param>
        /// <param name="displayText">Description of the enumeration item</param>
        /// <returns>Enum item value that has specified description in symbol</returns>
        public T GetEnumValue<T>(string paramName, string displayText)
        {
            T enumValue;
            string enumItemName = m_inst.ResolveEnumDisplayToId(paramName, displayText);

            try
            {
                enumValue = (T)Enum.Parse(typeof(T), enumItemName);
            }
            catch
            {
                enumValue = default(T);
            }

            return enumValue;
        }
        #endregion
    }
}
