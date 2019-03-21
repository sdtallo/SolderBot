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
            // Modified example from https://stackoverflow.com/questions/9679375/run-an-exe-from-c-sharp-code
            const string ex1 = "C:\\";
            const string ex2 = "C:\\Dir";

            // Use ProcessStartInfo class
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.CreateNoWindow = false;
            startInfo.UseShellExecute = false;
            startInfo.FileName = "seniorDesignP.exe";  //Gcode generator .exe
            startInfo.WindowStyle = ProcessWindowStyle.Hidden;
//            startInfo.Arguments = "-f j -o \"" + ex1 + "\" -z 1.0 -s y " + ex2;

            try
            {
                // Start the process with the info we specified.
                // Call WaitForExit and then the using statement will close.
                using (Process exeProcess = Process.Start(startInfo))
                {
                    exeProcess.WaitForExit();
                }
            }
            catch
            {
                // Log error.
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form5 f5 = new Form5();
            f5.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form3 f3 = new Form3();
            f3.ShowDialog();
        }

        private void button7_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form10 f10 = new Form10();
            f10.ShowDialog();
        }
    }
}
