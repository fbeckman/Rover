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
            this.btnLEDOn = new System.Windows.Forms.Button();
            this.btnLEDOff = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // btnLEDOn
            // 
            this.btnLEDOn.Location = new System.Drawing.Point(47, 40);
            this.btnLEDOn.Name = "btnLEDOn";
            this.btnLEDOn.Size = new System.Drawing.Size(76, 38);
            this.btnLEDOn.TabIndex = 0;
            this.btnLEDOn.Text = "LED ON";
            this.btnLEDOn.UseVisualStyleBackColor = true;
            this.btnLEDOn.Click += new System.EventHandler(this.btnLEDOn_Click);
            // 
            // btnLEDOff
            // 
            this.btnLEDOff.Location = new System.Drawing.Point(47, 96);
            this.btnLEDOff.Name = "btnLEDOff";
            this.btnLEDOff.Size = new System.Drawing.Size(76, 39);
            this.btnLEDOff.TabIndex = 1;
            this.btnLEDOff.Text = "LED OFF";
            this.btnLEDOff.UseVisualStyleBackColor = true;
            this.btnLEDOff.Click += new System.EventHandler(this.btnLEDOff_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(284, 261);
            this.Controls.Add(this.btnLEDOff);
            this.Controls.Add(this.btnLEDOn);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

            this.FormClosing += new FormClosingEventHandler(this.frmClosing);

        }



        #endregion

        private System.Windows.Forms.Button btnLEDOn;
        private System.Windows.Forms.Button btnLEDOff;
    }
}

