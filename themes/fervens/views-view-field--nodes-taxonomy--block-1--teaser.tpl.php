<?php
//print_r($row);
//$data = $row->{$field->field_alias};
$find = array('<p>','</p>');
$replace = array('<div>', '</div>');
$cleandata = str_replace($find, $replace, $output);
print $cleandata;
?>
