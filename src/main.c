/* 
* every frame starts with a 2-byte preamble consisting of two synchronization
* characters: 0xb5 0x62.
*
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
#include <stdio.h>

char gps_message;

// int sync(int gps[2])
// {
//   if (gps[0] == 0xb5)
//     if(gps[1] == 0x62)
//       return 0;
//   else return 1;
// }
//
// int msgtype(int class_id[2])
// {
//   if (class_id[0] == 0x01)
//     NAV(class_id[1]);
// }
//
// int NAV(int NAV_type)
// {
//   if (NAV_type == 0x05)
//   {
//     return 32;0x
//   }
// }

int NAV_POSECEF();
int NAV_POSLLH();
int NAV_STATUS();
int NAV_DOP();
int NAV_ATT();
int NAV_SOL();
int NAV_PVT();
int NAV_ODO();
int NAV_VELECEF();
int NAV_VELNED();
int NAV_TIMEUTC();
int NAV_CLOCK();
int NAV_TIMEGPS();
int NAV_TIMEGLO();
int NAV_TIMEBDS();
int NAV_TIMEGAL();
int NAV_SVINFO();
int NAV_DGPS();
int NAV_SBAS();
int NAV_ORB();
int NAV_SAT();
int NAV_GEOFENCE();
int NAV_SVIN();
int NAV_RELPOSNED();
int NAV_EELL();

int check_start_frame(char a, char b)
{
  if (a == 0xb5)
    if (b == 0x62)
      return 0;
  return 1;
}
int check_msg_class(char a)
{
  if (a == 0x01)
    return 0;
  return 1;
}
int check_msg_id(char a)
{
switch (a) {
    case 0x01: 
      NAV_POSECEF();
      break;

    case 0x02:
      NAV_POSLLH();
      break;

    case 0x03: 
      NAV_STATUS(); 
      break; 
    
    case 0x04: 
      NAV_DOP(); 
      break; 
    
    case 0x05: 
      NAV_ATT(); 
      break; 
    
    case 0x07: 
      NAV_PVT(); 
      break; 
    
    case 0x09:
      NAV_VELECEF(); 
      break; 
    
    case 0x0A:
      NAV_VELNED(); 
      break; 
    
    case 0x0D:
      NAV_TIMEUTC(); 
      break; 
    
    case 0x27: 
      NAV_SAT(); 
      break; 
    
    default:
    return 1;
  }
}

NAV_POSECEF(char a[20])
{

}
int main()
{
unsigned char data[] = { 0xB5, 0x62, 0x01, 0x07, 0x5C, 0x00, 0xF8, 0x54, 0x97,
    0x07, 0xE8, 0x07, 0x0B, 0x12, 0x0B, 0x16, 0x14, 0x37, 0x14, 0x00, 0x00,
    0x00, 0xC1, 0xBA, 0xEE, 0x0B, 0x03, 0x01, 0x0A, 0x09, 0x5B, 0xE2, 0xB4,
    0x2F, 0x51, 0x5E, 0xA4, 0x07, 0x5A, 0xC0, 0xFF, 0xFF, 0x1B, 0x18, 0x01,
    0x00, 0x02, 0x13, 0x00, 0x00, 0x1A, 0x29, 0x00, 0x00, 0x7D, 0xFF, 0xFF,
    0xFF, 0x3E, 0x00, 0x00, 0x00, 0x7B, 0xFF, 0xFF, 0xFF, 0x91, 0x00, 0x00,
    0x00, 0x62, 0x48, 0x41, 0x00, 0x6E, 0x04, 0x00, 0x00, 0xE2, 0xF2, 0x3E,
    0x00, 0x38, 0x01, 0x00, 0x00, 0xF8, 0x4A, 0x23, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x51, 0x0D };

  if(check_start_frame(data[0], data[1])
     return 0;
  if(check_msg_class(data[3]))
    return 0;


}
