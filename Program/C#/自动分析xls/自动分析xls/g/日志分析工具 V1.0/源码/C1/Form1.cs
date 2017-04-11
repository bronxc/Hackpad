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
using System.IO;
using System.Text;


namespace C1
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        /*public int ConMysql()
        {
            MySQLConnection DBConn;
            DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
            DBConn.Open();
            return 0;
        }

        public int CloseMysql(MySQLConnection DBConn)
        {
            DBConn.Close();
            return 0;
        }*/

        public static int Joinclass()
        {
            if (Form3.key != "")
            {
                MySQLConnection DBConn;
                DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                DBConn.Open();
                MySQLCommand DBComm = new MySQLCommand("select CLASS from config where CLASS='" + Form3.cla + "'", DBConn);
                MySQLDataReader DBReader = DBComm.ExecuteReaderEx();
                if (!DBReader.Read())
                {
                    DBComm = new MySQLCommand("insert into config(CLASS) values('" + Form3.cla + "')", DBConn);
                    DBComm.ExecuteNonQuery();
                }
                else if (Form3.cla != DBReader.GetString(0))
                {
                    DBComm = new MySQLCommand("insert into config(CLASS) values('" + Form3.cla + "')", DBConn);
                    DBComm.ExecuteNonQuery();
                }
                DBComm = new MySQLCommand("update config set keyword='" + Form3.key + "' where CLASS='" + Form3.cla + "'", DBConn);
                DBComm.ExecuteNonQuery();
                DBConn.Close();
            }
            return 0;
        }

        public string ToClass(string str)
        {
            string flag="";
            MySQLConnection DBConn;
            DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
            DBConn.Open();
            MySQLCommand DBComm = new MySQLCommand("select CLASS from config", DBConn);
            MySQLDataReader DBReader = DBComm.ExecuteReaderEx();
            while (DBReader.Read())
            {
                flag = DBReader.GetString(0);
                DBComm = new MySQLCommand("select keyword from config where CLASS='" + DBReader.GetString(0) + "'", DBConn);
                MySQLDataReader DBReader1 = DBComm.ExecuteReaderEx();
                if (DBReader1.Read())
                {
                    if (str.Contains(DBReader1.GetString(0)))
                    {
                        flag = DBReader.GetString(0);
                        DBConn.Close();
                        return flag;
                    }
                }
            }
            DBConn.Close();
            return flag;
        }

        private void 数据库连接ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form2 frm = new Form2();
            frm.Show();
        }

        private void 添加ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            
        }

        private void 设置ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 全部显示ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MySQLConnection DBConn;
                DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                DBConn.Open();

                //清空数据
                dataGridView1.Rows.Clear();

                int i = 0;

                MySQLCommand DBComm = new MySQLCommand("select id,DATE,IP,URL,CLASS,MD5 from xls", DBConn);
                MySQLDataReader DBReader = DBComm.ExecuteReaderEx();
                while (DBReader.Read())
                {
                    i = dataGridView1.Rows.Add();
                    dataGridView1.Rows[i].Cells[0].Value = DBReader.GetString(0);
                    dataGridView1.Rows[i].Cells[1].Value = DBReader.GetString(1);
                    dataGridView1.Rows[i].Cells[2].Value = DBReader.GetString(2);
                    dataGridView1.Rows[i].Cells[3].Value = DBReader.GetString(3);
                    dataGridView1.Rows[i].Cells[4].Value = DBReader.GetString(4);
                    dataGridView1.Rows[i].Cells[5].Value = DBReader.GetString(5);
                }
                DBConn.Close();
            }
            catch(MySQLException)
            {
                MessageBox.Show("请先连接数据库！");
            }
                
            
        }

        private void 帮助ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string path = "readme.txt";
            System.Diagnostics.Process.Start("notepad.exe", path);

        }

        private void 导出数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 添加分类ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            Form3 frm = new Form3();
            frm.Show();
        }

        private void 导入数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form4.addvalue();
            
            //try
            //{
            //    OpenFileDialog ofd = new OpenFileDialog();
            //    ofd.Title = "打开";
            //    ofd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
            //    ofd.Filter = "Excle Document(*.xls)|*.xls|All Files|*.*";
            //    if (ofd.ShowDialog() == DialogResult.OK)
            //    {
            //        string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;" + "data source=" + ofd.FileName + ";Extended Properties='Excel 8.0; HDR=Yes; IMEX=1'";
            //        OleDbConnection conn = new OleDbConnection(strConn);
            //        conn.Open();
            //        string strExcel = "";
            //        OleDbDataAdapter myCommand = null;
            //        DataTable dt = null;
            //        strExcel = "select * from [sheet1$]";
            //        myCommand = new OleDbDataAdapter(strExcel, strConn);
            //        dt = new DataTable();
            //        myCommand.Fill(dt);
            //        int countrow = dt.Rows.Count;
            //        string flag = null;
            //        string CLASS = null;
            //        MySQLConnection DBConn;
            //        DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
            //        DBConn.Open();

            //        //读取config中的值
            //        //MySQLCommand Rconfig = new MySQLCommand("select * from config", DBConn);
            //        //MySQLDataReader Rconfigdb = Rconfig.ExecuteReaderEx();

            //        for (int i = 0; i < countrow; i++)
            //        {
            //            string row1 = dt.Rows[i][0].ToString();
            //            string row2 = dt.Rows[i][1].ToString();
            //            string row3 = dt.Rows[i][2].ToString();
            //            string row4 = dt.Rows[i][3].ToString();
            //            //flag = ToClass(row4);

            //            //判定类别
            //            /*
            //            while(Rconfigdb.Read())
            //            {
            //                if (row4.Contains(Rconfigdb["keyword"].ToString().ToLower()))
            //                {
            //                    flag = Rconfigdb["id"].ToString();
            //                    CLASS = Rconfigdb["CLASS"].ToString();
            //                    textBox2.AppendText(Rconfigdb.GetString(2));
            //                }
            //                System.Threading.Thread.Sleep(0);
            //            }

            //            */
            //            MySQLCommand Rconfig = new MySQLCommand("select CLASS from config", DBConn);
            //            MySQLDataReader DBReader = Rconfig.ExecuteReaderEx();
            //            while (DBReader.Read())
            //            {
            //                //flag = DBReader.GetString(0);
            //                Rconfig = new MySQLCommand("select * from config where CLASS='" + DBReader.GetString(0) + "'", DBConn);
            //                MySQLDataReader DBReader1 = Rconfig.ExecuteReaderEx();
            //                if (DBReader1.Read())
            //                {
            //                    if (row4.Contains(DBReader1.GetString(2)))
            //                    {
            //                        flag = DBReader1.GetString(0);
            //                        CLASS = DBReader1.GetString(1);
            //                    }
            //                }
            //            }
            //            MySQLCommand DBComm = new MySQLCommand("insert into xls(MD5,DATE,IP,URL,FLAG,CLASS) values('" + row1 + "','" + row2 + "','" + row3 + "','" + row4 + "','" + flag + "','" + CLASS + "')", DBConn);
            //            DBComm.ExecuteNonQuery();
            //        }
            //        DBConn.Close();
                    
            //        MessageBox.Show("Success!");
            //    }
            //}
            //finally
            //{

            //}
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            string classx = comboBox1.SelectedItem.ToString();
            Grview(classx);
        }
        public void Grview(string str)
        {
            try
            {
                MySQLConnection DBConn;
                DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                DBConn.Open();

                //清空数据
                dataGridView1.Rows.Clear();

                int i = 0;

                MySQLCommand DBComm = new MySQLCommand("select id,DATE,IP,URL,CLASS,MD5 from xls where CLASS='" + str + "'", DBConn);
                MySQLDataReader DBReader = DBComm.ExecuteReaderEx();
                while (DBReader.Read())
                {
                    i = dataGridView1.Rows.Add();
                    dataGridView1.Rows[i].Cells[0].Value = DBReader.GetString(0);
                    dataGridView1.Rows[i].Cells[1].Value = DBReader.GetString(1);
                    dataGridView1.Rows[i].Cells[2].Value = DBReader.GetString(2);
                    dataGridView1.Rows[i].Cells[3].Value = DBReader.GetString(3);
                    dataGridView1.Rows[i].Cells[4].Value = DBReader.GetString(4);
                    dataGridView1.Rows[i].Cells[5].Value = DBReader.GetString(5);
                }
                DBConn.Close();
            }
            finally { }
        }
        private void button1_Click(object sender, EventArgs e)
        {
            string search = textBox1.Text;
            try
            {
                MySQLConnection DBConn;
                DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                DBConn.Open();

                //清空数据
                dataGridView1.Rows.Clear();

                int i = 0;

                MySQLCommand DBComm = new MySQLCommand("select id,DATE,IP,URL,CLASS,MD5 from xls where URL like '%" + search + "%'", DBConn);
                MySQLDataReader DBReader = DBComm.ExecuteReaderEx();
                while (DBReader.Read())
                {
                    i = dataGridView1.Rows.Add();
                    dataGridView1.Rows[i].Cells[0].Value = DBReader.GetString(0);
                    dataGridView1.Rows[i].Cells[1].Value = DBReader.GetString(1);
                    dataGridView1.Rows[i].Cells[2].Value = DBReader.GetString(2);
                    dataGridView1.Rows[i].Cells[3].Value = DBReader.GetString(3);
                    dataGridView1.Rows[i].Cells[4].Value = DBReader.GetString(4);
                    dataGridView1.Rows[i].Cells[5].Value = DBReader.GetString(5);
                }
                DBConn.Close();
            }
            catch (MySQLException)
            {
                MessageBox.Show("请先连接数据库！");
            }
        }
        public void ComboBoxshow()
        {     
            try
            {
                MySQLConnection combo;
                combo = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                combo.Open();
                MySQLCommand combocmd = new MySQLCommand("select CLASS from config", combo);
                //combocmd.ExecuteNonQuery();
                MySQLDataReader data = combocmd.ExecuteReaderEx();
                comboBox1.Items.Clear();
                while (data.Read())
                {
                    //comboBox1.Items.Add(data["CLASS"].ToString());
                    comboBox1.Items.Add(data.GetString(0));
                    //comboBox1.Items.Add("x");
                }
                combo.Close();

            }
            catch (MySQLException)
            {
                MessageBox.Show("请先连接数据库！");
            }
        }

        private void comboBox1_Click(object sender, EventArgs e)
        {
            ComboBoxshow();
        }

        private void 清除所有数据ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                MySQLConnection combo;
                combo = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                combo.Open();
                
                //删除数据库
                MySQLCommand deletcmd = new MySQLCommand(" drop database if exists test", combo);
                deletcmd.ExecuteNonQuery();

                //创建数据库
                MySQLCommand createcmd = new MySQLCommand("create database if not exists test", combo);
                createcmd.ExecuteNonQuery();

                combo.Close();
                MessageBox.Show("清除成功！");
            }
            catch (MySQLException)
            {
                MessageBox.Show("请先连接数据库！");
            }
        }
    }
    
}
