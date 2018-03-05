using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace ADFGX
{
    public partial class Form1 : Form
    {
        [DllImport("cADFGX.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr encode([MarshalAs(UnmanagedType.LPStr)]string vhod1, string vhod2, string vhod3);
        [DllImport("cADFGX.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr decode([MarshalAs(UnmanagedType.LPStr)]string vhod1, string vhod2, string vhod3);
        
        public Form1()
        {
            InitializeComponent();
            openFileDialog1.FileName = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = "";
            openFileDialog1.FileName = "";
            openFileDialog1.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                string s;
                if (openFileDialog1.FileName == "") { s = "prazno"; } else { s = openFileDialog1.FileName; }
                richTextBox1.Text = Marshal.PtrToStringAnsi(encode(s, textBox1.Text, textBox2.Text));
            }
            else richTextBox1.Text = "Napaka pri vnosu";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "" && textBox2.Text.Length%2==0)
            {
                string s;
                if (openFileDialog1.FileName=="") {s="prazno";} else {s=openFileDialog1.FileName;}
                richTextBox1.Text = Marshal.PtrToStringAnsi(decode(s, textBox1.Text, textBox2.Text));
            }
            else richTextBox1.Text = "Napaka pri vnosu";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
            textBox2.Text = "";
            richTextBox1.Text = "";
        }

       
    }
}
