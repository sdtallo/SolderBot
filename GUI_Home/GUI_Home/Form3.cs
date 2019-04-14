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
    public partial class Form3 : Form
    {
        public Form3(string leftPins, string middlePins, string rightPins, string errMsg)
        {
            InitializeComponent();
            textBox1.Text = leftPins;
            textBox2.Text = middlePins;
            textBox3.Text = rightPins;
            label3.Text = errMsg;
        }

        // Verify pin locations - next step
        private void button1_Click(object sender, EventArgs e)
        {
            // Verify pins
            // This variable builds the singular string to send to the Gcode-generating program (under seniorDesignP folder)
            // Delimiter between each board is " _ "
            string argStr = " \" " + textBox1.Text + " _ " + textBox2.Text + " _ " + textBox3.Text + " \" ";
            // Mono command run from /home/pi
            Process getGcode = new Process();
            getGcode.StartInfo.FileName = "solderbot-test/seniorDesignP/seniorDesignP.exe";
            getGcode.StartInfo.Arguments = argStr;
            getGcode.StartInfo.UseShellExecute = false;
            getGcode.StartInfo.RedirectStandardOutput = true;
            getGcode.StartInfo.CreateNoWindow = true;
            getGcode.Start();

            // Check (every 500 milliseconds) for Gcode to be done generating before starting robot
            while (!getGcode.WaitForExit(500)) ;

            // https://stackoverflow.com/questions/4291912/process-start-how-to-get-the-output/4291965
            // Read error message that gcode generator function outputs (using printf() function)
            string errorMsg = getGcode.StandardOutput.ReadLine();
            Console.WriteLine("errorMsg: |" + errorMsg + "|");

            // First line printed to console from Gcode generator is error message
            while (!getGcode.StandardOutput.EndOfStream)
            {
                string mymsg = getGcode.StandardOutput.ReadLine();
                Console.WriteLine("Mymsg: |" + mymsg + "|");
            }

            // If pins are valid, go to next page
            if (errorMsg == "This is a valid string")       // Doesn't work with the \n at end of string
            {
                this.Hide();
                Form9 f9 = new Form9(textBox1.Text, textBox2.Text, textBox3.Text);
                f9.ShowDialog();
                this.Close();
            }
            else
            {
                // Show error on page
                label3.Text = errorMsg;

                //this.Hide();
                //Form3 f3 = new Form3(textBox1.Text, textBox2.Text, textBox3.Text, errorMsg);
                //f3.ShowDialog();
                //this.Close();

                Console.WriteLine("INVALID STRING");
            }
        }
    }
}
