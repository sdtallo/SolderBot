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

namespace GUI_Home
{
    public partial class Form6 : Form
    {
        public Form6()
        {
            InitializeComponent();
            // Call robot - run from /home/pi or Desktop icon
            // Assistance from https://stackoverflow.com/questions/11779143/how-do-i-run-a-python-script-from-c

            Process runRobot = new Process();
            runRobot.StartInfo = new ProcessStartInfo("../../usr/bin/env", "solderbot/caller.py")
            {
                RedirectStandardOutput = true,
                UseShellExecute = false,
                CreateNoWindow = true
            };
            runRobot.Start();

            // When robot responds back with "done", move to next screen
            runRobot.EnableRaisingEvents = true;
            runRobot.Exited += new EventHandler(soldering_Complete);

            // While program is still going, if eStop is pressed
            // Message is printed to command line & GUI moves to next screen
            //while (!runRobot.HasExited)
            //{
            // Read line, if emergency stop line, execute that code
                string mymsg = runRobot.StandardOutput.ReadLine();
                Console.WriteLine("MYMSG = " + mymsg);

                if (mymsg == "Emergency stop pressed")
                {
                    Console.WriteLine("E-stop, closing process");
                    runRobot.Close();
                    runRobot.Exited += new EventHandler(eStop);
                    
                    /*
                    this.Hide();
                    Form8 f8 = new Form8();
                    f8.ShowDialog();
                    this.Close();
                    */
                }
            //}

            /*
                        runRobot.OutputDataReceived += new DataReceivedEventHandler((sender, e) =>
                            {
                                // Read line, if emergency stop line, execute that code
                                string mymsg = runRobot.StandardOutput.ReadLine();
                                Console.WriteLine("MYMSG = " + mymsg);

                                if (mymsg == "Emergency stop pressed")
                                {
                                    Console.WriteLine("E-stop, closing process");
                                    runRobot.Close();
                                    //runRobot.Exited += new EventHandler(eStop);
                                    Console.WriteLine("opening form 8");

                                    this.Hide();
                                    Form8 f8 = new Form8();
                                    f8.ShowDialog();
                                    this.Close();
                                }
                            });
            */
            //}
            
        }

        // Need event - move to finish screen when robot finishes soldering
        // https://stackoverflow.com/questions/12273825/c-sharp-process-start-how-do-i-know-if-the-process-ended
        // https://docs.microsoft.com/en-us/dotnet/api/system.diagnostics.process.enableraisingevents?view=netframework-4.7.2

        private void soldering_Complete(object sender, EventArgs e)
        {
            this.Hide();
            Form7 f7 = new Form7();
            f7.ShowDialog();
            this.Close();
        }

        // Emergency stop
        private void eStop(object sender, EventArgs e)
        {
            Console.WriteLine("opening form 8");

            this.Hide();
            Form8 f8 = new Form8();
            f8.ShowDialog();
            this.Close();
        }
    }
}
