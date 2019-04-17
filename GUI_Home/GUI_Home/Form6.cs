﻿/**********************************************************************
*
* Original Author: Samantha Stensland
* File Creation Date: February 11, 2019
* Description: This program controls functionality for Form6.
* It was originally generated by Microsoft Visual Studio and edited further.
*
**********************************************************************/

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
/*
            // Determine how the program exited
            // Assistance from https://www.c-sharpcorner.com/blogs/passing-parameters-to-events-c-sharp1
            runRobot.Exited += delegate (object sender, EventArgs e) {
                nextScreen(sender, e, runRobot);
            };
        }

        // Need event - move to finish screen when robot finishes soldering
        // https://stackoverflow.com/questions/12273825/c-sharp-process-start-how-do-i-know-if-the-process-ended
        // https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.enableraisingevents?view=netframework-4.7.2

        private void nextScreen(object sender, EventArgs e, Process myProc)
        {
            Console.WriteLine("Choosing the next screen");

            // Read last line of output from Travis and print to command line
//            string lastLine = myProc.StandardOutput.ReadLine();
            string lastLine = "Job completed";

//            Console.WriteLine("lastLine is: " + lastLine);

            if (lastLine == "Job completed")
            {
*/                this.Hide();
                Form7 f7 = new Form7();
                f7.ShowDialog();
                this.Close();
/*            }
            else if (lastLine == "Emergency stop pressed")
            {
                this.Hide();
                Form8 f8 = new Form8(myProc);
                f8.ShowDialog();
                this.Close();
            }
            else 
            {
                Console.WriteLine("Next page not determined properly");
            }

            Console.WriteLine("End of nextScreen function");
*/        }
    }
}
