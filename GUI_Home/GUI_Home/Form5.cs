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
    public partial class Form5 : Form
    {
        // Global variables
        string Lpins, Mpins, Rpins;

        public Form5(string leftPins, string middlePins, string rightPins)
        {
            InitializeComponent();
            Lpins = leftPins;
            Mpins = middlePins;
            Rpins = rightPins;
        }

        // Ready for machine to begin soldering
        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form6 f6 = new Form6();
            f6.ShowDialog(this);
            this.Close();
        }

        // Not ready for machine to begin soldering
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();            
            Form9 f9 = new Form9(Lpins, Mpins, Rpins);
            f9.ShowDialog();
            this.Close();
        }
    }
}
