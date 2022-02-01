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
    public partial class CyGeneralTab : CyTabControlWrapper
    {
        #region CyTabControlWrapper Members
        public override string TabName
        {
            get
            {
                return "Basic";
            }
        }
        #endregion

        #region Constructor(s)
        public CyGeneralTab(CyParameters param)
            : base(param)
        {
            // Initialize parameters objects
            m_params = param;
            m_params.m_generalTab = this;

            InitializeComponent();

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
        }
        #endregion

        #region Update UI
        public override void UpdateUI()
        {
            switch (m_params.SCBMode)
            {
                case CyESCBMode.UNCONFIG:
                    m_rbUnconfig.Checked = true;
                    break;
                case CyESCBMode.EZSPI:
                    m_rbEzSpi.Checked = true;
                    break;
                case CyESCBMode.EZI2C:
                    m_rbEZI2C.Checked = true;
                    break;
                case CyESCBMode.I2C:
                    m_rbI2C.Checked = true;
                    break;
                case CyESCBMode.UART:
                    m_rbUart.Checked = true;
                    break;
                case CyESCBMode.SPI:
                    m_rbSpi.Checked = true;
                    break;
            }
        }
        #endregion

        #region Event handlers
        private void rbconfig_CheckedChanged(object sender, EventArgs e)
        {
            RadioButton rb = sender as RadioButton;
            if (rb.Checked == false)
            {
                return;
            }

            if (rb == m_rbEZI2C)
            {
                m_params.SCBMode = CyESCBMode.EZI2C;
            }
            else if (rb == m_rbI2C)
            {
                m_params.SCBMode = CyESCBMode.I2C;
            }
            else if (rb == m_rbUart)
            {
                m_params.SCBMode = CyESCBMode.UART;
            }
            else if (rb == m_rbSpi)
            {
                m_params.SCBMode = CyESCBMode.SPI;
            }
            else if (rb == m_rbEzSpi)
            {
                m_params.SCBMode = CyESCBMode.EZSPI;
            }
            else if (rb == m_rbUnconfig)
            {
                m_params.SCBMode = CyESCBMode.UNCONFIG;
            }

            m_params.UpdateTabVisibility();
        }
        #endregion
    }
}
