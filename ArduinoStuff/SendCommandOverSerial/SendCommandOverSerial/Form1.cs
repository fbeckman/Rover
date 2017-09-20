using System;
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


            // Create a new SerialPort object with default settings.
            _serialPort = new SerialPort();

            // Allow the user to set the appropriate properties.
            _serialPort.PortName = "COM7";
            _serialPort.BaudRate = 115200;
            _serialPort.Parity = Parity.None;
            _serialPort.DataBits = 8;
            _serialPort.StopBits = StopBits.One;
            _serialPort.Handshake = Handshake.None;

            // Set the read/write timeouts
            //_serialPort.ReadTimeout = 500;
            //_serialPort.WriteTimeout = 500;
            _serialPort.Open();
        }

        private void frmClosing(object sender, EventArgs e)
        {
            _serialPort.Close();
        }

        private void WriteCommandToSerialPort(string command, SerialPort serialPort)
        {
            _serialPort.Write(command);
        }

        private void btnLEDOff_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("LEDOFF", _serialPort);
        }

        private void btnLEDOn_Click(object sender, EventArgs e)
        {
            WriteCommandToSerialPort("LEDON", _serialPort);
        }

    }
}
