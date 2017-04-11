<?php
$con = mysql_connect("127.0.0.1","root","");
if(!$con)
{
	die("数据库服务器连接失败");
}
mysql_query("set names utf8");
mysql_select_db("xx",$con);
?>