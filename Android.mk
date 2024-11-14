LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := diag_revealer

ASN1_SRC_FILES := $(wildcard asn1_group/*.c)

LOCAL_SRC_FILES := diag_revealer.c generate_diag_cfg.c decode.c $(ASN1_SRC_FILES)

LOCAL_C_INCLUDES := ./asn1_group


LOCAL_LDLIBS    := -L$(SYSROOT)/usr/lib -llog

include $(BUILD_EXECUTABLE)
