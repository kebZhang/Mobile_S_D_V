include Makefile.am.libasncodec

LIBS += -lm
CFLAGS += $(ASN_MODULE_CFLAGS) -DASN_PDU_COLLECTION -I.
ASN_LIBRARY ?= libasncodec.a
ASN_PROGRAM ?= converter-example
ASN_PROGRAM_SRCS ?= \
	converter-example.c\
	pdu_collection.c

all: $(ASN_PROGRAM)

$(ASN_PROGRAM): $(ASN_LIBRARY) $(ASN_PROGRAM_SRCS:.c=.o)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(ASN_PROGRAM) $(ASN_PROGRAM_SRCS:.c=.o) $(LDFLAGS) $(ASN_LIBRARY) $(LIBS)

$(ASN_LIBRARY): $(ASN_MODULE_SRCS:.c=.o)
	$(AR) rcs $@ $(ASN_MODULE_SRCS:.c=.o)

.SUFFIXES:
.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(ASN_PROGRAM) $(ASN_LIBRARY)
	rm -f $(ASN_MODULE_SRCS:.c=.o) $(ASN_PROGRAM_SRCS:.c=.o)

regen: regenerate-from-asn1-source

regenerate-from-asn1-source:
	asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto LTE_Contention_Resolution_Message_MSG4_Report.asn1 LTE_LL1_PCFICH_Decoding_Results.asn1 LTE_LL1_RACH_TX_Report.asn1 LTE_LL1_Serving_Cell_Measurement_Results.asn1 LTE_ML1_AdvRx_IC_Cell_List.asn1 LTE_ML1_CA_Metrics_Log_Packet.asn1 LTE_ML1_Cell_Measurement_Results.asn1 LTE_ML1_Common _DC_Offset.asn1 LTE_ML1_DCI_Information_Report.asn1 LTE_ML1_GM_TX_Report.asn1 LTE_ML1_Idle_Measurement_Request.asn1 LTE_ML1_Intra_Frequency_Cell_Reselection.asn1 LTE_ML1_Random_Access_Request_MSG1_ Report.asn1 LTE_ML1_Random_Access_Response_MSG2_Report.asn1 LTE_ML1_S_Criteria_Check_Procedure.asn1 LTE_ML1_Serving_Cell_Information.asn1 LTE_ML1_Serving_Cell_Measurements_And_Evaluation.asn1 LTE_PDCP_DL_Data_PDU.asn1 LTE_PDCP_UL_Delay_Statistics.asn1 LTE_RLC_DL_AM_Control_PDU.asn1 LTE_RRC_Supported_CA_Combos.asn1 LTE_UE_Identification_Message_MSG3_Report.asn1 Metadata_Header.asn1

