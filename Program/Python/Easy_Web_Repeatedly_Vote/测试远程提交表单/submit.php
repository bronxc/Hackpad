<?php
	include ("config.php");
	$sql = "SELECT time FROM time";
	$result = mysql_query($sql);
	$row = mysql_fetch_array($result);
	$re = $row['time'];
	$re = $re + 1;
	echo $re;
	$up = "update time set time='$re' where id=1";
	//sql="update ���ݱ� set �ֶ���=�ֶ�ֵ where �������ʽ"
	mysql_query($up);
	mysql_close();
	echo "<script>location.href='index.php';</script>";
?>