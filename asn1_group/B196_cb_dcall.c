#include <stdio.h>
#include <stdint.h>
#include "change_byte_sequence.h"
#include "LTE-ML1-Cell-Measurement-Results-S-H.h"
#include "LTE-ML1-Cell-Measurement-Results-cell-measurement.h"
#include "B196_cb_dcall.h"

void convert_S_H_B196(uint8_t *hex_data, size_t *index)
{
    *index+=4;
}

void convert_cell_B196(uint8_t *hex_data, size_t *index)
{
    //1-4
    convert_endianess(hex_data, index, 4);
    //5-6
    convert_endianess(hex_data, index, 2);
    //7-12
    *index+=6;
    //13-16
    convert_endianess(hex_data, index, 4);
    //17-20
    convert_endianess(hex_data, index, 4);
    //21-24
    *index+=4;
    //25-28
    convert_endianess(hex_data, index, 4);
    //29-32
    convert_endianess(hex_data, index, 4);
    //33-36
    convert_endianess(hex_data, index, 4);
    //37-40
    convert_endianess(hex_data, index, 4);
}

void decode_B196(uint8_t *hex_data, size_t length, size_t *index)
{
    LTE_ML1_Cell_Measurement_Results_S_H_t  *t_S_H = 0;
    asn_dec_rval_t rval_S_H;
    LTE_ML1_Cell_Measurement_Results_cell_measurement_t   *t_cell = 0;
    asn_dec_rval_t rval_cell;

    /*S_H*/
    int start_S_H = *index;
    printf("index=%d\n",*index);
    convert_S_H_B196(hex_data, index);
    int S_H_length = *index - start_S_H;
    printf("S_H_Length=%d\n", S_H_length);

    rval_S_H = uper_decode(0, &asn_DEF_LTE_ML1_Cell_Measurement_Results_S_H, (void **)&t_S_H, hex_data+start_S_H, S_H_length, 0, 0);
    if(rval_S_H.code != RC_OK) {
      printf("rval_S_H decode error\n");
      exit(65);
    }
    xer_fprint(stdout, &asn_DEF_LTE_ML1_Cell_Measurement_Results_S_H, t_S_H); 

    //get cell num
    int num_cell = hex_data[start_S_H+1];
    printf("num_cell=%d\n",num_cell);

    for(int i=0;i<num_cell;i++)
    {
        int start_cell = *index;
        printf("index=%d\n",*index);
        convert_cell_B196(hex_data, index);
        int cell_length = *index - start_cell;
        printf("cell_length=%d\n", cell_length);

        rval_cell = uper_decode(0, &asn_DEF_LTE_ML1_Cell_Measurement_Results_cell_measurement, (void **)&t_cell, hex_data+start_cell, cell_length, 0, 0);
        if(rval_cell.code != RC_OK) {
            printf("rval_cell decode error\n");
            exit(65);
        }
        xer_fprint(stdout, &asn_DEF_LTE_ML1_Cell_Measurement_Results_cell_measurement, t_cell); 

        double inst_rsrp_rx_0_data = ((hex_data[start_cell+14]&0x0f)<<8)|(hex_data[start_cell+15]);
        inst_rsrp_rx_0_data = (inst_rsrp_rx_0_data*0.0625-180);
        printf("inst_rsrp_rx_0_data=%f\n",inst_rsrp_rx_0_data);
        double inst_rsrp_rx_1_data = ((hex_data[start_cell+18]&0x0f)<<8)|(hex_data[start_cell+19]);
        inst_rsrp_rx_1_data = (inst_rsrp_rx_1_data*0.0625-180);
        printf("inst_rsrp_rx_1_data=%f\n",inst_rsrp_rx_1_data);

        double inst_rsrq_rx_0_data = ((hex_data[start_cell+26]&0x03)<<8)|(hex_data[start_cell+27]);
        inst_rsrq_rx_0_data = (inst_rsrq_rx_0_data*0.0625-30);
        printf("inst_rsrq_rx_0_data=%f\n",inst_rsrq_rx_0_data);
        double inst_rsrq_rx_1_data = ((hex_data[start_cell+30]&0x03)<<8)|(hex_data[start_cell+31]);
        inst_rsrq_rx_1_data = (inst_rsrq_rx_1_data*0.0625-30);
        printf("inst_rsrq_rx_1_data=%f\n",inst_rsrq_rx_1_data);

        double inst_rssi_rx_0_data = ((hex_data[start_cell+34]&0x07)<<8)|(hex_data[start_cell+35]);
        inst_rssi_rx_0_data = (inst_rssi_rx_0_data*0.0625-110);
        printf("inst_rssi_rx_0_data=%f\n",inst_rssi_rx_0_data);
        double inst_rssi_rx_1_data = ((hex_data[start_cell+38]&0x07)<<8)|(hex_data[start_cell+39]);
        inst_rssi_rx_1_data = (inst_rssi_rx_1_data*0.0625-110);
        printf("inst_rssi_rx_1_data=%f\n",inst_rssi_rx_1_data);
    }
    printf("decode_B196 over!!!!\n");
    printf("index=%d\n",*index);
}