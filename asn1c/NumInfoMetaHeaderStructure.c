/*
 * Generated by asn1c-0.9.29 (http://lionet.info/asn1c)
 * From ASN.1 module "DCIReportModule"
 * 	found in "dci_test.asn1"
 * 	`asn1c -S /usr/local/share/asn1c -fcompound-names -fskeletons-copy -gen-PER -pdu=auto`
 */

#include "NumInfoMetaHeaderStructure.h"

static int
memb_skip1_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_numofrecords_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 31)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_subframecfg_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 15)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static int
memb_skip2_constraint_1(const asn_TYPE_descriptor_t *td, const void *sptr,
			asn_app_constraint_failed_f *ctfailcb, void *app_key) {
	long value;
	
	if(!sptr) {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: value not given (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
	
	value = *(const long *)sptr;
	
	if((value >= 0 && value <= 3)) {
		/* Constraint check succeeded */
		return 0;
	} else {
		ASN__CTFAIL(app_key, td, sptr,
			"%s: constraint failed (%s:%d)",
			td->name, __FILE__, __LINE__);
		return -1;
	}
}

static asn_oer_constraints_t asn_OER_memb_skip1_constr_3 CC_NOTUSED = {
	{ 1, 1 }	/* (0..15) */,
	-1};
static asn_per_constraints_t asn_PER_memb_skip1_constr_3 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_numofrecords_constr_4 CC_NOTUSED = {
	{ 1, 1 }	/* (0..31) */,
	-1};
static asn_per_constraints_t asn_PER_memb_numofrecords_constr_4 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 5,  5,  0,  31 }	/* (0..31) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_subframecfg_constr_5 CC_NOTUSED = {
	{ 1, 1 }	/* (0..15) */,
	-1};
static asn_per_constraints_t asn_PER_memb_subframecfg_constr_5 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 4,  4,  0,  15 }	/* (0..15) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
static asn_oer_constraints_t asn_OER_memb_skip2_constr_6 CC_NOTUSED = {
	{ 1, 1 }	/* (0..3) */,
	-1};
static asn_per_constraints_t asn_PER_memb_skip2_constr_6 CC_NOTUSED = {
	{ APC_CONSTRAINED,	 2,  2,  0,  3 }	/* (0..3) */,
	{ APC_UNCONSTRAINED,	-1, -1,  0,  0 },
	0, 0	/* No PER value map */
};
asn_TYPE_member_t asn_MBR_NumInfoMetaHeaderStructure_1[] = {
	{ ATF_NOFLAGS, 0, offsetof(struct NumInfoMetaHeaderStructure, duplexmode),
		(ASN_TAG_CLASS_UNIVERSAL | (10 << 2)),
		0,
		&asn_DEF_DuplexMode,
		0,
		{ 0, 0, 0 },
		0, 0, /* No default value */
		"duplexmode"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NumInfoMetaHeaderStructure, skip1),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_skip1_constr_3, &asn_PER_memb_skip1_constr_3,  memb_skip1_constraint_1 },
		0, 0, /* No default value */
		"skip1"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NumInfoMetaHeaderStructure, numofrecords),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_numofrecords_constr_4, &asn_PER_memb_numofrecords_constr_4,  memb_numofrecords_constraint_1 },
		0, 0, /* No default value */
		"numofrecords"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NumInfoMetaHeaderStructure, subframecfg),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_subframecfg_constr_5, &asn_PER_memb_subframecfg_constr_5,  memb_subframecfg_constraint_1 },
		0, 0, /* No default value */
		"subframecfg"
		},
	{ ATF_NOFLAGS, 0, offsetof(struct NumInfoMetaHeaderStructure, skip2),
		(ASN_TAG_CLASS_UNIVERSAL | (2 << 2)),
		0,
		&asn_DEF_NativeInteger,
		0,
		{ &asn_OER_memb_skip2_constr_6, &asn_PER_memb_skip2_constr_6,  memb_skip2_constraint_1 },
		0, 0, /* No default value */
		"skip2"
		},
};
static const ber_tlv_tag_t asn_DEF_NumInfoMetaHeaderStructure_tags_1[] = {
	(ASN_TAG_CLASS_UNIVERSAL | (16 << 2))
};
static const asn_TYPE_tag2member_t asn_MAP_NumInfoMetaHeaderStructure_tag2el_1[] = {
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 1, 0, 3 }, /* skip1 */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 2, -1, 2 }, /* numofrecords */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 3, -2, 1 }, /* subframecfg */
    { (ASN_TAG_CLASS_UNIVERSAL | (2 << 2)), 4, -3, 0 }, /* skip2 */
    { (ASN_TAG_CLASS_UNIVERSAL | (10 << 2)), 0, 0, 0 } /* duplexmode */
};
asn_SEQUENCE_specifics_t asn_SPC_NumInfoMetaHeaderStructure_specs_1 = {
	sizeof(struct NumInfoMetaHeaderStructure),
	offsetof(struct NumInfoMetaHeaderStructure, _asn_ctx),
	asn_MAP_NumInfoMetaHeaderStructure_tag2el_1,
	5,	/* Count of tags in the map */
	0, 0, 0,	/* Optional elements (not needed) */
	-1,	/* First extension addition */
};
asn_TYPE_descriptor_t asn_DEF_NumInfoMetaHeaderStructure = {
	"NumInfoMetaHeaderStructure",
	"NumInfoMetaHeaderStructure",
	&asn_OP_SEQUENCE,
	asn_DEF_NumInfoMetaHeaderStructure_tags_1,
	sizeof(asn_DEF_NumInfoMetaHeaderStructure_tags_1)
		/sizeof(asn_DEF_NumInfoMetaHeaderStructure_tags_1[0]), /* 1 */
	asn_DEF_NumInfoMetaHeaderStructure_tags_1,	/* Same as above */
	sizeof(asn_DEF_NumInfoMetaHeaderStructure_tags_1)
		/sizeof(asn_DEF_NumInfoMetaHeaderStructure_tags_1[0]), /* 1 */
	{ 0, 0, SEQUENCE_constraint },
	asn_MBR_NumInfoMetaHeaderStructure_1,
	5,	/* Elements count */
	&asn_SPC_NumInfoMetaHeaderStructure_specs_1	/* Additional specs */
};
