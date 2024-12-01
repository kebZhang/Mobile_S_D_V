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
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=1;
    convert_endianess(hex_data, index, 2);
    *index+=90;
}

void getcarrierindexString_no_asn(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "pcc");
            break;
        case 1:
            strcpy(output, "scc1");
            break;
        case 2:
            strcpy(output, "scc2");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
}

void getretxindexString_no_asn(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "First");
            break;
        case 1:
            strcpy(output, "Second");
            break;
        case 2:
            strcpy(output, "Third");
            break;
        case 3:
            strcpy(output, "Fourth");
            break;
        case 4:
            strcpy(output, "Fifth");
            break;
        case 5:
            strcpy(output, "Sixth");
            break;
        case 6:
            strcpy(output, "Seventh");
            break;
        case 7:
            strcpy(output, "Eighth");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
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
        int redund_ver = (hex_data[start_record+2]&0x30)>>4;
        int re_tx_index = ((hex_data[start_record+2]&0x0F)<<1) | ((hex_data[start_record+3]&0x80)>>7);
        int ul_carrier_index = (hex_data[start_record+3]&0x03);
        int num_of_rb = ((hex_data[start_record+5]&0x3F)<<1) | ((hex_data[start_record+6]&0x80)>>7);
        int pusch_tb_size = (hex_data[start_record+8]<<8)|(hex_data[start_record+9]);
        int dl_carrier_index = (hex_data[start_record+7]&0x06)>>1;

        char re_tx_index1[50];
        getretxindexString_no_asn(re_tx_index,re_tx_index1);
        char ul_carrier_index1[50];
        getcarrierindexString_no_asn(ul_carrier_index,ul_carrier_index1);
        char dl_carrier_index1[50];
        getcarrierindexString_no_asn(dl_carrier_index,dl_carrier_index1);


        // FILE *fp_B139 = fopen("B139_report.txt", "a+");
        // fprintf(fp_B139, "%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%wd\t%s\t%s\t%s\n",
        //                     logcode, time_in_us_total, num_of_record, dispatch_sfn_sf,
        //                     current_sfn_sf, redund_ver, num_of_rb, pusch_tb_size,
        //                     re_tx_index1, ul_carrier_index1, dl_carrier_index1);
        // fclose(fp_B139);
    }
}