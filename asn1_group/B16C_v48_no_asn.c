#include "B16C_v48_no_asn.h"
#include "change_byte_sequence.h"

void decode_B16C_v48_no_asn(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    /*S_H*/
    int start_S_H = *index;
    *index+=4;
    int version = hex_data[start_S_H];
    int num_record = (hex_data[start_S_H+1]&0xFC)>>2;

    int first_sub_frame_number = 0;
    int first_sys_frame_number = 0;

    for(int i=0;i<num_record;i++)
    {
        int start_record = *index;
        convert_endianess(hex_data, index, 2);
        int subfn = (hex_data[start_record]&0x3C)>>2;
        int sysfn = ((hex_data[start_record]&0x03)<<8)|(hex_data[start_record+1]);            
        int num_ul_grant = (hex_data[start_record]&0xC0)>>6;

        if(i==0)
        {
            first_sub_frame_number = subfn;
            first_sys_frame_number = sysfn;
        }

        if(num_ul_grant!=0)
        {
            int start_UL = *index;
            *index+=126;
            int mcs_index = (hex_data[start_UL+5]&0xF8)>>3;
            int redundancy_version = (hex_data[start_UL+5]&0x06)>>1;
            int num_of_resource_blocks = (hex_data[start_UL+8]&0x7F);
            // printf("%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
            //         logcode, time_in_us_total, version, num_record, 
            //         first_sub_frame_number, first_sys_frame_number,
            //         subfn, sysfn, mcs_index, redundancy_version, num_of_resource_blocks);
        }
        else
        {
            *index+=126;
        }
    }
}