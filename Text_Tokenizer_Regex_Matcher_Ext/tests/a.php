<?php
dl('Text_Tokenizer_Regex_Matcher_Ext.so');
$a = new Text_Tokenizer_Regex_Matcher_Ext();
var_dump($a->addRegex('_._'));
var_dump($a->addRegex('_.._'));
var_dump($a->addRegex('_..._'));
var_dump($a->setSelectionCriteria(2));
var_dump($a->setInput('123456789abcdefg'));
while ($t = $a->match()) {
    var_dump($t);
    $a->consume(strlen($t['value']));
}

?>
