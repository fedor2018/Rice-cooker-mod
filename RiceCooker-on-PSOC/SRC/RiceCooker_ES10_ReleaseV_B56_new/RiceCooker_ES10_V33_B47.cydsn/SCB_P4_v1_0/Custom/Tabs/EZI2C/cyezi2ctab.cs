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
    public partial class CyEZI2CTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "EZI2C";
            }
        }
        #endregion

        #region Constructor(s)
        public CyEZI2CTab(CyParameters parameters)
            :base(parameters)
        {
            m_params = parameters;
            m_params.m_ezI2CTab = this;

            InitializeComponent();

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;

            m_cbClkMode.Items.AddRange(m_params.GetEnumDescriptions(CyParamNames.EZI2C_OPERATION_MODE));

            m_chbClkFromTerm.Tag = m_params.EZI2C_ClockFromTerminal;
            m_chbEnMedianFilter.Tag = m_params.EZI2C_EnableMedianFilter;
            m_chbEnableWakeup.Tag = m_params.EZI2C_EnableWakeupFromSleep;

            #region Add event handlers
            m_cbClkMode.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_chbClkFromTerm.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbClkFromTerm.EnabledChanged += new EventHandler(m_chb_EnabledChanged);

            m_cbDataRate.TextChanged += new EventHandler(m_cb_TextChanged);

            m_numOvsFactor.TextChanged += new EventHandler(m_num_TextChanged);

            m_rbAddressAck.CheckedChanged += new EventHandler(m_rbPostWakeupOp_CheckedChanged);
            m_rbAddressNack.CheckedChanged += new EventHandler(m_rbPostWakeupOp_CheckedChanged);

            m_rbWaitStates.CheckedChanged += new EventHandler(m_rbColideBehavior_CheckedChanged);
            m_rbNoWaitStates.CheckedChanged += new EventHandler(m_rbColideBehavior_CheckedChanged);

            m_chbEnableWakeup.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnMedianFilter.CheckedChanged += new EventHandler(m_chb_CheckedChanged);

            m_chbEnMedianFilter.EnabledChanged += new EventHandler(m_chb_EnabledChanged);
            m_chbEnableWakeup.EnabledChanged += new EventHandler(m_chb_EnabledChanged);

            m_binaryGridSlaveAddress.BitChanged +=
                new CyBinaryGrid.BitChangedEventHandler(m_binaryGridSlaveAddress_BitChanged);
            m_binaryGridSlaveAddressMask.BitChanged +=
                new CyBinaryGrid.BitChangedEventHandler(m_binaryGridSlaveAddressMask_BitChanged);

            m_tbSlaveAddress.TextChanged += new EventHandler(m_tbSlaveAddress_TextChanged);
            m_tbSlaveAddressMask.TextChanged += new EventHandler(m_tbSlaveAddressMask_TextChanged);
            #endregion
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            // Clock source
            m_cbClkMode.SelectedItem = m_params.GetValueDescription(CyParamNames.EZI2C_OPERATION_MODE,
                m_params.EZI2C_OperationMode);

            // Clock from terminal
            m_chbClkFromTerm.Checked = m_params.EZI2C_ClockFromTerminal;

            // Data rate
            m_cbDataRate.Text = m_params.EZI2C_DataRate.ToString();

            // Oversampling factor
            m_numOvsFactor.Text = m_params.EZI2C_OversamplingFactor.ToString();

            // Enable median filter
            m_chbEnMedianFilter.Checked = m_params.EZI2C_EnableMedianFilter;

            // Slave address mask
            if (m_params.EZI2C_IsSlaveAddressMaskHex)
                m_tbSlaveAddressMask.Text = CyConvert.IntToHex(m_params.EZI2C_SlaveAddressMask);
            else
                m_tbSlaveAddressMask.Text = m_params.EZI2C_SlaveAddressMask.ToString();

            // Slave address
            if (m_params.EZI2C_IsSlaveAddressHex)
                m_tbSlaveAddress.Text = CyConvert.IntToHex(m_params.EZI2C_SlaveAddress);
            else
                m_tbSlaveAddress.Text = m_params.EZI2C_SlaveAddress.ToString();

            // Enable wakeup from sleep mode
            m_chbEnableWakeup.Checked = m_params.EZI2C_EnableWakeupFromSleep;
            UpdatePostWakeupControls();

            // Post wakeup operation
            switch (m_params.EZI2C_PostWakeupBehavior)
            {
                case CyEI2CPostWakeupOperationType.ADDRESS_ACK:
                    m_rbAddressAck.Checked = true;
                    break;
                case CyEI2CPostWakeupOperationType.ADDRESS_NACK:
                    m_rbAddressNack.Checked = true;
                    break;
            }

            // Colade behavior
            switch (m_params.EZI2C_ColideBehavior)
            {
                case CyEEZColideBehavior.WAIT_STATES:
                    m_rbWaitStates.Checked = true;
                    break;
                case CyEEZColideBehavior.NO_WAIT_STATES:
                    m_rbNoWaitStates.Checked = true;
                    break;
            }

            UpdateClock();
        }

        private void UpdatePostWakeupControls()
        {
            m_grpWakeUp.Enabled = m_params.EZI2C_EnableWakeupFromSleep;
        }

        private void UpdateAddressAccordingToAddressMask()
        {
            // Show X as a bit of slave address when appropriate mask bit equal to 0
            // Create value in temporrary array
            string[] tmpBits = new string[m_binaryGridSlaveAddress.Bits.Length];

            for (int i = 0; i < tmpBits.Length; i++)
            {
                tmpBits[i] = m_binaryGridSlaveAddress.Bits[i];
            }

            for (int i = 0; i < tmpBits.Length; i++)
            {
                tmpBits[i] = (m_binaryGridSlaveAddressMask.Bits[i] == CyBinaryGrid.ZeroSign) ? CyBinaryGrid.XSign :
                    (m_binaryGridSlaveAddress.Bits[i] != CyBinaryGrid.XSign ? m_binaryGridSlaveAddress.Bits[i] :
                    CyBinaryGrid.ZeroSign);
            }
            // In 7-bit value LSB is always X
            if (m_binaryGridSlaveAddress.NumberOfBits == 7)
                tmpBits[m_binaryGridSlaveAddress.NumberOfBits] = CyBinaryGrid.XSign;

            // Do not update slave address value according to slave address mask,
            // only view of control should be changed
            m_binaryGridSlaveAddress.UpdateGridViewOnly(tmpBits);
        }

        public void UpdateWakeUpControls()
        {
            bool enabled = (m_params.EZI2C_OperationMode == CyEEZOperationalMode.INTERNALLY_CLOCKED) &&
                (m_params.EZI2C_InterruptMode == CyEInterruptModeType.INTERNAL);
            m_chbEnableWakeup.Enabled = enabled;
            m_grpWakeUp.Enabled = enabled && m_chbEnableWakeup.Checked;

            if (!enabled)
            {
                m_chbEnableWakeup.Checked = false;
            }
        }
        #endregion

        #region Event handlers
        void m_rbPostWakeupOp_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbAddressAck.Checked)
            {
                m_params.EZI2C_PostWakeupBehavior = CyEI2CPostWakeupOperationType.ADDRESS_ACK;
            }
            else if (m_rbAddressNack.Checked)
            {
                m_params.EZI2C_PostWakeupBehavior = CyEI2CPostWakeupOperationType.ADDRESS_NACK;
            }
        }

        void m_rbColideBehavior_CheckedChanged(object sender, EventArgs e)
        {
            if (m_rbNoWaitStates.Checked)
            {
                m_params.EZI2C_ColideBehavior = CyEEZColideBehavior.NO_WAIT_STATES;
            }
            else if (m_rbWaitStates.Checked)
            {
                m_params.EZI2C_ColideBehavior = CyEEZColideBehavior.WAIT_STATES;
            }
            if (m_params.m_ezI2CAdvancedTab != null)
            {
                m_params.m_ezI2CAdvancedTab.UpdateCheckBoxState();
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = sender as CheckBox;

            if (chb != null)
            {
                if (chb == m_chbEnableWakeup)
                {
                    m_params.EZI2C_EnableWakeupFromSleep = chb.Checked;
                    UpdatePostWakeupControls();
                }
                else if (chb == m_chbEnMedianFilter)
                {
                    m_params.EZI2C_EnableMedianFilter = chb.Checked;
                }
                else if (chb == m_chbClkFromTerm)
                {
                    m_params.EZI2C_ClockFromTerminal = chb.Checked;
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

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (cb != null)
            {
                if (cb == m_cbClkMode)
                {
                    m_params.EZI2C_OperationMode = m_params.GetEnumValue<CyEEZOperationalMode>(
                        CyParamNames.EZI2C_OPERATION_MODE, m_cbClkMode.Text);

                    UpdateClock();

                    // Update controls state
                    m_panInternalClockConfig.Enabled = (m_params.EZI2C_OperationMode != CyEEZOperationalMode.EXTERNALY_CLOCKED);
                    m_grpCollideBehavior.Enabled = (m_params.EZI2C_OperationMode == CyEEZOperationalMode.EXTERNALY_CLOCKED);
                    UpdateWakeUpControls();

                    if (m_params.EZI2C_OperationMode == CyEEZOperationalMode.EXTERNALY_CLOCKED)
                    {
                        m_chbClkFromTerm.Checked = false;
                        m_chbEnMedianFilter.Checked = false;
                    }

                    if (m_params.m_ezI2CAdvancedTab != null)
                    {
                        m_params.m_ezI2CAdvancedTab.UpdateCheckBoxState();
                        m_params.m_ezI2CAdvancedTab.UpdateInterruptSources();
                    }
                }
            }
        }

        void m_cb_TextChanged(object sender, EventArgs e)
        {
            ComboBox cb = sender as ComboBox;

            if (cb != null)
            {
                if (cb == m_cbDataRate)
                {
                    UInt16 value;

                    if (UInt16.TryParse(m_cbDataRate.Text, out value) && value >= CyParamRanges.I2C_DATA_RATE_MIN &&
                        value <= CyParamRanges.I2C_DATA_RATE_MAX)
                    {
                        m_errorProvider.SetError(m_cbDataRate, string.Empty);
                        m_params.EZI2C_DataRate = value;
                        UpdateClock();
                    }
                    else
                    {
                        m_errorProvider.SetError(m_cbDataRate, string.Format(Resources.BaudRateValueError,
                            CyParamRanges.I2C_DATA_RATE_MIN, CyParamRanges.I2C_DATA_RATE_MAX));
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
                        m_params.EZI2C_OversamplingFactor = value;
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

        #region Slave Address configuration
        private void m_binaryGridSlaveAddress_BitChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode) // avoid this on customizer load
            {
                CyBinaryGrid currentBinaryGrid = (CyBinaryGrid)sender;

                if (currentBinaryGrid.Locked == false)
                {
                    currentBinaryGrid.Locked = true; // lock binary box from updating after textbox update

                    if (m_tbSlaveAddress.Text.StartsWith(CyConvert.HEX_PREFIX))
                    {
                        // Hexadecimal value handling
                        m_tbSlaveAddress.Text = CyConvert.Bin7ToHex(currentBinaryGrid.Bits);
                    }
                    else
                    {
                        // Decimal value handling
                        m_tbSlaveAddress.Text = CyConvert.Bin7ToInt(currentBinaryGrid.Bits).ToString();
                    }
                    currentBinaryGrid.Locked = false; // release lock
                }
            }
        }

        private void m_tbSlaveAddress_TextChanged(object sender, EventArgs e)
        {
            TextBox currentTextBox = (TextBox)sender;

            #region Communication between textbox and binary grid
            if (m_binaryGridSlaveAddress.Locked == false)
            {
                m_binaryGridSlaveAddress.Locked = true; // lock textbox from updating after binary box update

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    int value = CyConvert.HexToInt(currentTextBox.Text);
                    if (value < CyParamRanges.EZI2C_SLAVE_ADDRESS_MIN || value > CyParamRanges.EZI2C_SLAVE_ADDRESS_MAX)
                    {
                        m_binaryGridSlaveAddress.ResetBits();
                    }
                    else
                    {
                        m_binaryGridSlaveAddress.Bits = CyConvert.HexToBin7(currentTextBox.Text);
                    }
                }
                else
                {
                    // Decimal value handling
                    int value = 0;
                    if (int.TryParse(currentTextBox.Text, out value))
                    {
                        if (value < CyParamRanges.EZI2C_SLAVE_ADDRESS_MIN ||
                            value > CyParamRanges.EZI2C_SLAVE_ADDRESS_MAX)
                            value = 0;
                    }
                    m_binaryGridSlaveAddress.Bits = CyConvert.IntToBin7(value);
                }

                string[] tmpBits = new string[m_binaryGridSlaveAddress.Bits.Length];

                // Restore X signs if zero
                for (int i = 0; i < tmpBits.Length; i++)
                {
                    tmpBits[i] = (m_binaryGridSlaveAddressMask.Bits[i] == CyBinaryGrid.ZeroSign) ? CyBinaryGrid.XSign :
                        m_binaryGridSlaveAddress.Bits[i];
                }
                // Change view only here
                m_binaryGridSlaveAddress.UpdateGridViewOnly(tmpBits);

                m_binaryGridSlaveAddress.Locked = false; // release lock
            }
            #endregion

            #region Set control value to appropriate parameter
            try
            {
                byte textboxValue = 0;
                string min, max;
                bool isHex = false;

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Value was input as hexadecimal
                    textboxValue = (byte)CyConvert.HexToInt(currentTextBox.Text);
                    min = CyConvert.IntToHex(CyParamRanges.EZI2C_SLAVE_ADDRESS_MIN);
                    max = CyConvert.IntToHex(CyParamRanges.EZI2C_SLAVE_ADDRESS_MAX);
                    isHex = true;
                }
                else
                {
                    // Value was input as decimal
                    textboxValue = byte.Parse(currentTextBox.Text);
                    min = CyParamRanges.EZI2C_SLAVE_ADDRESS_MIN.ToString();
                    max = CyParamRanges.EZI2C_SLAVE_ADDRESS_MAX.ToString();
                    isHex = false;
                }

                if (textboxValue >= CyParamRanges.EZI2C_SLAVE_ADDRESS_MIN &&
                    textboxValue <= CyParamRanges.EZI2C_SLAVE_ADDRESS_MAX)
                {
                    m_params.EZI2C_SlaveAddress = textboxValue;
                    m_params.EZI2C_IsSlaveAddressHex = isHex;
                }
                else
                    throw new Exception(string.Format(Resources.EZI2CSlaveAddressError, min, max));

                m_errorProvider.SetError(currentTextBox, string.Empty);
            }
            catch (Exception ex)
            {
                m_errorProvider.SetError(currentTextBox, ex.Message);
            }
            #endregion
        }
        #endregion

        #region Slave Address Mask configuration
        private void m_binaryGridSlaveAddressMask_BitChanged(object sender, EventArgs e)
        {
            CyBinaryGrid currentBinaryGrid = (CyBinaryGrid)sender;

            if (currentBinaryGrid.Locked == false)
            {
                currentBinaryGrid.Locked = true; // lock binary box from updating after textbox update

                if (m_tbSlaveAddressMask.Text.StartsWith(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    m_tbSlaveAddressMask.Text = CyConvert.BinToHex(currentBinaryGrid.Bits);
                }
                else
                {
                    // Decimal value handling
                    m_tbSlaveAddressMask.Text = CyConvert.BinToInt(currentBinaryGrid.Bits).ToString();
                }
                currentBinaryGrid.Locked = false; // release lock
            }
            UpdateAddressAccordingToAddressMask();
        }

        private void m_tbSlaveAddressMask_TextChanged(object sender, EventArgs e)
        {
            TextBox currentTextBox = (TextBox)sender;

            #region Communications between textbox and binary grid
            if (m_binaryGridSlaveAddressMask.Locked == false)
            {
                m_binaryGridSlaveAddressMask.Locked = true; // lock textbox from updating after binary box update

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Hexadecimal value handling
                    int value = CyConvert.HexToInt(currentTextBox.Text);
                    if (value < CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MIN ||
                        value > CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MAX)
                    {
                        m_binaryGridSlaveAddressMask.ResetBits();
                    }
                    else
                    {
                        m_binaryGridSlaveAddressMask.Bits = CyConvert.HexToBin(currentTextBox.Text);
                    }
                }
                else
                {
                    // Decimal value handling
                    int value = 0;
                    if (int.TryParse(currentTextBox.Text, out value))
                    {
                        if (value < CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MIN ||
                            value > CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MAX)
                            value = 0;
                    }
                    m_binaryGridSlaveAddressMask.Bits = CyConvert.IntToBin(value);
                }
                m_binaryGridSlaveAddressMask.Locked = false; // release lock

                UpdateAddressAccordingToAddressMask();
            }
            #endregion

            #region Set control value to appropriate parameter
            try
            {
                byte textboxValue = 0;
                string min, max;
                bool isHex = false;

                if (currentTextBox.Text.Contains(CyConvert.HEX_PREFIX))
                {
                    // Value was input as hexadecimal
                    textboxValue = (byte)CyConvert.HexToInt(currentTextBox.Text);
                    min = CyConvert.IntToHex(CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MIN);
                    max = CyConvert.IntToHex(CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MAX);
                    isHex = true;
                }
                else
                {
                    // Value was input as decimal
                    textboxValue = byte.Parse(currentTextBox.Text);
                    min = CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MIN.ToString();
                    max = CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MAX.ToString();
                    isHex = false;
                }

                if (textboxValue >= CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MIN &&
                    textboxValue <= CyParamRanges.EZI2C_SLAVE_ADDRESS_MASK_MAX)
                {
                    if ((textboxValue % 2) == 0) // even value only accepted
                    {
                        m_params.EZI2C_SlaveAddressMask = textboxValue;
                        m_params.EZI2C_IsSlaveAddressMaskHex = isHex;
                    }
                    else
                        throw new Exception(Resources.SlaveAddressMaskOddError);
                }
                else
                    throw new Exception(string.Format(Resources.EZI2CSlaveAddressMaskError, min, max));

                m_errorProvider.SetError(currentTextBox, string.Empty);
            }
            catch (Exception ex)
            {
                m_errorProvider.SetError(currentTextBox, ex.Message);
            }
            #endregion
        }
        #endregion
        #endregion

        #region Actual data rate
        public void UpdateClock()
        {
            string dataRateStr = Resources.ClockDisplayUnknown;

            if (m_params.EZI2C_OperationMode == CyEEZOperationalMode.INTERNALLY_CLOCKED)
            {
                double clkFreq = m_params.EZI2C_ClockFromTerminal ?
                    CyParameters.GetExternalClock(m_params.m_term) :
                    CyParameters.GetInternalClock(m_params.m_term);

                if (clkFreq > -1)
                {
                    double actualDataRate = Math.Round(clkFreq / (byte)m_params.EZI2C_OversamplingFactor, 3);
                    if (actualDataRate > 0)
                    {
                        dataRateStr = actualDataRate.ToString() + " kbps";
                    }
                }
            }

            // Update Actual Data Rate label
            m_lblActualDataRate.Text = string.Format(Resources.ActualDataRateDisplayFormat, dataRateStr);
        }
        #endregion
    }
}
