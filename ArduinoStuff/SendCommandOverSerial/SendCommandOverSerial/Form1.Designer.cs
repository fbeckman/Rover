using System;
using System.Windows.Forms;

namespace SendCommandOverSerial
{
    partial class Form1
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnFreeDrive = new System.Windows.Forms.Button();
            this.btnPark = new System.Windows.Forms.Button();
            this.cmbSerialPorts = new System.Windows.Forms.ComboBox();
            this.btnStop = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.btnRemoteControl = new System.Windows.Forms.Button();
            this.lblX = new System.Windows.Forms.Label();
            this.lblY = new System.Windows.Forms.Label();
            this.mousePad = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.mousePad)).BeginInit();
            this.SuspendLayout();
            // 
            // btnFreeDrive
            // 
            this.btnFreeDrive.BackColor = System.Drawing.Color.Lime;
            this.btnFreeDrive.Location = new System.Drawing.Point(24, 102);
            this.btnFreeDrive.Name = "btnFreeDrive";
            this.btnFreeDrive.Size = new System.Drawing.Size(76, 38);
            this.btnFreeDrive.TabIndex = 0;
            this.btnFreeDrive.Text = "Free Drive";
            this.btnFreeDrive.UseVisualStyleBackColor = false;
            this.btnFreeDrive.Click += new System.EventHandler(this.btnFreeDrive_Click);
            // 
            // btnPark
            // 
            this.btnPark.BackColor = System.Drawing.Color.Blue;
            this.btnPark.ForeColor = System.Drawing.Color.White;
            this.btnPark.Location = new System.Drawing.Point(24, 146);
            this.btnPark.Name = "btnPark";
            this.btnPark.Size = new System.Drawing.Size(76, 39);
            this.btnPark.TabIndex = 1;
            this.btnPark.Text = "Park";
            this.btnPark.UseVisualStyleBackColor = false;
            this.btnPark.Click += new System.EventHandler(this.btnPark_Click);
            // 
            // cmbSerialPorts
            // 
            this.cmbSerialPorts.FormattingEnabled = true;
            this.cmbSerialPorts.Location = new System.Drawing.Point(37, 307);
            this.cmbSerialPorts.Name = "cmbSerialPorts";
            this.cmbSerialPorts.Size = new System.Drawing.Size(206, 21);
            this.cmbSerialPorts.TabIndex = 2;
            this.cmbSerialPorts.SelectedIndexChanged += new System.EventHandler(this.cmbSerialPorts_SelectedIndexChanged);
            // 
            // btnStop
            // 
            this.btnStop.BackColor = System.Drawing.Color.Red;
            this.btnStop.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnStop.Location = new System.Drawing.Point(24, 30);
            this.btnStop.Name = "btnStop";
            this.btnStop.Size = new System.Drawing.Size(108, 51);
            this.btnStop.TabIndex = 3;
            this.btnStop.Text = "&Stop";
            this.btnStop.UseVisualStyleBackColor = false;
            this.btnStop.Click += new System.EventHandler(this.btnStop_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(34, 291);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(55, 13);
            this.label1.TabIndex = 4;
            this.label1.Tag = "Ser";
            this.label1.Text = "Serial Port";
            // 
            // btnRemoteControl
            // 
            this.btnRemoteControl.Location = new System.Drawing.Point(270, 234);
            this.btnRemoteControl.Name = "btnRemoteControl";
            this.btnRemoteControl.Size = new System.Drawing.Size(108, 23);
            this.btnRemoteControl.TabIndex = 6;
            this.btnRemoteControl.Text = "Remote Control";
            this.btnRemoteControl.UseVisualStyleBackColor = true;
            this.btnRemoteControl.Click += new System.EventHandler(this.btnRemoteControl_Click);
            // 
            // lblX
            // 
            this.lblX.AutoSize = true;
            this.lblX.Location = new System.Drawing.Point(282, 307);
            this.lblX.Name = "lblX";
            this.lblX.Size = new System.Drawing.Size(24, 13);
            this.lblX.TabIndex = 7;
            this.lblX.Text = "lblX";
            // 
            // lblY
            // 
            this.lblY.AutoSize = true;
            this.lblY.Location = new System.Drawing.Point(338, 307);
            this.lblY.Name = "lblY";
            this.lblY.Size = new System.Drawing.Size(24, 13);
            this.lblY.TabIndex = 8;
            this.lblY.Text = "lblY";
            // 
            // mousePad
            // 
            this.mousePad.BackColor = System.Drawing.Color.Silver;
            this.mousePad.Location = new System.Drawing.Point(226, 30);
            this.mousePad.Name = "mousePad";
            this.mousePad.Size = new System.Drawing.Size(180, 180);
            this.mousePad.TabIndex = 9;
            this.mousePad.TabStop = false;
            this.mousePad.MouseMove += mousePad_MouseMove;
            this.mousePad.Paint += mousePad_Paint;

            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 405);
            this.Controls.Add(this.mousePad);
            this.Controls.Add(this.lblY);
            this.Controls.Add(this.lblX);
            this.Controls.Add(this.btnRemoteControl);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.btnStop);
            this.Controls.Add(this.cmbSerialPorts);
            this.Controls.Add(this.btnPark);
            this.Controls.Add(this.btnFreeDrive);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmClosing);
            ((System.ComponentModel.ISupportInitialize)(this.mousePad)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }



        #endregion

        private System.Windows.Forms.Button btnFreeDrive;
        private System.Windows.Forms.Button btnPark;
        private ComboBox cmbSerialPorts;
        private Button btnStop;
        private Label label1;
        private Button btnRemoteControl;
        private Label lblX;
        private Label lblY;
        private PictureBox mousePad;

        
    }
}

