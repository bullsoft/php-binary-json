#!/home/work/local/php/bin/php -q
<?php
error_reporting(E_ALL);

/* Allow the script to hang around waiting for connections. */
set_time_limit(0);

/* Turn on implicit output flushing so we see what we're getting
 * as it comes in. */
ob_implicit_flush();

$address = '10.48.25.160';
$port = 10000;

if (($sock = socket_create(AF_INET, SOCK_STREAM, SOL_TCP)) === false) {
    echo "socket_create() failed: reason: " . socket_strerror(socket_last_error()) . "\n";
}

if (socket_bind($sock, $address, $port) === false) {
    echo "socket_bind() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
}

if (socket_listen($sock, 5) === false) {
    echo "socket_listen() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
}

do {
    if (($msgsock = socket_accept($sock)) === false) {
        echo "socket_accept() failed: reason: " . socket_strerror(socket_last_error($sock)) . "\n";
        break;
    }
    echo "Read head of the message ... " . PHP_EOL;
    
    if (false === ($head = socket_read($msgsock, BINARYJSON_MSG_HEADER_SIZE))) {
        echo "socket_read() failed: reason: " . socket_strerror(socket_last_error($msgsock)) . "\n";
        break 1;
    }
    $headPackArray = binaryjson_header_unpack($head);
    var_dump($headPackArray);

    echo "Read body of the message ... " . PHP_EOL; 
    if(false === ($body = socket_read($msgsock, $headPackArray['length']))) {
        echo "socket_read() failed: reason: " . socket_strerror(socket_last_error($msgsock)) . "\n";
        break 2;
    }
    $bodyPackArray = binaryjson_decode($body);
    var_dump($bodyPackArray);

    $bodyPackArray['hello'] = "hello, world";
    $bodyPackArray['foo']   = "bar, baz";
    $respondMsg = binaryjson_msg_pack($bodyPackArray);
    socket_write($msgsock, $respondMsg, strlen($respondMsg));
    
    socket_close($msgsock);
} while (true);

socket_close($sock);

/* socket_server.php ends here */