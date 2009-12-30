--TEST--
Text_Tokenizer_Regex_Matcher_Ext__addRegex
--SKIPIF--
<?php 

if(!extension_loaded('Text_Tokenizer_Regex_Matcher_Ext')) die('skip ');

 ?>
--FILE--
<?php
dl('Text_Tokenizer_Regex_Matcher_Ext.so');
$a = new Text_Tokenizer_Regex_Matcher_Ext();
var_dump($a->addRegex('xpto'));

?>
--EXPECT--
OK