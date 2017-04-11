using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Data.OleDb;
using MySQLDriverCS;
using System.Data.Odbc;

namespace C1
{
    public partial class Form2 : Form
    {

        public static string Ip;
        public static string Username;
        public static string Password;
        public static int Port;
        public static string KuName;

        public Form2()
        {
            InitializeComponent();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Ip = textBox1.Text.ToString();
            Password = textBox2.Text.ToString();
            Port = Convert.ToInt32(textBox3.Text);
            Username = textBox4.Text.ToString();
            KuName = textBox6.Text.ToString();
            MySQLConnection DBConn;
            DBConn = new MySQLConnection(new MySQLConnectionString(Ip,KuName,Username, Password,Port).AsString);
            DBConn.Open();
            try
            {
                MySQLCommand cmd = new MySQLCommand("select xls.id,config.id from xls,config where config.id=xls.id", DBConn);
                cmd.ExecuteNonQuery();
                MessageBox.Show("连接成功！");
            }
            catch(MySQLException ex)
            {
                switch (ex.Number)
                {
                    case 1146:
                        MessageBox.Show("相关表不存在，系统正在为您创建！");
                        string mySelectQuery = "CREATE TABLE xls(id int(11) auto_increment,DATE VARCHAR(255),IP VARCHAR(255),URL VARCHAR(255),MD5 VARCHAR(255),FLAG VARCHAR(255),CLASS VARCHAR(255),PRIMARY KEY (id))";
                        string configsql = "CREATE TABLE config(id int(11) auto_increment,CLASS VARCHAR(255),keyword VARCHAR(255),PRIMARY KEY (id))";
                        MySQLCommand cmd = new MySQLCommand(mySelectQuery, DBConn);
                        MySQLCommand cmd2 = new MySQLCommand(configsql, DBConn);
                        cmd.ExecuteNonQuery();
                        cmd2.ExecuteNonQuery();
                        MessageBox.Show("创建成功！");
                        break;
                    default:
                        MessageBox.Show(ex.Message);
                        break;
                }
            }
            DBConn.Close();            
            this.Close();
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {

        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

    }
}
