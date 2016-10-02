<?php
function c($str)
{
	$a = 0;
	for ($i = 0; $i < strlen($str); $i++)
	{
		if ($str[$i] == '*')
			$a++;
	}
	return ($a);
}

$content = file_get_contents("test");
$lines = explode("\n", $content);
foreach ($lines as $line)
{
	$tab = preg_split("@\t@", $line, NULL, PREG_SPLIT_NO_EMPTY);
	if (strncmp($tab[1], "sys_", 4) == 0)
		$tab[1] = substr($tab[1], 4, strlen($tab[1]) - 4);
	echo "{". (count($tab) - 2) . ", \"" . $tab[1] . "\", {";
	for ($i = 2; $i < count($tab); $i++)
	{
		if ($i != 2)
			echo ", ";
		if (strstr($tab[$i], "char") !== false && c($tab[$i]) == 1)
			echo "PARAM_STRING";
		else if (strstr($tab[$i], "*") !== false)
			echo "PARAM_ADDR";
		else
			echo "PARAM_NUMBER";
	}
	echo "}},\n";
}
?>
