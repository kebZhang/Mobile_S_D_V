/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DCIReportModule"
 * 	found in "dci_test.asn1"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#ifndef	_ModulationType_H_
#define	_ModulationType_H_


#include <asn_application.h>

/* Including external dependencies */
#include <NativeEnumerated.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Dependencies */
typedef enum ModulationType {
	ModulationType_unknown0	= 0,
	ModulationType_unknown1	= 1,
	ModulationType_i16qam	= 2,
	ModulationType_i64qam	= 3,
	ModulationType_unknown4	= 4,
	ModulationType_unknown5	= 5,
	ModulationType_unknown6	= 6,
	ModulationType_unknown7	= 7
} e_ModulationType;

/* ModulationType */
typedef long	 ModulationType_t;

/* Implementation */
extern asn_per_constraints_t asn_PER_type_ModulationType_constr_1;
extern asn_TYPE_descriptor_t asn_DEF_ModulationType;
extern const asn_INTEGER_specifics_t asn_SPC_ModulationType_specs_1;
asn_struct_free_f ModulationType_free;
asn_struct_print_f ModulationType_print;
asn_constr_check_f ModulationType_constraint;
ber_type_decoder_f ModulationType_decode_ber;
der_type_encoder_f ModulationType_encode_der;
xer_type_decoder_f ModulationType_decode_xer;
xer_type_encoder_f ModulationType_encode_xer;
oer_type_decoder_f ModulationType_decode_oer;
oer_type_encoder_f ModulationType_encode_oer;
per_type_decoder_f ModulationType_decode_uper;
per_type_encoder_f ModulationType_encode_uper;

#ifdef __cplusplus
}
#endif

#endif	/* _ModulationType_H_ */
#include <asn_internal.h>