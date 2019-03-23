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
            // Make last form a variable

            // go back to prevPage on button7_Click
        }

        // Move soldering iron backward, away from user
        private void button1_Click(object sender, EventArgs e)
        {
            // move 0.1" backward (away from user)
        }
        
        // Move soldering iron to the left
        private void button2_Click(object sender, EventArgs e)
        {
            // move 0.1 " to the left
        }

        // Move soldering iron to the right
        private void button3_Click(object sender, EventArgs e)
        {
            // move 0.1" to the right
        }

        // Move soldering iron forward, towards the user
        private void button4_Click(object sender, EventArgs e)
        {
            // move 0.1" forward
        }

        // Move soldering iron up
        private void button5_Click(object sender, EventArgs e)
        {
            // move 0.1" up
        }
        
        // Move soldering iron down
        private void button6_Click(object sender, EventArgs e)
        {
            // move 0.1" down
        }

        // Done calibrating - go back to last page
        private void button7_Click(object sender, EventArgs e)
        {
            // go to previous page, whichever one it was
            this.Hide();
            
        }
    }
}
