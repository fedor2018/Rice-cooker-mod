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
using System.ComponentModel;

namespace SCB_P4_v1_0
{
    #region Component Parameters Names
    public partial class CyParamNames
    {
        public const string EZI2C_COLIDE_BEHAVIOR = "EzI2cWaitStatesEnable";
        public const string EZI2C_DATA_RATE = "EzI2cDataRate";
        public const string EZI2C_OVERSAMPLING = "EzI2cOvsFactor";
        public const string EZI2C_OPERATION_MODE = "EzI2cOperationMode";
        public const string EZI2C_CLOCK_FROM_TERMINAL = "EzI2cClockFromTerm";
        public const string EZI2C_ENABLE_MEDIAN_FILTER = "EzI2cMedianFilterEnable";
        public const string EZI2C_IS_SLAVE_ADDRESS_HEX = "EzI2cIsSlaveAddressHex";
        public const string EZI2C_IS_SLAVE_ADDRESS_MASK_HEX = "EzI2cIsSlaveAddressMaskHex";
        public const string EZI2C_POST_WAKEUP_BEHAVIOR = "EzI2cWakeAction";
        public const string EZI2C_SLAVE_ADDRESS = "EzI2cSlaveAddress";
        public const string EZI2C_SLAVE_ADDRESS_MASK = "EzI2cSlaveAddressMask";
        public const string EZI2C_ENABLE_WAKEUP = "EzI2cWakeEnable";

        public const string EZI2C_INTERRUPT_MODE = "EzI2cInterruptMode";
        public const string EZI2C_INTERRUPT_WAKE = "EzI2cIntrWake";
        public const string EZI2C_INTERRUPT_STOP = "EzI2cIntrStop";
        public const string EZI2C_INTERRUPT_WRITE_STOP = "EzI2cIntrWriteStop";
        public const string EZI2C_INTERRUPT_RX_BLOCKED = "EzI2cIntrRxBlocked";
        public const string EZI2C_INTERRUPT_TX_BLOCKED = "EzI2cIntrTxBlocked";
    }
    #endregion

    #region Component Parameters Ranges
    public partial class CyParamRanges
    {
        public const byte EZI2C_SLAVE_ADDRESS_MIN = 8;
        public const byte EZI2C_SLAVE_ADDRESS_MAX = 120;

        public const byte EZI2C_SLAVE_ADDRESS_MASK_MIN = 0;
        public const byte EZI2C_SLAVE_ADDRESS_MASK_MAX = 254;
    }
    #endregion

    #region Component Enums
    public enum CyEEZOperationalMode
    {
        [Description("Internally clocked")]
        INTERNALLY_CLOCKED,
        [Description("Externally clocked")]
        EXTERNALY_CLOCKED
    };
    public enum CyEEZColideBehavior { WAIT_STATES = 1, NO_WAIT_STATES = 0 };
    #endregion

    public partial class CyParameters
    {
        #region Class properties
        #region EZI2C Basic tab properties
        public CyEEZOperationalMode EZI2C_OperationMode
        {
            get { return GetValue<CyEEZOperationalMode>(CyParamNames.EZI2C_OPERATION_MODE); }
            set { SetValue(CyParamNames.EZI2C_OPERATION_MODE, value); }
        }

        public bool EZI2C_ClockFromTerminal
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_CLOCK_FROM_TERMINAL); }
            set { SetValue(CyParamNames.EZI2C_CLOCK_FROM_TERMINAL, value); }
        }

        public UInt16 EZI2C_DataRate
        {
            get { return GetValue<UInt16>(CyParamNames.EZI2C_DATA_RATE); }
            set { SetValue(CyParamNames.EZI2C_DATA_RATE, value); }
        }

        public byte EZI2C_OversamplingFactor
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_OVERSAMPLING); }
            set { SetValue(CyParamNames.EZI2C_OVERSAMPLING, value); }
        }

        public CyEEZColideBehavior EZI2C_ColideBehavior
        {
            get { return GetValue<CyEEZColideBehavior>(CyParamNames.EZI2C_COLIDE_BEHAVIOR); }
            set { SetValue(CyParamNames.EZI2C_COLIDE_BEHAVIOR, value); }
        }

        public bool EZI2C_EnableMedianFilter
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_ENABLE_MEDIAN_FILTER); }
            set { SetValue(CyParamNames.EZI2C_ENABLE_MEDIAN_FILTER, value); }
        }

        public bool EZI2C_EnableWakeupFromSleep
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_ENABLE_WAKEUP); }
            set { SetValue(CyParamNames.EZI2C_ENABLE_WAKEUP, value); }
        }

        public CyEI2CPostWakeupOperationType EZI2C_PostWakeupBehavior
        {
            get { return GetValue<CyEI2CPostWakeupOperationType>(CyParamNames.EZI2C_POST_WAKEUP_BEHAVIOR); }
            set { SetValue(CyParamNames.EZI2C_POST_WAKEUP_BEHAVIOR, value); }
        }

        public byte EZI2C_SlaveAddress
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_SLAVE_ADDRESS); }
            set { SetValue(CyParamNames.EZI2C_SLAVE_ADDRESS, value); }
        }

        public byte EZI2C_SlaveAddressMask
        {
            get { return GetValue<byte>(CyParamNames.EZI2C_SLAVE_ADDRESS_MASK); }
            set { SetValue(CyParamNames.EZI2C_SLAVE_ADDRESS_MASK, value); }
        }

        public bool EZI2C_IsSlaveAddressHex
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_IS_SLAVE_ADDRESS_HEX); }
            set { SetValue(CyParamNames.EZI2C_IS_SLAVE_ADDRESS_HEX, value); }
        }

        public bool EZI2C_IsSlaveAddressMaskHex
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_IS_SLAVE_ADDRESS_MASK_HEX); }
            set { SetValue(CyParamNames.EZI2C_IS_SLAVE_ADDRESS_MASK_HEX, value); }
        }
        #endregion

        #region #region EZI2C Advanced tab properties
        public CyEInterruptModeType EZI2C_InterruptMode
        {
            get { return GetValue<CyEInterruptModeType>(CyParamNames.EZI2C_INTERRUPT_MODE); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_MODE, value); }
        }

        public bool EZI2C_InterruptEZWake
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_INTERRUPT_WAKE); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_WAKE, value); }
        }

        public bool EZI2C_InterruptEZStop
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_INTERRUPT_STOP); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_STOP, value); }
        }

        public bool EZI2C_InterruptEZWriteStop
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_INTERRUPT_WRITE_STOP); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_WRITE_STOP, value); }
        }

        public bool EZI2C_InterruptEZRxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_INTERRUPT_RX_BLOCKED); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_RX_BLOCKED, value); }
        }

        public bool EZI2C_InterruptEZTxBlocked
        {
            get { return GetValue<bool>(CyParamNames.EZI2C_INTERRUPT_TX_BLOCKED); }
            set { SetValue(CyParamNames.EZI2C_INTERRUPT_TX_BLOCKED, value); }
        }
        #endregion
        #endregion
    }
}
