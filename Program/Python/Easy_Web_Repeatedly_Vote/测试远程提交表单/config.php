<?php
$con = mysql_connect("127.0.0.1","root","");
if(!$con)
{
	die("���ݿ����������ʧ��");
}
mysql_query("set names utf8");
mysql_select_db("xx",$con);
?>