#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "DCIReport.h"
#include "RecordHeader.h"
#include "DCIUL.h"
#include "DCIDL.h"
#include "B16C_cb_dcall.h"


// Metadata header
void convert_S_H_B16C(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    int size=1;
    // 处理1字节的字段
    if ((*index) + size <= length)
    {
        uint8_t field4 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field4, size);
        *index += size;
        *out_index += size;
    }

    // 处理2字节的字段
    size=2;
    if (*index + size <= length)
    {
        uint16_t field5 = *(uint16_t *)(hex_data + *index);
        field5 = convert_2_bytes_little_to_big(field5);
        memcpy(output + *out_index, &field5, size);
        *index += size;
        *out_index += size;
    }

    // 处理1字节的字段
    size=1;
    if (*index + size <= length)
    {
        uint8_t field6 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field6, size);
        *index += size;
        *out_index += size;
    }
}

// 函数：解析和转换字节序并返回修改后的十六进制数据
void convert_R_H_B16C(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    if (*index + 4 <= length)
    {
        uint32_t field7 = *(uint32_t *)(hex_data + *index);
        //printf("field7 (big-endian) = 0x%x\n", field7);  // 以十六进制格式输出
        field7 = convert_4_bytes_little_to_big(field7);
        memcpy(output + *out_index, &field7, 4);
        *index += 4;
        *out_index += 4;
        // 输出 field7 的内容
        //printf("field7 (big-endian) = 0x%x\n", field7);  // 以十六进制格式输出
    }
}


void convert_UL_B16C(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field1 = *(uint16_t *)(hex_data + *index);
        field1 = convert_2_bytes_little_to_big(field1);
        memcpy(output + *out_index, &field1, 2);
        *index += 2;
        *out_index += 2;
    }

    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field2 = *(uint16_t *)(hex_data + *index);
        field2 = convert_2_bytes_little_to_big(field2);
        memcpy(output + *out_index, &field2, 2);
        *index += 2;
        *out_index += 2;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field3 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field3, 1);
        *index += 1;
        *out_index += 1;
    }

    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field4 = *(uint16_t *)(hex_data + *index);
        field4 = convert_2_bytes_little_to_big(field4);
        memcpy(output + *out_index, &field4, 2);
        *index += 2;
        *out_index += 2;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field5 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field5, 1);
        *index += 1;
        *out_index += 1;
    }

    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field6 = *(uint16_t *)(hex_data + *index);
        field6 = convert_2_bytes_little_to_big(field6);
        memcpy(output + *out_index, &field6, 2);
        *index += 2;
        *out_index += 2;
    }

    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field7 = *(uint16_t *)(hex_data + *index);
        field7 = convert_2_bytes_little_to_big(field7);
        memcpy(output + *out_index, &field7, 2);
        *index += 2;
        *out_index += 2;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field8 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field8, 1);
        *index += 1;
        *out_index += 1;
    }

    //below are useless, just because there are 3 bytes below
    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field9 = *(uint16_t *)(hex_data + *index);
        field9 = convert_2_bytes_little_to_big(field9);
        memcpy(output + *out_index, &field9, 2);
        *index += 2;
        *out_index += 2;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field10 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field10, 1);
        *index += 1;
        *out_index += 1;
    }
}


//DL decode
void convert_DL_B16C(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    // 2 Byte
    if (*index + 2 <= length)
    {
        uint16_t field1 = *(uint16_t *)(hex_data + *index);
        field1 = convert_2_bytes_little_to_big(field1);
        memcpy(output + *out_index, &field1, 2);
        *index += 2;
        *out_index += 2;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field2 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field2, 1);
        *index += 1;
        *out_index += 1;
    }

    //4 Byte
    if (*index + 4 <= length)
    {
        uint32_t field4 = *(uint32_t *)(hex_data + *index);
        field4 = convert_4_bytes_little_to_big(field4);
        memcpy(output + *out_index, &field4, 4);
        *index += 4;
        *out_index += 4;
    }

    // 1 Byte
    if (*index + 1 <= length)
    {
        uint8_t field5 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field5, 1);
        *index += 1;
        *out_index += 1;
    }

}





void decode_B16C(uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    /*引入不同的子结构*/
    DCIReport_t *t =0;
    asn_dec_rval_t rval; /* Decoder return value  */
    RecordHeader_t *t1 =0;
    asn_dec_rval_t rval1; 
    DCIUL_t *t2 =0;
    asn_dec_rval_t rval2;
    DCIDL_t *t3 =0;
    asn_dec_rval_t rval3;


    //S_H
    int start_S_H = *index;
    printf("start_S_H=%d\n",start_S_H);
    convert_S_H_B16C(hex_data, length, output, index, out_index);
    int S_H_length = *index - start_S_H;
    printf("S_H_length=%d\n", S_H_length);
    printf("Converted Hex Data: ");
    print_hex(output, start_S_H, *index);

    rval = uper_decode(0, &asn_DEF_DCIReport, (void **)&t, output+start_S_H, S_H_length, 0, 0);
    if(rval.code != RC_OK) {
        printf("rval_S_H decode error\n");
        exit(65); /* better, EX_DATAERR */
    }
    //xml输出结构
    xer_fprint(stdout, &asn_DEF_DCIReport, t);

    int num_of_records = ((output[start_S_H+1] & 0x07) << 2) | ((output[start_S_H+2] & 0xC0) >> 6);
    printf("num of records=%d\n", num_of_records);

    for(int i=0;i<num_of_records;i++)
    {
        //R_H
        int temp_start_R_H = *index;
        convert_R_H_B16C(hex_data, length, output, index, out_index);
        int R_H_length = *index-temp_start_R_H;
        print_hex(output, temp_start_R_H,*index);
        // write_data_to_file("data_rh.dat",output+temp_start_R_H,R_H_length);
        
        rval1 = uper_decode(0, &asn_DEF_RecordHeader, (void **)&t1, output+temp_start_R_H, R_H_length, 0, 0);
        if(rval1.code != RC_OK) {
            printf("rval_R_H decode error\n");
            exit(66); /* better, EX_DATAERR */
        }
        xer_fprint(stdout, &asn_DEF_RecordHeader, t1);

        int num_of_ul = ((output[temp_start_R_H+1] & 0x01)<<2) | ((output[temp_start_R_H+2] & 0xC0)>>6);
        int num_of_dl = ((output[temp_start_R_H+1] & 0x0E)>>1);
        printf("NUM OF DL=%d\n",num_of_dl);
        printf("num of Ul=%d\n", num_of_ul);

        //ul
        for(int j=0;j<num_of_ul;j++)
        {
            int temp_start_UL = *index;
            convert_UL_B16C(hex_data, length, output, index, out_index);
            int U_L_length = *index - temp_start_UL;
            print_hex(output, temp_start_UL, *index);
            // write_data_to_file("data_ul.dat", output+temp_start_UL, U_L_length);
            rval2 = uper_decode(0, &asn_DEF_DCIUL, (void **)&t2, output+temp_start_UL, U_L_length, 0, 0);
            if(rval2.code != RC_OK) {
                printf("rval_UL decode error\n");
                exit(67); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIUL, t2);
        }

        //dl
        for(int j=0;j<num_of_dl;j++)
        {
            int temp_start_DL = *index;
            convert_DL_B16C(hex_data, length, output, index, out_index);
            int D_L_length = *index - temp_start_DL;
            print_hex(output, temp_start_DL, *index);
            // write_data_to_file("data_dl.dat", output+temp_start_DL, D_L_length);
            rval3 = uper_decode(0, &asn_DEF_DCIDL, (void **)&t3, output+temp_start_DL, D_L_length, 0, 0);
            if(rval3.code != RC_OK) {
                printf("rval_DL decode error\n");
                exit(68); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIDL, t3);
        }
    }
}