<?php
$arr1 = array("我们才是年轻的一代", "hello" => "world");
echo "============Raw Array==========". PHP_EOL;
var_dump($arr1);
echo "=======Binary Json Encode======". PHP_EOL;
$arr1Enc = binaryjson_encode($arr1);
var_dump($arr1Enc);
echo "=======Binary Json Encode Hex======". PHP_EOL;
echo bin2hex($arr1Enc);
echo PHP_EOL;
echo "=======Binary Json Decode======".PHP_EOL;
$arr1Dec = binaryjson_decode($arr1Enc);
var_dump($arr1Dec);
echo "===========Pack Head===========". PHP_EOL;
$packHead = binaryjson_header_pack(BINARYJSON_HEADER_OP_MSG);
var_dump($packHead);
echo "==========Unpack Head==========" . PHP_EOL;
$unPackHead = binaryjson_header_unpack($packHead);
var_dump($unPackHead);
echo "============Pack Msg===========". PHP_EOL;
$pack = binaryjson_msg_pack($arr1, BINARYJSON_HEADER_OP_MSG);
var_dump($pack);
echo "======Get Head From Pack Msg=======". PHP_EOL;
$head = substr($pack, 0, BINARYJSON_MSG_HEADER_SIZE);
$headArr = binaryjson_header_unpack($head);
var_dump($headArr);
echo "======Get Body From Pack Msg=======". PHP_EOL;
$body = substr($pack, BINARYJSON_MSG_HEADER_SIZE, $headArr['length']);
$bodyArr = binaryjson_decode($body);
var_dump($bodyArr);
echo "===========Unpack Msg==========" . PHP_EOL;
var_dump(binaryjson_msg_unpack($pack));


echo "===========Obj Encode==========" . PHP_EOL;
$obj1 = new stdClass();
$obj1->foo = "bar";
$obj1->hello = "world";

$packObj = binaryjson_encode($obj1);
var_dump($packObj);
var_dump(binaryjson_decode($packObj));