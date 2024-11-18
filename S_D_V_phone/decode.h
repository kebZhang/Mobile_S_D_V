#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "./asn1_group/host.h"

static unsigned short calc_crc (unsigned char *data, size_t len, unsigned short crc);
int get_next_frame(char *buffer_read, char *output_frame, int buffer_size, int *current_index, int *crc_correct, int *output_frame_length);
int check_frame_format(char *output_frame);
int find_pkt_type(char *output_frame, int start_index);
void decode(char *buffer_read, int readlen, int offset, int msglen_effect_time[2]);
void computer_timestamp(uint32_t t);