/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DCIReportModule"
 * 	found in "dci_test.asn1"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_DlGrantCellIndex_H_
#define	_DlGrantCellIndex_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum DlGrantCellIndex {
	DlGrantCellIndex_pcc	= 0,
	DlGrantCellIndex_scc1	= 1,
	DlGrantCellIndex_scc2	= 2,
	DlGrantCellIndex_unkown3	= 3,
	DlGrantCellIndex_unkown4	= 4,
	DlGrantCellIndex_unkown5	= 5,
	DlGrantCellIndex_unkown6	= 6,
	DlGrantCellIndex_unkown7	= 7
} e_DlGrantCellIndex;

/* DlGrantCellIndex */
typedef long	 DlGrantCellIndex_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_DlGrantCellIndex_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_DlGrantCellIndex;
extern const asn_INTEGER_specifics_t asn_SPC_DlGrantCellIndex_specs_1;
asn_struct_free_f DlGrantCellIndex_free;
asn_struct_print_f DlGrantCellIndex_print;
asn_constr_check_f DlGrantCellIndex_constraint;
ber_type_decoder_f DlGrantCellIndex_decode_ber;
der_type_encoder_f DlGrantCellIndex_encode_der;
xer_type_decoder_f DlGrantCellIndex_decode_xer;
xer_type_encoder_f DlGrantCellIndex_encode_xer;
oer_type_decoder_f DlGrantCellIndex_decode_oer;
oer_type_encoder_f DlGrantCellIndex_encode_oer;
per_type_decoder_f DlGrantCellIndex_decode_uper;
per_type_encoder_f DlGrantCellIndex_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _DlGrantCellIndex_H_ */
#include <asn_internal.h>