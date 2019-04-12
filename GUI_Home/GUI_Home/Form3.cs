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
        public Form3(string leftPins, string middlePins, string rightPins)
        {
            InitializeComponent();
            textBox1.Text = leftPins;
            textBox2.Text = middlePins;
            textBox3.Text = rightPins;
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
            getGcode.Start();


            //            Process getGcode = Process.Start("solderbot-test/seniorDesignP/seniorDesignP.exe", argStr);

            // From https://stackoverflow.com/questions/1585354/get-return-value-from-process
            // Wait for exit code - tell if there's an error in strings or not
            while (!getGcode.StandardOutput.EndOfStream)
            {
                string output = getGcode.StandardOutput.ReadToEnd();
                Console.WriteLine("Output: " + output + "\n");
            }
            
            getGcode.WaitForExit();
            int result = getGcode.ExitCode;

            // Must have the readToEnd BEFORE the WaitForExit(), to avoid a deadlock condition

            // If pins are valid, go to next page
            if (result == 0)
            {
                this.Hide();
                Form9 f9 = new Form9(textBox1.Text, textBox2.Text, textBox3.Text);
                f9.ShowDialog();
                this.Close();
            }
            else
            {
                // Redirect to error page
                //                this.Hide();
                //                Form9 f9 = new Form9(textBox1.Text, textBox2.Text, textBox3.Text);
                //                f9.ShowDialog();
                //                Form1 f1 = new Form1();
                //                f1.ShowDialog();
                //                this.Close();

                Console.WriteLine("Result: " + result + "\n");
            }
        }
    }
}
