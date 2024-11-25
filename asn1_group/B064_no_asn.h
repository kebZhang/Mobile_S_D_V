#include <stdint.h>
#include <stdio.h>
#include "change_byte_sequence.h"

void decode_B064_no_asn(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode);