#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.c"
#include "RLC-DL-AM-CONTROL-PDU-S-HEADER.h"
#include "RLC-DL-AM-CONTROL-PDU-PDU.h"
#include "RLC-DL-AM-Control-PDU-E1.h"

// specific header
void convert_S_H(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    // version 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field1 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field1, 1);
        *index += 1;
        *out_index += 1;
    }

    // skip0 3Byte
    if (*index + 3 <= length)
    {
        uint16_t field2 = *(uint16_t *)(hex_data + *index);
        field2 = convert_3_bytes_little_to_big(field2);
        memcpy(output + *out_index, &field2, 3);
        *index += 3;
        *out_index += 3;
    }

    // versions-> num control pdu 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field3 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field3, 1);
        *index += 1;
        *out_index += 1;
    }

    // skip1 3Byte
    if (*index + 3 <= length)
    {
        uint16_t field4 = *(uint16_t *)(hex_data + *index);
        field4 = convert_3_bytes_little_to_big(field4);
        memcpy(output + *out_index, &field4, 3);
        *index += 3;
        *out_index += 3;
    }
}

// pdu structure
void convert_pdu(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    /*systime*/
    //skip2+subfn
    int size=1;
    if (*index + size <= length)
    {
        uint8_t field1 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field1, size);
        *index += size;
        *out_index += size;
    }
    
    //skip3
    size=1;
    if (*index + size <= length)
    {
        uint8_t field2 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field2, size);
        *index += size;
        *out_index += size;
    }

    // skip4+sfn
    size=2;
    if (*index + size <= length)
    {
        uint16_t field3 = *(uint16_t *)(hex_data + *index);
        field3 = convert_2_bytes_little_to_big(field3);
        memcpy(output + *out_index, &field3, size);
        *index += size;
        *out_index += size;
    }

    //skip5
    size=1;
    if (*index + size <= length)
    {
        uint8_t field4 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field4, size);
        *index += size;
        *out_index += size;
    }

    //skip6+ sn_length
    size=1;
    if (*index + size <= length)
    {
        uint8_t field5 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field5, size);
        *index += size;
        *out_index += size;
    }

    //control_pdu_size
    size=1;
    if (*index + size <= length)
    {
        uint8_t field6 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field6, size);
        *index += size;
        *out_index += size;
    }

    //d/c + cpt + skip7
    size=1;
    if (*index + size <= length)
    {
        uint8_t field7 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field7, size);
        *index += size;
        *out_index += size;
    }

    //skip8 + ack_part
    size=1;
    if (*index + size <= length)
    {
        uint8_t field8 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field8, size);
        *index += size;
        *out_index += size;
    }

    //rlcdl-ctrl-dck-sn + e1-exist-flag + e2-exist-flag   
    size=1;
    if (*index + size <= length)
    {
        uint8_t field9 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field9, size);
        *index += size;
        *out_index += size;
    }
}

// specific header
void convert_E1(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    // version 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field1 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field1, 1);
        *index += 1;
        *out_index += 1;
    }
    // versions-> num control pdu 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field3 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field3, 1);
        *index += 1;
        *out_index += 1;
    }
}

// 打印十六进制数据
void print_hex(const uint8_t *data, size_t start, size_t end)
{
    printf("print hex\n");
    for (size_t i = start; i < end; i++)
    {
        printf("%02x", data[i]);
    }
    printf("\n");
}

void decode_B083(const char *b, size_t length)
{
    uint8_t *hex_data = (uint8_t *)b;
    uint8_t *output=NULL;
    output = (uint8_t *)malloc(length); 
    size_t index = 0;
    size_t out_index = 0;

    /*introduce different sub structure*/
    RLC_DL_AM_CONTROL_PDU_S_HEADER_t *t_S_H =0;
    asn_dec_rval_t rval_S_H; /* Decoder return value  */
    RLC_DL_AM_CONTROL_PDU_PDU_t *t_PDU =0;
    asn_dec_rval_t rval_PDU; /* Decoder return value  */
    RLC_DL_AM_CONTROL_PDU_E1_t *t_E1 =0;
    asn_dec_rval_t rval_E1; /* Decoder return value  */



    /*S_H*/
    int start_S_H = index;
    convert_S_H(hex_data,length,output,&index, &out_index);
    int S_H_length = index - start_S_H;
    printf("S_H_Length=%d\n", S_H_length);
    printf("Converted Hex Data: ");
    print_hex(output, 0, index);

    rval_S_H = uper_decode(0, &asn_DEF_RLC_DL_AM_CONTROL_PDU_S_HEADER, (void **)&t_S_H, output+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_RLC_DL_AM_CONTROL_PDU_S_HEADER, t_S_H);   

    /*PDU*/
    int start_PDU = index;
    convert_pdu(hex_data,length,output,&inedx,&out_index);
    int PDU_length = index-start_PDU;
    printf("PDU_Length=%d\n", PDU_length);
    printf("Converted Hex Data: ");
    print_hex(output, start_PDU, index);

    rval_PDU = uper_decode(0, &asn_DEF_RLC_DL_AM_CONTROL_PDU_PDU, (void **)&t_PDU, output+start_PDU, PDU_length, 0, 0);
    if(rval_PDU.code != RC_OK) {
      printf("rval_PDU decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_RLC_DL_AM_CONTROL_PDU_PDU, t_PDU); 

    //E1 exist flag
    int E1_exist_flag =  ((output[17] & 0x03) >> 1 );
    printf("E1_exist_flag=%d\n", E1_exist_flag);
    int E2_exist_flag =  ((output[17] & 0x01));
    printf("E2_exist_flag=%d\n", E2_exist_flag);

    if(E1_exist_flag)
    {
        /*E1结构*/
        int start_E1 = index;
        convert_E1(hex_data,length,output,&inedx,&out_index);
        int E1_length = index-start_E1;
        printf("E1_length=%d\n", E1_length);
        printf("Converted Hex Data: ");
        print_hex(output, start_E1, index);

        rval_E1 = uper_decode(0, &asn_DEF_RLC_DL_AM_CONTROL_PDU_E1, (void **)&t_E1, output+start_E1, E1_length, 0, 0);
        if(rval_E1.code != RC_OK) {
            printf("rval_E1 decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_RLC_DL_AM_CONTROL_PDU_E1, t_E1); 
    }

    /*目前没有E2子结构数据*/
    if(E2_exist_flag)
    {
        printf("warning E2 exist flag=1\n");
    }
}