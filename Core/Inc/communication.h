#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#include <stdint.h>
#include "messages.h"
#include "device.h"

bool parse_velocity_package(device_settings *device_struct,  uint8_t  *message);
void device_response();


#endif //__COMMUNICATION_H
