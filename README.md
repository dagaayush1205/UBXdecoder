## *UBX format*
* Every frame starts with a 2-byte preamble consisting of two synchronization
characters: 0xb5 0x62.

* a 1-byte message class field follows. a class is a group of messages that are related to each other.

* a 1-byte message id field defines the message that is to follow.

* a 2-byte length field follows. the length is defined as being that of the payload only. it does not include the preamble, message class, message id, length, or cyclic redundancy check (crc) fields. the number format of the length field is a little-endian unsigned 16-bit integer.

* the payload field contains a variable number of bytes. in this case we will only decode some data and not all which include the following:

* the two 1-byte ck_a and ck_b fields hold a 16-bit checksum whose calculation is defined below. this concludes the frame.

## *UBX Checksum*

The checksum is calculated over the Message, starting and including the CLASS field up until, but
excluding, the Checksum Field. The checksum algorithm used is the 8-Bit Fletcher Algorithm, which is used in the TCP standard (RFC 1145).

The algorithm works as follows: 
* Buffer[N] contains the data over which the checksum is to be calculated.

* The two CK_ values are 8-Bit unsigned integers only! If implementing with larger-sized integer
values, make sure to mask both CK_A and CK_B with 0xFF after both operations in the loop.

'''
CK_A = 0, CK_B = 0
For(I=0;I<N;I++)
{
  CK_A = CK_A + Buffer[I]
  CK_B = CK_B + CK_A
}
'''

* After the loop, the two U1 values contain the checksum, transmitted after the Message, which
conclude the Frame.
