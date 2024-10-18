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
1.LTE_ML1_DCI_Information_Report----logcode----0xB16C----finished----tested  
2.LTE_RLC_DL_AM_Control_PDU     ----logcode----0xB083----finished----tested  
3.LTE_PDCP_DL_Data_PDU          ----logcode----0xB0A1----finished----tested  
4.LTE_PDCP_UL_Delay_Statistics  ----logcode----0xB0B6----finished----tested  
5.LTE_RRC_Supported_CA_Combos   ----logcode----0xB0CD----finished----tested  
6.LTE_LL1_Serving_Cell_Measurement_Results  ----logcode----0xB116----finished----tested  
7.LTE_LL1_PCFICH_Decoding_Results     ----logcode----0xB12A----finished----tested
8.LTE_LL1_RACH_TX_Report        ----logcode----0xB144----finished----wrongtest----negative integer less 1    
9.LTE_ML1_Random_Access_Request(MSG1)_Report    --logcode----0xB167----finished----wrongtest--------negative integer less 1    
10.LTE_ML1_Random_Access_Response(MSG2)_Report    ----logcode----0xB168----finished----tested  
11.LTE_UE_Identification_Message_MSG3_Report----logcode    ----0xB169----finished----tested  
12.LTE_Contention_Resulution_Message_MSG4_Report----logcode----0xB16A----finished----tested  
13.LTE_ML1_S_Criteria_Check_Procedure----logcode----0xB17A----finished----tested  
14.LTE_ML1_Idle_Measurement_Request----logcode--0xB17D----finished----tested  
15.LTE_ML1_AdvRx_IC_Cell_List----logcode----0xB18F----finished----tested  
16.LTE_ML1_Serving_Cell_Information----logcode----0xB197----finished----tested  
17.LTE_ML1_Common_DC_Offset----logcode----0xB1B2----finished----tested  
18.LTE_ML1_Intra_Frequency_Cell_Reselection_Payload----logcode----0xB181----cell part not finished----tested  
19.LTE_ML1_CA_Metrics_Log_Packet----logcode----0xB184----finished----tested  
20.LTE_ML1_Cell_Measurement_Results----logcode----0xB196----finished----tested  
21.LTE_ML1_Serving_Cell_Measurements_And_Evaluation----logcode----0xB17F----finished except some field----tested  
22.


#### Tip
1.in logcode_cb_dacll.c remember to call converter function with the paramter index, no * 
2.change_byte_sequence c and h file is used for change byte sequence, print hex, write to file  
3.we have changed the cb method in B0A1,B0B6,B0CD,B116 but not in B16C,B083
 

