﻿using System;
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
    public partial class Form8 : Form
    {
        public Form8()
        {
            InitializeComponent();
        }

        // Resume soldering
        private void button1_Click(object sender, EventArgs e)
        {
            // Pass last location to next page as argument to resume soldering

            this.Hide();
            Form6 f6 = new Form6();
            f6.ShowDialog();
            this.Close();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form1 f1 = new Form1();
            f1.ShowDialog();
            this.Close();
        }

        // Recalibrate button
        private void button7_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form10 f10 = new Form10();
            f10.ShowDialog();
            this.Close();
        }
    }
}
