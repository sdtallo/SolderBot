﻿/**********************************************************************
*
* Original Author: Samantha Stensland
* File Creation Date: February 11, 2019
* Description: This program controls functionality for Form2.
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
using System.Windows.Forms;

namespace GUI_Home
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        // Next step
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form3 f3 = new Form3(null, null, null, null);
            f3.ShowDialog();
            this.Close();
        }
    }
}
