namespace SCB_P4_v1_0
{
    partial class CyEZSPITab
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
            this.m_chbEnMedianFilter = new System.Windows.Forms.CheckBox();
            this.m_grpCollideBehavior = new System.Windows.Forms.GroupBox();
            this.m_radioNoWaitStates = new System.Windows.Forms.RadioButton();
            this.m_radioWaitStates = new System.Windows.Forms.RadioButton();
            this.pbDrawing = new System.Windows.Forms.PictureBox();
            this.m_lblActualBitRate = new System.Windows.Forms.Label();
            this.m_cbBitRate = new System.Windows.Forms.ComboBox();
            this.m_lblBitRate = new System.Windows.Forms.Label();
            this.m_chbClkFromTerm = new System.Windows.Forms.CheckBox();
            this.m_cbClkMode = new System.Windows.Forms.ComboBox();
            this.m_lblClkMode = new System.Windows.Forms.Label();
            this.m_chbEnWakeUp = new System.Windows.Forms.CheckBox();
            this.m_numOvsFactor = new System.Windows.Forms.NumericUpDown();
            this.m_lblOvsFactor = new System.Windows.Forms.Label();
            this.m_panInternalClockConfig = new System.Windows.Forms.Panel();
            this.m_grpCollideBehavior.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbDrawing)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).BeginInit();
            this.m_panInternalClockConfig.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_chbEnMedianFilter
            // 
            this.m_chbEnMedianFilter.AutoSize = true;
            this.m_chbEnMedianFilter.Location = new System.Drawing.Point(3, 79);
            this.m_chbEnMedianFilter.Name = "m_chbEnMedianFilter";
            this.m_chbEnMedianFilter.Size = new System.Drawing.Size(83, 17);
            this.m_chbEnMedianFilter.TabIndex = 2;
            this.m_chbEnMedianFilter.Text = "Median filter";
            this.m_chbEnMedianFilter.UseVisualStyleBackColor = true;
            // 
            // m_grpCollideBehavior
            // 
            this.m_grpCollideBehavior.Controls.Add(this.m_radioNoWaitStates);
            this.m_grpCollideBehavior.Controls.Add(this.m_radioWaitStates);
            this.m_grpCollideBehavior.Location = new System.Drawing.Point(6, 286);
            this.m_grpCollideBehavior.Name = "m_grpCollideBehavior";
            this.m_grpCollideBehavior.Size = new System.Drawing.Size(103, 67);
            this.m_grpCollideBehavior.TabIndex = 1;
            this.m_grpCollideBehavior.TabStop = false;
            this.m_grpCollideBehavior.Text = "Collide behavior";
            // 
            // m_radioNoWaitStates
            // 
            this.m_radioNoWaitStates.AutoSize = true;
            this.m_radioNoWaitStates.Location = new System.Drawing.Point(6, 42);
            this.m_radioNoWaitStates.Name = "m_radioNoWaitStates";
            this.m_radioNoWaitStates.Size = new System.Drawing.Size(92, 17);
            this.m_radioNoWaitStates.TabIndex = 1;
            this.m_radioNoWaitStates.TabStop = true;
            this.m_radioNoWaitStates.Text = "No wait states";
            this.m_radioNoWaitStates.UseVisualStyleBackColor = true;
            // 
            // m_radioWaitStates
            // 
            this.m_radioWaitStates.AutoSize = true;
            this.m_radioWaitStates.Location = new System.Drawing.Point(6, 19);
            this.m_radioWaitStates.Name = "m_radioWaitStates";
            this.m_radioWaitStates.Size = new System.Drawing.Size(78, 17);
            this.m_radioWaitStates.TabIndex = 0;
            this.m_radioWaitStates.TabStop = true;
            this.m_radioWaitStates.Text = "Wait states";
            this.m_radioWaitStates.UseVisualStyleBackColor = true;
            // 
            // pbDrawing
            // 
            this.pbDrawing.BackColor = System.Drawing.Color.White;
            this.pbDrawing.Location = new System.Drawing.Point(3, 3);
            this.pbDrawing.Name = "pbDrawing";
            this.pbDrawing.Size = new System.Drawing.Size(433, 128);
            this.pbDrawing.TabIndex = 76;
            this.pbDrawing.TabStop = false;
            // 
            // m_lblActualBitRate
            // 
            this.m_lblActualBitRate.AutoSize = true;
            this.m_lblActualBitRate.Location = new System.Drawing.Point(179, 6);
            this.m_lblActualBitRate.Name = "m_lblActualBitRate";
            this.m_lblActualBitRate.Size = new System.Drawing.Size(97, 13);
            this.m_lblActualBitRate.TabIndex = 78;
            this.m_lblActualBitRate.Text = "Up to: UNKNOWN";
            // 
            // m_cbBitRate
            // 
            this.m_cbBitRate.FormattingEnabled = true;
            this.m_cbBitRate.Location = new System.Drawing.Point(110, 3);
            this.m_cbBitRate.Name = "m_cbBitRate";
            this.m_cbBitRate.Size = new System.Drawing.Size(55, 21);
            this.m_cbBitRate.TabIndex = 82;
            // 
            // m_lblBitRate
            // 
            this.m_lblBitRate.AutoSize = true;
            this.m_lblBitRate.Location = new System.Drawing.Point(0, 6);
            this.m_lblBitRate.Name = "m_lblBitRate";
            this.m_lblBitRate.Size = new System.Drawing.Size(75, 13);
            this.m_lblBitRate.TabIndex = 81;
            this.m_lblBitRate.Text = "Bit rate (kbps):";
            // 
            // m_chbClkFromTerm
            // 
            this.m_chbClkFromTerm.AutoSize = true;
            this.m_chbClkFromTerm.Location = new System.Drawing.Point(3, 56);
            this.m_chbClkFromTerm.Name = "m_chbClkFromTerm";
            this.m_chbClkFromTerm.Size = new System.Drawing.Size(115, 17);
            this.m_chbClkFromTerm.TabIndex = 80;
            this.m_chbClkFromTerm.Text = "Clock from terminal";
            this.m_chbClkFromTerm.UseVisualStyleBackColor = true;
            // 
            // m_cbClkMode
            // 
            this.m_cbClkMode.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.m_cbClkMode.FormattingEnabled = true;
            this.m_cbClkMode.Location = new System.Drawing.Point(113, 137);
            this.m_cbClkMode.Name = "m_cbClkMode";
            this.m_cbClkMode.Size = new System.Drawing.Size(114, 21);
            this.m_cbClkMode.TabIndex = 79;
            // 
            // m_lblClkMode
            // 
            this.m_lblClkMode.AutoSize = true;
            this.m_lblClkMode.Location = new System.Drawing.Point(3, 140);
            this.m_lblClkMode.Name = "m_lblClkMode";
            this.m_lblClkMode.Size = new System.Drawing.Size(85, 13);
            this.m_lblClkMode.TabIndex = 77;
            this.m_lblClkMode.Text = "Operation mode:";
            // 
            // m_chbEnWakeUp
            // 
            this.m_chbEnWakeUp.AutoSize = true;
            this.m_chbEnWakeUp.Location = new System.Drawing.Point(6, 263);
            this.m_chbEnWakeUp.Name = "m_chbEnWakeUp";
            this.m_chbEnWakeUp.Size = new System.Drawing.Size(183, 17);
            this.m_chbEnWakeUp.TabIndex = 83;
            this.m_chbEnWakeUp.Text = "Enable wakeup from Sleep Mode";
            this.m_chbEnWakeUp.UseVisualStyleBackColor = true;
            // 
            // m_numOvsFactor
            // 
            this.m_numOvsFactor.Location = new System.Drawing.Point(110, 30);
            this.m_numOvsFactor.Name = "m_numOvsFactor";
            this.m_numOvsFactor.Size = new System.Drawing.Size(55, 20);
            this.m_numOvsFactor.TabIndex = 85;
            // 
            // m_lblOvsFactor
            // 
            this.m_lblOvsFactor.AutoSize = true;
            this.m_lblOvsFactor.Location = new System.Drawing.Point(0, 32);
            this.m_lblOvsFactor.Name = "m_lblOvsFactor";
            this.m_lblOvsFactor.Size = new System.Drawing.Size(104, 13);
            this.m_lblOvsFactor.TabIndex = 84;
            this.m_lblOvsFactor.Text = "Oversampling factor:";
            // 
            // m_panInternalClockConfig
            // 
            this.m_panInternalClockConfig.Controls.Add(this.m_chbClkFromTerm);
            this.m_panInternalClockConfig.Controls.Add(this.m_numOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_chbEnMedianFilter);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblOvsFactor);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblBitRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_cbBitRate);
            this.m_panInternalClockConfig.Controls.Add(this.m_lblActualBitRate);
            this.m_panInternalClockConfig.Location = new System.Drawing.Point(3, 161);
            this.m_panInternalClockConfig.Name = "m_panInternalClockConfig";
            this.m_panInternalClockConfig.Size = new System.Drawing.Size(432, 101);
            this.m_panInternalClockConfig.TabIndex = 86;
            // 
            // CyEZSPITab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_panInternalClockConfig);
            this.Controls.Add(this.m_chbEnWakeUp);
            this.Controls.Add(this.m_cbClkMode);
            this.Controls.Add(this.m_lblClkMode);
            this.Controls.Add(this.m_grpCollideBehavior);
            this.Controls.Add(this.pbDrawing);
            this.Name = "CyEZSPITab";
            this.Size = new System.Drawing.Size(438, 355);
            this.m_grpCollideBehavior.ResumeLayout(false);
            this.m_grpCollideBehavior.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pbDrawing)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.m_numOvsFactor)).EndInit();
            this.m_panInternalClockConfig.ResumeLayout(false);
            this.m_panInternalClockConfig.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox m_chbEnMedianFilter;
        private System.Windows.Forms.GroupBox m_grpCollideBehavior;
        private System.Windows.Forms.RadioButton m_radioNoWaitStates;
        private System.Windows.Forms.RadioButton m_radioWaitStates;
        private System.Windows.Forms.PictureBox pbDrawing;
        private System.Windows.Forms.Label m_lblActualBitRate;
        private System.Windows.Forms.ComboBox m_cbBitRate;
        private System.Windows.Forms.Label m_lblBitRate;
        private System.Windows.Forms.CheckBox m_chbClkFromTerm;
        private System.Windows.Forms.ComboBox m_cbClkMode;
        private System.Windows.Forms.Label m_lblClkMode;
        private System.Windows.Forms.CheckBox m_chbEnWakeUp;
        private System.Windows.Forms.NumericUpDown m_numOvsFactor;
        private System.Windows.Forms.Label m_lblOvsFactor;
        private System.Windows.Forms.Panel m_panInternalClockConfig;

    }
}
