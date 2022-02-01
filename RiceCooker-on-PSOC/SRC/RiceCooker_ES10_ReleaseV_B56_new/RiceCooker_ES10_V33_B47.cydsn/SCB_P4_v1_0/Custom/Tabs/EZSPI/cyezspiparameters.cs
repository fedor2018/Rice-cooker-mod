/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Common;
using CyDesigner.Extensions.Gde;

namespace SCB_P4_v1_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string EZSPI_OPERATION_MODE = "EzSpiOperationMode";
        public const string EZSPI_CLOCK_FROM_TERMINAL = "EzSpiClockFromTerm";
        public const string EZSPI_BIT_RATE = "EzSpiBitRate";
        public const string EZSPI_OVERSAMPLING = "EzSpiOvsFactor";
        public const string EZSPI_ENABLE_MEDIAN_FILTER = "EzSpiMedianFilterEnable";
        public const string EZSPI_WAKEUP_FROM_SLEEP_MODE = "EzSpiWakeEnable";
        public const string EZSPI_COLIDE_BEHAVIOR = "EzSpiWaitStatesEnable";

        public const string EZSPI_INTERRUPT_MODE = "EzSpiInterruptMode";
        public const string EZSPI_INTERRUPT_WAKE = "EzSpiIntrWake";
        public const string EZSPI_INTERRUPT_STOP = "EzSpiIntrStop";
        public const string EZSPI_INTERRUPT_WRITE_STOP = "EzSpiIntrWriteStop";
        public const string EZSPI_INTERRUPT_RX_BLOCKED = "EzSpiIntrRxBlocked";
        public const string EZSPI_INTERRUPT_TX_BLOCKED = "EzSpiIntrTxBlocked";
    }
    #endregion

    public partial class CyParameters
    {
        const string EZSPI_CLOCK_SCBCLK = "or_sclk";
        public const string EZSPI_CLOCK_HF = "or_hclk";
        #region Declaring public variables

        // List contains display names of type taken from symbol. It is used to fill combobox.
        //public List<string> m_modesList;

        #endregion

        #region Class properties
        #region EZSPI Basic tab properties
        public CyEEZOperationalMode EZSPI_OperationalMode
        {
            get { return GetValue<CyEEZOperationalMode>(CyParamNames.EZSPI_OPERATION_MODE); }
            set { SetValue(CyParamNames.EZSPI_OPERATION_MODE, value); }
        }

        public bool EZSPI_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_CLOCK_FROM_TERMINAL); }
            set { SetValue(CyParamNames.EZSPI_CLOCK_FROM_TERMINAL, value); }
        }

        public UInt16 EZSPI_BitRate
        {
            get { return GetValue<UInt16>(CyParamNames.EZSPI_BIT_RATE); }
            set { SetValue(CyParamNames.EZSPI_BIT_RATE, value); }
        }

        public byte EZSPI_OversamplingFactor
        {
            get { return GetValue<byte>(CyParamNames.EZSPI_OVERSAMPLING); }
            set { SetValue(CyParamNames.EZSPI_OVERSAMPLING, value); }
        }

        public bool EZSPI_MedianFilterEnabled
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_ENABLE_MEDIAN_FILTER); }
            set { SetValue(CyParamNames.EZSPI_ENABLE_MEDIAN_FILTER, value); }
        }

        public bool EZSPI_EnableWakeUpFromSleepMode
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_WAKEUP_FROM_SLEEP_MODE); }
            set { SetValue(CyParamNames.EZSPI_WAKEUP_FROM_SLEEP_MODE, value); }
        }

        public CyEEZColideBehavior EZSPI_ColideBehavior
        {
            get { return GetValue<CyEEZColideBehavior>(CyParamNames.EZSPI_COLIDE_BEHAVIOR); }
            set { SetValue(CyParamNames.EZSPI_COLIDE_BEHAVIOR, value); }
        }
        #endregion

        #region EZSPI Basic tab properties
        public CyEInterruptModeType EZSPI_InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.EZSPI_INTERRUPT_MODE); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_MODE, value); }
        }

        public bool EZSPI_InterruptEZWake
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_INTERRUPT_WAKE); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_WAKE, value); }
        }

        public bool EZSPI_InterruptEZStop
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_INTERRUPT_STOP); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_STOP, value); }
        }

        public bool EZSPI_InterruptEZWriteStop
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_INTERRUPT_WRITE_STOP); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_WRITE_STOP, value); }
        }

        public bool EZSPI_InterruptEZRxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_INTERRUPT_RX_BLOCKED); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_RX_BLOCKED, value); }
        }

        public bool EZSPI_InterruptEZTxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZSPI_INTERRUPT_TX_BLOCKED); }
            set { SetValue(CyParamNames.EZSPI_INTERRUPT_TX_BLOCKED, value); }
        }
        #endregion
        #endregion
    }
}
