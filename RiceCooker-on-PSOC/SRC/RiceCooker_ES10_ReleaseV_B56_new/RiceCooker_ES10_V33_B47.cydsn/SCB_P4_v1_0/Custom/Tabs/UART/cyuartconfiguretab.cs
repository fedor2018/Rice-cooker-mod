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
    public partial class CyUARTConfigureTab : CyTabControlWrapper
    {
        #region Auxiliary data
        readonly UInt32[] IRDA_DATA_RATES_LIST = new UInt32[]
        {
            1200,
            2400,
            9600,
            19200,
            38400,
            57600,
            115200
        };

        readonly UInt16[] IRDA_OVS_FACTOR_LIST = new UInt16[]
        {
            1536,
            768,
            192,
            96,
            48,
            32,
            16
        };

        readonly UInt32[] DATA_RATES_LIST = new UInt32[]
        {
            110,
            300,
            1200,
            2400,
            4800,
            9600,
            19200,
            38400,
            57600,
            115200,
            230400,
            460800,
            921600
        };
        #endregion

        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "UART Basic";
            }
        }
        #endregion

        #region Constructor(s)
        public CyUARTConfigureTab(CyParameters parameters)
            : base(parameters)
        {
            m_params = parameters;
            m_params.m_uartConfigTab = this;

            InitializeComponent();

            #region Add items to comboboxes
            m_cbMode.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.UART_SUB_MODE));
            m_cbDirection.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.UART_DIRECTION));
            m_cbDataBits.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.UART_NUMBER_OF_DATA_BITS));
            m_cbParityType.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.UART_PARITY_TYPE));
            m_cbStopBits.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.UART_NUMBER_OF_STOP_BITS));
            UpdateBaudRateList();
            #endregion

            #region Add event handlers
            m_cbMode.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbDirection.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbDataBits.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbParityType.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbStopBits.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_cbBaudRate.TextChanged += new EventHandler(m_cb_TextChanged);

            m_numOversamplingFactor.TextChanged += new EventHandler(m_num_TextChanged);

            m_chbEnableMedianFilter.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbRetryOnNack.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInvertRx.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnableWakeup.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbLowPowerTransmit.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbClockFromTerminal.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            #endregion
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            m_cbMode.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_SUB_MODE, m_params.UART_SubMode);
            m_cbDirection.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_DIRECTION,
                m_params.UART_Direction);
            m_cbBaudRate.Text = m_params.UART_DataRate.ToString();
            m_cbDataBits.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_NUMBER_OF_DATA_BITS,
                m_params.UART_NumberDataBits);
            m_cbParityType.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_PARITY_TYPE,
                m_params.UART_ParityType);
            m_cbStopBits.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_NUMBER_OF_STOP_BITS,
                m_params.UART_NumberStopBits);

            m_numOversamplingFactor.Text = m_params.UART_OversamplingFactor.ToString();

            //Clock from terminal
            m_chbClockFromTerminal.Checked = m_params.UART_ClockFromTerm;
            m_chbEnableMedianFilter.Checked = m_params.UART_MedianFilterEnabled;
            m_chbRetryOnNack.Checked = m_params.UART_RetryOnNACK;
            m_chbInvertRx.Checked = m_params.UART_InvertRXProperty;
            m_chbEnableWakeup.Checked = m_params.UART_WakeupFromSleepEnabled;
            m_chbLowPowerTransmit.Checked = m_params.UART_LowPowerTransmitting;

            UpdateCheckBoxesState();
            UpdateOvsFactor();
            UpdateComboBoxStates();
            UpdateClock();
        }

        private void UpdateCheckBoxesState()
        {
            bool isNotTransmit = m_params.UART_Direction != CyEUARTDirectionType.TX;

            m_chbEnableMedianFilter.Enabled = (m_params.UART_SubMode != CyEUARTSubModeType.IRDA) && isNotTransmit;
            m_chbRetryOnNack.Enabled = (m_params.UART_SubMode == CyEUARTSubModeType.SMART_CARD) && isNotTransmit;
            m_chbInvertRx.Enabled = (m_params.UART_SubMode == CyEUARTSubModeType.IRDA) && isNotTransmit;
            m_chbEnableWakeup.Enabled = (m_params.UART_SubMode == CyEUARTSubModeType.STANDARD) && isNotTransmit;
            m_chbLowPowerTransmit.Enabled = m_params.UART_SubMode == CyEUARTSubModeType.IRDA;

            if (m_params.UART_SubMode == CyEUARTSubModeType.IRDA &&
                (m_params.UART_Direction == CyEUARTDirectionType.TX_RX ||
                (m_params.UART_Direction == CyEUARTDirectionType.RX)))
            {
                m_chbEnableMedianFilter.Checked = true;
            }
        }

        private void UpdateComboBoxStates()
        {
            if (m_params.UART_SubMode == CyEUARTSubModeType.SMART_CARD)
            {
                m_cbParityType.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_PARITY_TYPE,
                    CyEUARTParityType.EVEN);
            }
            else if ((m_params.UART_SubMode == CyEUARTSubModeType.IRDA) ||
                (m_params.UART_NumberDataBits == CyEUARTNumberDataBitsType.NINE))
            {
                m_cbParityType.SelectedItem = m_params.GetValueDescription(CyParamNames.UART_PARITY_TYPE,
                    CyEUARTParityType.PARITY_NONE);
            }

            m_cbParityType.Enabled = (m_params.UART_SubMode == CyEUARTSubModeType.STANDARD) &&
                (m_params.UART_NumberDataBits != CyEUARTNumberDataBitsType.NINE);
        }

        private void UpdateOvsFactor()
        {
            bool isIrDAMode = m_params.UART_SubMode == CyEUARTSubModeType.IRDA;

            if (isIrDAMode)
            {
                m_numOversamplingFactor.Value = 16;

                if (m_params.UART_LowPowerTransmitting == true)
                {
                    for (int i = 0; i < IRDA_DATA_RATES_LIST.GetLength(0); i++)
                    {
                        if (IRDA_DATA_RATES_LIST[i] == m_params.UART_DataRate)
                        {
                            m_numOversamplingFactor.Value = IRDA_OVS_FACTOR_LIST[i];
                        }
                    }
                }
            }
            m_numOversamplingFactor.Enabled = !isIrDAMode;
        }

        private void UpdateBaudRateList()
        {
            m_cbBaudRate.Items.Clear();

            uint[] baudRates = (m_params.UART_SubMode == CyEUARTSubModeType.IRDA) ? IRDA_DATA_RATES_LIST :
                DATA_RATES_LIST;

            foreach (UInt32 rate in baudRates)
            {
                m_cbBaudRate.Items.Add(rate);
            }
            m_cbBaudRate.Text = m_params.UART_DataRate.ToString();

            m_cb_TextChanged(m_cbBaudRate, null);
        }
        #endregion

        #region Event handlers
        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (sender == m_cbMode)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.UART_SubMode = m_params.GetEnumValue<CyEUARTSubModeType>(CyParamNames.UART_SUB_MODE,
                        m_cbMode.Text);
                }
                UpdateBaudRateList();
                UpdateOvsFactor();
                UpdateCheckBoxesState();
                UpdateComboBoxStates();
                if (m_params.m_uartAdvancedTab != null)
                {
                    m_params.m_uartAdvancedTab.UpdateTXNACKIntr();
                    m_params.m_uartAdvancedTab.UpdateRxDropOnParityError();
                    m_params.m_uartAdvancedTab.UpdateMultiprocessorMode();
                }
            }
            else if (sender == m_cbDirection)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.UART_Direction =
                        m_params.GetEnumValue<CyEUARTDirectionType>(CyParamNames.UART_DIRECTION, m_cbDirection.Text);
                }

                UpdateCheckBoxesState();
                if (m_params.m_uartAdvancedTab != null)
                {
                    m_params.m_uartAdvancedTab.UpdateInterruptSources();
                    m_params.m_uartAdvancedTab.UpdateRXFrameErrorIntr();
                    m_params.m_uartAdvancedTab.UpdateRxDropOnParityError();
                    m_params.m_uartAdvancedTab.UpdateRxDropOnFrameError();
                }
            }
            else if (sender == m_cbDataBits)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.UART_NumberDataBits =
                        m_params.GetEnumValue<CyEUARTNumberDataBitsType>(CyParamNames.UART_NUMBER_OF_DATA_BITS,
                        m_cbDataBits.Text);
                }
                if (m_params.m_uartAdvancedTab != null)
                {
                    m_params.m_uartAdvancedTab.UpdateMultiprocessorMode();
                }
                UpdateComboBoxStates();
            }
            else if (sender == m_cbParityType)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.UART_ParityType =
                        m_params.GetEnumValue<CyEUARTParityType>(CyParamNames.UART_PARITY_TYPE, m_cbParityType.Text);
                }
                if (m_params.m_uartAdvancedTab != null)
                {
                    m_params.m_uartAdvancedTab.UpdateRxDropOnParityError();
                }
            }
            else if (sender == m_cbStopBits)
            {
                if (m_params.GlobalEditMode)
                {
                    m_params.UART_NumberStopBits =
                        m_params.GetEnumValue<CyEUARTNumberStopBitsType>(CyParamNames.UART_NUMBER_OF_STOP_BITS,
                        m_cbStopBits.Text);
                }
                if (m_params.m_uartAdvancedTab != null)
                {
                    m_params.m_uartAdvancedTab.UpdateRXFrameErrorIntr();
                }
            }
        }

        void m_num_TextChanged(object sender, EventArgs e)
        {
            if (sender == m_numOversamplingFactor)
            {
                UInt16 value;

                bool skipCheckRange = (m_params.UART_SubMode == CyEUARTSubModeType.IRDA &&
                    m_params.UART_LowPowerTransmitting);
                bool parseSuccess = UInt16.TryParse(m_numOversamplingFactor.Text, out value);

                if (parseSuccess && m_params.GlobalEditMode)
                {
                    m_params.UART_OversamplingFactor = value;
                }

                if (parseSuccess && (skipCheckRange ||
                    (value >= CyParamRanges.UART_OVS_FACTOR_MIN && value <= CyParamRanges.UART_OVS_FACTOR_MAX)))
                {
                    m_errorProvider.SetError(m_numOversamplingFactor, string.Empty);
                    UpdateClock();
                }
                else
                {
                    m_errorProvider.SetError(m_numOversamplingFactor, string.Format(Resources.UARTOvsFactorError,
                            CyParamRanges.UART_OVS_FACTOR_MIN, CyParamRanges.UART_OVS_FACTOR_MAX));
                }
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_chbEnableMedianFilter)
                {
                    m_params.UART_MedianFilterEnabled = m_chbEnableMedianFilter.Checked;
                }
                else if (sender == m_chbRetryOnNack)
                {
                    m_params.UART_RetryOnNACK = m_chbRetryOnNack.Checked;
                }
                else if (sender == m_chbInvertRx)
                {
                    m_params.UART_InvertRXProperty = m_chbInvertRx.Checked;
                }
                else if (sender == m_chbEnableWakeup)
                {
                    m_params.UART_WakeupFromSleepEnabled = m_chbEnableWakeup.Checked;
                }
                else if (sender == m_chbLowPowerTransmit)
                {
                    m_params.UART_LowPowerTransmitting = m_chbLowPowerTransmit.Checked;
                    UpdateOvsFactor();
                }
                else if (sender == m_chbClockFromTerminal)
                {
                    m_params.UART_ClockFromTerm = m_chbClockFromTerminal.Checked;
                    UpdateClock();
                }
            }
        }

        void m_cb_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbBaudRate)
                {
                    UInt32 value;
                    bool parseSuccess = UInt32.TryParse(m_cbBaudRate.Text, out value);

                    if (parseSuccess)
                    {
                        m_params.UART_DataRate = value;
                    }

                    if (m_params.UART_SubMode == CyEUARTSubModeType.IRDA)
                    {
                        List<uint> rates = new List<uint>(IRDA_DATA_RATES_LIST);
                        if (parseSuccess && rates.Contains(value))
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Empty);
                            UpdateOvsFactor();
                            UpdateClock();
                        }
                        else
                        {
                            m_errorProvider.SetError(m_cbBaudRate, Resources.BaudRateIrDAValueError);
                        }
                    }
                    else
                    {
                        if (parseSuccess && value >= CyParamRanges.UART_DATA_RATE_MIN_VALUE &&
                            value <= CyParamRanges.UART_DATA_RATE_MAX_VALUE)
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Empty);
                            UpdateClock();
                        }
                        else
                        {
                            m_errorProvider.SetError(m_cbBaudRate, string.Format(Resources.BaudRateValueError,
                                CyParamRanges.UART_DATA_RATE_MIN_VALUE, CyParamRanges.UART_DATA_RATE_MAX_VALUE));
                        }
                    }
                }
            }
        }
        #endregion

        #region Actual baud rate
        public void UpdateClock()
        {
            double clkFreq = m_params.UART_ClockFromTerm ?
                CyParameters.GetExternalClock(m_params.m_term) :
                CyParameters.GetInternalClock(m_params.m_term);

            string dataRateStr = Resources.ClockDisplayUnknown;

            if (clkFreq > -1)
            {
                double actualBaudRate = Math.Round(clkFreq / m_params.UART_OversamplingFactor, 3);
                if (actualBaudRate > 0)
                {
                    dataRateStr = actualBaudRate.ToString() + " kbps";
                }
            }

            // Update Actual Data Rate label
            m_lblActualBaudRate.Text = string.Format(Resources.ActualBaudRateDisplayFormat, dataRateStr);
        }
        #endregion
    }
}
