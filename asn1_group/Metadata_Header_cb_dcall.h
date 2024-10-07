#include <stdint.h>
#include <stdio.h>

void decode_metadata_header(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index);
