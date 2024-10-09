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




### Support Message Types
LTE_ML1_DCI_Information_Report----logcode----0xB16C----finished----tested  
LTE_RLC_DL_AM_Control_PDU     ----logcode----0xB083----finished----tested
LTE_PDCP_DL_Data_PDU          ----logcode----0xB0A1----finished----tested

#### Tip
1.in logcode_cb_dacll.c remember to call converter function with the paramter index, no * 
2.change_byte_sequence c and h file is used for change byte sequence, print hex, write to file  
3.we have changed the cb method in B0A1 but not in B16C and B083
 

