## 1007 version:
We use main.c as the external interface  
input: data.dat logcode  
output:decode xml  

For each message type, we need to write five files:  
1.corresponding asn1  
2.logcode_cb_dacll.c--change byte sequence & call uper_decode to decode   
3.logcode_cb_dcall.h--just include decode_logcode function  
4.logcode_test_data.txt  
5.logcode_test_data.dat  
6.main.c -- add the corresponding branch in switch  




### Support Message Types
LTE_ML1_DCI_Information_Report----logcode----0xB16C----finished----tested  
LTE_RLC_DL_AM_Control_PDU     ----logcode----0xB083----finished----tested  
LTE_PDCP_DL_Data_PDU          ----logcode----0xB0A1----finished----tested  
LTE_PDCP_UL_Delay_Statistics  ----logcode----0xB0B6----finished----tested  
LTE_RRC_Supported_CA_Combos   ----logcode----0xB0CD----finished----tested  
LTE_LL1_Serving_Cell_Measurement_Results  ----logcode----0xB116----finished----tested  

#### Tip
1.in logcode_cb_dacll.c remember to call converter function with the paramter index, no * 
2.change_byte_sequence c and h file is used for change byte sequence, print hex, write to file  
3.we have changed the cb method in B0A1,B0B6,B0CD,B116 but not in B16C,B083
 

