using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Threading;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.IO;
using System.Configuration;
using System.Text.RegularExpressions;

namespace Test1
{
    public partial class Form1 : Form
    {
        [DllImport("User32.dll", EntryPoint = "FindWindow")]
        public extern static IntPtr FindWindow(string lpClassName, string lpWindowName);

        [DllImport("User32.dll", EntryPoint = "FindWindowEx")]
        public static extern IntPtr FindWindowEx(IntPtr hwndParent, IntPtr hwndChildAfter, string lpClassName, string lpWindowName);

        [DllImport("user32")]
        static extern int SetForegroundWindow(IntPtr hwnd);

        delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
        [DllImport("user32.dll")]
        static extern int EnumWindows(EnumWindowsProc hWnd, IntPtr lParam);

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        static extern int GetWindowText(IntPtr hWnd, StringBuilder lpText, int nCount);

        [System.Runtime.InteropServices.DllImport("user32.dll", EntryPoint = "SendMessageA")]
        public static extern int SendMessage(IntPtr hwnd, int wMsg, int wParam, int lParam);


        private String softPath = "";//软件根目录
        private int userCount = 0;              //正确读取出的账号个数
        private int failedCount = 0;            //扫描目前状态记录次数
        private String currentUser = null;      //当前正在登录的账号
        private bool alreadyLoginSu = false;    //当前账号是否已经登陆成功
        private bool currentLoginSu = false;    //当前账号是否登陆成功
        private List<String> username = new List<string>();
        private List<String> password = new List<string>();
       
        public Form1()
        {
            InitializeComponent();

            readConfig();           //读取配置文件
            readUsers();            //读取用户

            //将信息显示在界面中
            pathText.Text = softPath;
            userCountText.Text = userCount + "个";
            statusLabel.Text = "读取用户 " + userCount + " 个";
            statusLabel.Refresh();
        }

        private void button3_Click(object sender, EventArgs e)
        {
            int numberCount = 0;            //当前登录账号序号
            int loginSuccess = 0;           //登录成功账号统计
            while (numberCount < userCount)
            {
                //显示Hint
                int tempshow = numberCount + 1;
                statusLabel.Text = "登录中...当前" + tempshow + "/" + userCount;
                statusLabel.Refresh();

                //清空登录记录
                if (File.Exists(softPath + @"\dat\ShowLogin.dat"))
                {
                    File.Delete(softPath + @"\dat\ShowLogin.dat");
                }

                currentUser = username[numberCount];            //当前账号

                //登录前，判断账号是否已经登录
                alreadyLoginSu = false;
                EnumWindows(callBackEnumWindows, IntPtr.Zero);

                //若已经登录，则进行下一个账号的登录
                if (alreadyLoginSu == true)
                {
                    loginSuccess++;
                    continue;
                }

                //创建进程，打开客户端
                Process myProcess = new Process();
                try
                {
                    myProcess.StartInfo.UseShellExecute = false;
                    myProcess.StartInfo.FileName = softPath + "\\SinaShow.exe";
                    myProcess.StartInfo.CreateNoWindow = true;
                    myProcess.Start();

                    //获得句柄
                    IntPtr maindHwnd;
                    failedCount = 0;
                    while (true)
                    {
                        maindHwnd = FindWindow(null, "新浪SHOW");
                        if (failedCount > 60)
                        {
                            MessageBox.Show("获取句柄超时，请重试");
                            break;
                        }
                        if (maindHwnd != IntPtr.Zero)
                        {
                            break;
                        }
                        else
                        {
                            failedCount++;
                            Thread.Sleep(1000);
                        }
                    }

                    //传输参数和登陆
                    Thread.Sleep(500);
                    SetForegroundWindow(maindHwnd);
                    System.Windows.Forms.SendKeys.Send("{BACKSPACE}");
                    System.Windows.Forms.SendKeys.Send(username[numberCount]);
                    System.Windows.Forms.SendKeys.Send("{TAB}");
                    System.Windows.Forms.SendKeys.Send(password[numberCount]);
                    System.Windows.Forms.SendKeys.SendWait("{ENTER}");

                    //模糊查询登陆成功后的结果
                    currentLoginSu = false;

                    failedCount = 0;
                    while (true)
                    {
                        EnumWindows(callBackEnumWindows, IntPtr.Zero);
                        if (failedCount > 60)
                        {
                            MessageBox.Show("账号" + currentUser + "登陆超时，请重试");
                            break;
                        }
                        if (currentLoginSu)
                        {
                            loginSuccess++;
                            break;
                        }
                        else
                        {
                            failedCount++;
                            Thread.Sleep(1000);
                        }
                    }
                    Thread.Sleep(5000);             //下一次登录间隙时间
                    numberCount++;
                }
                catch (Exception ex)
                {
                    MessageBox.Show("发生异常，请尝试重启软件、配置路径或联系管理员\n\n" + ex.StackTrace);
                    System.Environment.Exit(0);
                }
            }
            statusLabel.Text = "登录完成，共登录" + loginSuccess + "/" + userCount;
            statusLabel.Refresh();
        }

        //EnumWindows的回调函数，完成窗口比较，判断是否当前账号是否登陆完成
        private bool callBackEnumWindows(IntPtr hWnd, IntPtr lParam)
        {
            StringBuilder sb = new StringBuilder(50);
            GetWindowText(hWnd, sb, sb.Capacity);
            if (sb.ToString().Contains(currentUser))
            {
                currentLoginSu = true;
                alreadyLoginSu = true;
                return false;
            }
            else
            {
                return true;
            }
        }

        public void readConfig()
        {
            Configuration config = ConfigurationManager.OpenExeConfiguration(System.Windows.Forms.Application.ExecutablePath);
            foreach (string key in config.AppSettings.Settings.AllKeys)
            {
                switch (key)
                {
                    case "softPath":
                        softPath = config.AppSettings.Settings[key].Value;
                        break;
                }
            }
        }

        public void readUsers()
        {
            try
            {
                username.Clear();
                password.Clear();
                StreamReader sr = new StreamReader(@"User.txt", Encoding.Default);
                String line = "";
                userCount = 0;              //赋初值为0
                while ((line = sr.ReadLine()) != null)
                {
                    userCount++;
                    username.Add(Regex.Split(line, "\t", RegexOptions.IgnoreCase)[0]);
                    password.Add(Regex.Split(line, "\t", RegexOptions.IgnoreCase)[1]);
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("启动程序失败，读取User.txt文件发生错误，请检查文件格式\n\n" + e.StackTrace);
                System.Environment.Exit(0);
            }
        }

        private void setSoft_Click(object sender, EventArgs e)
        {
            //将配置写入文件
            Configuration config = ConfigurationManager.OpenExeConfiguration(System.Windows.Forms.Application.ExecutablePath);
            config.AppSettings.Settings["softPath"].Value = pathText.Text;
            config.Save(ConfigurationSaveMode.Modified);
            ConfigurationManager.RefreshSection("appSettings");
            
            //重新加载配置文件和用户文件
            readConfig();
            readUsers();

            //更新Hint
            userCountText.Text = userCount + "个";
            statusLabel.Text = "读取用户 " + userCount + " 个";
            statusLabel.Refresh();

            //显示Hint
            statusLabel.Text = "状态： 配置成功";
            statusLabel.Refresh();
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            fbd.SelectedPath = @"C:\";
            if(fbd .ShowDialog() == DialogResult.OK)
            {
               pathText.Text = fbd.SelectedPath;
            }
        }

        private void editButton_Click(object sender, EventArgs e)
        {
            string path = @"User.txt";
            System.Diagnostics.Process.Start(path);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }
    }
}