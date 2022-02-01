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

namespace SCB_P4_v1_0
{
    public partial class CyUARTAdvancedTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "UART Advanced";
            }
        }
        #endregion

        #region Constructor(s)
        public CyUARTAdvancedTab(CyParameters parameters)
            : base(parameters)
        {
            m_params = parameters;
            m_params.m_uartAdvancedTab = this;

            InitializeComponent();

            #region Add combobox ranges
            for (int level = 0; level < 8; level++)
            {
                m_cbRXTriggerLevel.Items.Add(level.ToString());
                m_cbTXTriggerLevel.Items.Add(level.ToString());
            }
            #endregion

            #region Add event handlers
            m_numRXBufferSize.TextChanged += new EventHandler(m_numBufferSize_TextChanged);
            m_numTXBufferSize.TextChanged += new EventHandler(m_numBufferSize_TextChanged);

            m_chbInterruptUARTDone.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXNotFull.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXEmpty.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXOverflow.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXUnderflow.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXLostArb.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTxNack.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptTXTrigger.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXFull.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXNotEmpty.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXOverflow.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXUnderflow.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXFrameErr.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXParityErr.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbInterruptRXTrigger.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEnMultiProcMode.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbAcceptAddress.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbDropOnParityError.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbDropOnFrameError.CheckedChanged += new EventHandler(m_chb_CheckedChanged);

            m_cbTXTriggerLevel.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);
            m_cbRXTriggerLevel.SelectedIndexChanged += new EventHandler(m_cb_SelectedIndexChanged);

            m_rbNone.CheckedChanged += new EventHandler(m_rbIntrMode_CheckedChanged);
            m_rbExternal.CheckedChanged += new EventHandler(m_rbIntrMode_CheckedChanged);
            m_rbInternal.CheckedChanged += new EventHandler(m_rbIntrMode_CheckedChanged);

            m_numAddress.TextChanged += new EventHandler(m_numAddress_TextChanged);
            m_numAddressMask.TextChanged += new EventHandler(m_numAddress_TextChanged);
            #endregion

            m_numRXBufferSize.Maximum = decimal.MaxValue;
            m_numRXBufferSize.Minimum = 0;

            m_numTXBufferSize.Maximum = decimal.MaxValue;
            m_numTXBufferSize.Minimum = 0;

            m_numAddress.Maximum = decimal.MaxValue;
            m_numAddress.Minimum = 0;

            m_numAddressMask.Maximum = decimal.MaxValue;
            m_numAddressMask.Minimum = 0;
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            // Buffer sizes
            m_numRXBufferSize.Text = m_params.UART_RXBufferSize.ToString();
            m_numTXBufferSize.Text = m_params.UART_TXBufferSize.ToString();

            // Interrupt sources
            m_chbInterruptUARTDone.Checked = m_params.UART_InterruptOnUARTDone;
            m_chbInterruptTXNotFull.Checked = m_params.UART_InterruptOnTXFIFONotFull;
            m_chbInterruptTXEmpty.Checked = m_params.UART_InterruptOnTXFIFOEmpty;
            m_chbInterruptTXOverflow.Checked = m_params.UART_InterruptOnTXFIFOOverflow;
            m_chbInterruptTXUnderflow.Checked = m_params.UART_InterruptOnTXFIFOUnderflow;
            m_chbInterruptTXLostArb.Checked = m_params.UART_InterruptOnTXLostArbitration;
            m_chbInterruptTxNack.Checked = m_params.UART_InterruptOnTXNACK;
            m_chbInterruptTXTrigger.Checked = m_params.UART_InterruptOnTXFIFOTrigger;

            m_cbTXTriggerLevel.SelectedIndex = m_params.UART_TXTriggerLevel;

            m_chbInterruptRXFull.Checked = m_params.UART_InterruptOnRXFIFOFull;
            m_chbInterruptRXNotEmpty.Checked = m_params.UART_InterruptOnRXFIFONotEmpty;
            m_chbInterruptRXOverflow.Checked = m_params.UART_InterruptOnRXFIFOOverflow;
            m_chbInterruptRXUnderflow.Checked = m_params.UART_InterruptOnRXFIFOUnderflow;
            m_chbInterruptRXFrameErr.Checked = m_params.UART_InterruptOnRXFrameError;
            m_chbInterruptRXParityErr.Checked = m_params.UART_InterruptOnRXParityError;
            m_chbInterruptRXTrigger.Checked = m_params.UART_InterruptOnRXFIFOTrigger;

            m_cbRXTriggerLevel.SelectedIndex = m_params.UART_RXTriggerLevel;

            // Interrupt connections
            switch (m_params.UART_InterruptMode)
            {
                case CyEInterruptModeType.INTERRUPT_NONE:
                    m_rbNone.Checked = true;
                    break;
                case CyEInterruptModeType.EXTERNAL:
                    m_rbExternal.Checked = true;
                    break;
                case CyEInterruptModeType.INTERNAL:
                    m_rbInternal.Checked = true;
                    break;
            }

            // Multiprocessor mode
            m_chbEnMultiProcMode.Checked = m_params.UART_MultiProcessorModeEnabled;
            m_numAddress.Text = m_params.UART_MultiProcessorAddress.ToString("X2");
            m_numAddressMask.Text = m_params.UART_MultiProcessorAddressMask.ToString("X2");
            m_chbAcceptAddress.Checked = m_params.UART_MultiProcessorAcceptAddress;

            // RX FIFO Drop
            m_chbDropOnParityError.Checked = m_params.UART_RXFIFODropOnParityError;
            m_chbDropOnFrameError.Checked = m_params.UART_RXFIFODropOnFrameError;

            UpdateMultiprocessorMode();
            UpdateRXFrameErrorIntr();
            UpdateRxDropOnParityError();
            UpdateRxDropOnFrameError();
        }

        public void UpdateInterruptSources()
        {
            bool interruptEnabled = m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;
            bool txIntrEnabled = interruptEnabled && m_params.UART_Direction != CyEUARTDirectionType.RX;
            bool rxIntrEnabled = interruptEnabled && m_params.UART_Direction != CyEUARTDirectionType.TX;

            m_chbInterruptUARTDone.Enabled = txIntrEnabled;
            m_chbInterruptTXEmpty.Enabled = txIntrEnabled;
            m_chbInterruptTXOverflow.Enabled = txIntrEnabled;
            m_chbInterruptTXUnderflow.Enabled = txIntrEnabled;
            m_chbInterruptTXLostArb.Enabled = txIntrEnabled;
            m_chbInterruptTXTrigger.Enabled = txIntrEnabled;

            m_chbInterruptRXFull.Enabled = rxIntrEnabled;
            m_chbInterruptRXOverflow.Enabled = rxIntrEnabled;
            m_chbInterruptRXUnderflow.Enabled = rxIntrEnabled;
            m_chbInterruptRXParityErr.Enabled = rxIntrEnabled;
            m_chbInterruptRXTrigger.Enabled = rxIntrEnabled;

            UpdateTXNotFullIntr();
            UpdateRXNotEmtyIntr();

            UpdateTXTriggerLevel();
            UpdateRXTriggerLevel();

            UpdateRXFrameErrorIntr();
            UpdateTXNACKIntr();
        }

        private void UpdateRXNotEmtyIntr()
        {
            bool rxBufSizeOverflow = m_params.UART_RXBufferSize > 8;

            m_chbInterruptRXNotEmpty.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.TX) && !rxBufSizeOverflow;

            if (rxBufSizeOverflow)
            {
                m_chbInterruptRXNotEmpty.Checked = true;
            }
        }

        private void UpdateTXNotFullIntr()
        {
            bool txBufSizeOverflow = m_params.UART_TXBufferSize > 8;

            m_chbInterruptTXNotFull.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.RX) && !txBufSizeOverflow;
            if (txBufSizeOverflow)
            {
                m_chbInterruptTXNotFull.Checked = false;
            }
        }

        private void UpdateTXTriggerLevel()
        {
            m_cbTXTriggerLevel.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.RX) && m_params.UART_InterruptOnTXFIFOTrigger;
        }

        private void UpdateRXTriggerLevel()
        {
            m_cbRXTriggerLevel.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.TX) && m_params.UART_InterruptOnRXFIFOTrigger;
        }

        private void UpdateInterruptConnection()
        {
            bool bufSizeOverflow = (m_params.UART_RXBufferSize > 8) || (m_params.UART_TXBufferSize > 8);

            m_rbNone.Enabled = !bufSizeOverflow;
            m_rbExternal.Enabled = !bufSizeOverflow;
            m_rbInternal.Checked = bufSizeOverflow || m_params.UART_InterruptMode == CyEInterruptModeType.INTERNAL;
        }

        public void UpdateTXNACKIntr()
        {
            m_chbInterruptTxNack.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.RX) &&
                (m_params.UART_SubMode == CyEUARTSubModeType.SMART_CARD);

            if (m_params.UART_SubMode != CyEUARTSubModeType.SMART_CARD)
            {
                m_chbInterruptTxNack.Checked = false;
            }
        }

        public void UpdateRXFrameErrorIntr()
        {
            m_chbInterruptRXFrameErr.Enabled = (m_params.UART_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.UART_Direction != CyEUARTDirectionType.TX) &&
                (m_params.UART_NumberStopBits != CyEUARTNumberStopBitsType.ONE_BIT ||
                m_params.UART_Direction != CyEUARTDirectionType.RX);
        }

        public void UpdateMultiprocessorMode()
        {
            bool enabled = m_params.UART_NumberDataBits == CyEUARTNumberDataBitsType.NINE &&
                m_params.UART_SubMode == CyEUARTSubModeType.STANDARD;

            m_chbEnMultiProcMode.Enabled = enabled;

            bool multiprocModeEnabled = enabled && m_params.UART_MultiProcessorModeEnabled;

            m_lblAddress.Enabled = multiprocModeEnabled;
            m_numAddress.Enabled = multiprocModeEnabled;
            m_lblMask.Enabled = multiprocModeEnabled;
            m_numAddressMask.Enabled = multiprocModeEnabled;
            m_chbAcceptAddress.Enabled = multiprocModeEnabled;
        }

        public void UpdateRxDropOnParityError()
        {
            m_chbDropOnParityError.Enabled = m_params.UART_ParityType != CyEUARTParityType.PARITY_NONE &&
                m_params.UART_SubMode != CyEUARTSubModeType.IRDA &&
                m_params.UART_Direction != CyEUARTDirectionType.TX;
        }

        public void UpdateRxDropOnFrameError()
        {
            m_chbDropOnFrameError.Enabled = m_params.UART_Direction != CyEUARTDirectionType.TX;
        }
        #endregion

        #region Event handlers
        void m_numBufferSize_TextChanged(object sender, EventArgs e)
        {
            if (sender == m_numRXBufferSize || sender == m_numTXBufferSize)
            {
                m_errorProvider.SetError(sender as NumericUpDown, string.Empty);

                UInt32 value;

                if (UInt32.TryParse((sender as NumericUpDown).Text, out value))
                {
                    UInt32 minValue = 1;
                    string errorMsg = string.Empty;

                    if (sender == m_numRXBufferSize)
                    {
                        if (m_params.GlobalEditMode)
                        {
                            m_params.UART_RXBufferSize = value;
                        }

                        minValue = CyParamRanges.UART_RX_BUFFER_MIN_SIZE;
                        if (value < minValue)
                        {
                            errorMsg = string.Format(Resources.UARTRXBufferSizeError, minValue);
                        }
                        UpdateRXNotEmtyIntr();
                    }
                    else if (sender == m_numTXBufferSize)
                    {
                        if (m_params.GlobalEditMode)
                        {
                            m_params.UART_TXBufferSize = value;
                        }

                        minValue = CyParamRanges.UART_TX_BUFFER_MIN_SIZE;
                        if (value < minValue)
                        {
                            errorMsg = string.Format(Resources.UARTTXBufferSizeError, minValue);
                        }
                        UpdateTXNotFullIntr();
                    }

                    UpdateInterruptConnection();

                    m_errorProvider.SetError(sender as Control, errorMsg);
                }
                else
                {
                    m_errorProvider.SetError(sender as Control, Resources.UARTBufferSizeValueFormatError);
                }
            }
        }

        void m_numAddress_TextChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_numAddress || sender == m_numAddressMask)
                {
                    try
                    {
                        UInt16 value = Convert.ToUInt16((sender as NumericUpDown).Text, 16);

                        if (sender == m_numAddress)
                        {
                            m_params.UART_MultiProcessorAddress = (byte)value;
                        }
                        else
                        {
                            m_params.UART_MultiProcessorAddressMask = (byte)value;
                        }

                        if (value >= byte.MinValue && value <= byte.MaxValue)
                        {
                            m_errorProvider.SetError(sender as Control, string.Empty);
                        }
                        else
                        {
                            throw new Exception();
                        }
                    }
                    catch
                    {
                        m_errorProvider.SetError(sender as Control, string.Format(Resources.UARTAddressFormatError,
                            byte.MinValue, byte.MaxValue));
                    }
                }
            }
        }

        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                // Interrupts
                if (sender == m_chbInterruptUARTDone)
                {
                    m_params.UART_MedianFilterEnabled = m_chbInterruptUARTDone.Checked;
                }
                else if (sender == m_chbInterruptTXNotFull)
                {
                    m_params.UART_InterruptOnTXFIFONotFull = m_chbInterruptTXNotFull.Checked;
                }
                else if (sender == m_chbInterruptTXEmpty)
                {
                    m_params.UART_InterruptOnTXFIFOEmpty = m_chbInterruptTXEmpty.Checked;
                }
                else if (sender == m_chbInterruptTXOverflow)
                {
                    m_params.UART_InterruptOnTXFIFOOverflow = m_chbInterruptTXOverflow.Checked;
                }
                else if (sender == m_chbInterruptTXUnderflow)
                {
                    m_params.UART_InterruptOnTXFIFOUnderflow = m_chbInterruptTXUnderflow.Checked;
                }
                else if (sender == m_chbInterruptTXLostArb)
                {
                    m_params.UART_InterruptOnTXLostArbitration = m_chbInterruptTXLostArb.Checked;
                }
                else if (sender == m_chbInterruptTxNack)
                {
                    m_params.UART_InterruptOnTXNACK = m_chbInterruptTxNack.Checked;
                }
                else if (sender == m_chbInterruptTXTrigger)
                {
                    m_params.UART_InterruptOnTXFIFOTrigger = m_chbInterruptTXTrigger.Checked;
                    UpdateTXTriggerLevel();
                }
                else if (sender == m_chbInterruptRXFull)
                {
                    m_params.UART_InterruptOnRXFIFOFull = m_chbInterruptRXFull.Checked;
                }
                else if (sender == m_chbInterruptRXNotEmpty)
                {
                    m_params.UART_InterruptOnRXFIFONotEmpty = m_chbInterruptRXNotEmpty.Checked;
                }
                else if (sender == m_chbInterruptRXOverflow)
                {
                    m_params.UART_InterruptOnRXFIFOOverflow = m_chbInterruptRXOverflow.Checked;
                }
                else if (sender == m_chbInterruptRXUnderflow)
                {
                    m_params.UART_InterruptOnRXFIFOUnderflow = m_chbInterruptRXUnderflow.Checked;
                }
                else if (sender == m_chbInterruptRXFrameErr)
                {
                    m_params.UART_InterruptOnRXFrameError = m_chbInterruptRXFrameErr.Checked;
                }
                else if (sender == m_chbInterruptRXParityErr)
                {
                    m_params.UART_InterruptOnRXParityError = m_chbInterruptRXParityErr.Checked;
                }
                else if (sender == m_chbInterruptRXTrigger)
                {
                    m_params.UART_InterruptOnRXFIFOTrigger = m_chbInterruptRXTrigger.Checked;
                    UpdateRXTriggerLevel();
                }
                // Multi processor mode
                else if (sender == m_chbEnMultiProcMode)
                {
                    m_params.UART_MultiProcessorModeEnabled = m_chbEnMultiProcMode.Checked;
                    UpdateMultiprocessorMode();
                }
                // RX FIFO Drop
                else if (sender == m_chbDropOnFrameError)
                {
                    m_params.UART_RXFIFODropOnFrameError = m_chbDropOnFrameError.Checked;
                }
                else if (sender == m_chbDropOnParityError)
                {
                    m_params.UART_RXFIFODropOnParityError = m_chbDropOnParityError.Checked;
                }
                else if (sender == m_chbAcceptAddress)
                {
                    m_params.UART_MultiProcessorAcceptAddress = m_chbAcceptAddress.Checked;
                }
            }
        }

        void m_cb_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (sender == m_cbRXTriggerLevel)
                {
                    m_params.UART_RXTriggerLevel = (byte)m_cbRXTriggerLevel.SelectedIndex;
                }
                else if (sender == m_cbTXTriggerLevel)
                {
                    m_params.UART_TXTriggerLevel = (byte)m_cbTXTriggerLevel.SelectedIndex;
                }
            }
        }

        void m_rbIntrMode_CheckedChanged(object sender, EventArgs e)
        {
            if (m_params.GlobalEditMode)
            {
                if (m_rbNone.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.INTERRUPT_NONE;
                }
                else if (m_rbExternal.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.EXTERNAL;
                }
                else if (m_rbInternal.Checked)
                {
                    m_params.UART_InterruptMode = CyEInterruptModeType.INTERNAL;
                }
            }

            UpdateInterruptSources();
        }
        #endregion
    }
}
