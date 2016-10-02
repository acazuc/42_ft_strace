<?php
$content = file_get_contents("srcs/syscalls_init.c");
$lines = explode("\n", $content);
for($i = 0; $i < 7; $i++)
	unset($lines[$i]);
for ($i = 320; $i < 328; $i++)
	unset($lines[$i]);
$syscalls = array();
foreach ($lines as $key => $val)
{
	$lines[$key] = substr($val, 1, strlen($val) - 4);
	$ex = explode(",", $lines[$key]);
	$syscalls[$key] = array("number" => $ex[0], "name" => substr($ex[1], 1, strlen($ex[1]) - 1));
	echo exec("man 2 ".$syscalls[$key]["name"]." | grep \"".$syscalls[$key]["name"]."(\" | head -n 1")."\n";
}
//print_r($syscalls);
?>
