using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace LZWD
{
    public partial class Form1 : Form
    {
        [DllImport("LZW.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr zip([MarshalAs(UnmanagedType.LPStr)]string vhod1);
        [DllImport("LZW.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr unzip([MarshalAs(UnmanagedType.LPStr)]string vhod1);
        public Form1()
        {
            InitializeComponent();
            openFileDialog1.FileName = "";
        }

        private void button1_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            openFileDialog1.InitialDirectory = "";
            openFileDialog1.FileName = "";
            openFileDialog1.ShowDialog();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            if (openFileDialog1.FileName != "")
            {
                richTextBox1.Text = "Procenat stiskanja je " + Marshal.PtrToStringAnsi(zip(openFileDialog1.FileName));
            }
            else richTextBox1.Text = "Niste naložili datoteko";
        }

        private void button3_Click(object sender, EventArgs e)
        {
            richTextBox1.Text = "";
            if (openFileDialog1.FileName != "")
            {
                richTextBox1.Text = "Procenat stiskanja je " + Marshal.PtrToStringAnsi(unzip(openFileDialog1.FileName));
            }
            else richTextBox1.Text = "Niste naložili datoteko";
        }

    }
}
