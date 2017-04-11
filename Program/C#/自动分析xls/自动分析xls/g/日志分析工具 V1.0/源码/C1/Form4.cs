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
    public partial class Form4 : Form
    {
        public Form4()
        {
            InitializeComponent();
        }
        public static int addvalue()
        {
            try
            {
                OpenFileDialog ofd = new OpenFileDialog();
                ofd.Title = "打开";
                ofd.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
                ofd.Filter = "Excle Document(*.xls)|*.xls|All Files|*.*";
                if (ofd.ShowDialog() == DialogResult.OK)
                {
                    string strConn = "Provider=Microsoft.Jet.OLEDB.4.0;" + "data source=" + ofd.FileName + ";Extended Properties='Excel 8.0; HDR=Yes; IMEX=1'";
                    OleDbConnection conn = new OleDbConnection(strConn);
                    conn.Open();
                    string strExcel = "";
                    OleDbDataAdapter myCommand = null;
                    DataTable dt = null;
                    strExcel = "select * from [sheet1$]";
                    myCommand = new OleDbDataAdapter(strExcel, strConn);
                    dt = new DataTable();
                    myCommand.Fill(dt);
                    int countrow = dt.Rows.Count;
                    string flag = null;
                    string CLASS = null;
                    MySQLConnection DBConn;
                    DBConn = new MySQLConnection(new MySQLConnectionString(Form2.Ip, Form2.KuName, Form2.Username, Form2.Password, Form2.Port).AsString);
                    DBConn.Open();

                    //读取config中的值
                    //MySQLCommand Rconfig = new MySQLCommand("select * from config", DBConn);
                    //MySQLDataReader Rconfigdb = Rconfig.ExecuteReaderEx();

                    for (int i = 0; i < countrow; i++)
                    {
                        string row1 = dt.Rows[i][0].ToString();
                        string row2 = dt.Rows[i][1].ToString();
                        string row3 = dt.Rows[i][2].ToString();
                        string row4 = dt.Rows[i][3].ToString();
                        //flag = ToClass(row4);

                        //判定类别
                        /*
                        while(Rconfigdb.Read())
                        {
                            if (row4.Contains(Rconfigdb["keyword"].ToString().ToLower()))
                            {
                                flag = Rconfigdb["id"].ToString();
                                CLASS = Rconfigdb["CLASS"].ToString();
                                textBox2.AppendText(Rconfigdb.GetString(2));
                            }
                            System.Threading.Thread.Sleep(0);
                        }

                        */
                        MySQLCommand Rconfig = new MySQLCommand("select CLASS from config", DBConn);
                        MySQLDataReader DBReader = Rconfig.ExecuteReaderEx();
                        while (DBReader.Read())
                        {
                            //flag = DBReader.GetString(0);
                            Rconfig = new MySQLCommand("select * from config where CLASS='" + DBReader.GetString(0) + "'", DBConn);
                            MySQLDataReader DBReader1 = Rconfig.ExecuteReaderEx();
                            if (DBReader1.Read())
                            {
                                if (row4.Contains(DBReader1.GetString(2)))
                                {
                                    flag = DBReader1.GetString(0);
                                    CLASS = DBReader1.GetString(1);
                                }
                            }
                        }
                        MySQLCommand DBComm = new MySQLCommand("insert into xls(MD5,DATE,IP,URL,FLAG,CLASS) values('" + row1 + "','" + row2 + "','" + row3 + "','" + row4 + "','" + flag + "','" + CLASS + "')", DBConn);
                        DBComm.ExecuteNonQuery();
                    }
                    DBConn.Close();

                    MessageBox.Show("Success!");
                }
            }
            finally
            {

            }
            return 0;
        }
        private void Form4_Load(object sender, EventArgs e)
        {

        }
    }
}
