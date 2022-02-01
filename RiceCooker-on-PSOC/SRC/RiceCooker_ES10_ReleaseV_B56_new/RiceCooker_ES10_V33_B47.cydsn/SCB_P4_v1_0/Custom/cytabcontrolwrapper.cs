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
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v1_0
{
    public partial class CyTabControlWrapper : UserControl, ICyParamEditingControl
    {
        protected CyParameters m_params = null;
        protected ErrorProvider m_errorProvider = null;

        /// <summary>
        /// This property returns the tab name that will be associated with parameters in expression view.
        /// </summary>
        public virtual string TabName
        {
            get { return ""; }
        }

        /// <summary>
        /// This is method that updates UI from the parameters.
        /// </summary>
        public virtual void UpdateUI()
        {
        }

        #region Constructor(s)
        private CyTabControlWrapper() { }

        public CyTabControlWrapper(CyParameters prms)
        {
            m_params = prms;
            this.Load += new EventHandler(this.CyTabControlWrapper_Load);

            m_errorProvider = new ErrorProvider();
            m_errorProvider.BlinkStyle = ErrorBlinkStyle.NeverBlink;
        }
        #endregion

        private void CyTabControlWrapper_Load(object sender, EventArgs e)
        {
            this.Dock = DockStyle.Fill;
            this.AutoScroll = true;

        }

        protected void CommitCellValueImmediately(DataGridView dataGridView)
        {
            if (dataGridView.CurrentCell != null)
                if (dataGridView.CurrentCell.GetType() == typeof(DataGridViewCheckBoxCell))
                    if (dataGridView.IsCurrentCellDirty)
                    {
                        dataGridView.CommitEdit(DataGridViewDataErrorContexts.Commit);
                    }
        }

        protected override Point ScrollToControl(Control activeControl)
        {
            return AutoScrollPosition;
        }

        #region ICyParamEditingControl Members
        public Control DisplayControl
        {
            get { return this; }
        }

        public virtual IEnumerable<CyCustErr> GetErrors()
        {
            List<CyCustErr> errs = new List<CyCustErr>();
            string errorMessage = string.Empty;

            if (m_errorProvider != null)
            {
                // Check controls for errors
                foreach (Control control in this.Controls)
                {
                    errorMessage = m_errorProvider.GetError(control);
                    if (string.IsNullOrEmpty(errorMessage) == false)
                        errs.Add(new CyCustErr(errorMessage));

                    // Check controls inside groupbox
                    foreach (Control internalControl in control.Controls)
                    {
                        errorMessage = m_errorProvider.GetError(internalControl);
                        if (string.IsNullOrEmpty(errorMessage) == false)
                            errs.Add(new CyCustErr(errorMessage));
                    }
                }
            }

            foreach (string paramName in m_params.m_inst.GetParamNames())
            {
                CyCompDevParam param = m_params.m_inst.GetCommittedParam(paramName);
                if (param.TabName.Equals(TabName))
                {
                    if (param.ErrorCount > 0)
                    {
                        foreach (string errMsg in param.Errors)
                        {
                            errs.Add(new CyCustErr(errMsg));
                        }
                    }
                }
            }

            return errs;
        }
        #endregion
    }
}
