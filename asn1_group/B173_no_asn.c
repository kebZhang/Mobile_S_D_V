#include "B173_no_asn.h"
#include "change_byte_sequence.h"

void convert_R_H_B173_no_asn(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index+=10;
}

void convert_TB_B173_no_asn(uint8_t *hex_data, int *index)
{
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=6;
}

void decode_B173_no_asn(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    /*S_H*/
    int start_S_H = *index;
    *index+=4;
    int version = hex_data[start_S_H];
    int num_of_record = hex_data[start_S_H+1];

    int firt_sub_frame_num = 0;
    int first_sys_frame_num = 0;

    for(int i=0;i<num_of_record;i++)
    {
        int start_record = *index;
        convert_R_H_B173_no_asn(hex_data, index);

        int sysfn = (hex_data[start_record]<<4) | ((hex_data[start_record+1]&0xF0)>>4);
        int subfn = (hex_data[start_record+1]&0x0F);
        int num_of_transport_blocks = hex_data[start_record+4];
        int serving_cell_index = (hex_data[start_record+5] & 0x03);

        if(i==0)
        {
            firt_sub_frame_num = subfn;
            first_sys_frame_num = sysfn;
        }
        /*TB*/
        for(int j=0;j<2;j++)
        {
            if(num_of_transport_blocks==1 && j==1)
            {
                convert_TB_B173_no_asn(hex_data, index);
                continue;
            }
            int start_TB=*index;
            convert_TB_B173_no_asn(hex_data, index);

            int redundancy_version = (hex_data[start_TB]&0x30)>>4;
            int TB_index = (hex_data[start_TB+1]&0x10)>>4;
            int TB_size = (hex_data[start_TB+4]<<8) | (hex_data[start_TB+5]);
            int mcs = hex_data[start_TB+6];
            int num_of_rbs = hex_data[start_TB+7];

            // printf("%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            //         logcode, time_in_us_total, firt_sub_frame_num, first_sys_frame_num,
            //         subfn, sysfn, num_of_transport_blocks, redundancy_version, TB_index,
            //         TB_size, mcs, num_of_rbs);

            FILE *fp_B173 = fopen("B173_report.txt", "a+");
            fprintf(fp_B173, "%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
                                logcode, time_in_us_total, firt_sub_frame_num, first_sys_frame_num,
                                subfn, sysfn, num_of_transport_blocks, serving_cell_index, redundancy_version, TB_index,
                                TB_size, mcs, num_of_rbs);
            fclose(fp_B173);

        }
        /*Record tail*/
        *index+=4;

    }
}