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
    public partial class Form10 : Form
    {
        public Form10()
        {
            InitializeComponent();
            // go back to prevPage on button7_Click
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // move 0.1" backward (away from user)
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // move 0.1 " to the left
        }

        private void button3_Click(object sender, EventArgs e)
        {
            // move 0.1" to the right
        }

        private void button4_Click(object sender, EventArgs e)
        {
            // move 0.1" forward
        }

        private void button5_Click(object sender, EventArgs e)
        {
            // move 0.1" up
        }

        private void button6_Click(object sender, EventArgs e)
        {
            // move 0.1" down
        }

        private void button7_Click(object sender, EventArgs e)
        {
            // go to previous page, whichever one it was
        }
    }
}
