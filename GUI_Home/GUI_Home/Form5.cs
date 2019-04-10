using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace GUI_Home
{
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }

        // Ready for machine to begin soldering
        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form6 f6 = new Form6();
            f6.ShowDialog();
        }

        // Not ready for machine to begin soldering
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
//            var Lpins = this.leftPins;
            
//            Form9 f9 = new Form9(Lpins, Mpins, Rpins);
//            f9.ShowDialog();
            Form3 f3= new Form3();
            f3.ShowDialog();
            this.Close();
        }

        // Recalibrate
        private void button7_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form10 f10 = new Form10();
            f10.ShowDialog();
            this.Close();
        }
    }
}
