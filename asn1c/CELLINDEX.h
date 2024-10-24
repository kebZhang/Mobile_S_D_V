/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DCIReportModule"
 * 	found in "dci_test.asn1"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_CELLINDEX_H_
#define	_CELLINDEX_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum CELLINDEX {
	CELLINDEX_pcc	= 0,
	CELLINDEX_unknown	= 1
} e_CELLINDEX;

/* CELLINDEX */
typedef long	 CELLINDEX_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_CELLINDEX_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_CELLINDEX;
extern const asn_INTEGER_specifics_t asn_SPC_CELLINDEX_specs_1;
asn_struct_free_f CELLINDEX_free;
asn_struct_print_f CELLINDEX_print;
asn_constr_check_f CELLINDEX_constraint;
ber_type_decoder_f CELLINDEX_decode_ber;
der_type_encoder_f CELLINDEX_encode_der;
xer_type_decoder_f CELLINDEX_decode_xer;
xer_type_encoder_f CELLINDEX_encode_xer;
oer_type_decoder_f CELLINDEX_decode_oer;
oer_type_encoder_f CELLINDEX_encode_oer;
per_type_decoder_f CELLINDEX_decode_uper;
per_type_encoder_f CELLINDEX_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _CELLINDEX_H_ */
#include <asn_internal.h>
