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
    public partial class Form6 : Form
    {
        public Form6()
        {
            InitializeComponent();
            // Call robot
            Process runRobot = Process.Start("/usr/bin/env","/home/pi/solderbot/caller.py");

            // When robot responds back with "done", move to next screen
        }

        // Emergency stop
        private void button1_Click(object sender, EventArgs e)
        {
            // Make machine stop and raise up slightly
            // Pass last location soldered to next page as argument

            this.Hide();
            Form8 f8 = new Form8();
            f8.ShowDialog();
        }

        // Need event - move to finish screen when robot finishes soldering
    }
}
