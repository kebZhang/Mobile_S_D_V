#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Common-DC-Offset-S-H.h"
#include "B1B2_cb_dcall.h"

/*now we can only decode the first 8 Bytes*/
void convert_S_H_B1B2(uint8_t *hex_data, int *index)
{
    //1 2 3 4
    *index+=4;
    //5 6 7 8
    convert_endianess(hex_data, index, 4);
}


void decode_B1B2(uint8_t *hex_data, size_t length, int *index)
{
    LTE_ML1_Common_DC_Offset_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;

    /*S_H*/
    int start_S_H = *index;
    printf("index=%d\n",*index);
    convert_S_H_B1B2(hex_data, index);
    int S_H_length = *index - start_S_H;
    printf("S_H_Length=%d\n", S_H_length);

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Common_DC_Offset_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Common_DC_Offset_S_H, t_S_H); 

    printf("we can only decode the first 8 Bytes now\n");
}