/*******************************************************************************
* Copyright 2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

using System;
using System.Collections.Generic;
using System.Text;
using CyDesigner.Extensions.Gde;
using CyDesigner.Extensions.Common;

namespace SCB_P4_v1_0
{
    public class CyCustomizer : ICyAPICustomize_v1, ICyParamEditHook_v1, ICyBootLoaderSupport
    {
        #region ICyParamEditHook_v1 members
        public System.Windows.Forms.DialogResult EditParams(ICyInstEdit_v1 edit, ICyTerminalQuery_v1 termQuery,
            ICyExpressMgr_v1 mgr)
        {
            CyParameters parameters = new CyParameters(edit);
            parameters.m_term = termQuery;
            parameters.GlobalEditMode = false;

            ICyTabbedParamEditor editor = edit.CreateTabbedParamEditor();
            parameters.m_editor = editor;

            #region Create tab pages
            CyGeneralTab generalTab = new CyGeneralTab(parameters);
            CySCBTab scbTab = new CySCBTab(parameters);
            CyI2CTab i2cTab = new CyI2CTab(parameters);
            CySPIBasicTab spiBasicTab = new CySPIBasicTab(parameters);
            CySPIAdvancedTab spiAdvancedTab = new CySPIAdvancedTab(parameters);
            CyUARTConfigureTab uartConfigTab = new CyUARTConfigureTab(parameters);
            CyUARTAdvancedTab uartAdvancedTab = new CyUARTAdvancedTab(parameters);
            CyEZI2CTab ezI2CTab = new CyEZI2CTab(parameters);
            CyEZI2CAdvancedTab ezI2CAdvancedTab = new CyEZI2CAdvancedTab(parameters);
            CyEZSPITab ezSPITab = new CyEZSPITab(parameters);
            CyEZSPIAdvancedTab ezSPIAdvancedTab = new CyEZSPIAdvancedTab(parameters);
            #endregion

            #region Interaction between expression view and custom view
            CyParamExprDelegate generalChanged =
            delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                generalTab.UpdateUI();
                scbTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate i2CDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                i2cTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezI2CDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                ezI2CTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezI2CAdvancedDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                ezI2CAdvancedTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezSPIDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                ezSPITab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate ezSPIAdvancedDataChanged = delegate(ICyParamEditor custEditor,
                CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                ezSPIAdvancedTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate spiDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                spiBasicTab.UpdateUI();
                spiAdvancedTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };

            CyParamExprDelegate uartDataChanged = delegate(ICyParamEditor custEditor, CyCompDevParam param)
            {
                parameters.GlobalEditMode = false;
                uartConfigTab.UpdateUI();
                uartAdvancedTab.UpdateUI();
                parameters.GlobalEditMode = true;
            };
            #endregion

            #region Add tabs to the customizer
            editor.AddCustomPage(Resources.GeneralTabDisplayName, generalTab, generalChanged, generalTab.TabName);
            editor.AddCustomPage(Resources.SCBTabDisplayName, scbTab, generalChanged, scbTab.TabName);
            editor.AddCustomPage(Resources.I2CTabDisplayName, i2cTab, i2CDataChanged, i2cTab.TabName);
            editor.AddCustomPage(Resources.SPIBasicTabDisplayName, spiBasicTab, spiDataChanged, spiBasicTab.TabName);
            editor.AddCustomPage(Resources.SPIAdvancedTabDisplayName, spiAdvancedTab, spiDataChanged,
                spiAdvancedTab.TabName);
            editor.AddCustomPage(Resources.UARTConfigTabDisplayName, uartConfigTab, uartDataChanged,
                uartConfigTab.TabName);
            editor.AddCustomPage(Resources.UARTAdvancedTabDisplayName, uartAdvancedTab, uartDataChanged,
                uartAdvancedTab.TabName);
            editor.AddCustomPage(Resources.EZI2CBasicTabDisplayName, ezI2CTab, ezI2CDataChanged, ezI2CTab.TabName);
            editor.AddCustomPage(Resources.EZI2CAdvancedTabDisplayName, ezI2CAdvancedTab, ezI2CAdvancedDataChanged,
                ezI2CAdvancedTab.TabName);
            editor.AddCustomPage(Resources.EZSPIBasicTabDisplayName, ezSPITab, ezSPIDataChanged, ezSPITab.TabName);
            editor.AddCustomPage(Resources.EZSPIAdvancedTabDisplayName, ezSPIAdvancedTab, ezSPIAdvancedDataChanged,
                ezSPIAdvancedTab.TabName);

            editor.AddDefaultPage(Resources.BuiltInTabDisplayName, "Built-in");
            #endregion

            parameters.UpdateTabVisibility();

            // Update all tabs
            generalTab.UpdateUI();
            scbTab.UpdateUI();
            i2cTab.UpdateUI();
            spiBasicTab.UpdateUI();
            spiAdvancedTab.UpdateUI();
            uartConfigTab.UpdateUI();
            uartAdvancedTab.UpdateUI();
            ezI2CTab.UpdateUI();
            ezI2CAdvancedTab.UpdateUI();
            ezSPITab.UpdateUI();
            ezSPIAdvancedTab.UpdateUI();

            parameters.GlobalEditMode = true;

            edit.NotifyWhenDesignUpdates(parameters.UpdateDesigns);

            return editor.ShowDialog();
        }

        public bool EditParamsOnDrop
        {
            get { return false; }
        }

        public CyCompDevParamEditorMode GetEditorMode()
        {
            return CyCompDevParamEditorMode.COMPLETE;
        }
        #endregion

        #region ICyAPICustomize_v1 members

        #region API Customizer File Constants and Variables
        const string I2C_FILE_PATTERN = "_I2C";
        const string EZI2C_FILE_PATTERN = "_EZI2C";
        const string EZSPI_FILE_PATTERN = "_EZSPI";
        const string EZ_FILE_PATTERN = "_EZ_";
        const string UART_PATTERN = "_UART";
        const string SPI_PATTERN = "_SPI";

        const string I2C_SLAVE_NAME = "SCB_I2C_SLAVE.c";
        const string I2C_MASTER_NAME = "SCB_I2C_MASTER.c ";
        const string SCB_PINS_NAME = "SCB_PINS.h";
        const string SPI_INTERRUPTS_FILE_PATTERN = "_SPI_UART_INT";
        CyAPICustomizer m_i2cSlaveName = null;
        CyAPICustomizer m_i2cMasterName = null;
        CyAPICustomizer m_scbPinsName = null;
        CyAPICustomizer m_spiUartInterruptName = null;

        List<CyAPICustomizer> m_i2cFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_ezFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_spiFiles = new List<CyAPICustomizer>();
        List<CyAPICustomizer> m_uartFiles = new List<CyAPICustomizer>();
        #endregion

        public IEnumerable<CyAPICustomizer> CustomizeAPIs(ICyInstQuery_v1 query, ICyTerminalQuery_v1 termQuery, 
            IEnumerable<CyAPICustomizer> apis)
        {
            List<CyAPICustomizer> inputCustomizers = new List<CyAPICustomizer>(apis);
            List<CyAPICustomizer> outputCustomizers = new List<CyAPICustomizer>();

            Dictionary<string, string> paramDict = null;

            CyParameters parameters = new CyParameters(query);

            paramDict = inputCustomizers[0].MacroDictionary;

            foreach (CyAPICustomizer file in inputCustomizers)
            {
                if (file.OriginalName.Contains(I2C_FILE_PATTERN))
                    m_i2cFiles.Add(file);
                if (file.OriginalName.Contains(SPI_PATTERN) )
                    m_spiFiles.Add(file);
                if (file.OriginalName.Contains(UART_PATTERN))
                    m_uartFiles.Add(file);
                if ((file.OriginalName.Contains(EZI2C_FILE_PATTERN)) ||
                    (file.OriginalName.Contains(EZSPI_FILE_PATTERN)) ||
                    (file.OriginalName.Contains(EZ_FILE_PATTERN)))
                    m_ezFiles.Add(file);

                if (file.OriginalName.EndsWith(I2C_SLAVE_NAME))
                    m_i2cSlaveName = file;

                if (file.OriginalName.EndsWith(I2C_MASTER_NAME))
                    m_i2cMasterName = file;

                if (file.OriginalName.Contains(SPI_INTERRUPTS_FILE_PATTERN))
                    m_spiUartInterruptName = file;

                if (file.OriginalName.EndsWith(SCB_PINS_NAME))
                    m_scbPinsName = file;
            }

            outputCustomizers.AddRange(inputCustomizers);


            if (parameters.SCBMode != CyESCBMode.UNCONFIG)
            {
                outputCustomizers.Remove(m_scbPinsName);
            }

            switch (parameters.SCBMode)
            {
                case CyESCBMode.I2C:

                    foreach (CyAPICustomizer item in m_ezFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_spiFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_uartFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    //Remove SCB_I2C_SLAVE.c 
                    if (parameters.I2C_Mode != CyEI2CModeType.I2C_SLAVE && parameters.I2C_Mode != 
                        CyEI2CModeType.I2C_MULTI_MASTER_SLAVE)
                        outputCustomizers.Remove(m_i2cSlaveName);

                    //Remove SCB_I2C_MASTER.c
                    if (parameters.I2C_Mode == CyEI2CModeType.I2C_SLAVE)
                        outputCustomizers.Remove(m_i2cMasterName);

                    break;
                case CyESCBMode.EZI2C:
                case CyESCBMode.EZSPI:
                    foreach (CyAPICustomizer item in m_i2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_spiFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_uartFiles)
                    {
                        outputCustomizers.Remove(item);
                    }
                    
                    for (int i = 0; i < m_ezFiles.Count; i++)
                    {
                        if (m_ezFiles[i].OriginalName.Contains(EZSPI_FILE_PATTERN) &&
                            parameters.SCBMode == CyESCBMode.EZI2C)
                        {
                            outputCustomizers.Remove(m_ezFiles[i]);
                        }
                        if (m_ezFiles[i].OriginalName.Contains(EZI2C_FILE_PATTERN) &&
                            parameters.SCBMode == CyESCBMode.EZSPI)
                        {
                            outputCustomizers.Remove(m_ezFiles[i]);
                        }
                    }
                    break;
                case CyESCBMode.UART:
                case CyESCBMode.SPI:

                    foreach (CyAPICustomizer item in m_i2cFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    foreach (CyAPICustomizer item in m_ezFiles)
                    {
                        outputCustomizers.Remove(item);
                    }

                    if (parameters.SCBMode == CyESCBMode.SPI &&
                        parameters.SPI_InterruptMode != CyEInterruptModeType.INTERNAL)
                    {
                        outputCustomizers.Remove(m_spiUartInterruptName);
                    }

                    if (parameters.SCBMode == CyESCBMode.UART)
                    {
                        foreach (CyAPICustomizer item in m_spiFiles)
                        {
                            if (m_uartFiles.Contains(item) == false)
                            {
                                outputCustomizers.Remove(item);
                            }
                        }
                    }
                    else
                        foreach (CyAPICustomizer item in m_uartFiles)
                            if (m_spiFiles.Contains(item) == false)
                            {
                                outputCustomizers.Remove(item);
                            }

                    break;
            }

            // Add #include
            StringBuilder builderInclude = new StringBuilder();
            string instName = query.GetCommittedParam("INSTANCE_NAME").Value;
            switch (parameters.SCBMode)
            {
                case CyESCBMode.EZI2C:
                case CyESCBMode.EZSPI:
                    for (int i = 0; i < m_ezFiles.Count; i++)
                    {
                        if (m_ezFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_ezFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.I2C:
                    for (int i = 0; i < m_i2cFiles.Count; i++)
                    {
                        if (m_i2cFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_i2cFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.UART:
                    for (int i = 0; i < m_uartFiles.Count; i++)
                    {
                        if (m_uartFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_uartFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.SPI:
                    for (int i = 0; i < m_spiFiles.Count; i++)
                    {
                        if (m_spiFiles[i].OutputName.EndsWith(".h"))
                        {
                            builderInclude.AppendLine(AddIncludeStr(m_spiFiles[i].OutputName));
                        }
                    }
                    break;
                case CyESCBMode.UNCONFIG:
                    for (int i = 0; i < inputCustomizers.Count; i++)
                    {
                        if (inputCustomizers[i].OutputName.EndsWith(".h") && 
                            inputCustomizers[i].OutputName != instName + ".h")
                        {
                            builderInclude.AppendLine(AddIncludeStr(inputCustomizers[i].OutputName));
                        }
                    }
                    break;
                default:
                    break;
            }
            paramDict.Add("IncludeDefines", builderInclude.ToString());


            // Replace macro dictionaries with paramDict
            foreach (CyAPICustomizer file in outputCustomizers)
            {
                file.MacroDictionary = paramDict;
            }

            return outputCustomizers;
        }

        private static string AddIncludeStr(string name)
        {
            return String.Format("#include \"{0}\"", name);
        }
        #endregion

        #region ICyBootLoaderSupport members
        public CyCustErr IsBootloaderReady(ICyInstQuery_v1 inst)
        {
            CyParameters parameters = new CyParameters(inst);

            if ((parameters.SCBMode != CyESCBMode.UNCONFIG) && (parameters.SCBMode != CyESCBMode.I2C ||
                (parameters.I2C_Mode == CyEI2CModeType.I2C_SLAVE &&
                parameters.I2C_Mode == CyEI2CModeType.I2C_MULTI_MASTER_SLAVE)))
            {
                return new CyCustErr(Resources.BootloaderSupportModeFailError);
            }

            return CyCustErr.OK;
        }
        #endregion
    }
}
