--TEST--
Text_Tokenizer_Regex_Matcher_Ext basic test
--FILE--
<?php
dl('Text_Tokenizer_Regex_Matcher_Ext.so');
$a = new Text_Tokenizer_Regex_Matcher_Ext();
var_dump($a->setInput('xpto'));
?>
--EXPECT--
OK
