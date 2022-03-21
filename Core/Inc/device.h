#ifndef DEVICE_H_
#define DEVICE_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint8_t device_adress;
	int8_t velocity;
} device_settings;

void UpdateDeviceSettings(device_settings *device_struct);

#endif /* DEVICE_H_ */
