
#ifndef CHECKSUM_H_
#define CHECKSUM_H_

#include <stdint.h>
#include <stdbool.h>

bool IsChecksumm8bCorrect(uint8_t *msg, uint16_t length);
void AddChecksumm8b(uint8_t *msg, uint16_t length);

#endif /* CHECKSUM_H_ */
