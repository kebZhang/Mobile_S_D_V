#include "host.h"



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

int trY()
{
    printf("try");
}

//我们直接把这个函数作为补充放进mobileinisght的decode_log_packet函数中
int S_D_V_decode(uint8_t *hex_data, size_t file_size, uint16_t logcode, int *index_in, uint64_t time_in_us_total, int crc_check, int check_format, int pkt_type)
{
    // FILE *fp=freopen("decode_result.txt","a",stdout);
    // if(fp==NULL)
    // {
    //     perror("failed");
    //     return -1;
    // }

    // printf("in\n");
    // fclose(fp);

    //fp=freopen("decode_result.txt","a",stdout);

    uint8_t *output = NULL;

    // size_t index = *index_in;
    int index = *index_in;
    // printf("index_in=%d\n", index);

    //fclose(fp);
    //fp=freopen("decode_result.txt","a",stdout);

    switch (logcode)
    {
        case 0xB083:
        {
            //printf("in B083 branch\n");
            decode_B083(hex_data, file_size, &index);
            *index_in = index;
            //fclose(fp);
            return 83;
        }
        case 0xB16C:
        {
            //printf("in B16C branch\n");
            decode_B16C_v48_no_asn(hex_data, file_size, &index, time_in_us_total, logcode, crc_check, check_format, pkt_type);
            //decode_B16C(hex_data, file_size, &index);
            *index_in = index;
            //fclose(fp);
            return 1;
        }
        case 0xB064:
        {
            //printf("in B064 branch\n");
            //decode_B064(hex_data, file_size, &index, time_in_us_total, logcode);
            decode_B064_no_asn(hex_data, file_size, &index, time_in_us_total, logcode);
            *index_in = index;
            //fclose(fp);
            return 64;
        }
        case 0xB173:
        {
            //printf("in B173 branch\n");
            //decode_B173(hex_data, file_size, &index, time_in_us_total, logcode);
            decode_B173_no_asn(hex_data, file_size, &index, time_in_us_total, logcode);
            *index_in = index;
            //fclose(fp);
            return 173;
        }
        // case 0xB0A1:
        // {
        //     printf("into B0A1 branch\n");
        //     decode_B0A1(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 2;
        // }
        // case 0xB0B6:
        // {
        //     printf("into B0B6 branch\n");
        //     decode_B0B6(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 3;
        // }
        // case 0xB0CD:
        // {
        //     printf("into B0CD branch\n");
        //     decode_B0CD(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 4;
        // }
        // case 0xB116:
        // {
        //     printf("into B116 branch\n");
        //     decode_B116(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 5;
        // }
        // case 0xB12A:
        // {
        //     printf("into B12A branch\n");
        //     decode_B12A(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 6;
        // }
        // case 0xB144:
        // {
        //     printf("into B144 branch\n");
        //     decode_B144(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 7;
        // }
        // case 0xB167:
        // {
        //     printf("into B167 branch\n");
        //     decode_B167(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 8;
        // }
        // case 0xB168:
        // {
        //     printf("into B168 branch\n");
        //     decode_B168(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 9;
        // }
        // case 0xB169:
        // {
        //     printf("into B169 branch\n");
        //     decode_B169(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 10;
        // }
        // case 0xB16A:
        // {
        //     printf("into B16A branch\n");
        //     decode_B16A(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 11;
        // }
        // case 0xB17A:
        // {
        //     printf("into B17A branch\n");
        //     decode_B17A(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 12;
        // }
        // case 0xB17D:
        // {
        //     printf("into B17D branch\n");
        //     decode_B17D(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 13;
        // }
        // case 0xB17F:
        // {
        //     printf("into B17F branch\n");
        //     decode_B17F(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 20;
        // }
        // case 0xB18F:
        // {
        //     printf("into B18F branch\n");
        //     decode_B18F(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 14;
        // }
        // case 0xB197:
        // {
        //     printf("into B197 branch\n");
        //     decode_B197(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 15;
        // }
        // case 0xB1B2:
        // {
        //     printf("into B1B2 branch\n");
        //     decode_B1B2(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 16;
        // }
        // case 0xB181:
        // {
        //     printf("into B181 branch\n");
        //     decode_B181(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 17;
        // }
        // case 0xB184:
        // {
        //     printf("into B184 branch\n");
        //     decode_B184(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 18;
        // }
        // case 0xB196:
        // {
        //     printf("into B196 branch\n");
        //     decode_B196(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 19;
        // }
        // case 0xB16D:
        // {
        //     // FILE *fp1 = fopen("decode3.txt","a");
        //     // fprintf(fp1,"into B16D branch\n");
        //     // fclose(fp1);
        //     printf("into B16D branch\n");
        //     decode_B16D(hex_data, file_size, &index);
        //     *index_in = index;
        //     fclose(fp);
        //     return 21;
        // }
        default:
        {
            printf("over\n");
            *index_in = index;
            //fclose(fp);
            return 999;
        }
    }

    return 0;
}


// int main(int argc, char *argv[]) 
// {
//     if (argc != 3) {
//         printf("Usage: %s <filename> <logcode:Bxxx>\n", argv[0]);
//         return 1;
//     }
//     const char *filename = argv[1];
//     const char *input_logcode = argv[2];
//     printf("File: %s\n", filename);
//     printf("input log code: %s\n", input_logcode);

//     // get file size
//     long file_size = get_file_size(filename);
//     if (file_size == -1) {
//         printf("Failed to get file size.\n");
//         return 1;
//     }
//     printf("File size: %ld bytes\n", file_size);

//     //open file
//     FILE *fp = fopen(filename, "rb");
//     if (!fp) {
//         perror("Error opening file");
//         return 1;
//     }

//     //buffer malloc
//     uint8_t *hex_data = NULL; /*input pointer*/
//     uint8_t *output = NULL;
//     size_t index=0;
//     size_t out_index=0;
//     hex_data = (uint8_t *)malloc(file_size);  
//     output = (uint8_t *)malloc(file_size); 

    
//     //read to buffer
//     if (fread(hex_data, 1, file_size, fp) != file_size) {
//         perror("fread");
//         free(hex_data);
//         fclose(fp);
//         return -1;
//     }
//     printf("filesize =%d\n",file_size);
//     // decode Metadata header
//     decode_metadata_header(hex_data, file_size, output, &index, &out_index);
    
//     printf("index after decode M_H=%d\n",index);

//     //get logcode
//     uint16_t logcode = (output[2] << 8) | output[3];
//     switch(logcode)
//     {
//         case 0xB083:
//         {
//             printf("into B083 branch\n");
//             decode_B083(hex_data, file_size, output, &index, &out_index);
//             return 0;
//         }
//         case 0xB16C:
//         {
//             printf("into B16C branch\n");
//             decode_B16C(hex_data, file_size, output, &index, &out_index);
//             return 1;
//         }
//         case 0xB0A1:
//         {
//             printf("into B0A1 branch\n");
//             decode_B0A1(hex_data, file_size, &index);
//             return 2;
//         }
//         case 0xB0B6:
//         {
//             printf("into B0B6 branch\n");
//             decode_B0B6(hex_data, file_size, &index);
//             return 3;
//         }
//         case 0xB0CD:
//         {
//             printf("into B0CD branch\n");
//             decode_B0CD(hex_data, file_size, &index);
            
//             return 4;
//         }
//         case 0xB116:
//         {
//             printf("into B116 branch\n");
//             decode_B116(hex_data, file_size, &index);
//             return 5;
//         }
//         case 0xB12A:
//         {
//             printf("into B12A branch\n");
//             decode_B12A(hex_data, file_size, &index);
//             return 6;
//         }
//         case 0xB144:
//         {
//             printf("into B144 branch\n");
//             decode_B144(hex_data, file_size, &index);
//             return 7;
//         }
//         case 0xB167:
//         {
//             printf("into B167 branch\n");
//             decode_B167(hex_data, file_size, &index);
//             return 8;
//         }
//         case 0xB168:
//         {
//             printf("into B168 branch\n");
//             decode_B168(hex_data, file_size, &index);
//             return 9;
//         }
//         case 0xB169:
//         {
//             printf("into B169 branch\n");
//             decode_B169(hex_data, file_size, &index);
//             return 10;
//         }
//         case 0xB16A:
//         {
//             printf("into B16A branch\n");
//             decode_B16A(hex_data, file_size, &index);
//             return 11;
//         }
//         case 0xB17A:
//         {
//             printf("into B17A branch\n");
//             decode_B17A(hex_data, file_size, &index);
//             return 12;
//         }
//         case 0xB17D:
//         {
//             printf("into B17D branch\n");
//             decode_B17D(hex_data, file_size, &index);
//             return 13;
//         }
//         case 0xB17F:
//         {
//             printf("into B17F branch\n");
//             decode_B17F(hex_data, file_size, &index);
//             return 20;
//         }
//         case 0xB18F:
//         {
//             printf("into B18F branch\n");
//             decode_B18F(hex_data, file_size, &index);
//             return 14;
//         }
//         case 0xB197:
//         {
//             printf("into B197 branch\n");
//             decode_B197(hex_data, file_size, &index);
//             return 15;
//         }
//         case 0xB1B2:
//         {
//             printf("into B1B2 branch\n");
//             decode_B1B2(hex_data, file_size, &index);
//             return 16;
//         }
//         case 0xB181:
//         {
//             printf("into B181 branch\n");
//             decode_B181(hex_data, file_size, &index);
//             return 17;
//         }
//         case 0xB184:
//         {
//             printf("into B184 branch\n");
//             decode_B184(hex_data, file_size, &index);
//             return 18;
//         }
//         case 0xB196:
//         {
//             printf("into B196 branch\n");
//             decode_B196(hex_data, file_size, &index);
//             return 19;
//         }
//         case 0xB16D:
//         {
//             printf("into B16D branch\n");
//             decode_B16D(hex_data, file_size, &index);
//             return 21;
//         }
//         default:
//         {
//             printf("over\n");
//             return 999;
//         }
//     }


//     // 关闭文件
//     fclose(fp);

//     return 0;
// }

