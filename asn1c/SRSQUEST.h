/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DCIReportModule"
 * 	found in "dci_test.asn1"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_SRSQUEST_H_
#define	_SRSQUEST_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum SRSQUEST {
	SRSQUEST_no	= 0,
	SRSQUEST_unknown	= 1
} e_SRSQUEST;

/* SRSQUEST */
typedef long	 SRSQUEST_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_SRSQUEST_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_SRSQUEST;
extern const asn_INTEGER_specifics_t asn_SPC_SRSQUEST_specs_1;
asn_struct_free_f SRSQUEST_free;
asn_struct_print_f SRSQUEST_print;
asn_constr_check_f SRSQUEST_constraint;
ber_type_decoder_f SRSQUEST_decode_ber;
der_type_encoder_f SRSQUEST_encode_der;
xer_type_decoder_f SRSQUEST_decode_xer;
xer_type_encoder_f SRSQUEST_encode_xer;
oer_type_decoder_f SRSQUEST_decode_oer;
oer_type_encoder_f SRSQUEST_encode_oer;
per_type_decoder_f SRSQUEST_decode_uper;
per_type_encoder_f SRSQUEST_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _SRSQUEST_H_ */
#include <asn_internal.h>