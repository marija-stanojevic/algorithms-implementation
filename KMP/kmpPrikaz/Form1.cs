using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace kmpPrikaz
{
    public partial class Form1 : Form
    {
        [DllImport("kmp.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr kmpmain([MarshalAs(UnmanagedType.LPStr)]string vhod1, string vhod2);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            label3.Text = Marshal.PtrToStringAnsi(kmpmain(textBox1.Text, textBox2.Text));
        }
    }
}
