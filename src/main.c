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
#include <stdint.h>
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

typedef struct{
  uint32_t iTOW;
  int32_t ECEF_X;
  int32_t ECEF_Y;
  int32_t ECEF_Z;
  uint32_t Pacc;
  uint16_t year;
  uint8_t month, day, hour, min, sec;
  uint8_t valid;
  uint32_t tAcc;
  int32_t nano;
  uint8_t fixType, flags, flags2, numSV;
  int32_t lon, lat, height, hMSL;
  uint32_t hAcc, vAcc;
  int32_t velN, velE, velD, gSpeed, heading;
  uint32_t sAcc, headAcc;
  uint16_t pDOP;
  int32_t headVeh;
  int16_t magDec;
  uint16_t magAcc;
}data;

int NAV_POSECEF(uint8_t *buffer, data *gps);
int NAV_POSLLH(uint8_t *buffer, data *gps);
int NAV_STATUS(uint8_t *buffer, data *gps);
int NAV_DOP(uint8_t *buffer, data *gps);
int NAV_ATT(uint8_t *buffer, data *gps);
int NAV_SOL(uint8_t *buffer, data *gps);
int NAV_PVT(uint8_t *buffer, data *gps);
int NAV_ODO(uint8_t *buffer, data *gps);
int NAV_VELECEF(uint8_t *buffer, data *gps);
int NAV_VELNED(uint8_t *buffer, data *gps);
int NAV_TIMEUTC(uint8_t *buffer, data *gps);
int NAV_CLOCK(uint8_t *buffer, data *gps);
int NAV_TIMEGPS(uint8_t *buffer, data *gps);
int NAV_TIMEGLO(uint8_t *buffer, data *gps);
int NAV_TIMEBDS(uint8_t *buffer, data *gps);
int NAV_TIMEGAL(uint8_t *buffer, data *gps);
int NAV_SVINFO(uint8_t *buffer, data *gps);
int NAV_DGPS(uint8_t *buffer, data *gps);
int NAV_SBAS(uint8_t *buffer, data *gps);
int NAV_ORB(uint8_t *buffer, data *gps);
int NAV_SAT(uint8_t *buffer, data *gps);
int NAV_GEOFENCE(uint8_t *buffer, data *gps);
int NAV_SVIN(uint8_t *buffer, data *gps);
int NAV_RELPOSNED(uint8_t *buffer, data *gps);
int NAV_EELL(uint8_t *buffer, data *gps);

int NAV_PVT(uint8_t *buffer, data *gps)
{
  gps->iTOW  = *(uint32_t *)(buffer);
  gps->year  = *(uint16_t *)(buffer + 4);
  gps->month = *(uint8_t *)(buffer + 6);
  gps->day   = *(uint8_t *)(buffer + 7);
  gps->hour  = *(uint8_t *)(buffer + 8);
  gps->min   = *(uint8_t *)(buffer + 9);
  gps->sec   = *(uint8_t *)(buffer + 10);
  gps->valid = *(uint8_t *)(buffer + 11);
  gps->tAcc  = *(uint32_t *)(buffer + 12);
  gps->nano  = *(int32_t *)(buffer + 16);
  gps->fixType = *(uint8_t *)(buffer + 20);
  gps->flags = *(uint8_t *)(buffer + 21);
  gps->flags2 = *(uint8_t *)(buffer + 22);
  gps->numSV = *(uint8_t *)(buffer + 23);
  gps->lon  = *(int32_t *)(buffer + 24);
  gps->lat  = *(int32_t *)(buffer + 28);
  gps->height = *(int32_t *)(buffer + 32);
  gps->hMSL   = *(int32_t *)(buffer + 36);
  gps->hAcc = *(uint32_t *)(buffer + 40);
  gps->vAcc = *(uint32_t *)(buffer + 44);
  gps->velN = *(int32_t *)(buffer + 48);
  gps->velE = *(int32_t *)(buffer + 52);
  gps->velD = *(int32_t *)(buffer + 56);
  gps->gSpeed = *(int32_t *)(buffer + 60);
  gps->heading = *(int32_t *)(buffer + 64);
  gps->sAcc = *(uint32_t *)(buffer + 68);
  gps->headAcc = *(uint32_t *)(buffer + 72);
  gps->pDOP = *(uint16_t *)(buffer + 76);
  gps->headVeh = *(int32_t *)(buffer + 80);
  gps->magDec = *(int16_t *)(buffer + 84);
  gps->magAcc = *(uint16_t *)(buffer + 86);
}
int check_start_frame(uint8_t a, uint8_t b)
{
  if (a == 0xb5)
    if (b == 0x62)
      return 0;
  return 1;
}
int check_msg_class(uint8_t a)
{
  if (a == 0x01)
    return 0;
  return 1;
}
int decode(uint8_t *buffer, data *gps)
{
switch (buffer[0]) {
    case 0x01: 
      // NAV_POSECEF(buffer, gps);
      break;

    case 0x02:
      // NAV_POSLLH();
      break;

    case 0x03: 
      // NAV_STATUS(); 
      break; 

    case 0x04: 
      // NAV_DOP(); 
      break; 

    case 0x05: 
      // NAV_ATT(); 
      break; 

    case 0x07: 
      NAV_PVT(buffer, gps); 
      break; 

    case 0x09:
      // NAV_VELECEF(); 
      break; 

    case 0x0A:
      // NAV_VELNED(); 
      break; 

    case 0x0D:
      // NAV_TIMEUTC(); 
      break; 

    case 0x27: 
      // NAV_SAT(); 
      break; 

    default:
    return 1;
  }
}

int main()
{
    uint8_t gps_input[] = { 0xB5, 0x62, 0x01, 0x07, 0x5C, 0x00, 0xF8, 0x54, 0x97,
    0x07, 0xE8, 0x07, 0x0B, 0x12, 0x0B, 0x16, 0x14, 0x37, 0x14, 0x00, 0x00,
    0x00, 0xC1, 0xBA, 0xEE, 0x0B, 0x03, 0x01, 0x0A, 0x09, 0x5B, 0xE2, 0xB4,
    0x2F, 0x51, 0x5E, 0xA4, 0x07, 0x5A, 0xC0, 0xFF, 0xFF, 0x1B, 0x18, 0x01,
    0x00, 0x02, 0x13, 0x00, 0x00, 0x1A, 0x29, 0x00, 0x00, 0x7D, 0xFF, 0xFF,
    0xFF, 0x3E, 0x00, 0x00, 0x00, 0x7B, 0xFF, 0xFF, 0xFF, 0x91, 0x00, 0x00,
    0x00, 0x62, 0x48, 0x41, 0x00, 0x6E, 0x04, 0x00, 0x00, 0xE2, 0xF2, 0x3E,
    0x00, 0x38, 0x01, 0x00, 0x00, 0xF8, 0x4A, 0x23, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x51, 0x0D };
  data gps;
  if(check_start_frame(gps_input[0], gps_input[1]))
     return 1;
  if(check_msg_class(gps_input[2]))
    return 1;
  decode(&gps_input[4], &gps);
  printf("GPS Data:\n");
    printf("iTOW: %u\n", gps.iTOW);
    printf("ECEF X: %d, ECEF Y: %d, ECEF Z: %d\n", gps.ECEF_X, gps.ECEF_Y, gps.ECEF_Z);
    printf("Position Accuracy: %u\n", gps.Pacc);
    printf("Timestamp: %04u-%02u-%02u %02u:%02u:%02u\n", 
           gps.year, gps.month, gps.day, gps.hour, gps.min, gps.sec);
    printf("Valid: %u\n", gps.valid);
    printf("Time Accuracy: %u\n", gps.tAcc);
    printf("Nanoseconds: %d\n", gps.nano);
    printf("Fix Type: %u, Flags: %u, Flags2: %u, Satellites: %u\n", 
           gps.fixType, gps.flags, gps.flags2, gps.numSV);
    printf("Longitude: %d, Latitude: %d\n", gps.lon, gps.lat);
    printf("Height: %d, Height MSL: %d\n", gps.height, gps.hMSL);
    printf("Horizontal Accuracy: %u, Vertical Accuracy: %u\n", gps.hAcc, gps.vAcc);
    printf("Velocity N: %d, Velocity E: %d, Velocity D: %d\n", gps.velN, gps.velE, gps.velD);
    printf("Ground Speed: %d, Heading: %d\n", gps.gSpeed, gps.heading);
    printf("Speed Accuracy: %u, Heading Accuracy: %u\n", gps.sAcc, gps.headAcc);
    printf("pDOP: %u\n", gps.pDOP);
    printf("Heading Vehicle: %d\n", gps.headVeh);
    printf("Magnetic Declination: %d, Magnetic Accuracy: %u\n", gps.magDec, gps.magAcc);
}
