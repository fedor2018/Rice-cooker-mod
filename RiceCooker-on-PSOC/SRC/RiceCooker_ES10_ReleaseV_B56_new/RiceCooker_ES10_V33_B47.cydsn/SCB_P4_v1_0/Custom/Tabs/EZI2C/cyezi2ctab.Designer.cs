namespace SCB_P4_v1_0
{
    partial class CyEZI2CTab
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.m_rbNoWaitStates = new System.Windows.Forms.RadioButton();
            this.m_rbWaitStates = new System.Windows.Forms.RadioButton();
            this.panel1 = new System.Windows.Forms.Panel();
            this.m_panInternalClockConfig = new System.Windows.Forms.Panel();
            this.m_chbClkFromTerm = new System.Windows.Forms.CheckBox();
            this.m_numOvsFactor = new System.Windows.Forms.NumericUpDown();
            this.m_lblDataRate = new System.Windows.Forms.Label();
            this.m_lblOvsFactor = new System.Windows.Forms.Label();
            this.m_cbDataRate = new System.Windows.Forms.ComboBox();
            this.m_lblActualDataRate = new System.Windows.Forms.Label();
            this.m_chbEnMedianFilter = new System.Windows.Forms.CheckBox();
            this.m_cbClkMode = new System.Windows.Forms.ComboBox();
            this.m_lblClkMode = new System.Windows.Forms.Label();
            this.m_grpCollideBehavior = new System.Windows.Forms.GroupBox();
            this.panel2 = new System.Windows.Forms.Panel();
            this.m_chbEnableWakeup = new System.Windows.Forms.CheckBox();
            this.m_grpWakeUp = new System.Windows.Forms.GroupBox();
            this.m_rbAddressAck = new System.Windows.Forms.RadioButton();
            this.m_rbAddressNack = new System.Windows.Forms.RadioButton();
            this.m_binaryGridSlaveAddressMask = new SCB_P4_v1_0.CyBinaryGrid();
            this.m_binaryGridSlaveAddress = new SCB_P4_v1_0.CyBinaryGrid();
            this.lblSlaveAddress = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.m_tbSlaveAddress = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.m_tbSlaveAddressMask = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.panel1.SuspendLayout();
            this.m_panInternalClockConfig.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).BeginInit();
            this.m_grpCollideBehavior.SuspendLayout();
            this.panel2.SuspendLayout();
            this.m_grpWakeUp.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_rbNoWaitStates
            // 
            this.m_rbNoWaitStates.AutoSize = true;
            this.m_rbNoWaitStates.Location = new System.Drawing.Point(6, 42);
            this.m_rbNoWaitStates.Name = "m_rbNoWaitStates";
            this.m_rbNoWaitStates.Size = new System.Drawing.Size(92, 17);
            this.m_rbNoWaitStates.TabIndex = 1;
            this.m_rbNoWaitStates.TabStop = true;
            this.m_rbNoWaitStates.Text = "No wait states";
            this.m_rbNoWaitStates.UseVisualStyleBackColor = true;
            // 
            // m_rbWaitStates
            // 
            this.m_rbWaitStates.AutoSize = true;
            this.m_rbWaitStates.Location = new System.Drawing.Point(6, 19);
            this.m_rbWaitStates.Name = "m_rbWaitStates";
            this.m_rbWaitStates.Size = new System.Drawing.Size(78, 17);
            this.m_rbWaitStates.TabIndex = 0;
            this.m_rbWaitStates.TabStop = true;
            this.m_rbWaitStates.Text = "Wait states";
            this.m_rbWaitStates.UseVisualStyleBackColor = true;
            // 
            // panel1
            // 
            this.panel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel1.Controls.Add(this.m_panInternalClockConfig);
            this.panel1.Controls.Add(this.m_cbClkMode);
            this.panel1.Controls.Add(this.m_lblClkMode);
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(422, 124);
            this.panel1.TabIndex = 0;
            // 
            // m_panInternalClockConfig
            // 
            this.m_panInternalClockConfig.Controls.Add(this.m_chbClkFromTerm);
            this.m_panInternalClockConfig.Controls.Add(this.m_numOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_cbDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblActualDataRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_chbEnMedianFilter);
            this.m_panInternalClockConfig.Location = new System.Drawing.Point(3, 24);
            this.m_panInternalClockConfig.Name = "m_panInternalClockConfig";
            this.m_panInternalClockConfig.Size = new System.Drawing.Size(416, 100);
            this.m_panInternalClockConfig.TabIndex = 88;
            // 
            // m_chbClkFromTerm
            // 
            this.m_chbClkFromTerm.AutoSize = true;
            this.m_chbClkFromTerm.Location = new System.Drawing.Point(3, 59);
            this.m_chbClkFromTerm.Name = "m_chbClkFromTerm";
            this.m_chbClkFromTerm.Size = new System.Drawing.Size(115, 17);
            this.m_chbClkFromTerm.TabIndex = 2;
            this.m_chbClkFromTerm.Text = "Clock from terminal";
            this.m_chbClkFromTerm.UseVisualStyleBackColor = true;
            // 
            // m_numOvsFactor
            // 
            this.m_numOvsFactor.Location = new System.Drawing.Point(110, 33);
            this.m_numOvsFactor.Name = "m_numOvsFactor";
            this.m_numOvsFactor.Size = new System.Drawing.Size(55, 20);
            this.m_numOvsFactor.TabIndex = 87;
            // 
            // m_lblDataRate
            // 
            this.m_lblDataRate.AutoSize = true;
            this.m_lblDataRate.Location = new System.Drawing.Point(0, 9);
            this.m_lblDataRate.Name = "m_lblDataRate";
            this.m_lblDataRate.Size = new System.Drawing.Size(86, 13);
            this.m_lblDataRate.TabIndex = 3;
            this.m_lblDataRate.Text = "Data rate (kbps):";
            // 
            // m_lblOvsFactor
            // 
            this.m_lblOvsFactor.AutoSize = true;
            this.m_lblOvsFactor.Location = new System.Drawing.Point(0, 35);
            this.m_lblOvsFactor.Name = "m_lblOvsFactor";
            this.m_lblOvsFactor.Size = new System.Drawing.Size(104, 13);
            this.m_lblOvsFactor.TabIndex = 86;
            this.m_lblOvsFactor.Text = "Oversampling factor:";
            // 
            // m_cbDataRate
            // 
            this.m_cbDataRate.FormattingEnabled = true;
            this.m_cbDataRate.Items.AddRange(new object[] {
            "50",
            "100",
            "400",
            "1000"});
            this.m_cbDataRate.Location = new System.Drawing.Point(110, 6);
            this.m_cbDataRate.Name = "m_cbDataRate";
            this.m_cbDataRate.Size = new System.Drawing.Size(55, 21);
            this.m_cbDataRate.TabIndex = 4;
            // 
            // m_lblActualDataRate
            // 
            this.m_lblActualDataRate.AutoSize = true;
            this.m_lblActualDataRate.Location = new System.Drawing.Point(179, 9);
            this.m_lblActualDataRate.Name = "m_lblActualDataRate";
            this.m_lblActualDataRate.Size = new System.Drawing.Size(97, 13);
            this.m_lblActualDataRate.TabIndex = 0;
            this.m_lblActualDataRate.Text = "Up to: UNKNOWN";
            // 
            // m_chbEnMedianFilter
            // 
            this.m_chbEnMedianFilter.AutoSize = true;
            this.m_chbEnMedianFilter.Location = new System.Drawing.Point(3, 82);
            this.m_chbEnMedianFilter.Name = "m_chbEnMedianFilter";
            this.m_chbEnMedianFilter.Size = new System.Drawing.Size(83, 17);
            this.m_chbEnMedianFilter.TabIndex = 1;
            this.m_chbEnMedianFilter.Text = "Median filter";
            this.m_chbEnMedianFilter.UseVisualStyleBackColor = true;
            // 
            // m_cbClkMode
            // 
            this.m_cbClkMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbClkMode.FormattingEnabled = true;
            this.m_cbClkMode.Location = new System.Drawing.Point(113, 3);
            this.m_cbClkMode.Name = "m_cbClkMode";
            this.m_cbClkMode.Size = new System.Drawing.Size(114, 21);
            this.m_cbClkMode.TabIndex = 1;
            // 
            // m_lblClkMode
            // 
            this.m_lblClkMode.AutoSize = true;
            this.m_lblClkMode.Location = new System.Drawing.Point(3, 6);
            this.m_lblClkMode.Name = "m_lblClkMode";
            this.m_lblClkMode.Size = new System.Drawing.Size(85, 13);
            this.m_lblClkMode.TabIndex = 0;
            this.m_lblClkMode.Text = "Operation mode:";
            // 
            // m_grpCollideBehavior
            // 
            this.m_grpCollideBehavior.Controls.Add(this.m_rbNoWaitStates);
            this.m_grpCollideBehavior.Controls.Add(this.m_rbWaitStates);
            this.m_grpCollideBehavior.Location = new System.Drawing.Point(232, 93);
            this.m_grpCollideBehavior.Name = "m_grpCollideBehavior";
            this.m_grpCollideBehavior.Size = new System.Drawing.Size(125, 70);
            this.m_grpCollideBehavior.TabIndex = 8;
            this.m_grpCollideBehavior.TabStop = false;
            this.m_grpCollideBehavior.Text = "Collide behavior";
            // 
            // panel2
            // 
            this.panel2.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.panel2.Controls.Add(this.m_chbEnableWakeup);
            this.panel2.Controls.Add(this.m_grpWakeUp);
            this.panel2.Controls.Add(this.m_grpCollideBehavior);
            this.panel2.Controls.Add(this.m_binaryGridSlaveAddressMask);
            this.panel2.Controls.Add(this.m_binaryGridSlaveAddress);
            this.panel2.Controls.Add(this.lblSlaveAddress);
            this.panel2.Controls.Add(this.label18);
            this.panel2.Controls.Add(this.label7);
            this.panel2.Controls.Add(this.label17);
            this.panel2.Controls.Add(this.m_tbSlaveAddress);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Controls.Add(this.label16);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.m_tbSlaveAddressMask);
            this.panel2.Controls.Add(this.label11);
            this.panel2.Controls.Add(this.label15);
            this.panel2.Controls.Add(this.label14);
            this.panel2.Controls.Add(this.label12);
            this.panel2.Controls.Add(this.label13);
            this.panel2.Location = new System.Drawing.Point(3, 135);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(422, 173);
            this.panel2.TabIndex = 1;
            // 
            // m_chbEnableWakeup
            // 
            this.m_chbEnableWakeup.AutoSize = true;
            this.m_chbEnableWakeup.Location = new System.Drawing.Point(11, 93);
            this.m_chbEnableWakeup.Margin = new System.Windows.Forms.Padding(2);
            this.m_chbEnableWakeup.Name = "m_chbEnableWakeup";
            this.m_chbEnableWakeup.Size = new System.Drawing.Size(183, 17);
            this.m_chbEnableWakeup.TabIndex = 4;
            this.m_chbEnableWakeup.Text = "Enable wakeup from Sleep Mode";
            this.m_chbEnableWakeup.UseVisualStyleBackColor = true;
            // 
            // m_grpWakeUp
            // 
            this.m_grpWakeUp.Controls.Add(this.m_rbAddressAck);
            this.m_grpWakeUp.Controls.Add(this.m_rbAddressNack);
            this.m_grpWakeUp.Location = new System.Drawing.Point(3, 95);
            this.m_grpWakeUp.Name = "m_grpWakeUp";
            this.m_grpWakeUp.Size = new System.Drawing.Size(203, 68);
            this.m_grpWakeUp.TabIndex = 9;
            this.m_grpWakeUp.TabStop = false;
            // 
            // m_rbAddressAck
            // 
            this.m_rbAddressAck.AutoSize = true;
            this.m_rbAddressAck.Location = new System.Drawing.Point(17, 20);
            this.m_rbAddressAck.Name = "m_rbAddressAck";
            this.m_rbAddressAck.Size = new System.Drawing.Size(87, 17);
            this.m_rbAddressAck.TabIndex = 5;
            this.m_rbAddressAck.TabStop = true;
            this.m_rbAddressAck.Text = "Clock stretch";
            this.m_rbAddressAck.UseVisualStyleBackColor = false;
            // 
            // m_rbAddressNack
            // 
            this.m_rbAddressNack.AutoSize = true;
            this.m_rbAddressNack.Location = new System.Drawing.Point(17, 43);
            this.m_rbAddressNack.Name = "m_rbAddressNack";
            this.m_rbAddressNack.Size = new System.Drawing.Size(95, 17);
            this.m_rbAddressNack.TabIndex = 6;
            this.m_rbAddressNack.TabStop = true;
            this.m_rbAddressNack.Text = "Address NACK";
            this.m_rbAddressNack.UseVisualStyleBackColor = true;
            // 
            // m_binaryGridSlaveAddressMask
            // 
            this.m_binaryGridSlaveAddressMask.Bits = new string[] {
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0"};
            this.m_binaryGridSlaveAddressMask.Location = new System.Drawing.Point(232, 56);
            this.m_binaryGridSlaveAddressMask.Name = "m_binaryGridSlaveAddressMask";
            this.m_binaryGridSlaveAddressMask.NumberOfBits = 8;
            this.m_binaryGridSlaveAddressMask.Size = new System.Drawing.Size(166, 20);
            this.m_binaryGridSlaveAddressMask.TabIndex = 0;
            this.m_binaryGridSlaveAddressMask.TabStop = false;
            // 
            // m_binaryGridSlaveAddress
            // 
            this.m_binaryGridSlaveAddress.Bits = new string[] {
        "1",
        "0",
        "0",
        "0",
        "0",
        "0",
        "0",
        "X"};
            this.m_binaryGridSlaveAddress.Location = new System.Drawing.Point(232, 27);
            this.m_binaryGridSlaveAddress.Name = "m_binaryGridSlaveAddress";
            this.m_binaryGridSlaveAddress.NumberOfBits = 8;
            this.m_binaryGridSlaveAddress.Size = new System.Drawing.Size(166, 20);
            this.m_binaryGridSlaveAddress.TabIndex = 0;
            this.m_binaryGridSlaveAddress.TabStop = false;
            // 
            // lblSlaveAddress
            // 
            this.lblSlaveAddress.AutoSize = true;
            this.lblSlaveAddress.Location = new System.Drawing.Point(4, 30);
            this.lblSlaveAddress.Name = "lblSlaveAddress";
            this.lblSlaveAddress.Size = new System.Drawing.Size(111, 13);
            this.lblSlaveAddress.TabIndex = 0;
            this.lblSlaveAddress.Text = "Slave address (7-bits):";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Location = new System.Drawing.Point(380, 11);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(13, 13);
            this.label18.TabIndex = 0;
            this.label18.Text = "0";
            // 
            // label7
            // 
            this.label7.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label7.Location = new System.Drawing.Point(0, 85);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(422, 2);
            this.label7.TabIndex = 0;
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Location = new System.Drawing.Point(359, 11);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(13, 13);
            this.label17.TabIndex = 0;
            this.label17.Text = "1";
            // 
            // m_tbSlaveAddress
            // 
            this.m_tbSlaveAddress.Location = new System.Drawing.Point(131, 27);
            this.m_tbSlaveAddress.Name = "m_tbSlaveAddress";
            this.m_tbSlaveAddress.Size = new System.Drawing.Size(50, 20);
            this.m_tbSlaveAddress.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 59);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(105, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Slave address mask:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Location = new System.Drawing.Point(233, 11);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(13, 13);
            this.label16.TabIndex = 0;
            this.label16.Text = "7";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(207, 11);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(19, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "Bit";
            // 
            // m_tbSlaveAddressMask
            // 
            this.m_tbSlaveAddressMask.Location = new System.Drawing.Point(131, 56);
            this.m_tbSlaveAddressMask.MaxLength = 5;
            this.m_tbSlaveAddressMask.Name = "m_tbSlaveAddressMask";
            this.m_tbSlaveAddressMask.Size = new System.Drawing.Size(50, 20);
            this.m_tbSlaveAddressMask.TabIndex = 1;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(338, 11);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(13, 13);
            this.label11.TabIndex = 0;
            this.label11.Text = "2";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(254, 11);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(13, 13);
            this.label15.TabIndex = 0;
            this.label15.Text = "6";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(275, 11);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(13, 13);
            this.label14.TabIndex = 0;
            this.label14.Text = "5";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(317, 11);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(13, 13);
            this.label12.TabIndex = 0;
            this.label12.Text = "3";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(296, 11);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(13, 13);
            this.label13.TabIndex = 0;
            this.label13.Text = "4";
            // 
            // label8
            // 
            this.label8.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.label8.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.label8.Location = new System.Drawing.Point(3, 130);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(422, 2);
            this.label8.TabIndex = 1;
            // 
            // CyEZI2CTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.panel2);
            this.Name = "CyEZI2CTab";
            this.Size = new System.Drawing.Size(428, 311);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.m_panInternalClockConfig.ResumeLayout(false);
            this.m_panInternalClockConfig.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).EndInit();
            this.m_grpCollideBehavior.ResumeLayout(false);
            this.m_grpCollideBehavior.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.m_grpWakeUp.ResumeLayout(false);
            this.m_grpWakeUp.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.RadioButton m_rbNoWaitStates;
        private System.Windows.Forms.RadioButton m_rbWaitStates;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label m_lblActualDataRate;
        private System.Windows.Forms.CheckBox m_chbEnMedianFilter;
        private System.Windows.Forms.Panel panel2;
        private CyBinaryGrid m_binaryGridSlaveAddressMask;
        private CyBinaryGrid m_binaryGridSlaveAddress;
        private System.Windows.Forms.Label lblSlaveAddress;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.RadioButton m_rbAddressNack;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.RadioButton m_rbAddressAck;
        private System.Windows.Forms.TextBox m_tbSlaveAddress;
        public System.Windows.Forms.CheckBox m_chbEnableWakeup;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label2;
        public System.Windows.Forms.TextBox m_tbSlaveAddressMask;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.GroupBox m_grpCollideBehavior;
        private System.Windows.Forms.ComboBox m_cbClkMode;
        private System.Windows.Forms.Label m_lblClkMode;
        private System.Windows.Forms.CheckBox m_chbClkFromTerm;
        private System.Windows.Forms.ComboBox m_cbDataRate;
        private System.Windows.Forms.Label m_lblDataRate;
        private System.Windows.Forms.NumericUpDown m_numOvsFactor;
        private System.Windows.Forms.Label m_lblOvsFactor;
        private System.Windows.Forms.Panel m_panInternalClockConfig;
        private System.Windows.Forms.GroupBox m_grpWakeUp;
    }
}
