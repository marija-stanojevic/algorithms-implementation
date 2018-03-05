using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace SLC
{
    public partial class Form1 : Form
    {
        Bitmap dd;
        Graphics g, g1, g2;
        int n = 0, k=0;
        double [,] dis;
        int[] klaster;
        Point[] tac;
        int kl = 0;
        uint ch = 0xEF555555;
        Pen mypen = new Pen(Color.Black, 5);
        public Form1()
        {
            InitializeComponent();
            dd = new Bitmap(pictureBox1.Size.Width, pictureBox1.Size.Height);
            tac = new Point [50];
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {
            MouseEventArgs mouseAgrs = (MouseEventArgs)e;
            pictureBox1.Image = dd;
            g = Graphics.FromImage(pictureBox1.Image);
            if (pictureBox1.Location.X - mouseAgrs.X < 655)
            {
                tac[k++].X = pictureBox1.Location.X - mouseAgrs.X;
            }
            if (pictureBox1.Location.X - mouseAgrs.X < 655)
            {
                tac[k++].X = pictureBox1.Location.Y - mouseAgrs.Y;
            }
            g.DrawLine(mypen, tac[k - 1].X - 2, tac[k - 1].Y - 2, tac[k - 1].X + 2, tac[k - 1].Y + 2);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            k = 0;
            dd = new Bitmap(pictureBox1.Size.Width, pictureBox1.Size.Height);
            pictureBox1.Image = dd;
            g2 = Graphics.FromImage(pictureBox1.Image);
            Random r = new Random();
            try
            {
                n = int.Parse(textBox1.Text);
            }
            catch (Exception ex) { textBox1.Text = "Napaka pri vnosu!"; }
            tac=new Point [n];
            for (int i = 0; i < n; i++)
            {
                tac[i].X = r.Next(0, 400)+150;
                tac[i].Y = r.Next(0, 250)+100;
                g2.DrawLine(mypen, tac[i].X - 2, tac[i].Y - 2, tac[i].X + 2, tac[i].Y + 2);
            }
        }
        
        private void button2_Click(object sender, EventArgs e)
        {
            if (k != 0) n = k;
            dis=new double [n, n];
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                {
                    dis[i, j] = Math.Sqrt((tac[i].X - tac[j].X) * (tac[i].X - tac[j].X) + (tac[i].Y - tac[j].Y) * (tac[i].Y - tac[j].Y));
                }
            obradi();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (k != 0) n = k;
            dis = new double[n, n];
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                {
                    dis[i, j] =Math.Abs(tac[i].X-tac[j].X) + Math.Abs(tac[i].Y-tac[j].Y);
                }
            obradi();
        }

        private void button4_Click(object sender, EventArgs e)
        {
            if (k != 0) n = k;
            dis = new double[n, n];
            for (int i = 0; i < n; i++)
                for (int j = i + 1; j < n; j++)
                {
                    dis[i, j] = Math.Max(Math.Abs(tac[i].X - tac[j].X), Math.Abs(tac[i].Y - tac[j].Y));
                }
            obradi();
        }
        void obradi()
        {
            kl = 0;
            pictureBox1.Image = dd;
            g1 = Graphics.FromImage(pictureBox1.Image);
            klaster = new int[n];
            int ii=0, jj=0;
            for (int i = 0; i < n; i++) klaster[i] = 0;
            for (int r = 0; r < n * n / 2 - 1-n; r++)
            {
                double min = 5000;
                for (int i = 0; i < n; i++)
                    for (int j = i + 1; j < n; j++)
                    {
                        if (dis[i, j] != 0 && dis[i, j] < min && (klaster[i]!=klaster[j] || (klaster[i]==0 && klaster[j]==0))) { min = dis[i, j]; ii = i; jj = j; }
                    }
                if (klaster[ii] == 0 && klaster[jj] == 0) { kl++; klaster[ii] = kl; klaster[jj] = kl; }
                else if (klaster[ii] == 0)
                {
                    kl++;
                    klaster[ii] = kl;
                    for (int i = 0; i < n; i++)
                        if (i != jj && klaster[i] == klaster[jj]) { klaster[i] = kl; }
                    klaster[jj] = kl;
                }
                else if (klaster[jj] == 0)
                {
                    kl++;
                    klaster[jj] = kl;
                    for (int i = 0; i < n; i++)
                        if (i != ii && klaster[i] == klaster[ii]) { klaster[i] = kl; }
                    klaster[ii] = kl;
                }
                else
                {
                    kl++;
                    for (int i = 0; i < n; i++)
                        if (i != ii && klaster[i] == klaster[ii]) { klaster[i] = kl; }
                    klaster[ii] = kl;
                    for (int i = 0; i < n; i++)
                        if (i != jj && klaster[i] == klaster[jj]) { klaster[i] = kl; }
                    klaster[jj] = kl;
                }
                double x=700, y=500, width=0, height=0;
                for (int i = 0; i < n; i++)
                    for (int j = i + 1; j < n; j++)
                    {
                        if (klaster[i] == kl && klaster[j] == kl)
                        {
                            if (width < Math.Abs(tac[i].X - tac[j].X)) { width=Math.Abs(tac[i].X - tac[j].X);}
                            if (height < Math.Abs(tac[i].Y - tac[j].Y)) { height=Math.Abs(tac[i].Y - tac[j].Y);}
                            double pomx, pomy;
                            if (tac[i].X < tac[j].X) pomx = tac[i].X; else pomx = tac[j].X;
                            if (tac[i].Y < tac[j].Y) pomy = tac[i].Y; else pomy = tac[j].Y;
                            if (x > pomx) x = pomx;
                            if (y > pomy) y = pomy;
                        }
                    }
                if (height == 0) height = 10;
                if (width == 0) width = 10;
                x -= width / 4; y -= height / 4; 
                if (width < 50) width *= 2; else width = width * 1.5;
                if (height < 50) height *= 2; else height = height * 1.5;
                Pen mypen1 = new Pen(Color.FromArgb((int)ch), 2); //videti kako da se svaki put promeni boja
                ch += 0x00342816;
                g1.DrawEllipse(mypen1, (int)x, (int)y, (int)width, (int)height);
            }
        }
    }
}
