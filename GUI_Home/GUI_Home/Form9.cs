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
            // File must be saved in same folder from which mono is run
            //            System.Diagnostics.Process.Start("seniorDesignP.exe");
 //           pass_to_gcode(leftPins, middlePins, rightPins);
            System.Diagnostics.Process.Start("seniorDesignP.exe", "\"" + leftPins + "_" + middlePins + "_" + rightPins + "\"");
        }

        // Starting code from this website: https://social.msdn.microsoft.com/Forums/vstudio/en-US/9c574d79-13cd-4333-bb7c-dcf2305d8155/how-to-run-an-exe-file-when-cliking-a-button-cnet?forum=csharpgeneral

 /*       static void pass_to_gcode(string L_arg, string M_arg, string R_arg)
        {
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "seniorDesignP.exe";

            // Create arguments string - 3 total
            // First for left board, second for middle, third for right
            string myArgs = L_arg + ", " + M_arg + ", " + R_arg;
            startInfo.Arguments = myArgs;
            Process.Start(startInfo, @"something.exe", a + " " + b + " " + c);
        }
*/
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
