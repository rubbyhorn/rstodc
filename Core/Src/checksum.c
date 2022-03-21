
#include "checksum.h"

bool IsChecksumm8bCorrect(uint8_t *msg, uint16_t length)
{
	uint8_t crcGot, crc = 0;
	int i;

	crcGot = msg[length-1] ;

	for (i = 0; i < length - 1; ++i) {
		crc ^= msg[i];
	}

	if (crc == crcGot) {
		return 1;
	}
	else {
		return 0;
	}
}

void AddChecksumm8b(uint8_t *msg, uint16_t length)
{
	uint8_t crc = 0;

	for(int i = 1; i < length - 1; i++) {
		crc ^= msg[i];
	}

	msg[length-1] = crc;
}
