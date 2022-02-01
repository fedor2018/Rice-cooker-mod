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
    public partial class CyBinaryGrid : UserControl
    {
        #region Constants
        private const string ZERO = "0";
        private const string ONE = "1";
        private const string X = "X";
        #endregion

        #region Class private members
        private int m_numberOfBits = 8;
        private bool m_valueUpdateLocked = false;
        private bool m_locked = false;
        private string[] m_bits;
        private List<Label> m_labelList = new List<Label>();
        #endregion

        public static readonly string ZeroSign = ZERO;
        public static readonly string OneSign = ONE;
        public static readonly string XSign = X;

        // Delegates
        public delegate void BitChangedEventHandler(object sender, EventArgs e);

        // Events
        public event BitChangedEventHandler BitChanged;

        #region Constructor(s)
        public CyBinaryGrid()
        {
            InitializeComponent();

            m_bits = new string[m_numberOfBits];

            // Add labels to the list for easy operating
            m_labelList.Add(lblBit7);
            m_labelList.Add(lblBit6);
            m_labelList.Add(lblBit5);
            m_labelList.Add(lblBit4);
            m_labelList.Add(lblBit3);
            m_labelList.Add(lblBit2);
            m_labelList.Add(lblBit1);
            m_labelList.Add(lblBit0);
        }
        #endregion

        #region Class properties
        public string[] Bits
        {
            get { return m_bits; }
            set
            {
                m_bits = value;
                UpdateGrid();
            }
        }

        public int NumberOfBits
        {
            get { return m_numberOfBits; }
            set { m_numberOfBits = value; }
        }

        public bool Locked
        {
            get { return m_locked; }
            set { m_locked = value; }
        }
        #endregion

        #region Event handlers
        private void lblBit_Click(object sender, EventArgs e)
        {
            Label currentLabel = (Label)sender;

            switch (currentLabel.Text)
            {
                case ZERO:
                    currentLabel.Text = ONE;
                    break;
                case ONE:
                    currentLabel.Text = ZERO;
                    break;
                default:
                    break;
            }
        }

        private void CyI2CP4FFBinaryGrid_Load(object sender, EventArgs e)
        {
            // Initial grid fill
            {
                // Disable unused bits
                for (int i = m_labelList.Count - 1; i >= m_numberOfBits; i--)
                {
                    m_labelList[i].Enabled = false;
                    m_bits[i] = X;
                }

                UpdateGrid();
            }
        }

        private void lblBit_TextChanged(object sender, EventArgs e)
        {
            if (m_valueUpdateLocked == false)
            {
                // Update values in array
                for (int i = 0; i < m_numberOfBits; i++)
                {
                    this.Bits[i] = m_labelList[i].Text;
                }

                // Raise Event
                if (BitChanged != null)
                    BitChanged(this, new EventArgs());
            }
        }
        #endregion

        private void UpdateGrid()
        {
            m_valueUpdateLocked = true;
            for (int i = 0; i < m_labelList.Count; i++)
            {
                m_labelList[i].Text = this.Bits[i];
            }
            m_valueUpdateLocked = false;
        }

        public void UpdateGridViewOnly(string[] bits)
        {
            m_valueUpdateLocked = true;
            for (int i = 0; i < m_labelList.Count; i++)
            {
                m_labelList[i].Text = bits[i];
            }
            m_valueUpdateLocked = false;
        }

        public void ResetBits()
        {
            for (int i = 0; i < m_bits.Length; i++)
            {
                m_bits[i] = ZERO;
            }
            UpdateGrid();
        }
    }
}
