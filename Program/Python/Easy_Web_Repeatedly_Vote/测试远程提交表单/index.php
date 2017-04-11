<html>
	<head>
	</head>
	<body>
		<form method="POST" action="submit.php">
			<input type="submit" value="Submit">
		</form>
	</body>
</html>

<?php
	include ("config.php");
	$sql = "SELECT time FROM time";
	$result = mysql_query($sql);
	$row = mysql_fetch_array($result);
	$re = $row['time'];
	echo $re;
?>