using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace GUI_Home
{
    public partial class Form8 : Form
    {
        public Form8()
        {
            InitializeComponent();
        }

        // Resuming Soldering - call Travis's program again
        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
            Form6 f6 = new Form6();
            f6.ShowDialog();
            this.Close();
        }

        // Return to home page - write null or "\n" to gCodeLoc.txt
        private void button2_Click(object sender, EventArgs e)
        {
            // Write null or "\n" to gCodeLoc.txt
            string path = "/home/pi/solderbot/gCodeLoc.txt";
            // This text is added only once to the file.
            if (!File.Exists(path))
            {
                // Create a file to write to.
                string createText = "" + Environment.NewLine;
                File.WriteAllText(path, createText);
            }

            this.Hide();
            Form1 f1 = new Form1();
            f1.ShowDialog();
            this.Close();
        }        
    }
}
