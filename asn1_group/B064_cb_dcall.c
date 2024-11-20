#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-MAC-Ul-Transport-Block-S-H.h"
#include "LTE-MAC-Ul-Transport-Block-Subpkt-H.h"
#include "LTE-MAC-Ul-Transport-Block-Sample-H.h"
#include "B064_cb_dcall.h"

void convert_S_H_B064(uint8_t *hex_data, int *index)
{
    *index += 4;
}

void convert_Subpkt_H_B064(uint8_t *hex_data, int *index)
{
    *index += 2;
    convert_endianess(hex_data, index, 2);
    *index += 1;
}

void convert_Sample_H_B064(uint8_t *hex_data, int *index)
{
    *index += 4;
    convert_endianess(hex_data, index, 2);
    convert_endianess(hex_data, index, 2);
    *index += 1;
    convert_endianess(hex_data, index, 2);
    *index += 3;
}

void decode_B064(uint8_t *hex_data, size_t length, int *index)
{
    LTE_MAC_Ul_Transport_Block_S_H_t *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_MAC_Ul_Transport_Block_Subpkt_H_t *t_Subpkt_H = 0;
    asn_dec_rval_t rval_Subpkt_H;
    LTE_MAC_Ul_Transport_Block_Sample_H_t *t_Sample_H = 0;
    asn_dec_rval_t rval_Sample_H;

    /*S_H*/
    int start_S_H = *index;
    printf("index=%d\n", *index);
    convert_S_H_B064(hex_data, index);
    int S_H_length = *index - start_S_H;
    printf("S_H_Length=%d\n", S_H_length);

    rval_S_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_S_H, (void **)&t_S_H, hex_data + start_S_H, S_H_length, 0, 0);
    if (rval_S_H.code != RC_OK)
    {
        printf("rval_S_H decode error\n");
        exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_S_H, t_S_H);

    int num_subpkt = hex_data[start_S_H + 1];
    printf("num_subpkt=%d\n", num_subpkt);

    for (int i = 0; i < num_subpkt; i++)
    {
        printf("Subpkt [%d]\n", i);
        int start_Subpkt_H = *index;
        printf("index=%d\n", *index);
        convert_Subpkt_H_B064(hex_data, index);
        int Subpkt_H_length = *index - start_Subpkt_H;
        printf("Subpkt_H_length=%d\n", Subpkt_H_length);

        rval_Subpkt_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_Subpkt_H, (void **)&t_Subpkt_H, hex_data + start_Subpkt_H, Subpkt_H_length, 0, 0);
        if (rval_Subpkt_H.code != RC_OK)
        {
            printf("rval_Subpkt_H decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_Subpkt_H, t_Subpkt_H);

        int num_sample = hex_data[start_Subpkt_H + 4];
        printf("num_sample=%d\n", num_sample);

        for (int j = 0; j < num_sample; j++)
        {
            printf("Samples [%d]\n", j);
            int start_Sample_H = *index;
            printf("index=%d\n", *index);
            convert_Sample_H_B064(hex_data, index);
            int Sample_H_length = *index - start_Sample_H;
            printf("Sample_H_length=%d\n", Sample_H_length);

            rval_Sample_H = uper_decode(0, &asn_DEF_LTE_MAC_Ul_Transport_Block_Sample_H, (void **)&t_Sample_H, hex_data + start_Sample_H, Sample_H_length, 0, 0);
            if (rval_Sample_H.code != RC_OK)
            {
                printf("rval_Sample_H decode error\n");
                exit(65);
            }
            xer_fprint(stdout, &asn_DEF_LTE_MAC_Ul_Transport_Block_Sample_H, t_Sample_H);

            int hdrlen = hex_data[start_Sample_H + 13] printf("hdrlen=%d\n", hdrlen);

            /*element*/
            int lcg = -1;
            int bsr_type = 0;
            int step = *index;
            printf("start_element=%d\n", step);
            int E = -1;
            int LCID_data = -1;
            int F = -1;
            int L = -1;
            int buffer_size[4] = {0, 0, 0, 0};
            while (step < hdrlen)
            {
                E = (hex_data[step] >> 5) & 1;
                printf("E=%d\n", E);
                LCID_data = (hex_data[step]) & 31;
                printf("LCID_data=%d\n", LCID_data);

                if (LCID_data == 29)
                {
                    printf("***** Short BSRT *****\n");
                    bsr_type = 1;
                }
                else if (LCID_data == 30)
                {
                    printf("***** Long BSRT *****\n");
                    bsr_type = 2;
                }
                else if (LCID_data == 31)
                {
                    if (bsr_type == 0)
                    {
                        printf("***** Padding *****\n");
                        bsr_type = 3;
                    }
                }


                if (E == 1 && LCID_data <= 11)
                {
                    step += 1;
                    F = (hex_data[step] >> 7) & 1;
                    printf("F=%d\n", F);
                    if (F == 0)
                    {
                        L = (hex_data[step]) & 127;
                        printf("L=%d\n", L);
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
                        lcg = (hex_data[step] >> 6) & 3;
                        buffer_size[lcg] = (hex_data[step] & 63);
                        printf("BSR index saved\n");
                    }
                    else if (bsr_type == 2)
                    {
                        buffer_size[0] = (hex_data[step] & 0xFC) >> 2;
                        buffer_size[1] = ((hex_data[step] & 3) << 4) | ((hex_data[step + 1] & 0xF0) >> 4);
                        buffer_size[2] = ((hex_data[step + 1] & 15) << 2) | ((hex_data[step + 2] & 0xC0) >> 6);
                        buffer_size[3] = (hex_data[step + 2] & 63);
                        printf("BSR index saved\n");
                        step += 2;
                    }
                    if (step + 1 > hdrlen)
                    {
                        bsr_type -= bsr_type;
                    }
                    break;
                }
                step += 1;
            }
            *index = step;
        }
    }
    printf("B064 over!!!!\n");
}