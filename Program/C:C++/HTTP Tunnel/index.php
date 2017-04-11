<?php
	$result = $_POST['result'];
	
	$myfile = fopen("result.txt", "a") or die("Unable to open file!");
	
	fwrite($myfile, $result);
	fclose($myfile);

?>