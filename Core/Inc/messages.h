#ifndef __MESSAGES_H
#define __MESSAGES_H

#include <stdint.h>

#define MAX_BUFFER_LENGTH 20
#define RECEIVE_TIMEOUT                     100

#define MAGIC 0xAA

#define VELOCITY_REQUEST_LENGTH              7
#define VELOCITY_RESPONSE_LENGTH             10

#pragma pack(push, 1)

struct VelocityRequest
{
    uint8_t AA1;
    uint8_t AA2;
    uint8_t address;
    uint8_t setting;
    int8_t velocity1;
    int8_t velocity2;
    uint8_t checksum;
};

struct VelocityResponse
{
    uint8_t AA;
    uint8_t address;
    uint8_t errors;
    uint16_t current1;
    uint16_t current2;
    uint8_t velocity1;
    uint8_t velocity2;
    uint8_t crc;
};

#pragma pack(pop)

#endif //__MESSAGES_H
