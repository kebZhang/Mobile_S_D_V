#include <stdint.h>
#include <stdio.h>
#include "MetadataHeader.h"
#include "change_byte_sequence.c"

void convert_M_H(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    /*convert byte sequence*/
    int size=2;
    //msg_len
    if (*index + size <= length)
    {
        uint16_t field1 = *(uint16_t *)(hex_data + *index);
        field1 = convert_2_bytes_little_to_big(field1);
        memcpy(output + *out_index, &field1, size);
        *index += size;
        *out_index += size;
    }

    //logcode
    size=2;
    if (*index + size <= length)
    {
        uint16_t field2 = *(uint16_t *)(hex_data + *index);
        field2 = convert_2_bytes_little_to_big(field2);
        memcpy(output + *out_index, &field2, size);
        *index += size;
        *out_index += size;
    }

    //timestamp
    size=8;
    if (*index + size <= length)
    {
        uint16_t field3 = *(uint16_t *)(hex_data + *index);
        field3 = convert_8_bytes_little_to_big(field3);
        memcpy(output + *out_index, &field3, size);
        *index += size;
        *out_index += size;
    }
}

void decode_metadata_header(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    Metadata_Header_t *t_M_H =0;
    asn_dec_rval_t rval_M_H; /* Decoder return value  */
    /*convert byte sequence*/
    int start_M_H = index;
    convert_M_H(hex_data,length,output,index,out_index);

    /*asn1c decode*/
    int M_H_Length = index-start_M_H;
    printf("Converted Hex Data: \n");
    print_hex(output, 0, M_H_Length);
    rval_M_H = uper_decode(0, &asn_DEF_Metadata_Header, (void **)&t_M_H, output+start_M_H, M_H_length, 0, 0);
    if(rval_M_H.code != RC_OK) {
        printf("rval_M_H decode error\n");
        exit(65); /* better, EX_DATAERR */
    }
    //xml输出结构
    xer_fprint(stdout, &asn_DEF_Metadata_Header, t_M_H);
}