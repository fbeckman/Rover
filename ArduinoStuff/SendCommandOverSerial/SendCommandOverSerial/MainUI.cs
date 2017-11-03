using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;

namespace SendCommandOverSerial
{
    public partial class MainUI : Form
    {
        SerialPort _serialPort;

        Point mCenter;
        Point mCurrent;
        bool remoteControlActive = false;

        public MainUI()
        {
            InitializeComponent();
            mousePad.Cursor = Cursors.SizeAll;

            var ports = SerialPort.GetPortNames();
            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();


            mCenter = new Point(mousePad.DisplayRectangle.Left + mousePad.DisplayRectangle.Width / 2, mousePad.DisplayRectangle.Top + mousePad.DisplayRectangle.Height / 2);
            mCurrent = mCenter;
            cmbSerialPorts.DataSource = ports;

            chkRemoteControl.Checked = false;
            lblX.Text = "0";
            lblY.Text = "0";
        }

        private void frmClosing(object sender, EventArgs e)
        {
            _serialPort.Close();
        }

        private void WriteCommandToSerialPort(string command, SerialPort serialPort)
        {
            _serialPort.Write(command);
        }

        private void btnPark_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("Park", _serialPort);
            remoteControlActive = false;
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("Stop", _serialPort);
            remoteControlActive = false;
        }

        private void btnFreeDrive_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("FreeDrive", _serialPort);
            remoteControlActive = false;
        }

        private void chkRemoteControl_CheckedChanged(object sender, EventArgs e)
        {
            remoteControlActive = chkRemoteControl.Checked;
            if (remoteControlActive)
                WriteCommandToSerialPort("RemoteControl", _serialPort);
        }

        private void mousePad_Paint(object sender, PaintEventArgs e)
        {
            Pen pen1 = new Pen(Color.Black);
            pen1.Width = 12;
            Pen pen2 = new Pen(Color.DarkSlateGray);
            pen2.Width = 15;
            e.Graphics.DrawLine(pen1, mCenter, mCurrent);
            e.Graphics.DrawEllipse(pen2, mCurrent.X - 7, mCurrent.Y - 7, 14, 14);
        }

        private void mousePad_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e)
        {
            // Update the mouse path that is drawn onto the Panel.
            if (e.Button == MouseButtons.Left)
            {
                int direction = e.X - (mousePad.Size.Width / 2);
                int speed = -e.Y + (mousePad.Size.Height / 2);
                lblX.Text = direction.ToString();
                lblY.Text = speed.ToString();
                mCurrent = e.Location;
                mousePad.Invalidate();

                if (remoteControlActive)
                {
                    WriteCommandToSerialPort(string.Format("Speed:{0}", speed), _serialPort);
                    WriteCommandToSerialPort(string.Format("Heading:{0}", direction), _serialPort);
                }
            }

        }

        private void cmbSerialPorts_SelectedIndexChanged(object sender, EventArgs e)
        {
            // Allow the user to set the appropriate properties.
            _serialPort.Close();
            _serialPort.PortName = cmbSerialPorts.SelectedItem.ToString();
            _serialPort.BaudRate = 115200;
            _serialPort.Parity = Parity.None;
            _serialPort.DataBits = 8;
            _serialPort.StopBits = StopBits.One;
            _serialPort.Handshake = Handshake.None;
            // Set the read/write timeouts
            //_serialPort.ReadTimeout = 500;
            //_serialPort.WriteTimeout = 500;
            try
            {
                _serialPort.Open();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

    }
}
