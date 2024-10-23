## 1021 version:
We use main.c as the external interface  
input: data.dat logcode  
output:decode xml  

For each message type, we need to write five files:  
1.corresponding asn1  
2.logcode_cb_dacll.c--change byte sequence & call uper_decode to decode   
3.logcode_cb_dcall.h--just include decode_logcode function  
4.logcode_test_data.txt  
5.logcode_test_data.dat  
6.host.c -- add the corresponding branch in switch, no main function 

For now, we have 22 more message_types than mobileinsight  
but some field still cannot decode now  
we will solve it later


### Support Message Types
|Index|Message Name|Logcode|version|finish|test|else
|--|--|--|--|--|--|--|
|1|LTE_RLC_DL_AM_Control_PDU|0xB083|48|1|1|none|
|2|LTE_PDCP_DL_Data_PDU|0xB0A1|53|1|1|none|
|3|LTE_PDCP_UL_Delay_Statistics|0xB0B6|56|1|1|none| 
|4|LTE_RRC_Supported_CA_Combos|0xB0CD|41|1|1|none|
|5|LTE_LL1_Serving_Cell_Measurement_Results|0xB116|21|1|1|none|  
|6|LTE_LL1_PCFICH_Decoding_Results|0xB12A|161|1|1|none| 
|7|LTE_LL1_RACH_TX_Report|0xB144|161|1|0|negative field need extra process|
|8|LTE_ML1_Random_Access_Request(MSG1)_Report|0xB167|40|1|0|negative integer less 1|
|9|LTE_ML1_Random_Access_Response(MSG2)_Report|0xB168|24|1|1|none|  
|10|LTE_UE_Identification_Message_MSG3_Report|0xB169|40|1|1|none|  
|11|LTE_Contention_Resulution_Message_MSG4_Report|0xB16A|1|1|1|none|  
|12|LTE_ML1_DCI_Information_Report|0xB16C|49|1|1|none|
|13|LTE_ML1_GM_TX_Report|0xB16D|49|0|1|use total tx power to decide pusch and pucch, some field lack of data|
|14|LTE_ML1_S_Criteria_Check_Procedure|0xB17A|1|1|1|none|  
|15|LTE_ML1_Idle_Measurement_Request|0xB17D|1|1|1|none|  
|16|LTE_ML1_Serving_Cell_Measurements_And_Evaluation|0xB17F|5|some field lack|1|some filed lack|
|17|LTE_ML1_Intra_Frequency_Cell_Reselection_Payload|0xB181|1|cell part not finished|1|cell part|
|18|LTE_ML1_CA_Metrics_Log_Packet|0xB184|50|1|1|none|
|19|LTE_ML1_AdvRx_IC_Cell_List|0xB18F|54|1|1|none|  
|20|LTE_ML1_Cell_Measurement_Results|0xB196|41|1|1|none|
|21|LTE_ML1_Serving_Cell_Information|0xB197|2|1|1|none|
|22|LTE_ML1_Common_DC_Offset|0xB1B2|49|1|1|none|




#### Tip
1.in logcode_cb_dacll.c remember to call converter function with the paramter index, no * 
2.change_byte_sequence c and h file is used for change byte sequence, print hex, write to file  
3.we have changed the cb method in B0A1,B0B6,B0CD,B116 but not in B16C,B083
 

