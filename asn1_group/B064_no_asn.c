#include "B064_no_asn.h"
#include "change_byte_sequence.h"

void convert_S_H_B064_no_asn(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_Subpkt_H_B064_no_asn(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 1;
}

void convert_Sample_H_B064_no_asn(uint8_t *hex_data, int *index)
{
    *index += 4;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 3;
}

void getBsrEventString_no_asn(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "none");
            break;
        case 1:
            strcpy(output, "periodic");
            break;
        case 2:
            strcpy(output, "high-data-arrival");
            break;
        case 3:
            strcpy(output, "robustness-bsr");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
}
void getBsrTrigString_no_asn(int num, char *output) {
    switch (num) {
        case 0:
            strcpy(output, "no-bsr");
            break;
        case 1:
            strcpy(output, "cacelled");
            break;
        case 2:
            strcpy(output, "l-bsr");
            break;
        case 3:
            strcpy(output, "s-bsr");
            break;
        case 4:
            strcpy(output, "pad-l-bsr");
            break;
        case 5:
            strcpy(output, "pad-s-bsr");
            break;
        case 6:
            strcpy(output, "pad-t-bsr");
            break;
        default:
            strcpy(output, "invalid");
            break;
    }
}

void decode_B064_no_asn(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{

    /*S_H*/
    int start_S_H = *index;
    convert_S_H_B064_no_asn(hex_data, index);
    int num_subpkt = hex_data[start_S_H];

    for (int i = 0; i < num_subpkt; i++)
    {
        int start_Subpkt_H = *index;
        convert_Subpkt_H_B064_no_asn(hex_data, index);

        int num_samples = hex_data[start_Subpkt_H+4];
        int first_sub_frame_number = 0;
        int first_sys_frame_number = 0;
        
        for (int j = 0; j < num_samples; j++)
        {
            int start_Sample_H = *index;
            convert_Sample_H_B064_no_asn(hex_data, index);
            int sysfn = (hex_data[start_Sample_H+4]<<4) | ((hex_data[start_Sample_H+5]&0xF0)>>4);
            int subfn = hex_data[start_Sample_H+5] & 0x0F;
            int grant_bytes = (hex_data[start_Sample_H+6]<<8) | (hex_data[start_Sample_H+7]);
            int padding = (hex_data[start_Sample_H+9]<<8) | (hex_data[start_Sample_H+10]);
            int bsr_event = hex_data[start_Sample_H+11]&0x03;
            int bsr_trig = hex_data[start_Sample_H+12]&0x07;
            
            if(j==0)
            {
                first_sub_frame_number = subfn;
                first_sys_frame_number = sysfn;
            }
            int hdrlen = hex_data[start_Sample_H+13];
            // printf("hdrlen=%d\n", hdrlen);

            /*element*/
            int lcg = -1;
            int bsr_type = 0;
            int step = 0;
            int start_element=*index;
            //printf("start_element= *index = %d\n", start_element);
            int E = -1;
            int LCID_data = -1;
            int F = -1;
            int L = -1;
            int buffer_size[4] = {0, 0, 0, 0};
            while (step < hdrlen)
            {
                E = (hex_data[start_element+step] >> 5) & 1;
                //printf("E=%d\n", E);
                LCID_data = (hex_data[start_element+step]) & 31;
                //printf("LCID_data=%d\n", LCID_data);

                if (LCID_data == 29)
                {
                    //printf("***** Short BSR *****\n");
                    bsr_type = 1;
                }
                else if (LCID_data == 30)
                {
                    //printf("***** Long BSR *****\n");
                    bsr_type = 2;
                }
                else if (LCID_data == 31)
                {
                    if (bsr_type == 0)
                    {
                        //printf("***** Padding *****\n");
                        bsr_type = 3;
                    }
                }


                if (E == 1 && LCID_data <= 11)
                {
                    step += 1;
                    F = (hex_data[start_element+step] >> 7) & 1;
                    //printf("F=%d\n", F);
                    if (F == 0)
                    {
                        L = (hex_data[start_element+step]) & 127;
                        //printf("L=%d\n", L);
                    }
                    else if (F != 0)
                    {
                        step += 1;
                    }
                }
                else if (E == 0)
                {
                    step += 1;
                    if (bsr_type == 1)
                    {
                        lcg = (hex_data[start_element+step] >> 6) & 3;
                        buffer_size[lcg] = (hex_data[start_element+step] & 63);
                        //printf("BSR index saved\n");
                    }
                    else if (bsr_type == 2)
                    {
                        buffer_size[0] = (hex_data[start_element+step] & 0xFC) >> 2;
                        buffer_size[1] = ((hex_data[start_element+step] & 3) << 4) | ((hex_data[start_element+step + 1] & 0xF0) >> 4);
                        buffer_size[2] = ((hex_data[start_element+step + 1] & 15) << 2) | ((hex_data[start_element+step + 2] & 0xC0) >> 6);
                        buffer_size[3] = (hex_data[start_element+step + 2] & 63);
                        //printf("BSR index saved\n");
                        step += 2;
                    }
                    if (step + 1 > (hdrlen))
                    {
                        bsr_type -= bsr_type;
                    }
                    break;
                }
                step += 1;
            }
            *index += (hdrlen) ;

            char bsr_event1[50];
            getBsrEventString_no_asn(bsr_event, bsr_event1);
            char bsr_trig1[50];
            getBsrTrigString_no_asn(bsr_trig, bsr_trig1);

            // printf("%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%s\t%d\t%d\t%d\t%d\n",
            //         logcode, time_in_us_total, first_sub_frame_number, first_sys_frame_number, subfn, sysfn,
            //         grant_bytes, padding, bsr_event1, bsr_type, lcg, bsr_trig1,
            //         buffer_size[0], buffer_size[1], buffer_size[2], buffer_size[3]);
            FILE *fp_B064 = fopen("B064_report.txt", "a+");
            fprintf(fp_B064, "%02X\t%llu\t%d\t%d\t%d\t%d\t%d\t%d\t%s\t%d\t%d\t%s\t%d\t%d\t%d\t%d\n",
                                logcode, time_in_us_total, first_sub_frame_number, first_sys_frame_number, subfn, sysfn,
                                grant_bytes, padding, bsr_event1, bsr_type, lcg, bsr_trig1,
                                buffer_size[0], buffer_size[1], buffer_size[2], buffer_size[3]);
            fclose(fp_B064);

        }
    }
    //printf("B064 over!!!!\n");
}