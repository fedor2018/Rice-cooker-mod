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
    public partial class CyEZSPIAdvancedTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "EZSPIAdvanced";
            }
        }
        #endregion

        #region Constructor(s)
        public CyEZSPIAdvancedTab(CyParameters parameters)
            : base(parameters)
        {
            m_params.m_ezSPIAdvancedTab = this;

            InitUI();
        }
        #endregion

        #region Update UI
        private void InitUI()
        {
            InitializeComponent();

            // Set initial states for checkboxes' tags
            m_chbEzWake.Tag = m_params.EZSPI_InterruptEZWake;
            m_chbRxFifoBlocked.Tag = m_params.EZSPI_InterruptEZRxBlocked;
            m_chbTxFifoBlocked.Tag = m_params.EZSPI_InterruptEZTxBlocked;

            // Assign event handlers
            m_rbNoneIntr.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbExternalIntr.CheckedChanged += new EventHandler(m_rb_CheckedChanged);
            m_rbInternalIntr.CheckedChanged += new EventHandler(m_rb_CheckedChanged);

            m_chbEzWake.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEzStop.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbEzWriteStop.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbRxFifoBlocked.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
            m_chbTxFifoBlocked.CheckedChanged += new EventHandler(m_chb_CheckedChanged);
        }

        public override void UpdateUI()
        {
            switch (m_params.EZSPI_InterruptMode)
            {
                case CyEInterruptModeType.INTERRUPT_NONE:
                    m_rbNoneIntr.Checked = true;
                    break;
                case CyEInterruptModeType.INTERNAL:
                    m_rbInternalIntr.Checked = true;
                    break;
                case CyEInterruptModeType.EXTERNAL:
                    m_rbExternalIntr.Checked = true;
                    break;
            }

            m_chbEzWake.Checked = m_params.EZSPI_InterruptEZWake;
            m_chbEzStop.Checked = m_params.EZSPI_InterruptEZStop;
            m_chbEzWriteStop.Checked = m_params.EZSPI_InterruptEZWriteStop;
            m_chbRxFifoBlocked.Checked = m_params.EZSPI_InterruptEZRxBlocked;
            m_chbTxFifoBlocked.Checked = m_params.EZSPI_InterruptEZTxBlocked;
        }

        public void UpdateCheckBoxState()
        {
            m_chbEzWake.Enabled = m_params.EZSPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE &&
                m_params.EZSPI_OperationalMode == CyEEZOperationalMode.EXTERNALY_CLOCKED;
            m_chbEzStop.Enabled = m_params.EZSPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;
            m_chbEzWriteStop.Enabled = m_params.EZSPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE;

            bool fifoBlockedIntrEnabled = (m_params.EZSPI_InterruptMode != CyEInterruptModeType.INTERRUPT_NONE) &&
                (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.EXTERNALY_CLOCKED) &&
                (m_params.EZSPI_ColideBehavior == CyEEZColideBehavior.NO_WAIT_STATES);

            m_chbRxFifoBlocked.Enabled = fifoBlockedIntrEnabled;
            m_chbTxFifoBlocked.Enabled = fifoBlockedIntrEnabled;
        }

        public void UpdateInterruptSources()
        {
            CheckBox[] sources = new CheckBox[] { m_chbEzWake, m_chbRxFifoBlocked, m_chbTxFifoBlocked };

            foreach (CheckBox chb in sources)
            {
                if (chb.Enabled || m_params.EZSPI_InterruptMode == CyEInterruptModeType.INTERRUPT_NONE)
                {
                    chb.Checked = (bool)chb.Tag;
                }
                else
                {
                    chb.Tag = chb.Checked;
                }

                if (m_params.EZSPI_OperationalMode == CyEEZOperationalMode.INTERNALLY_CLOCKED)
                {
                    chb.Checked = false;
                }
            }
        }
        #endregion

        #region Event handlers
        void m_chb_CheckedChanged(object sender, EventArgs e)
        {
            CheckBox chb = sender as CheckBox;

            if (chb != null)
            {
                if (chb == m_chbEzWake)
                {
                    m_params.EZSPI_InterruptEZWake = chb.Checked;
                }
                else if (chb == m_chbEzStop)
                {
                    m_params.EZSPI_InterruptEZStop = chb.Checked;
                }
                else if (chb == m_chbEzWriteStop)
                {
                    m_params.EZSPI_InterruptEZWriteStop = chb.Checked;
                }
                else if (chb == m_chbRxFifoBlocked)
                {
                    m_params.EZSPI_InterruptEZRxBlocked = chb.Checked;
                }
                else if (chb == m_chbTxFifoBlocked)
                {
                    m_params.EZSPI_InterruptEZTxBlocked = chb.Checked;
                }
            }
        }

        void m_rb_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;

            if (rb != null)
            {
                if (rb == m_rbNoneIntr)
                {
                    m_params.EZSPI_InterruptMode = CyEInterruptModeType.INTERRUPT_NONE;
                }
                else if (rb == m_rbExternalIntr)
                {
                    m_params.EZSPI_InterruptMode = CyEInterruptModeType.EXTERNAL;
                }
                else if (rb == m_rbInternalIntr)
                {
                    m_params.EZSPI_InterruptMode = CyEInterruptModeType.INTERNAL;
                }
                UpdateCheckBoxState();
                m_params.m_ezSPITab.UpdateWakeUpControls();
            }
        }
        #endregion
    }
}
