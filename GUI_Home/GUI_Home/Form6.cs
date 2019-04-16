﻿using System;
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
            roboInfo.RedirectStandardOutput = true;
            roboInfo.UseShellExecute = false;
            roboInfo.CreateNoWindow = true;

            Process runRobot = Process.Start(roboInfo);
            Console.WriteLine("process started");

            //Process runRobot = Process.Start("../../usr/bin/env", "solderbot/caller.py");
            //runRobot.StartInfo.RedirectStandardOutput = true;

            // When robot responds back with "done", move to next screen
            runRobot.EnableRaisingEvents = true;

            // Determine what the last line is
            string lastLine = "mystring";
            while (!runRobot.StandardOutput.EndOfStream)
            {
                lastLine = runRobot.StandardOutput.ReadLine();
            }
            Console.WriteLine("lastLine is " + lastLine);

            // Determine how the program exited
            // Assistance from https://www.c-sharpcorner.com/blogs/passing-parameters-to-events-c-sharp1
            runRobot.Exited += delegate (object sender, EventArgs e) {
                nextScreen(sender, e, lastLine);
            };

            Console.WriteLine("after nextScreen event");

            //runRobot.OutputDataReceived += new DataReceivedEventHandler();

            // While program is still going, if eStop is pressed
            // Message is printed to command line & GUI moves to next screen
            //runRobot.OutputDataReceived += new DataReceivedEventHandler((sender, e) =>
            // Read line, if emergency stop line, execute that code 

            /*
                if (mymsg == "Emergency stop pressed")
                {
                    Console.WriteLine("E-stop, closing process");
                    //runRobot.Close();
                    runRobot.Exited += new EventHandler(eStop);
                    /*
                    Console.WriteLine("opening form 8");
                    this.Hide();
                    Form8 f8 = new Form8();
                    f8.ShowDialog();
                    this.Close();
                }
                */
            //});
        }

        // Need event - move to finish screen when robot finishes soldering
        // https://stackoverflow.com/questions/12273825/c-sharp-process-start-how-do-i-know-if-the-process-ended
        // https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.enableraisingevents?view=netframework-4.7.2

        private void nextScreen(object sender, EventArgs e, string lastline)
        {
            Console.WriteLine("choosing nextScreen");

            if (lastline == "Job completed")
            {
                Console.WriteLine("move to page 7");

                this.Hide();
                Form7 f7 = new Form7();
                f7.ShowDialog();
                this.Close();
            }
            else
            {
                Console.WriteLine("move to page 8");

                this.Hide();
                Form8 f8 = new Form8();
                f8.ShowDialog();
                this.Close();
            }
        }
    }
}
