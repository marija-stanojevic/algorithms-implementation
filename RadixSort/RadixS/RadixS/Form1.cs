using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace RadixS
{
    public partial class Form1 : Form
    {
        [DllImport("RadixSort.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr radix([MarshalAs(UnmanagedType.LPStr)]string vhod);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                int n = Int32.Parse(textBox1.Text);
                int br = Int32.Parse(textBox2.Text);
                richTextBox1.Text = Marshal.PtrToStringAnsi(radix(textBox1.Text+" "+textBox2.Text+" "));
            }
            catch (Exception ex)
            {
                if (ex is ArgumentNullException || ex is FormatException || ex is OverflowException)
                {
                    richTextBox1.Text = "Napačni vnos.";
                }
                else { throw; }
            }
        }
    }
}
