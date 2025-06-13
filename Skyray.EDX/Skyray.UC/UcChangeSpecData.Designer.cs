namespace Skyray.UC
{
    partial class UcChangeSpecData
    {
        /// <summary> 
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region 组件设计器生成的代码

        /// <summary> 
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.btnGenFormula = new Skyray.Controls.ButtonW();
            this.cuInitCountRateLabel = new Skyray.Controls.LabelW();
            this.cuInitCountRate = new Skyray.Controls.NumricUpDownW();
            this.cuInitPeakChanLabel = new Skyray.Controls.LabelW();
            this.cuInitPeakChan = new Skyray.Controls.NumricUpDownW();
            this.cuTestDataLabel = new Skyray.Controls.LabelW();
            this.cuFormula = new Skyray.Controls.TextBoxW();
            this.isAdjustSpecData = new Skyray.Controls.CheckBoxW();
            this.labelW1 = new Skyray.Controls.LabelW();
            this.cuTestData = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.cuInitCountRate)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.cuInitPeakChan)).BeginInit();
            this.SuspendLayout();
            // 
            // btnGenFormula
            // 
            this.btnGenFormula.bSilver = false;
            this.btnGenFormula.Location = new System.Drawing.Point(89, 302);
            this.btnGenFormula.MaxImageSize = new System.Drawing.Point(0, 0);
            this.btnGenFormula.MenuPos = new System.Drawing.Point(0, 0);
            this.btnGenFormula.Name = "btnGenFormula";
            this.btnGenFormula.Size = new System.Drawing.Size(75, 23);
            this.btnGenFormula.Style = Skyray.Controls.Style.Office2007Blue;
            this.btnGenFormula.TabIndex = 8;
            this.btnGenFormula.Text = "生成公式";
            this.btnGenFormula.ToFocused = false;
            this.btnGenFormula.UseVisualStyleBackColor = true;
            this.btnGenFormula.Click += new System.EventHandler(this.btWSubmit_Click);
            // 
            // cuInitCountRateLabel
            // 
            this.cuInitCountRateLabel.AutoSize = true;
            this.cuInitCountRateLabel.BackColor = System.Drawing.Color.Transparent;
            this.cuInitCountRateLabel.Location = new System.Drawing.Point(87, 54);
            this.cuInitCountRateLabel.Name = "cuInitCountRateLabel";
            this.cuInitCountRateLabel.Size = new System.Drawing.Size(89, 12);
            this.cuInitCountRateLabel.TabIndex = 12;
            this.cuInitCountRateLabel.Text = "Cu初始化计数率";
            // 
            // cuInitCountRate
            // 
            this.cuInitCountRate.ArrowColor = System.Drawing.Color.FromArgb(((int)(((byte)(19)))), ((int)(((byte)(88)))), ((int)(((byte)(128)))));
            this.cuInitCountRate.BaseColor = System.Drawing.Color.FromArgb(((int)(((byte)(175)))), ((int)(((byte)(210)))), ((int)(((byte)(255)))));
            this.cuInitCountRate.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(153)))), ((int)(((byte)(194)))));
            this.cuInitCountRate.DecimalPlaces = 1;
            this.cuInitCountRate.Location = new System.Drawing.Point(182, 54);
            this.cuInitCountRate.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.cuInitCountRate.Name = "cuInitCountRate";
            this.cuInitCountRate.Size = new System.Drawing.Size(103, 21);
            this.cuInitCountRate.TabIndex = 14;
            this.cuInitCountRate.Value = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            // 
            // cuInitPeakChanLabel
            // 
            this.cuInitPeakChanLabel.AutoSize = true;
            this.cuInitPeakChanLabel.BackColor = System.Drawing.Color.Transparent;
            this.cuInitPeakChanLabel.Location = new System.Drawing.Point(348, 54);
            this.cuInitPeakChanLabel.Name = "cuInitPeakChanLabel";
            this.cuInitPeakChanLabel.Size = new System.Drawing.Size(89, 12);
            this.cuInitPeakChanLabel.TabIndex = 31;
            this.cuInitPeakChanLabel.Text = "Cu初始化峰通道";
            // 
            // cuInitPeakChan
            // 
            this.cuInitPeakChan.ArrowColor = System.Drawing.Color.FromArgb(((int)(((byte)(19)))), ((int)(((byte)(88)))), ((int)(((byte)(128)))));
            this.cuInitPeakChan.BaseColor = System.Drawing.Color.FromArgb(((int)(((byte)(175)))), ((int)(((byte)(210)))), ((int)(((byte)(255)))));
            this.cuInitPeakChan.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(153)))), ((int)(((byte)(194)))));
            this.cuInitPeakChan.DecimalPlaces = 1;
            this.cuInitPeakChan.Location = new System.Drawing.Point(443, 54);
            this.cuInitPeakChan.Maximum = new decimal(new int[] {
            1000000,
            0,
            0,
            0});
            this.cuInitPeakChan.Name = "cuInitPeakChan";
            this.cuInitPeakChan.Size = new System.Drawing.Size(103, 21);
            this.cuInitPeakChan.TabIndex = 32;
            this.cuInitPeakChan.Value = new decimal(new int[] {
            5255,
            0,
            0,
            65536});
            // 
            // cuTestDataLabel
            // 
            this.cuTestDataLabel.AutoSize = true;
            this.cuTestDataLabel.BackColor = System.Drawing.Color.Transparent;
            this.cuTestDataLabel.Location = new System.Drawing.Point(87, 94);
            this.cuTestDataLabel.Name = "cuTestDataLabel";
            this.cuTestDataLabel.Size = new System.Drawing.Size(65, 12);
            this.cuTestDataLabel.TabIndex = 33;
            this.cuTestDataLabel.Text = "Cu测试数据";
            // 
            // cuFormula
            // 
            this.cuFormula.BorderColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(153)))), ((int)(((byte)(194)))));
            this.cuFormula.Location = new System.Drawing.Point(182, 237);
            this.cuFormula.Name = "cuFormula";
            this.cuFormula.Size = new System.Drawing.Size(338, 21);
            this.cuFormula.Style = Skyray.Controls.Style.Office2007Blue;
            this.cuFormula.TabIndex = 45;
            // 
            // isAdjustSpecData
            // 
            this.isAdjustSpecData.AutoSize = true;
            this.isAdjustSpecData.BaseColor = System.Drawing.Color.FromArgb(((int)(((byte)(121)))), ((int)(((byte)(153)))), ((int)(((byte)(194)))));
            this.isAdjustSpecData.Location = new System.Drawing.Point(89, 23);
            this.isAdjustSpecData.Name = "isAdjustSpecData";
            this.isAdjustSpecData.Size = new System.Drawing.Size(72, 16);
            this.isAdjustSpecData.Style = Skyray.Controls.Style.Office2007Blue;
            this.isAdjustSpecData.TabIndex = 47;
            this.isAdjustSpecData.Text = "应用公式";
            this.isAdjustSpecData.UseVisualStyleBackColor = true;
            this.isAdjustSpecData.CheckedChanged += new System.EventHandler(this.isAdjustSpecData_CheckedChanged);
            // 
            // labelW1
            // 
            this.labelW1.AutoSize = true;
            this.labelW1.BackColor = System.Drawing.Color.Transparent;
            this.labelW1.Location = new System.Drawing.Point(87, 237);
            this.labelW1.Name = "labelW1";
            this.labelW1.Size = new System.Drawing.Size(41, 12);
            this.labelW1.TabIndex = 48;
            this.labelW1.Text = "Cu公式";
            // 
            // cuTestData
            // 
            this.cuTestData.Location = new System.Drawing.Point(182, 94);
            this.cuTestData.Name = "cuTestData";
            this.cuTestData.Size = new System.Drawing.Size(338, 117);
            this.cuTestData.TabIndex = 49;
            this.cuTestData.Text = "";
            // 
            // UcChangeSpecData
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.GhostWhite;
            this.Controls.Add(this.cuTestData);
            this.Controls.Add(this.labelW1);
            this.Controls.Add(this.isAdjustSpecData);
            this.Controls.Add(this.cuFormula);
            this.Controls.Add(this.cuTestDataLabel);
            this.Controls.Add(this.cuInitPeakChan);
            this.Controls.Add(this.cuInitPeakChanLabel);
            this.Controls.Add(this.cuInitCountRate);
            this.Controls.Add(this.cuInitCountRateLabel);
            this.Controls.Add(this.btnGenFormula);
            this.Name = "UcChangeSpecData";
            this.Size = new System.Drawing.Size(649, 359);
            ((System.ComponentModel.ISupportInitialize)(this.cuInitCountRate)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.cuInitPeakChan)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Skyray.Controls.ButtonW btnGenFormula;
        private Skyray.Controls.LabelW cuInitCountRateLabel;
        private Skyray.Controls.NumricUpDownW cuInitCountRate;
        private Skyray.Controls.LabelW cuInitPeakChanLabel;
        private Skyray.Controls.NumricUpDownW cuInitPeakChan;
        private Skyray.Controls.LabelW cuTestDataLabel;
        private Skyray.Controls.TextBoxW cuFormula;
        private Skyray.Controls.CheckBoxW isAdjustSpecData;
        private Skyray.Controls.LabelW labelW1;
        private System.Windows.Forms.RichTextBox cuTestData;

    }
}
