namespace Test1
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.setSoft = new System.Windows.Forms.Button();
            this.path = new System.Windows.Forms.Label();
            this.login = new System.Windows.Forms.Button();
            this.read = new System.Windows.Forms.Label();
            this.statusLabel = new System.Windows.Forms.Label();
            this.pathText = new System.Windows.Forms.TextBox();
            this.userCountText = new System.Windows.Forms.TextBox();
            this.openButton = new System.Windows.Forms.Button();
            this.editButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // setSoft
            // 
            this.setSoft.Location = new System.Drawing.Point(44, 161);
            this.setSoft.Name = "setSoft";
            this.setSoft.Size = new System.Drawing.Size(75, 23);
            this.setSoft.TabIndex = 0;
            this.setSoft.Text = "配置";
            this.setSoft.UseVisualStyleBackColor = true;
            this.setSoft.Click += new System.EventHandler(this.setSoft_Click);
            // 
            // path
            // 
            this.path.AutoSize = true;
            this.path.Location = new System.Drawing.Point(42, 35);
            this.path.Name = "path";
            this.path.Size = new System.Drawing.Size(53, 12);
            this.path.TabIndex = 2;
            this.path.Text = "软件路径";
            // 
            // login
            // 
            this.login.Location = new System.Drawing.Point(182, 162);
            this.login.Name = "login";
            this.login.Size = new System.Drawing.Size(75, 22);
            this.login.TabIndex = 3;
            this.login.Text = "开始登陆";
            this.login.UseVisualStyleBackColor = true;
            this.login.Click += new System.EventHandler(this.button3_Click);
            // 
            // read
            // 
            this.read.AutoSize = true;
            this.read.Location = new System.Drawing.Point(40, 69);
            this.read.Name = "read";
            this.read.Size = new System.Drawing.Size(101, 12);
            this.read.TabIndex = 4;
            this.read.Text = "读取账号密码个数";
            // 
            // statusLabel
            // 
            this.statusLabel.AutoSize = true;
            this.statusLabel.Location = new System.Drawing.Point(112, 131);
            this.statusLabel.Name = "statusLabel";
            this.statusLabel.Size = new System.Drawing.Size(101, 12);
            this.statusLabel.TabIndex = 5;
            this.statusLabel.Text = "状态：未开始登陆";
            this.statusLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // pathText
            // 
            this.pathText.Location = new System.Drawing.Point(148, 26);
            this.pathText.Name = "pathText";
            this.pathText.Size = new System.Drawing.Size(100, 21);
            this.pathText.TabIndex = 7;
            // 
            // userCountText
            // 
            this.userCountText.Location = new System.Drawing.Point(149, 65);
            this.userCountText.Name = "userCountText";
            this.userCountText.ReadOnly = true;
            this.userCountText.Size = new System.Drawing.Size(100, 21);
            this.userCountText.TabIndex = 8;
            // 
            // openButton
            // 
            this.openButton.Location = new System.Drawing.Point(257, 24);
            this.openButton.Name = "openButton";
            this.openButton.Size = new System.Drawing.Size(38, 23);
            this.openButton.TabIndex = 11;
            this.openButton.Text = "打开";
            this.openButton.UseVisualStyleBackColor = true;
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // editButton
            // 
            this.editButton.Location = new System.Drawing.Point(257, 65);
            this.editButton.Name = "editButton";
            this.editButton.Size = new System.Drawing.Size(38, 23);
            this.editButton.TabIndex = 12;
            this.editButton.Text = "编辑";
            this.editButton.UseVisualStyleBackColor = true;
            this.editButton.Click += new System.EventHandler(this.editButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(305, 206);
            this.Controls.Add(this.editButton);
            this.Controls.Add(this.openButton);
            this.Controls.Add(this.userCountText);
            this.Controls.Add(this.pathText);
            this.Controls.Add(this.statusLabel);
            this.Controls.Add(this.read);
            this.Controls.Add(this.login);
            this.Controls.Add(this.path);
            this.Controls.Add(this.setSoft);
            this.MaximizeBox = false;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Robot";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button setSoft;
        private System.Windows.Forms.Label path;
        private System.Windows.Forms.Button login;
        private System.Windows.Forms.Label read;
        private System.Windows.Forms.Label statusLabel;
        private System.Windows.Forms.TextBox pathText;
        private System.Windows.Forms.TextBox userCountText;
        private System.Windows.Forms.Button openButton;
        private System.Windows.Forms.Button editButton;
    }
}

