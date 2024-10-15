#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-S-Criteria-Check-Procedure-S-H.h"
#include "LTE-ML1-S-Criteria-Check-Procedure-Subpacket-ID-4.h"
#include "LTE-ML1-S-Criteria-Check-Procedure-Subpacket-ID-9.h"
#include "B17A_cb_dcall.h"

void convert_S_H_B17A(uint8_t *hex_data, size_t *index)
{
    *index+=4;
}

void convert_Subpacket_id4_B17A(uint8_t *hex_data, size_t *index)
{
    //1 2 3 4 5 6 7
    *index+=7;
    //8 9 10
    convert_endianess(hex_data, index, 3);
    //11
    *index +=1;
    //12 13
    convert_endianess(hex_data, index, 2);
    //14 15
    convert_endianess(hex_data, index, 2);
    //16 17 18 19 
    *index+=4;
    //20 21
    convert_endianess(hex_data, index, 2);
    //22 23
    *index+=2;
}

void convert_Subpacket_id9_B17A(uint8_t *hex_data, size_t *index)
{
    //1 2 3 4 5 6 7 8 9
    *index+=9;
    //10 11
    convert_endianess(hex_data, index, 2);
    //12 13
    convert_endianess(hex_data, index, 2);
    //14 15
    convert_endianess(hex_data, index, 2);
    //16 17
    convert_endianess(hex_data, index, 2);
    //18 19
    convert_endianess(hex_data, index, 2);
    //20 21
    convert_endianess(hex_data, index, 2);
    //22 23
    *index +=2;
}

void decode_B17A(uint8_t *hex_data, size_t length, size_t *index)
{
    LTE_ML1_S_Criteria_Check_Procedure_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_4_t  *t_id_4 = 0;
    asn_dec_rval_t rval_id4;
    LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_9_t  *t_id_9 = 0;
    asn_dec_rval_t rval_id9;

    /*S_H*/
    int start_S_H = *index;
    printf("index=%d\n",*index);
    convert_S_H_B17A(hex_data, index);
    int S_H_length = *index - start_S_H;
    printf("S_H_Length=%d\n", S_H_length);

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_S_H, t_S_H); 

    //get number of subpackets
    int num_of_subpkt = hex_data[start_S_H+1];
    printf("num_of_subpkt=%d\n",num_of_subpkt);

    for(int i=0;i<num_of_subpkt;i++)
    {
        /*subpacket id*/
        int subpacket_id = hex_data[*index];
        *index+=1;
        printf("index=%d\n",*index);

        switch(subpacket_id)
        {
            case 4:
            {
                printf("SubPacket ID : 4\n");
                int start_id4 = *index;
                convert_Subpacket_id4_B17A(hex_data, index);
                int id4_length = *index - start_id4;
                printf("id4_length=%d\n", id4_length);
                rval_id4 = uper_decode(0, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_4, (void **)&t_id_4, hex_data+start_id4, id4_length, 0, 0);
                if(rval_id4.code != RC_OK) {
                    printf("rval_id4 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_4, t_id_4); 
                break;
            }
            case 9:
            {
                printf("SubPacket ID : 9\n");
                int start_id9 = *index;
                convert_Subpacket_id9_B17A(hex_data, index);
                int id9_length = *index - start_id9;
                printf("id9_length=%d\n", id9_length);
                rval_id9 = uper_decode(0, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_9, (void **)&t_id_9, hex_data+start_id9, id9_length, 0, 0);
                if(rval_id9.code != RC_OK) {
                    printf("rval_id4 decode error\n");
                    exit(65);
                }
                xer_fprint(stdout, &asn_DEF_LTE_ML1_S_Criteria_Check_Procedure_Subpacket_ID_9, t_id_9); 
                break;
            }
            default:
            {
                printf("in default\n");
                break;
            }
        }
    }



    printf("decode_B17A over!!!!\n");
    printf("index=%d\n",*index);
}