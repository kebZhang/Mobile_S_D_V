#include <stdio.h>
#include <stdint.h>
#include "DCIReport.h"
#include "RecordHeader.h"
#include "DCIUL.h"
#include "DCIDL.h"


// 将2字节的小端整数转换为大端
uint16_t convert_2_bytes_little_to_big(uint16_t little_endian)
{
    return (little_endian >> 8) | (little_endian << 8);
}

// 将3字节的小端整数转换为大端
uint32_t convert_3_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x0000FF) << 16) | // 提取第1个字节并移到最高位
           ((little_endian & 0x00FF00)) |       // 保持中间的字节不变
           ((little_endian & 0xFF0000) >> 16);  // 提取第3个字节并移到最低位
}

// 函数：将4字节的小端整数转换为大端
uint32_t convert_4_bytes_little_to_big(uint32_t little_endian)
{
    return ((little_endian & 0x000000FF) << 24) |
           ((little_endian & 0x0000FF00) << 8) |
           ((little_endian & 0x00FF0000) >> 8) |
           ((little_endian & 0xFF000000) >> 24);
}

// 函数：将8字节的小端整数转换为大端
uint64_t convert_8_bytes_little_to_big(uint64_t little_endian)
{
    return ((little_endian & 0x00000000000000FF) << 56) |
           ((little_endian & 0x000000000000FF00) << 40) |
           ((little_endian & 0x0000000000FF0000) << 24) |
           ((little_endian & 0x00000000FF000000) << 8) |
           ((little_endian & 0x000000FF00000000) >> 8) |
           ((little_endian & 0x0000FF0000000000) >> 24) |
           ((little_endian & 0x00FF000000000000) >> 40) |
           ((little_endian & 0xFF00000000000000) >> 56);
}

// Metadata header
void convert_M_H(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
{
    // 2 byte msg_len
    // if (*index + 2 <= length)
    // {
    //     uint16_t field1 = *(uint16_t *)(hex_data + *index);
    //     field1 = convert_2_bytes_little_to_big(field1);
    //     memcpy(output + *out_index, &field1, 2);
    //     *index += 2;
    //     *out_index += 2;
    // }

    // 2 byte typeid
    // if (*index + 2 <= length)
    // {
    //     uint16_t field2 = *(uint16_t *)(hex_data + *index);
    //     field2 = convert_2_bytes_little_to_big(field2);
    //     memcpy(output + *out_index, &field2, 2);
    //     *index += 2;
    //     *out_index += 2;
    // }

    // 8 byte timestamp
    // if (*index + 8 <= length)
    // {
    //     uint64_t field3 = *(uint64_t *)(hex_data + *index);
    //     field3 = convert_8_bytes_little_to_big(field3);
    //     memcpy(output + *out_index, &field3, 8);
    //     *index += 8;
    //     *out_index += 8;
    // }

    // 处理1字节的字段
    if (*index + 1 <= length)
    {
        uint8_t field4 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field4, 1);
        *index += 1;
        *out_index += 1;
    }

    // 处理2字节的字段
    if (*index + 2 <= length)
    {
        uint16_t field5 = *(uint16_t *)(hex_data + *index);
        field5 = convert_2_bytes_little_to_big(field5);
        memcpy(output + *out_index, &field5, 2);
        *index += 2;
        *out_index += 2;
    }

    // 处理1字节的字段
    if (*index + 1 <= length)
    {
        uint8_t field6 = *(uint8_t *)(hex_data + *index);
        memcpy(output + *out_index, &field6, 1);
        *index += 1;
        *out_index += 1;
    }
}

// 函数：解析和转换字节序并返回修改后的十六进制数据
void convert_R_H(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
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


void convert_UL(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
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
void convert_DL(const uint8_t *hex_data, size_t length, uint8_t *output, size_t *index, size_t *out_index)
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

// 将输出数据写入文件
void write_data_to_file(const char *filename, const uint8_t *data, size_t length)
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        perror("Failed to open file");
        return;
    }

    fwrite(data, 1, length, file);
    fclose(file);
}

int main()
{
    char *filename="data.dat";      /* Input file name */
    FILE *fp;         
    size_t size;         /* Number of bytes read  */ 
    size_t file_size;
    // char buf[1024];      /* Temporary buffer      */ 


    uint8_t *hex_data = NULL; /*input pointer*/
    uint8_t *output = NULL;
    size_t index = 0;
    size_t out_index = 0;

    /*引入不同的子结构*/
    DCIReport_t *t =0;
    asn_dec_rval_t rval; /* Decoder return value  */
    RecordHeader_t *t1 =0;
    asn_dec_rval_t rval1; 
    DCIUL_t *t2 =0;
    asn_dec_rval_t rval2;
    DCIDL_t *t3 =0;
    asn_dec_rval_t rval3;



    fp = fopen(filename, "rb");
    if(!fp) {
      perror(filename);
      exit(66); /* better, EX_NOINPUT */
    }

    //获取大小
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* 分配缓冲区以读取文件内容 */
    hex_data = (uint8_t *)malloc(file_size);  
    output = (uint8_t *)malloc(file_size); 
    if (!hex_data) {
        perror("malloc");
        fclose(fp);
        return -1;
    }

    /* 读取文件内容到缓冲区 */
    if (fread(hex_data, 1, file_size, fp) != file_size) {
        perror("fread");
        free(hex_data);
        fclose(fp);
        return -1;
    }

    fclose(fp);

    //M_H
    convert_M_H(hex_data, file_size, output, &index, &out_index);
    int M_H_length = index;
    printf("M_H_Length=%d\n", M_H_length);
    printf("Converted Hex Data: ");
    print_hex(output, 0, M_H_length);
    write_data_to_file("data_mh.dat", output, M_H_length);

    rval = uper_decode(0, &asn_DEF_DCIReport, (void **)&t, output, M_H_length, 0, 0);
    if(rval.code != RC_OK) {
      fprintf(stderr,
        "%s: ravl %ld\n",
        filename, (long)rval.consumed);
      exit(65); /* better, EX_DATAERR */
    }
    //xml输出结构
    xer_fprint(stdout, &asn_DEF_DCIReport, t);

    int num_of_records = ((output[1] & 0x07) << 2) | ((output[2] & 0xC0) >> 6);
    printf("num of records=%d\n", num_of_records);

    for(int i=0;i<num_of_records;i++)
    {
        //R_H
        int temp_start_R_H = index;
        convert_R_H(hex_data, file_size, output, &index, &out_index);
        int R_H_length = index-temp_start_R_H;
        print_hex(output, temp_start_R_H,index);
        write_data_to_file("data_rh.dat",output+temp_start_R_H,R_H_length);
        
        rval1 = uper_decode(0, &asn_DEF_RecordHeader, (void **)&t1, output+temp_start_R_H, R_H_length, 0, 0);
        if(rval1.code != RC_OK) {
        fprintf(stderr,
            "%s: ravl1 %ld\n",
            filename, (long)rval.consumed);
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
            int temp_start_UL = index;
            convert_UL(hex_data, file_size, output, &index, &out_index);
            int U_L_length = index - temp_start_UL;
            print_hex(output, temp_start_UL, index);
            write_data_to_file("data_ul.dat", output+temp_start_UL, U_L_length);
            rval2 = uper_decode(0, &asn_DEF_DCIUL, (void **)&t2, output+temp_start_UL, U_L_length, 0, 0);
            if(rval2.code != RC_OK) {
            fprintf(stderr,
                "%s: ravl2 %ld\n",
                filename, (long)rval.consumed);
            exit(67); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIUL, t2);
        }

        //dl
        for(int j=0;j<num_of_dl;j++)
        {
            int temp_start_DL = index;
            convert_DL(hex_data, file_size, output, &index, &out_index);
            int D_L_length = index - temp_start_DL;
            print_hex(output, temp_start_DL, index);
            write_data_to_file("data_dl.dat", output+temp_start_DL, D_L_length);
            rval3 = uper_decode(0, &asn_DEF_DCIDL, (void **)&t3, output+temp_start_DL, D_L_length, 0, 0);
            if(rval3.code != RC_OK) {
            fprintf(stderr,
                "%s: ravl3 %ld\n",
                filename, (long)rval.consumed);
            exit(68); /* better, EX_DATAERR */
            }
            xer_fprint(stdout, &asn_DEF_DCIDL, t3);
        }
    }
    return 0;

}