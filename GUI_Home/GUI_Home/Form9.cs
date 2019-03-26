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
            string argStr = " \" " + leftPins + "_" + middlePins + "_" + rightPins + " \" ";
//            string testStr = "a";
//            System.Diagnostics.Process.Start("seniorDesignP.exe", "a");
            System.Diagnostics.Process.Start("helloargs.exe", "printme");


            // Test code from https://stackoverflow.com/questions/14113384/passing-arguments-and-returns-between-c-sharp-application-and-c-exe-file

/*            ProcessStartInfo myInfo = new ProcessStartInfo("seniorDesignP.exe", testStr);
            myInfo.RedirectStandardOutput = true;
            myInfo.UseShellExecute = false;
            myInfo.CreateNoWindow = true;

            using (Process p = Process.Start(myInfo))
            {
                p.WaitForExit();
                int a = p.ExitCode;
                label1.Text = a.ToString();
            }
*/        }

        // Starting code from this website: https://social.msdn.microsoft.com/Forums/vstudio/en-US/9c574d79-13cd-4333-bb7c-dcf2305d8155/how-to-run-an-exe-file-when-cliking-a-button-cnet?forum=csharpgeneral

        
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
