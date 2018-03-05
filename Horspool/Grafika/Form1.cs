using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Grafika
{
    public partial class Form1 : Form
    {
        [DllImport("horspool.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr horspool([MarshalAs(UnmanagedType.LPStr)]string vhod1, string vhod2, string vhod3);
        public Form1()
        {
            InitializeComponent();
            openFileDialog1.FileName = "";
        }
        private void button1_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "" && textBox2.Text != "")
            {
                string s, tekst;
                if (openFileDialog1.FileName == "") { tekst = textBox2.Text; s="prazno";} 
                else {tekst = ""; s=openFileDialog1.FileName;} 
                s = Marshal.PtrToStringAnsi(horspool(textBox1.Text, tekst, s));
                textBox1.Text = s;
                string t1, t2;
                int kp, k=s.IndexOf('~');
                t1 = s.Substring(0, k);
                t2 = s.Substring(k + 1, s.Length - k - 1);
                kp=0;
                k=t1.IndexOf('`');
                while (k<t1.Length && k>=0)
                {
                    textBox1.AppendText(t1.Substring(kp, k));
                    kp = k;
                    k = t1.IndexOf('`', kp+1);
                    textBox1.SelectionStart = textBox1.TextLength;
                    textBox1.SelectionLength = 0;
                   // textBox1.SelectionColor = Color.Yellow;
                    textBox1.AppendText(t1.Substring(kp, k));
                }
                textBox2.Text = t2;
           }
            else richTextBox1.Text = "Napaka pri vnosu";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            openFileDialog1.InitialDirectory = "";
            openFileDialog1.FileName = "";
            openFileDialog1.ShowDialog();
        }
    }
}
