using System;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;

namespace SendCommandOverSerial
{
    public partial class Form1 : Form
    {
        SerialPort _serialPort;

        public Form1()
        {
            InitializeComponent();
            mousePad.Cursor = Cursors.SizeAll;

            lblX.Text = (pointer.Location.X - 8).ToString();
            lblY.Text = (pointer.Location.Y - 8).ToString();

            var ports = SerialPort.GetPortNames();
            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();

            cmbSerialPorts.DataSource = ports;
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
        }

        private void btnStop_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("Stop", _serialPort);
        }

        private void btnFreeDrive_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("FreeDrive", _serialPort);
        }

        private void btnRemoteControl_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("RemoteControl", _serialPort);
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

                //lblX.Text = e.X.ToString();
                //lblY.Text = e.Y.ToString();
                pointer.Location = new Point(e.X - 8, e.Y - 8);
            }
            //WriteCommandToSerialPort(string.Format("Speed:{0}", speed), _serialPort);
            //WriteCommandToSerialPort(string.Format("Direction:{0}", direction), _serialPort);

        }

        private void mousePad_MouseLeave(object sender, System.EventArgs e) 
        {
            //lblX.Text = "0";
            //lblY.Text = "0";
            //WriteCommandToSerialPort("Speed:0", _serialPort);
            //WriteCommandToSerialPort("Direction:0", _serialPort);

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
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
    }
}
