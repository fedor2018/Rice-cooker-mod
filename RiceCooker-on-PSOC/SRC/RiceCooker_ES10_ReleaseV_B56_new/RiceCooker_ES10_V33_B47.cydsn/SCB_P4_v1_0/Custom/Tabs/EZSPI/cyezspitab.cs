/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v1_0
{
    public partial class CyEZSPITab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "EZSPI";
            }
        }
        #endregion

        #region Constructor(s)
        public CyEZSPITab(CyParameters parameters)
            : base(parameters)
        {
            m_params.m_ezSPITab = this;

            InitializeComponent();

            InitializeBitRates();

            m_cbClkMode.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.EZSPI_OPERATION_MODE));

            m_chbClkFromTerm.Tag = m_params.EZSPI_ClockFromTerminal;
            m_chbEnMedianFilter.Tag = m_params.EZSPI_MedianFilterEnabled;
            m_chbEnWakeUp.Tag = m_params.EZSPI_EnableWakeUpFromSleepMode;

            // Load image
            pbDrawing.Image = Resources.Motorola_00;

            #region Init event handlers
            m_cbClkMode.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_cbBitRate.TextChanged += new EventHandler(m_cb_TextChanged);

            m_numOvsFactor.TextChanged += new EventHandler(m_num_TextChanged);

            m_radioWaitStates.CheckedChanged += new EventHandler(m_rbCollide_CheckedChanged);
            m_radioNoWaitStates.CheckedChanged += new EventHandler(m_rbCollide_CheckedChanged);

            m_chbClkFromTerm.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnMedianFilter.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnWakeUp.CheckedChanged += new EventHandler(m_chb_CheckedChanged);

            m_chbClkFromTerm.EnabledChanged += new EventHandler(m_chb_EnabledChanged);
            m_chbEnMedianFilter.EnabledChanged += new EventHandler(m_chb_EnabledChanged);
            m_chbEnWakeUp.EnabledChanged += new EventHandler(m_chb_EnabledChanged);
            #endregion
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            // Clock source
            m_cbClkMode.SelectedItem = m_params.GetValueDescription(CyParamNames.EZSPI_OPERATION_MODE,
                m_params.EZSPI_OperationalMode);

            // Clock from terminal
            m_chbClkFromTerm.Checked = m_params.EZSPI_ClockFromTerminal;

            // Bit rate
            m_cbBitRate.Text = m_params.EZSPI_BitRate.ToString();

            // Oversampling factor
            m_numOvsFactor.Text = m_params.EZSPI_OversamplingFactor.ToString();

            // Enable median filter
            m_chbEnMedianFilter.Checked = m_params.EZSPI_MedianFilterEnabled;

            // Enable wakeup from Sleep Mode
            m_chbEnWakeUp.Checked = m_params.EZSPI_EnableWakeUpFromSleepMode;

            // Colide behavior
            if (m_params.EZSPI_ColideBehavior == CyEEZColideBehavior.WAIT_STATES)
                m_radioWaitStates.Checked = true;
            else
                m_radioNoWaitStates.Checked = true;

            UpdateClock();
        }

        private void InitializeBitRates()
        {
            foreach (ushort i in CyParameters.SPI_DATA_RATE_LIST)
            {
                m_cbBitRate.Items.Add(i.ToString());
            }
        }

        public void UpdateWakeUpControls()
        {
            bool enabled = (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.INTERNALLY_CLOCKED) &&
                (m_params.EZSPI_InterruptMode == CyEInterruptModeType.INTERNAL);

            m_chbEnWakeUp.Enabled = enabled;
            if (!enabled)
            {
                m_chbEnWakeUp.Checked = false;
            }
        }
        #endregion

        #region Event handlers
        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chBox = sender as CheckBox;

            if (chBox != null)
            {
                if (chBox == m_chbEnMedianFilter)
                {
                    m_params.EZSPI_MedianFilterEnabled = chBox.Checked;
                }
                else if (chBox == m_chbEnWakeUp)
                {
                    m_params.EZSPI_EnableWakeUpFromSleepMode = chBox.Checked;
                }
                else if (chBox == m_chbClkFromTerm)
                {
                    m_params.EZSPI_ClockFromTerminal = chBox.Checked;
                    UpdateClock();
                }
            }
        }

        void m_chb_EnabledChanged(object sender, EventArgs e)
        {
            CheckBox chb = sender as CheckBox;

            if (chb != null)
            {
                if (chb.Enabled)
                {
                    chb.Checked = (bool)chb.Tag;
                }
                else
                {
                    chb.Tag = chb.Checked;
                }
            }
        }

        void m_rbCollide_CheckedChanged(object sender, EventArgs e)
        {
            m_params.EZSPI_ColideBehavior = m_radioWaitStates.Checked ? CyEEZColideBehavior.WAIT_STATES :
                CyEEZColideBehavior.NO_WAIT_STATES;
            if (m_params.m_ezSPIAdvancedTab != null)
            {
                m_params.m_ezSPIAdvancedTab.UpdateCheckBoxState();
            }
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (cb != null)
            {
                if (cb == m_cbClkMode)
                {
                    m_params.EZSPI_OperationalMode = m_params.GetEnumValue<CyEEZOperationalMode>(
                        CyParamNames.EZSPI_OPERATION_MODE, m_cbClkMode.Text);

                    UpdateClock();

                    // Update controls states
                    m_grpCollideBehavior.Enabled = (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.EXTERNALY_CLOCKED);
                    m_panInternalClockConfig.Enabled = (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.INTERNALLY_CLOCKED);
                    if (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.EXTERNALY_CLOCKED)
                    {
                        m_chbClkFromTerm.Checked = false;
                        m_chbEnMedianFilter.Checked = false;
                    }

                    UpdateWakeUpControls();

                    if (m_params.m_ezSPIAdvancedTab != null)
                    {
                        m_params.m_ezSPIAdvancedTab.UpdateCheckBoxState();
                        m_params.m_ezSPIAdvancedTab.UpdateInterruptSources();
                    }
                }
            }
        }

        void m_cb_TextChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (cb != null)
            {
                if (cb == m_cbBitRate)
                {
                    UInt16 value;
                    UInt16 minValue = CyParameters.SPI_MIN_DATA_RATE;
                    UInt16 maxValue = CyParameters.SPI_MAX_DATA_RATE;

                    if (UInt16.TryParse(m_cbBitRate.Text, out value) && value >= minValue && value <= maxValue)
                    {
                        m_errorProvider.SetError(m_cbBitRate, string.Empty);
                        m_params.EZSPI_BitRate = value;
                        UpdateClock();
                    }
                    else
                    {
                        m_errorProvider.SetError(m_cbBitRate, string.Format(Resources.EZSPIBitRateValueError, minValue,
                            maxValue));
                    }
                }
            }
        }

        void m_num_TextChanged(object sender, EventArgs e)
        {
            NumericUpDown num = sender as NumericUpDown;

            if (num != null)
            {
                if (num == m_numOvsFactor)
                {
                    byte minValue = 1;
                    byte maxValue = CyParamRanges.I2C_OVS_FACTOR_MAX;
                    byte value;

                    if (byte.TryParse(m_numOvsFactor.Text, out value) && value >= minValue && value <= maxValue)
                    {
                        m_errorProvider.SetError(m_numOvsFactor, string.Empty);
                        m_params.EZSPI_OversamplingFactor = value;
                        UpdateClock();
                    }
                    else
                    {
                        m_errorProvider.SetError(m_numOvsFactor, string.Format(Resources.UARTOvsFactorError, minValue,
                            maxValue));
                    }
                }
            }
        }
        #endregion

        #region Actual data rate
        public void UpdateClock()
        {
            string dataRateStr = Resources.ClockDisplayUnknown;

            if (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.INTERNALLY_CLOCKED)
            {
                double clkFreq = m_params.EZSPI_ClockFromTerminal ?
                    CyParameters.GetExternalClock(m_params.m_term) :
                    CyParameters.GetInternalClock(m_params.m_term);

                if (clkFreq > -1)
                {
                    double actualBitRate = Math.Round(clkFreq / (byte)m_params.EZSPI_OversamplingFactor, 3);
                    if (actualBitRate > 0)
                    {
                        dataRateStr = actualBitRate.ToString() + " kbps";
                    }
                }
            }

            // Update Actual Data Rate label
            m_lblActualBitRate.Text = string.Format(Resources.ActualBitRateDisplayFormat, dataRateStr);
        }
        #endregion
    }
}
