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
            Process runRobot = Process.Start("../../usr/bin/env","solderbot/caller.py");

            // When robot responds back with "done", move to next screen
            // make new event handler
            runRobot.EnableRaisingEvents = true;
            runRobot.Exited += new EventHandler(soldering_Complete);
        }

        // Emergency stop
        private void button1_Click(object sender, EventArgs e)
        {
            // Make machine stop and raise up slightly
            // Pass last location soldered to next page as argument

            this.Hide();
            Form8 f8 = new Form8();
            f8.ShowDialog();
            this.Close();
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
    }
}
