namespace SCB_P4_v1_0
{
    partial class CyEZSPIAdvancedTab
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
            this.m_grpIntrSources = new System.Windows.Forms.GroupBox();
            this.m_chbTxFifoBlocked = new System.Windows.Forms.CheckBox();
            this.m_chbRxFifoBlocked = new System.Windows.Forms.CheckBox();
            this.m_chbEzWriteStop = new System.Windows.Forms.CheckBox();
            this.m_chbEzStop = new System.Windows.Forms.CheckBox();
            this.m_chbEzWake = new System.Windows.Forms.CheckBox();
            this.m_grpIntrConnection = new System.Windows.Forms.GroupBox();
            this.m_rbExternalIntr = new System.Windows.Forms.RadioButton();
            this.m_rbInternalIntr = new System.Windows.Forms.RadioButton();
            this.m_rbNoneIntr = new System.Windows.Forms.RadioButton();
            this.m_grpIntrSources.SuspendLayout();
            this.m_grpIntrConnection.SuspendLayout();
            this.SuspendLayout();
            // 
            // m_grpIntrSources
            // 
            this.m_grpIntrSources.Controls.Add(this.m_chbTxFifoBlocked);
            this.m_grpIntrSources.Controls.Add(this.m_chbRxFifoBlocked);
            this.m_grpIntrSources.Controls.Add(this.m_chbEzWriteStop);
            this.m_grpIntrSources.Controls.Add(this.m_chbEzStop);
            this.m_grpIntrSources.Controls.Add(this.m_chbEzWake);
            this.m_grpIntrSources.Location = new System.Drawing.Point(3, 101);
            this.m_grpIntrSources.Name = "m_grpIntrSources";
            this.m_grpIntrSources.Size = new System.Drawing.Size(128, 137);
            this.m_grpIntrSources.TabIndex = 3;
            this.m_grpIntrSources.TabStop = false;
            this.m_grpIntrSources.Text = "Interrupt sources";
            // 
            // m_chbTxFifoBlocked
            // 
            this.m_chbTxFifoBlocked.AutoSize = true;
            this.m_chbTxFifoBlocked.Location = new System.Drawing.Point(7, 116);
            this.m_chbTxFifoBlocked.Name = "m_chbTxFifoBlocked";
            this.m_chbTxFifoBlocked.Size = new System.Drawing.Size(107, 17);
            this.m_chbTxFifoBlocked.TabIndex = 4;
            this.m_chbTxFifoBlocked.Text = "TX FIFO blocked";
            this.m_chbTxFifoBlocked.UseVisualStyleBackColor = true;
            // 
            // m_chbRxFifoBlocked
            // 
            this.m_chbRxFifoBlocked.AutoSize = true;
            this.m_chbRxFifoBlocked.Location = new System.Drawing.Point(7, 92);
            this.m_chbRxFifoBlocked.Name = "m_chbRxFifoBlocked";
            this.m_chbRxFifoBlocked.Size = new System.Drawing.Size(108, 17);
            this.m_chbRxFifoBlocked.TabIndex = 3;
            this.m_chbRxFifoBlocked.Text = "RX FIFO blocked";
            this.m_chbRxFifoBlocked.UseVisualStyleBackColor = true;
            // 
            // m_chbEzWriteStop
            // 
            this.m_chbEzWriteStop.AutoSize = true;
            this.m_chbEzWriteStop.Location = new System.Drawing.Point(7, 68);
            this.m_chbEzWriteStop.Name = "m_chbEzWriteStop";
            this.m_chbEzWriteStop.Size = new System.Drawing.Size(88, 17);
            this.m_chbEzWriteStop.TabIndex = 2;
            this.m_chbEzWriteStop.Text = "EZ write stop";
            this.m_chbEzWriteStop.UseVisualStyleBackColor = true;
            // 
            // m_chbEzStop
            // 
            this.m_chbEzStop.AutoSize = true;
            this.m_chbEzStop.Location = new System.Drawing.Point(7, 44);
            this.m_chbEzStop.Name = "m_chbEzStop";
            this.m_chbEzStop.Size = new System.Drawing.Size(63, 17);
            this.m_chbEzStop.TabIndex = 1;
            this.m_chbEzStop.Text = "EZ stop";
            this.m_chbEzStop.UseVisualStyleBackColor = true;
            // 
            // m_chbEzWake
            // 
            this.m_chbEzWake.AutoSize = true;
            this.m_chbEzWake.Location = new System.Drawing.Point(7, 20);
            this.m_chbEzWake.Name = "m_chbEzWake";
            this.m_chbEzWake.Size = new System.Drawing.Size(69, 17);
            this.m_chbEzWake.TabIndex = 0;
            this.m_chbEzWake.Text = "EZ wake";
            this.m_chbEzWake.UseVisualStyleBackColor = true;
            // 
            // m_grpIntrConnection
            // 
            this.m_grpIntrConnection.Controls.Add(this.m_rbExternalIntr);
            this.m_grpIntrConnection.Controls.Add(this.m_rbInternalIntr);
            this.m_grpIntrConnection.Controls.Add(this.m_rbNoneIntr);
            this.m_grpIntrConnection.Location = new System.Drawing.Point(3, 3);
            this.m_grpIntrConnection.Name = "m_grpIntrConnection";
            this.m_grpIntrConnection.Size = new System.Drawing.Size(128, 92);
            this.m_grpIntrConnection.TabIndex = 2;
            this.m_grpIntrConnection.TabStop = false;
            this.m_grpIntrConnection.Text = "Interrupt";
            // 
            // m_rbExternalIntr
            // 
            this.m_rbExternalIntr.AutoSize = true;
            this.m_rbExternalIntr.Location = new System.Drawing.Point(7, 68);
            this.m_rbExternalIntr.Name = "m_rbExternalIntr";
            this.m_rbExternalIntr.Size = new System.Drawing.Size(63, 17);
            this.m_rbExternalIntr.TabIndex = 2;
            this.m_rbExternalIntr.TabStop = true;
            this.m_rbExternalIntr.Text = "External";
            this.m_rbExternalIntr.UseVisualStyleBackColor = true;
            // 
            // m_rbInternalIntr
            // 
            this.m_rbInternalIntr.AutoSize = true;
            this.m_rbInternalIntr.Location = new System.Drawing.Point(7, 44);
            this.m_rbInternalIntr.Name = "m_rbInternalIntr";
            this.m_rbInternalIntr.Size = new System.Drawing.Size(60, 17);
            this.m_rbInternalIntr.TabIndex = 1;
            this.m_rbInternalIntr.TabStop = true;
            this.m_rbInternalIntr.Text = "Internal";
            this.m_rbInternalIntr.UseVisualStyleBackColor = true;
            // 
            // m_rbNoneIntr
            // 
            this.m_rbNoneIntr.AutoSize = true;
            this.m_rbNoneIntr.Location = new System.Drawing.Point(7, 20);
            this.m_rbNoneIntr.Name = "m_rbNoneIntr";
            this.m_rbNoneIntr.Size = new System.Drawing.Size(51, 17);
            this.m_rbNoneIntr.TabIndex = 0;
            this.m_rbNoneIntr.TabStop = true;
            this.m_rbNoneIntr.Text = "None";
            this.m_rbNoneIntr.UseVisualStyleBackColor = true;
            // 
            // CyEZSPIAdvancedTab
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.m_grpIntrSources);
            this.Controls.Add(this.m_grpIntrConnection);
            this.Name = "CyEZSPIAdvancedTab";
            this.Size = new System.Drawing.Size(135, 241);
            this.m_grpIntrSources.ResumeLayout(false);
            this.m_grpIntrSources.PerformLayout();
            this.m_grpIntrConnection.ResumeLayout(false);
            this.m_grpIntrConnection.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox m_grpIntrSources;
        private System.Windows.Forms.CheckBox m_chbTxFifoBlocked;
        private System.Windows.Forms.CheckBox m_chbRxFifoBlocked;
        private System.Windows.Forms.CheckBox m_chbEzWriteStop;
        private System.Windows.Forms.CheckBox m_chbEzStop;
        private System.Windows.Forms.CheckBox m_chbEzWake;
        private System.Windows.Forms.GroupBox m_grpIntrConnection;
        private System.Windows.Forms.RadioButton m_rbExternalIntr;
        private System.Windows.Forms.RadioButton m_rbInternalIntr;
        private System.Windows.Forms.RadioButton m_rbNoneIntr;
    }
}
