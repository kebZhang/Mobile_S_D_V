#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "change_byte_sequence.c"
#include "Metadata_Header_cb_dcall.c"
#include "B16c_cb_dcall.c"
#include "B083_cb_dcall.c"


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
    // decode Metadata header
    decode_metadata_header(hex_data, file_size, output, &index, &out_index);
    //get logcode
    uint16_t logcode = (output[2] << 8) | output[3];
    switch(logcode)
    {
        case 0xB083:
            decode_B083(hex_data, file_size, output, &index, &out_index);
        case 0xB16C:
            decode_B16c(hex_data, file_size, output, &index, &out_index);
    }


    // 关闭文件
    fclose(fp);

    return 0;
}

