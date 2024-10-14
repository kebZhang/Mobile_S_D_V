#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "Metadata_Header_cb_dcall.h"
#include "B16C_cb_dcall.h"
#include "B083_cb_dcall.h"
#include "B0A1_cb_dcall.h"
#include "B0B6_cb_dcall.h"
#include "B0CD_cb_dcall.h"
#include "B116_cb_dcall.h"
#include "B12A_cb_dcall.h"
#include "B167_cb_dcall.h"
#include "B168_cb_dcall.h"
#include "B169_cb_dcall.h"

long get_file_size(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        return -1; // 打开文件失败，返回-1
    }

    // 移动文件指针到文件末尾
    fseek(file, 0, SEEK_END);
    long size = ftell(file); // 获取当前位置（文件长度）
    fclose(file);

    return size;
}



int main(int argc, char *argv[]) 
{
    if (argc != 3) {
        printf("Usage: %s <filename> <logcode:Bxxx>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    const char *input_logcode = argv[2];
    printf("File: %s\n", filename);
    printf("input log code: %s\n", input_logcode);

    // get file size
    long file_size = get_file_size(filename);
    if (file_size == -1) {
        printf("Failed to get file size.\n");
        return 1;
    }
    printf("File size: %ld bytes\n", file_size);

    //open file
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }

    //buffer malloc
    uint8_t *hex_data = NULL; /*input pointer*/
    uint8_t *output = NULL;
    size_t index=0;
    size_t out_index=0;
    hex_data = (uint8_t *)malloc(file_size);  
    output = (uint8_t *)malloc(file_size); 

    
    //read to buffer
    if (fread(hex_data, 1, file_size, fp) != file_size) {
        perror("fread");
        free(hex_data);
        fclose(fp);
        return -1;
    }
    printf("filesize =%d\n",file_size);
    // decode Metadata header
    decode_metadata_header(hex_data, file_size, output, &index, &out_index);
    
    printf("index after decode M_H=%d\n",index);

    //get logcode
    uint16_t logcode = (output[2] << 8) | output[3];
    switch(logcode)
    {
        case 0xB083:
        {
            printf("into B083 branch\n");
            decode_B083(hex_data, file_size, output, &index, &out_index);
            return 0;
        }
        case 0xB16C:
        {
            printf("into B16C branch\n");
            decode_B16C(hex_data, file_size, output, &index, &out_index);
            return 1;
        }
        case 0xB0A1:
        {
            printf("into B0A1 branch\n");
            decode_B0A1(hex_data, file_size, &index);
            return 2;
        }
        case 0xB0B6:
        {
            printf("into B0B6 branch\n");
            decode_B0B6(hex_data, file_size, &index);
            return 3;
        }
        case 0xB0CD:
        {
            printf("into B0CD branch\n");
            decode_B0CD(hex_data, file_size, &index);
            
            return 4;
        }
        case 0xB116:
        {
            printf("into B116 branch\n");
            decode_B116(hex_data, file_size, &index);
            return 5;
        }
        case 0xB12A:
        {
            printf("into B12A branch\n");
            decode_B12A(hex_data, file_size, &index);
            return 6;
        }
        case 0xB144:
        {
            printf("into B144 branch\n");
            decode_B144(hex_data, file_size, &index);
            return 7;
        }
        case 0xB167:
        {
            printf("into B167 branch\n");
            decode_B167(hex_data, file_size, &index);
            return 8;
        }
        case 0xB168:
        {
            printf("into B168 branch\n");
            decode_B168(hex_data, file_size, &index);
            return 9;
        }
        case 0xB169:
        {
            printf("into B169 branch\n");
            decode_B169(hex_data, file_size, &index);
            return 10;
        }
        default:
        {
            printf("over\n");
            return 999;
        }
    }


    // 关闭文件
    fclose(fp);

    return 0;
}

