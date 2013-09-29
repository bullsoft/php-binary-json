php binary json
=======

A simple data serializer in C, wrapped in php extension


Test Conditions
-----------

Hackintosh laptop: i3 2.2Ghz, 4GB of RAM, over TCP on localhost.

Message count: 100,000 messages

Test Results for one field

"msgid" as a name, with the message number as the value

BSON
----
 - Average per message encoding: 1140 ns 
 - Average per message decoding: 245 ns
 - Average Bytes per message: 16 bytes

Protobuf
----
 - Average per message encoding: 3981 ns
 - Average per message decoding: 4036 ns
 - Average Bytes per message: 15 bytes

YAML
----
 - Average per message encoding: 244490 ns
 - Average per message decoding: 412915 ns
 - Average Bytes per message: Not recorded
 - Test Results for 2 fields

Putting in two numbers, in random field order and sending to the server.

BSON
----
 - Average per message encoding: Not recorded
 - Average per message decoding: 299 ns
 - Average Bytes per message: 32 bytes

Protobuf
----
 - Average per message encoding: Not recorded
 - Average per message decoding: 7422 ns
 - Average Bytes per message: 57 bytes

YAML
----
 - Average per message encoding: Not recorded
 - Average per message decoding: 316531 ns
 - Average Bytes per message: 32 bytes
 - Test results for 50 fields

Putting in 50 fields, randomly sorted, each with a number consisting of the current message id multiplied by the index of the shuffled field name array. Decoding time includes access to "field_1" which is in a random location within the entire data set.

BSON
----
 - Average per message encoding: 14196 ns
 - Average per message decoding: 302 ns
 - Average Bytes per message: 695 bytes

Protobuf
----
 - Average per message encoding: 110480 ns
 - Average per message decoding: 106609 ns
 - Average Bytes per message: 695 bytes

YAML
----
 - Average per message encoding: 7135667 ns
 - Average per message decoding: 4893947 ns
 - Average Bytes per message: 853 bytes
