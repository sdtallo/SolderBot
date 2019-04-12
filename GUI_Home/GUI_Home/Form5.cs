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
    public partial class Form5 : Form
    {
        // Global variables
        string Lpins, Mpins, Rpins;

        public Form5(string leftPins, string middlePins, string rightPins)
        {
            InitializeComponent();
            Lpins = leftPins;
            Mpins = middlePins;
            Rpins = rightPins;

            // RUN GCODE-GENERATING PROGRAM HERE

            // This variable builds the singular string to send to the Gcode-generating program (under seniorDesignP folder)
            // Delimiter between each board is " _ "
            string argStr = " \" " + leftPins + " _ " + middlePins + " _ " + rightPins + " \" ";
            // Mono command run from /home/pi
            Process getGcode = Process.Start("/home/pi/solderbot-test/seniorDesignP/seniorDesignP.exe", argStr);

            // Check (every 500 milliseconds) for Gcode to be done generating before starting robot
            while (!getGcode.WaitForExit(500));

        }

        // Ready for machine to begin soldering
        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form6 f6 = new Form6();
            f6.ShowDialog();
        }

        // Not ready for machine to begin soldering
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();            
            Form9 f9 = new Form9(Lpins, Mpins, Rpins);
            f9.ShowDialog();
//            Form3 f3= new Form3(null, null, null);
//            f3.ShowDialog();
            this.Close();
        }
    }
}
