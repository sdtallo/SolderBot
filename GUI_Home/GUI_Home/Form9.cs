using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Diagnostics;

namespace GUI_Home
{
    public partial class Form9 : Form
    {
        public Form9(string leftPins, string middlePins, string rightPins)
        {
            InitializeComponent();
            label6.Text = leftPins;
            label7.Text = middlePins;
            label8.Text = rightPins;

            // Call Gcode program here
            // This variable builds the singular string to send to the Gcode-generating program (under seniorDesignP folder)
            // Delimiter between each board is " _ "
            string argStr = " \" " + leftPins + " _ " + middlePins + " _ " + rightPins + " \" ";
            // Mono command run from pi, two folders above seniorDesignP.exe
            Process getGcode = Process.Start("/home/pi/solderbot-test/seniorDesignP/seniorDesignP.exe", argStr);

            // Check (every 500 milliseconds) for Gcode to be done generating before starting robot
            while (!getGcode.WaitForExit(500));
        }
        
        // Pins match what was entered into textboxes
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form5 f5 = new Form5();
            f5.ShowDialog();

            // Call Gcode program here...but how???
        }

        // Pins don't match what was entered into textboxes
        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form3 f3 = new Form3();
            f3.ShowDialog();
        }

        // Recalibrate button
        private void button7_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form10 f10 = new Form10();
            f10.ShowDialog();
        }
    }
}
