<?php
error_reporting(E_ALL);
echo "TCP/IP Connection\n";
$service_port = 10000;
$address = '10.48.25.160';

/* Create a TCP/IP socket. */
$socket = socket_create(AF_INET, SOCK_STREAM, SOL_TCP);
if ($socket === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
} else {
    echo "OK.\n";
}

echo "Attempting to connect to '$address' on port '$service_port'...";
$result = socket_connect($socket, $address, $service_port);
if ($result === false) {
    echo "socket_connect() failed.\nReason: ($result) " . socket_strerror(socket_last_error($socket)) . "\n";
} else {
    echo "OK.\n";
}
$msgArr = array(
    "hello" => "world",
    "foo"   => "bar"
);
$in = binaryjson_msg_pack($msgArr, BINARYJSON_HEADER_OP_MSG);
echo "Sending request...";
socket_write($socket, $in, strlen($in));
echo "OK.\n";

echo "Reading response:\n\n";
$headPack = socket_read($socket, BINARYJSON_MSG_HEADER_SIZE);
$headPackArray = binaryjson_header_unpack($headPack);
var_dump($headPackArray);

$bodyPack = socket_read($socket, $headPackArray['length']);
var_dump(binaryjson_decode($bodyPack));

echo "Closing socket...";
socket_close($socket);
echo "OK.\n\n";