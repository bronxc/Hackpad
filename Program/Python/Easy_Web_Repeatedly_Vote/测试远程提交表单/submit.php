<?php
	include ("config.php");
	$sql = "SELECT time FROM time";
	$result = mysql_query($sql);
	$row = mysql_fetch_array($result);
	$re = $row['time'];
	$re = $re + 1;
	echo $re;
	$up = "update time set time='$re' where id=1";
	//sql="update 数据表 set 字段名=字段值 where 条件表达式"
	mysql_query($up);
	mysql_close();
	echo "<script>location.href='index.php';</script>";
?>