#include "B139_v161_no_asn.h"
#include "change_byte_sequence.h"

void convert_S_H_B139_v161_no_asn(uint8_t *hex_data, int *index)
{
    *index+=4;
    convert_endianess(hex_data, index, 2);
    *index+=2;
}

void convert_R_B139_V161_no_asn(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
    *index+=3;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=90;
}

void decode_B139_v161_no_asn(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B139_v161_no_asn(hex_data, index);
    int version = hex_data[start_S_H];
    int num_of_record = (hex_data[start_S_H+2]&0xFE)>>1;
    int dispatch_sfn_sf = (hex_data[start_S_H+4]<<8)|(hex_data[start_S_H+5]);

    for(int i=0;i<num_of_record;i++)
    {
        int start_record = *index;
        convert_R_B139_V161_no_asn(hex_data, index);
        
        int current_sfn_sf = (hex_data[start_record]<<8)|(hex_data[start_record+1]);
        int redund_ver = (hex_data[start_record+3]&0x30)>>4;
        int num_of_rb = ((hex_data[start_record+5]&0x3F)<<1) | ((hex_data[start_record+6]&0x80)>>7);
        int pusch_tb_size = (hex_data[start_record+8]<<8)|(hex_data[start_record+9]);


        FILE *fp_B139 = fopen("B139_report.txt", "a+");
        fprintf(fp_B139, "%02X\t%llu\t%d\t%d\t%d\t%d\t%d\n",
                            logcode, time_in_us_total, dispatch_sfn_sf,
                            current_sfn_sf, redund_ver, num_of_rb, pusch_tb_size);
        fclose(fp_B139);
    }
}