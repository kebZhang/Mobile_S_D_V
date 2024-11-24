#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-DCI-Information-Report-v48-S-H.h"
#include "LTE-ML1-DCI-Information-Report-v48-R-H.h"
#include "LTE-ML1-DCI-Information-Report-v48-R-UL.h"
#include "B16C_v48_cb_dcall.h"

void convert_S_H_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=4;
}

void convert_R_H_B16C_v48(uint8_t *hex_data, int *index)
{
    convert_endianess(hex_data, index, 2);
}

void convert_R_UL_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=126;
}

void convert_R_DL_B16C_v48(uint8_t *hex_data, int *index)
{
    *index+=126;
}

void decode_B16C_v48(uint8_t *hex_data, size_t length, int *index, uint64_t time_in_us_total, uint16_t logcode)
{
    LTE_ML1_DCI_Information_Report_v48_S_H_t *t_S_H=0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_DCI_Information_Report_v48_R_H_t *t_R_H=0;
    asn_dec_rval_t rval_R_H;
    LTE_ML1_DCI_Information_Report_v48_R_UL_t *t_R_UL=0;
    asn_dec_rval_t rval_R_UL;

    /*S_H*/
    int start_S_H = *index;
    //printf("index=%d\n",*index);
    convert_S_H_B16C_v48(hex_data, index);
    int S_H_length = *index - start_S_H;
    //printf("S_H_Length=%d\n", S_H_length);

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    // if(rval_S_H.code != RC_OK) {
    //   //printf("rval_S_H decode error\n");
    //   exit(65);
    // }
    //xer_fprint(stdout, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_S_H, t_S_H);   
    //printf("version = %ld, num_of_record = %ld\n", t_S_H->version, t_S_H->num_of_record);

    // int num_of_record = (hex_data[start_S_H+1]&0xFC)>>2;
    // printf("num_of_record = %d \n", num_of_record);

    int first_sub_frame_number = 0;
    int first_sys_frame_number = 0;

    for(int i=0;i<t_S_H->num_of_record;i++)
    {
        //printf("[%d] Record\n",i);
        int start_record = *index;
        convert_R_H_B16C_v48(hex_data, index);
        int R_H_Length = *index-start_record;
        //printf("R_H_Length=%d\n", R_H_Length);
        rval_R_H = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_H, (void **)&t_R_H, hex_data+start_record, R_H_Length, 0, 0);
        // if(rval_R_H.code != RC_OK) {
        //     //printf("rval_R_H decode error\n");
        //     exit(65);
        // }
        //xer_fprint(stdout, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_H, t_R_H); 
        //printf("Num Ul Grant : %ld, Sub Frame Number: %ld, System Frame Number: %ld\n", t_R_H->num_ul_grant_info, t_R_H->sub_frame_number, t_R_H->sys_frame_number);

        // int num_ul_grant = (hex_data[start_record]&0xC0)>>6;
        // printf("num_ul_grant = %d \n", num_ul_grant);
        
        if(i==0)
        {
            first_sub_frame_number = t_R_H->sub_frame_number;
            first_sys_frame_number = t_R_H->sys_frame_number;
        }

        if(t_R_H->num_ul_grant_info!=0)
        {
            int start_UL = *index;
            convert_R_UL_B16C_v48(hex_data, index);
            int R_UL_Length = *index-start_UL;
            //printf("R_UL_Length=%d\n", R_UL_Length);
            rval_R_UL = uper_decode(0, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_UL, (void **)&t_R_UL, hex_data+start_UL, R_UL_Length, 0, 0);
            // if(rval_R_UL.code != RC_OK) {
            //     //printf("rval_R_UL decode error\n");
            //     exit(65);
            // }
            //xer_fprint(stdout, &asn_DEF_LTE_ML1_DCI_Information_Report_v48_R_UL, t_R_UL); 
            printf("%02X\t%llu\t%ld\t%ld\t%d\t%d\t%ld\t%ld\t%ld\t%ld\t%ld\n", logcode, time_in_us_total,
                t_S_H->version, t_S_H->num_of_record, first_sub_frame_number, first_sys_frame_number,
                t_R_H->sub_frame_number, t_R_H->sys_frame_number, 
                t_R_UL->mcs_index, t_R_UL->rendundancy_version, t_R_UL->number_of_resource_blocks);
        }
        else
        {
            //convert_R_DL_B16C_v48(hex_data, index);
            *index+=126;
        }
    }
    //printf("decode B16C over!!!\n");
}