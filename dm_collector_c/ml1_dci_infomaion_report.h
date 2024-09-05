#include "consts.h"
#include "log_packet.h"
#include "log_packet_helper.h"

const Fmt dci_info_head_Fmt [] = {
    {UINT, "Version", 1},
    {UINT, "num records and cfg", 2},
    {PLACEHOLDER, "Number of Records", 0},
    {PLACEHOLDER, "Subframe Cfg", 0},
    {UINT, "SKIP", 1},
};

const Fmt dci_info_record_head [] = {
    {UINT, "dci record head", 4},
    {PLACEHOLDER, "system frame number", 0},
    {PLACEHOLDER, "subframe number", 0},
    {PLACEHOLDER, "ul grant num", 0},
    {PLACEHOLDER, "dl grant num", 0},
    {PLACEHOLDER, "TPC DCI Present", 0},
    {PLACEHOLDER, "TPC DCI Format Type", 0},
    {PLACEHOLDER, "TPC DCI RNTI Type", 0},
    {PLACEHOLDER, "TPC DCI TPC Command", 0}
};

const ValueName ValueName_tpc_dci_present[]={
    {0,"No"}
};
const ValueName ValueName_tpc_dci_formate_type[]={
    {0,"Format 3"}
};
const ValueName ValueName_tpc_dci_rnti_type[]={
    {0,"C_RNTI"}
};
const ValueName ValueName_srs_request[]={
    {0,"No"}
};
const ValueName Valuename_tpc_dci_cell_index[]={
    {0,"PCC"}
};
const ValueName ValueName_tbs_index[]={
    {0,"TBS_INDEX_0"},
    {1,"TBS_INDEX_1"},
    {2,"TBS_INDEX_2"},
    {3,"TBS_INDEX_3"},
    {4,"TBS_INDEX_4"},
    {5,"TBS_INDEX_5"},
    {6,"TBS_INDEX_6"},
    {7,"TBS_INDEX_7"},
    {8,"TBS_INDEX_8"},
    {9,"TBS_INDEX_9"},
    {10,"TBS_INDEX_10"},
    {11,"TBS_INDEX_11"},
    {12,"TBS_INDEX_12"},
    {13,"TBS_INDEX_13"},
    {14,"TBS_INDEX_14"},
    {15,"TBS_INDEX_15"},
    {16,"TBS_INDEX_16"},
    {17,"TBS_INDEX_17"},
    {18,"TBS_INDEX_18"},
    {19,"TBS_INDEX_19"},
    {20,"TBS_INDEX_20"},
    {21,"TBS_INDEX_21"},
    {22,"TBS_INDEX_22"},
    {23,"TBS_INDEX_23"},
    {24,"TBS_INDEX_24"},
    {25,"TBS_INDEX_25"},
    {26,"TBS_INDEX_26"},
    {27,"TBS_INDEX_27"},
    {28,"TBS_INDEX_28"},
    {29,"TBS_INDEX_29"},
    {30,"TBS_INDEX_30"},
    {31,"TBS_INDEX_31"},
    {32,"TBS_INDEX_32"},
    {33,"TBS_INDEX_33"},
};

const ValueName ValueName_modulation_type[]={
    {2,"16 QAM"},
    {3,"64 QAM"}
};

const Fmt dci_ul_grant_info[]={
    {UINT, "dci_ul_grant_Byte12",2},
    {PLACEHOLDER,"Cell Index", 0},
    {PLACEHOLDER,"HARQ ID", 0},
    {PLACEHOLDER,"NDI", 0},
    {PLACEHOLDER,"TPC", 0},
    {PLACEHOLDER,"UL grant RNTI Type", 0},
    {PLACEHOLDER,"K of DCI", 0},
    {PLACEHOLDER,"UL Index/DAI", 0},
    {UINT, "dci_ul_grant_Byte34", 2},
    {PLACEHOLDER,"TBS Index", 0},
    {PLACEHOLDER,"MCS Index", 0},
    {PLACEHOLDER,"Redundancy version index", 0},
    {UINT, "dci_ul_grant_Byte5", 1},
    {PLACEHOLDER, "modulation type", 0},
    {PLACEHOLDER, "cqi request", 0},
    {PLACEHOLDER, "SRS Request", 0},
    {PLACEHOLDER, "Resource Allocation Type", 0},
    {UINT, "dci_ul_grant_Byte67",2},
    {PLACEHOLDER, "number of resource blocks", 0},
    {PLACEHOLDER, "start of resource block", 0},
    {PLACEHOLDER, "rbg size", 0},
    {UINT, "dci_ul_grant_Byte8", 1},
    {PLACEHOLDER, "cyclic shift dmrs", 0},
    {PLACEHOLDER, "hopping flag", 0},
    {PLACEHOLDER, "search space", 0},
    {UINT, "dci_ul_grant_Byte910",2},
    {PLACEHOLDER, "RIV value", 0},
    {PLACEHOLDER, "RIV Width", 0},
    {UINT, "dci_ul_grant_Byte1112",2},
    {PLACEHOLDER, "start of resource block 2", 0},
    {PLACEHOLDER, "number of resource blocks 2", 0},
    {UINT, "dci_ul_grant_Byte13", 1},
    {PLACEHOLDER, "tx antenna selection", 0},
    {PLACEHOLDER, "aggregation level", 0},
    {SKIP, NULL, 3}
};
const ValueName ValueName_dl_cell_index[]={
    {0,"PCC"},
    {1,"SCC1"},
    {2,"SCC2"}
};
const ValueName ValueName_dl_format_type[]={
    {0,"1a"},
    {1, "2"},
};

const Fmt dci_dl_grant_info[]={
    {UINT, "dci_dl_grant_Byte12", 2},
    {PLACEHOLDER, "DL Grant TPC Command", 0},
    {PLACEHOLDER, "Num Ack/Nack Bits", 0},
    {PLACEHOLDER, "DL Grant Cell Index", 0},
    {PLACEHOLDER, "DL Grant Format Type", 0},
    {PLACEHOLDER, "DAI", 0},
    {PLACEHOLDER, "DL Grant Srs Req", 0},
    {PLACEHOLDER, "DL Rnti Type", 0},  
    {PLACEHOLDER, "Aggregation Level dl", 0},
    {PLACEHOLDER, "Search Space dl", 0},  
    {UINT, "DL Grant N CCE", 1},
    {SKIP, NULL, 6}
};



static int _decode_dci_info_report_payload(const char *b, int offset, size_t length, PyObject *result){
    
    FILE *debug_file_3 = fopen("ty_debug3.txt","a");
    fprintf(debug_file_3,"open debug3 and get into dci payload decode\n ");
    uint utemp = _search_result_uint(result, "num records and cfg");
    fprintf(debug_file_3," utemp hex =%02x\n",utemp);
    
    // debug: number of records
    uint inumberofrecords = (utemp >> 6) & 31;
    // fprintf(debug_file_3," number of records dec =%u\n",inumberofrecords);
    // fprintf(debug_file_3," number of records hex =%02x\n",inumberofrecords);
    PyObject *old_object = _replace_result_int(result, "Number of Records", inumberofrecords);
    Py_DECREF(old_object);
    // int num_records_and_cfg_1 = (int) _map_result_field_to_name(
    //         result,
    //         "Number of Records",
    //         LogPacketTypeID_To_Name,
    //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
    //         "Unsupported");
    // fprintf(debug_file_3,"num of record is %d\n", num_records_and_cfg_1);



    //debug: subframe config
    uint isubframecfg = (utemp >> 2) & 15;
    //fprintf(debug_file_3," subframe crg dec =%u\n",isubframecfg);
    PyObject *old_object1 = _replace_result_int(result, "Subframe Cfg", isubframecfg);
    Py_DECREF(old_object1);   
    // int isubframecfg_debug = (int) _map_result_field_to_name(
    //         result,
    //         "Subframe Cfg",
    //         LogPacketTypeID_To_Name,
    //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
    //         "Unsupported");
    // fprintf(debug_file_3,"subframe cfg is %d\n", isubframecfg_debug);




    // make the header clear done
    int num_of_records = _search_result_uint(result, "Number of Records");
    fprintf(debug_file_3,"the num_of_records is %d\n", num_of_records);

    PyObject *result_record = PyList_New(0);//build the list of records
    for(int j=0; j<num_of_records; j++)
    {   
        PyObject *result_record_item = PyList_New(0);

        fprintf(debug_file_3,"\nthis is the %d record\n", j);
        fprintf(debug_file_3,"offset1=%d",offset);
        offset += _decode_by_fmt(dci_info_record_head,
            ARRAY_SIZE(dci_info_record_head, Fmt),
            b, offset, length, result_record_item);
        fprintf(debug_file_3,"offset2=%d",offset);
        // each records header
        uint dci_hdead_record = _search_result_uint(result_record_item, "dci record head");
        fprintf(debug_file_3,"ubyte1 hex =%08x\n",dci_hdead_record);
        
        //debug system_frame_number
        uint system_frame_number_dci_head = dci_hdead_record & 1023;
        fprintf(debug_file_3,"system fram number in dci head =%u\n",system_frame_number_dci_head);
        PyObject *old_object2 = _replace_result_int(result_record_item, "system frame number", system_frame_number_dci_head);
        Py_DECREF(old_object2);
        // int system_frame_number_dci_1 = (int) _map_result_field_to_name(
        //         result,
        //         "system frame number",
        //         LogPacketTypeID_To_Name,
        //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
        //         "Unsupported");
        // fprintf(debug_file_3,"system frame number is %d\n", system_frame_number_dci_1);

        //debug sub_frame_number
        uint sub_frame_num_dci_head = (dci_hdead_record>>10) & 15;
        fprintf(debug_file_3,"subframe number in dci head =%u\n",sub_frame_num_dci_head);
        PyObject *old_object3 = _replace_result_int(result_record_item, "subframe number", sub_frame_num_dci_head);
        Py_DECREF(old_object3);
        // int sub_frame_num_dci_1 = (int) _map_result_field_to_name(
        //         result,
        //         "subframe number",
        //         LogPacketTypeID_To_Name,
        //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
        //         "Unsupported");
        // fprintf(debug_file_3,"sub frame number is %d\n", sub_frame_num_dci_1);

        //debug ul grant
        uint ul_grant_i = (dci_hdead_record>>14) & 7;
        fprintf(debug_file_3,"ul grant in dci head =%u\n",ul_grant_i);
        PyObject *old_object4 = _replace_result_int(result_record_item, "ul grant num", ul_grant_i);
        Py_DECREF(old_object4);
        // int ul_grant_dci_i = (int) _map_result_field_to_name(
        //         result,
        //         "ul grant num",
        //         LogPacketTypeID_To_Name,
        //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
        //         "Unsupported");
        // fprintf(debug_file_3,"ul grant num is %d\n", ul_grant_dci_i);

        //debug dl grant
        uint dl_grant_i = (dci_hdead_record>>17) & 7;
        fprintf(debug_file_3,"dl grant in dci head =%u\n",dl_grant_i);
        PyObject *old_object5 = _replace_result_int(result_record_item, "dl grant num", dl_grant_i);
        Py_DECREF(old_object5);
        // int dl_grant_dci_i = (int) _map_result_field_to_name(
        //         result,
        //         "dl grant num",
        //         LogPacketTypeID_To_Name,
        //         ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
        //         "Unsupported");
        // fprintf(debug_file_3,"dl grant num is %d\n", dl_grant_dci_i);


        //tpc dci present

        uint U_tpc_dci_present = (dci_hdead_record >> 24) & 3;
        fprintf(debug_file_3,"U_tpc_dci_present is %02x\n", U_tpc_dci_present);
        PyObject *old_object6 = _replace_result_int(result_record_item, "TPC DCI Present", U_tpc_dci_present);
        Py_DECREF(old_object6);
        _map_result_field_to_name(
                result_record_item,
                "TPC DCI Present",
                ValueName_tpc_dci_present,
                ARRAY_SIZE(ValueName_tpc_dci_present, ValueName),
                "Unsupported");
    
        
        //tpc dci format type
        uint U_tpc_dci_format_type = (dci_hdead_record >> 26) & 3;
        fprintf(debug_file_3,"U_tpc_dci_format_type is %02x\n", U_tpc_dci_format_type);
        PyObject *old_object7 = _replace_result_int(result_record_item, "TPC DCI Format Type", U_tpc_dci_format_type);
        Py_DECREF(old_object7);
        _map_result_field_to_name(
                result_record_item,
                "TPC DCI Format Type",
                ValueName_tpc_dci_formate_type,
                ARRAY_SIZE(ValueName_tpc_dci_formate_type, ValueName),
                "Unsupported");
        
        //tpc dci rnti type
        uint U_tpc_dci_rnti_type = (dci_hdead_record >> 28) & 3;
        fprintf(debug_file_3,"U_tpc_dci_rnti_type is %02x\n", U_tpc_dci_rnti_type);
        PyObject *old_object8 = _replace_result_int(result_record_item, "TPC DCI RNTI Type", U_tpc_dci_format_type);
        Py_DECREF(old_object8);
        _map_result_field_to_name(
                result_record_item,
                "TPC DCI RNTI Type",
                ValueName_tpc_dci_rnti_type,
                ARRAY_SIZE(ValueName_tpc_dci_rnti_type, ValueName),
                "Unsupported");  
        

        //tpc dci tpc command
        uint U_tpc_command = (dci_hdead_record >> 32) & 3;
        fprintf(debug_file_3,"U_tpc_command is %02x\n", U_tpc_command);
        PyObject *old_object9 = _replace_result_int(result_record_item, "TPC DCI TPC Command", U_tpc_command);
        Py_DECREF(old_object9);    

        fprintf(debug_file_3,"payload record header end\n");


        if(ul_grant_i!=0)
        {
            PyObject *result_record_ul = PyList_New(0);//build the list of ul records
            for(int k=0;k<ul_grant_i;k++)
            {
                PyObject *result_record_ul_item = PyList_New(0);
                fprintf(debug_file_3,"this is the %d ul grant in %d record\n",k,j);
                offset += _decode_by_fmt(dci_ul_grant_info,
                        ARRAY_SIZE(dci_ul_grant_info, Fmt),
                        b, offset, length, result_record_ul_item);
                
                /*byte 1 2*/
                uint U_dci_ul_grant_Byte12 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte12");
                fprintf(debug_file_3,"\ndci_ul_grant_Byte12 hex = %02x\n\n", U_dci_ul_grant_Byte12);

                //cell index
                uint U_cell_index = (U_dci_ul_grant_Byte12>>9)&1;
                PyObject *old_object9 = _replace_result_int(result_record_ul_item, "Cell Index", U_cell_index);
                Py_DECREF(old_object9);
                _map_result_field_to_name(
                    result_record_ul_item,
                    "Cell Index",
                    Valuename_tpc_dci_cell_index,
                    ARRAY_SIZE(Valuename_tpc_dci_cell_index, ValueName),
                    "Unsupported");  
                
                //harq id
                uint U_harq_id = (U_dci_ul_grant_Byte12>>4)&7;
                PyObject *old_object10 = _replace_result_int(result_record_ul_item, "HARQ ID", U_harq_id);
                Py_DECREF(old_object10);
                int harq_id_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "HARQ ID",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"HARQ ID is dec %d\n", harq_id_debug);

                //NDI
                uint U_NDI = (U_dci_ul_grant_Byte12 >> 3) & 1;
                PyObject *old_object11 = _replace_result_int(result_record_ul_item, "NDI", U_NDI);
                Py_DECREF(old_object11);
                int ndi_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "NDI",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"NDI is dec %d\n", ndi_debug);     

                //tpc
                uint U_tpc = (U_dci_ul_grant_Byte12 >> 7) & 3;
                PyObject *old_object12 = _replace_result_int(result_record_ul_item, "TPC", U_tpc);
                Py_DECREF(old_object12);
                int TPC_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "TPC",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"TPC is dec %d\n", TPC_debug);
                
                //rnti type
                uint U_rnti_type = U_dci_ul_grant_Byte12 & 7;
                fprintf(debug_file_3,"U_rnti_type hex=%02x\n",U_rnti_type);
                PyObject *old_object13 = _replace_result_int(result_record_ul_item, "UL grant RNTI Type", U_rnti_type);
                Py_DECREF(old_object13);
                _map_result_field_to_name(
                        result_record_ul_item,
                        "UL grant RNTI Type",
                        ValueName_tpc_dci_rnti_type,
                        ARRAY_SIZE(ValueName_tpc_dci_rnti_type, ValueName),
                        "Unsupported");

                //K of DCI
                uint U_k_of_DCI = (U_dci_ul_grant_Byte12 >> 13) & 7;
                PyObject *old_object14 = _replace_result_int(result_record_ul_item, "K of DCI", U_k_of_DCI);
                Py_DECREF(old_object14);
                int K_of_DCI_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "K of DCI",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"K_of_DCI_debug is dec %d\n", K_of_DCI_debug);   

                //UL Index/DAI
                uint U_DAI = (U_dci_ul_grant_Byte12 >> 10) & 7;
                PyObject *old_object15 = _replace_result_int(result_record_ul_item, "UL Index/DAI", U_DAI);
                Py_DECREF(old_object15);
                int DAI_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "UL Index/DAI",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"DAI_debug is dec %d\n", DAI_debug);   

                /*byte 3 4*/
                uint U_dci_ul_grant_Byte34 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte34");
                fprintf(debug_file_3,"\ndci_ul_grant_Byte34 hex = %02x\n\n", U_dci_ul_grant_Byte34);

                //TBS_index
                uint U_TBS_index = (U_dci_ul_grant_Byte34 >> 10) & 63;
                fprintf(debug_file_3,"U_TBS_Index hex=%02x\n",U_TBS_index);
                PyObject *old_object16 = _replace_result_int(result_record_ul_item, "TBS Index", U_TBS_index);
                Py_DECREF(old_object16);                
                _map_result_field_to_name(
                        result_record_ul_item,
                        "TBS Index",
                        ValueName_tbs_index,
                        ARRAY_SIZE(ValueName_tbs_index, ValueName),
                        "Unsupported");
                
                //MCS index
                uint U_MCS_index = (U_dci_ul_grant_Byte34 >> 5) & 31;
                //fprintf(debug_file_3,"U_MCS_index hex=%02x\n",U_MCS_index);
                PyObject *old_object17 = _replace_result_int(result_record_ul_item, "MCS Index", U_MCS_index);
                Py_DECREF(old_object17);
                int MCS_index_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "MCS Index",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"MCS_index_debug dec is %d\n", MCS_index_debug);   

                //Redundancy version index
                uint U_redundancy_version_index = (U_dci_ul_grant_Byte34 >> 3) & 3;
                //fprintf(debug_file_3,"U_redundancy_version_index hex =%02x\n",U_redundancy_version_index);
                PyObject *old_object18 = _replace_result_int(result_record_ul_item, "Redundancy version index", U_redundancy_version_index);
                Py_DECREF(old_object18);
                int Redundancy_version_index_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "Redundancy version index",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"Redundancy_version_index_debug is dec %d\n", Redundancy_version_index_debug); 


                /*byte 5*/
                uint U_dci_ul_grant_Byte5 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte5");
                fprintf(debug_file_3,"\ndci_ul_grant_Byte5 hex = %02x\n\n", U_dci_ul_grant_Byte5);
                
                
                //modulation type
                uint U_modulation_type = U_dci_ul_grant_Byte5 & 3;
                fprintf(debug_file_3,"U_modulation_type hex =%02x\n",U_modulation_type);
                PyObject *old_object19 = _replace_result_int(result_record_ul_item, "modulation type", U_modulation_type);
                Py_DECREF(old_object19);
                _map_result_field_to_name(
                        result_record_ul_item,
                        "modulation type",
                        ValueName_modulation_type,
                        ARRAY_SIZE(ValueName_modulation_type, ValueName),
                        "Unsupported");
                
                //cqi request
                uint U_cqi_request = (U_dci_ul_grant_Byte5>>3) & 3;
                //fprintf(debug_file_3,"U_cqi_request hex =%02x\n",U_cqi_request);
                PyObject *old_object20 = _replace_result_int(result_record_ul_item, "cqi request", U_cqi_request);
                Py_DECREF(old_object20);
                int cqi_request_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "cqi request",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"cqi request is dec %d\n", cqi_request_debug);

                //srs request
                uint U_srs_request = (U_dci_ul_grant_Byte5>>6)&1;
                fprintf(debug_file_3,"U_srs_request hex =%02x\n",U_srs_request);
                PyObject *old_object21 = _replace_result_int(result_record_ul_item, "SRS Request", U_srs_request);
                Py_DECREF(old_object21);
                _map_result_field_to_name(
                        result_record_ul_item,
                        "SRS Request",
                        ValueName_srs_request,
                        ARRAY_SIZE(ValueName_srs_request, ValueName),
                        "Unsupported");   

                //resource allocation type
                uint U_resource_allocation_type = (U_dci_ul_grant_Byte5>>7) & 1;
                //fprintf(debug_file_3,"U_resource_allocation_type hex =%02x\n",U_resource_allocation_type);
                PyObject *old_object22 = _replace_result_int(result_record_ul_item, "Resource Allocation Type", U_resource_allocation_type);
                Py_DECREF(old_object22);
                int resource_allocation_type_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "Resource Allocation Type",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"Resource Allocation Type is dec %d\n", resource_allocation_type_debug);                             


                /*byte 6 7*/
                uint U_dci_ul_grant_Byte67 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte67");
                fprintf(debug_file_3,"\nU_dci_ul_grant_Byte67 hex = %02x\n\n", U_dci_ul_grant_Byte67);

                //number of resource blocks
                uint U_num_resource_block = (U_dci_ul_grant_Byte67>>10) & 63;
                //fprintf(debug_file_3,"U_num_resource_block hex =%02x\n",U_num_resource_block);
                PyObject *old_object23 = _replace_result_int(result_record_ul_item, "number of resource blocks", U_num_resource_block);
                Py_DECREF(old_object23);
                int U_num_resource_block_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "number of resource blocks",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_num_resource_block_debug is dec %d\n", U_num_resource_block_debug);  

                //start of resource block
                uint U_start_of_resource_block = (U_dci_ul_grant_Byte67>>3) & 127;
                //fprintf(debug_file_3,"U_start_of_resource_block hex =%02x\n",U_start_of_resource_block);
                PyObject *old_object24 = _replace_result_int(result_record_ul_item, "start of resource block", U_start_of_resource_block);
                Py_DECREF(old_object24);
                int U_start_of_resource_block_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "start of resource block",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_start_of_resource_block_debug is dec %d\n", U_start_of_resource_block_debug);  

                //rbg size
                uint U_rbg_size = U_dci_ul_grant_Byte67 & 7;
                //fprintf(debug_file_3,"U_rbg_size hex =%02x\n",U_rbg_size);
                PyObject *old_object25 = _replace_result_int(result_record_ul_item, "rbg size", U_rbg_size);
                Py_DECREF(old_object25);
                int U_rbg_size_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "rbg size",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_rbg_size is dec %d\n", U_rbg_size_debug);  

                /*Byte 8*/
                uint U_dci_ul_grant_Byte8 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte8");
                fprintf(debug_file_3,"\nU_dci_ul_grant_Byte8 hex = %02x\n\n", U_dci_ul_grant_Byte8);

                //cyclic shift dmrs
                uint u_cyclic_shift_dmrs = (U_dci_ul_grant_Byte8 >> 1) & 7;
                //fprintf(debug_file_3,"u_cyclic_shift_dmrs hex =%02x\n",u_cyclic_shift_dmrs);
                PyObject *old_object26 = _replace_result_int(result_record_ul_item, "cyclic shift dmrs", u_cyclic_shift_dmrs);
                Py_DECREF(old_object26);
                int u_cyclic_shift_dmrs_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "cyclic shift dmrs",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_cyclic_shift_dmrs_debug is dec %d\n", u_cyclic_shift_dmrs_debug);  

                //hopping flag
                uint u_hopping_flag = (U_dci_ul_grant_Byte8 >> 7) & 1;
                //fprintf(debug_file_3,"u_hopping_flag hex =%02x\n",u_hopping_flag);
                PyObject *old_object27 = _replace_result_int(result_record_ul_item, "hopping flag", u_hopping_flag);
                Py_DECREF(old_object27);
                int u_hopping_flag_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "hopping flag",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_hopping_flag_debug is dec %d\n", u_hopping_flag_debug); 

                // search space
                uint u_search_space = (U_dci_ul_grant_Byte8 >> 5) & 1;
                //fprintf(debug_file_3,"u_search_space hex =%02x\n",u_search_space);
                PyObject *old_object28 = _replace_result_int(result_record_ul_item, "search space", u_search_space);
                Py_DECREF(old_object28);
                int u_search_space_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "search space",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_search_space_debug is dec %d\n", u_search_space_debug); 

                /*Byte 9 10*/
                uint U_dci_ul_grant_Byte910 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte910");
                fprintf(debug_file_3,"\nU_dci_ul_grant_Byte910 hex = %02x\n\n", U_dci_ul_grant_Byte910);

                //RIV value
                uint u_riv_value = (U_dci_ul_grant_Byte910 >> 4) & 4095;
                //fprintf(debug_file_3,"u_riv_value hex =%02x\n",u_riv_value);
                PyObject *old_object29 = _replace_result_int(result_record_ul_item, "RIV value", u_riv_value);
                Py_DECREF(old_object29);
                int u_riv_value_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "RIV value",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_riv_value_debug is dec %d\n", u_riv_value_debug); 

                //RIV width
                uint u_riv_width = U_dci_ul_grant_Byte910  & 15;
                //fprintf(debug_file_3,"u_riv_width hex =%02x\n",u_riv_width);
                PyObject *old_object30 = _replace_result_int(result_record_ul_item, "RIV Width", u_riv_width);
                Py_DECREF(old_object30);
                int u_riv_width_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "RIV Width",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_riv_width_debug is dec %d\n", u_riv_width_debug); 

                /*Byte 11 12*/
                uint U_dci_ul_grant_Byte1112 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte1112");
                fprintf(debug_file_3,"\nU_dci_ul_grant_Byte1112 hex = %02x\n\n", U_dci_ul_grant_Byte1112);

                //start of resource block 2
                uint u_start_of_resource_block_2 = (U_dci_ul_grant_Byte1112>>2)  & 127;
                //fprintf(debug_file_3,"u_start_of_resource_block_2 =%02x\n",u_start_of_resource_block_2);
                PyObject *old_object31 = _replace_result_int(result_record_ul_item, "start of resource block 2", u_start_of_resource_block_2);
                Py_DECREF(old_object31);
                int u_start_of_resource_block_2_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "start of resource block 2",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_start_of_resource_block_2_debug is dec %d\n", u_start_of_resource_block_2_debug);                 

                //number of resource block 2
                uint u_number_of_resource_block_2 = (U_dci_ul_grant_Byte1112>>9)  & 127;
                //fprintf(debug_file_3,"u_number_of_resource_block_2 =%02x\n",u_number_of_resource_block_2);
                PyObject *old_object32 = _replace_result_int(result_record_ul_item, "number of resource blocks 2", u_number_of_resource_block_2);
                Py_DECREF(old_object32);
                int u_number_of_resource_block_2_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "number of resource blocks 2",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_number_of_resource_block_2_debug is dec %d\n", u_number_of_resource_block_2_debug);                 


                /*Byte 13*/
                uint U_dci_ul_grant_Byte13 = _search_result_uint(result_record_ul_item, "dci_ul_grant_Byte13");
                fprintf(debug_file_3,"\nU_dci_ul_grant_Byte13 hex = %02x\n\n", U_dci_ul_grant_Byte13);

                //TX Antenna Selection
                uint u_tx_antenna_selection = (U_dci_ul_grant_Byte13>>7)  & 1;
                //fprintf(debug_file_3,"u_tx_antenna_selection =%02x\n",u_tx_antenna_selection);
                PyObject *old_object33 = _replace_result_int(result_record_ul_item, "tx antenna selection", u_tx_antenna_selection);
                Py_DECREF(old_object33);
                int u_tx_antenna_selection_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "tx antenna selection",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_tx_antenna_selection_debug is dec %d\n", u_tx_antenna_selection_debug);                 


                //Aggregation level
                uint u_aggregation_level = (U_dci_ul_grant_Byte13>>3)  & 7;
                //fprintf(debug_file_3,"u_tx_antenna_selection =%02x\n",u_tx_antenna_selection);
                PyObject *old_object34 = _replace_result_int(result_record_ul_item, "aggregation level", u_aggregation_level);
                Py_DECREF(old_object34);
                int u_aggregation_level_debug = (int) _map_result_field_to_name(
                        result_record_ul_item,
                        "aggregation level",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"u_aggregation_level_debug is dec %d\n", u_aggregation_level_debug);  
                

                PyObject *t1 = Py_BuildValue("(sOs)", "Records ul item",
                                                    result_record_ul_item, "dict");
                PyList_Append(result_record_ul, t1);   
                Py_DECREF(t1);
                Py_DECREF(result_record_ul_item);
            }
            PyObject *t2 = Py_BuildValue("(sOs)", "Records ul",
                                                result_record_ul, "list");
            PyList_Append(result_record_item, t2);   
            Py_DECREF(t2);
            Py_DECREF(result_record_ul);            
        }
        if(dl_grant_i!=0)
        {
            PyObject *result_record_dl = PyList_New(0);//build dl list
            for(int kd=0;kd<dl_grant_i;kd++)
            {
                PyObject *result_record_dl_item = PyList_New(0);
                fprintf(debug_file_3,"this is the %d dl grant in %d record\n",kd,j);
                offset += _decode_by_fmt(dci_dl_grant_info,
                        ARRAY_SIZE(dci_dl_grant_info, Fmt),
                        b, offset, length, result_record_dl_item);                
                
                /*byte 1 2*/
                uint U_dci_dl_grant_Byte12 = _search_result_uint(result_record_dl_item, "dci_dl_grant_Byte12");
                fprintf(debug_file_3,"\ndci_dl_grant_Byte12 hex = %02x\n\n", U_dci_dl_grant_Byte12);

                //dl grant tpc command
                uint U_dl_grant_tpc_command = (U_dci_dl_grant_Byte12>>9)&3;
                PyObject *old_object35 = _replace_result_int(result_record_dl_item, "DL Grant TPC Command", U_dl_grant_tpc_command);
                Py_DECREF(old_object35);
                int U_dl_grant_tpc_command_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "DL Grant TPC Command",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_dl_grant_tpc_command_debug is dec %d\n", U_dl_grant_tpc_command_debug);

                //num ack/nak bits
                uint U_num_ack_bits = (U_dci_dl_grant_Byte12>>7)&3;
                fprintf(debug_file_3,"U_num_ack_bits is hex is %02x\n", U_num_ack_bits);
                PyObject *old_object36 = _replace_result_int(result_record_dl_item, "Num Ack/Nack Bits", U_num_ack_bits);
                Py_DECREF(old_object36);
                int U_num_ack_bits_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "Num Ack/Nack Bits",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_num_ack_bits_debug is dec %d\n", U_num_ack_bits_debug);

                //dl grant cell index
                uint U_dl_cell_index = (U_dci_dl_grant_Byte12) & 7;
                fprintf(debug_file_3,"dl cell index is hex %02x\n", U_dl_cell_index);
                PyObject *old_object37 = _replace_result_int(result_record_dl_item, "DL Grant Cell Index", U_dl_cell_index);
                Py_DECREF(old_object37);               
                _map_result_field_to_name(
                    result_record_dl_item,
                    "DL Grant Cell Index",
                    ValueName_dl_cell_index,
                    ARRAY_SIZE(ValueName_dl_cell_index, ValueName),
                    "Unsupported");  
                
                //dl grant format type
                uint U_dl_grant_format_type = (U_dci_dl_grant_Byte12>>5) & 3;
                fprintf(debug_file_3,"U_dl_grant_format_type is hex %02x\n", U_dl_grant_format_type);
                PyObject *old_object38 = _replace_result_int(result_record_dl_item, "DL Grant Format Type", U_dl_cell_index);
                Py_DECREF(old_object38);               
                _map_result_field_to_name(
                    result_record_dl_item,
                    "DL Grant Format Type",
                    ValueName_dl_format_type,
                    ARRAY_SIZE(ValueName_dl_format_type, ValueName),
                    "Unsupported");  
                
                //dai
                uint U_dai = (U_dci_dl_grant_Byte12>>12)&1;
                fprintf(debug_file_3, "dai debug hex is %02x\n", U_dai);
                PyObject *old_object39 = _replace_result_int(result_record_dl_item, "DAI", U_dai);
                Py_DECREF(old_object39);
                int U_dai_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "DAI",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_dai_debug is dec %d\n", U_dai_debug);

                //DL grant srs req
                uint U_dl_grant_srs_req = (U_dci_dl_grant_Byte12>>3)&1;
                PyObject *old_object40 = _replace_result_int(result_record_dl_item, "DL Grant Srs Req", U_dl_grant_srs_req);
                Py_DECREF(old_object40);
                int U_dl_grant_srs_req_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "DL Grant Srs Req",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_dl_grant_srs_req_debug is dec %d\n", U_dl_grant_srs_req_debug);

                //rnti type
                uint U_dl_rnti_type = (U_dci_dl_grant_Byte12 >> 15) & 1;
                fprintf(debug_file_3,"U_dl_rnti_type is %02x\n", U_dl_rnti_type);
                PyObject *old_object41 = _replace_result_int(result_record_dl_item, "DL Rnti Type", U_dl_rnti_type);
                Py_DECREF(old_object41);
                _map_result_field_to_name(
                        result_record_dl_item,
                        "DL Rnti Type",
                        ValueName_tpc_dci_rnti_type,
                        ARRAY_SIZE(ValueName_tpc_dci_rnti_type, ValueName),
                        "Unsupported");  
                
                //aggregation level
                uint U_aggregation_level_dl = (U_dci_dl_grant_Byte12>>14)&1;
                PyObject *old_object42 = _replace_result_int(result_record_dl_item, "Aggregation Level dl", U_aggregation_level_dl);
                Py_DECREF(old_object42);
                int U_aggregation_level_dl_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "Aggregation Level dl",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_aggregation_level_dl_debug is dec %d\n", U_aggregation_level_dl_debug);

                //search space
                uint U_search_space_dl = (U_dci_dl_grant_Byte12>>13)&1;
                PyObject *old_object43 = _replace_result_int(result_record_dl_item, "Search Space dl", U_search_space_dl);
                Py_DECREF(old_object43);
                int U_search_space_dl_debug = (int) _map_result_field_to_name(
                        result_record_dl_item,
                        "Search Space dl",
                        LogPacketTypeID_To_Name,
                        ARRAY_SIZE(LogPacketTypeID_To_Name, ValueName),
                        "Unsupported");
                fprintf(debug_file_3,"U_search_space_dl_debug is dec %d\n", U_search_space_dl_debug);

                /*byte 3*/
                //don't need process

                PyObject *t3 = Py_BuildValue("(sOs)", "Records dl item",
                                    result_record_dl_item, "dict");
                PyList_Append(result_record_dl, t3);   
                Py_DECREF(t3);
                Py_DECREF(result_record_dl_item);
            }
            PyObject *t4 = Py_BuildValue("(sOs)", "Records dl",
                                    result_record_dl, "list");
            PyList_Append(result_record_item, t4);   
            Py_DECREF(t4);
            Py_DECREF(result_record_dl);             
        }
        
        PyObject *t6 = Py_BuildValue("(sOs)", "ignored",
                        result_record_item, "dict");
        PyList_Append(result_record, t6);  
        Py_DECREF(t6);
        Py_DECREF(result_record_item); 
    }
    PyObject *t7 = Py_BuildValue("(sOs)", "Records",
                result_record, "list");
    PyList_Append(result, t7);  
    Py_DECREF(t7);
    Py_DECREF(result_record); 


    fprintf(debug_file_3,"file 3 close");
    fclose(debug_file_3);
    return 0;
}