using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using System.Diagnostics;
using System.IO;

namespace GUI_Home
{
    public partial class Form6 : Form
    {
        public Form6()
        {
            InitializeComponent();
            
            // Call robot - run from /home/pi or Desktop icon
            Console.WriteLine("running");

            ProcessStartInfo roboInfo = new ProcessStartInfo();
            roboInfo.FileName = "../../usr/bin/env";
            roboInfo.Arguments = "solderbot/caller.py";
            roboInfo.WorkingDirectory = "";
            roboInfo.RedirectStandardOutput = true;
            roboInfo.UseShellExecute = false;
            roboInfo.CreateNoWindow = true;

            Process runRobot = Process.Start(roboInfo);
            Console.WriteLine("process started");

            // When robot responds back with "done", move to next screen
            runRobot.EnableRaisingEvents = true;

            // Determine what the last line is
            string lastLine = "mystring";
            int count = 0;        

            // Determine how the program exited
            // Assistance from https://www.c-sharpcorner.com/blogs/passing-parameters-to-events-c-sharp1
            runRobot.Exited += delegate (object sender, EventArgs e) {
                
                // Read last line of output from Travis
                lastLine = runRobot.StandardOutput.ReadLine();
                count = count + 1;
                Console.WriteLine("lastLine is " + lastLine + " - run #" + count);

                nextScreen(sender, e, lastLine, runRobot);
            };

            Console.WriteLine("after nextScreen event");
        }

        // Need event - move to finish screen when robot finishes soldering
        // https://stackoverflow.com/questions/12273825/c-sharp-process-start-how-do-i-know-if-the-process-ended
        // https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.enableraisingevents?view=netframework-4.7.2

        private void nextScreen(object sender, EventArgs e, string lastline, Process myProc)
        {
            Console.WriteLine("choosing nextScreen");

            if (lastline == "Job completed")
            {
                Console.WriteLine("move to page 7");

                this.Hide();
                Form7 f7 = new Form7();
                f7.Show();
                this.Hide();
//                this.Close();
            }
            else if (lastline == "Emergency stop pressed")
            {
                Console.WriteLine("move to page 8");

                this.Hide();
                Form8 f8 = new Form8(myProc);
                f8.Show();
//                this.Close();
            }
            else 
            {
                Console.WriteLine("uh oh");
            }
        }
    }
}
