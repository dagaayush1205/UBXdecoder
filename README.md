# UBXdecoder
Every frame starts with a 2-byte preamble consisting of two synchronization
characters: 0xb5 0x62.

* a 1-byte message class field follows. a class is a group of messages that are
* related to each other.
*
* a 1-byte message id field defines the message that is to follow.
*
* a 2-byte length field follows. the length is defined as being that of the
* payload only. it does not include the preamble, message class, message id,
* length, or cyclic redundancy check (crc) fields. the number format of the
* length field is a little-endian unsigned 16-bit integer.
*
*the payload field contains a variable number of bytes. in this case we will
*only decode some data and not all which include the following:
*
*the two 1-byte ck_a and ck_b fields hold a 16-bit checksum whose calculation
*is defined below. this concludes the frame.
*/

