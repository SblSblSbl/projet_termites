LOCAL_PATH := $(call my-dir)


# ========================================================
# termites (host)
# ========================================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES := projet_termites_outils_terminal.cpp projet_termites_common.cpp termite.cpp projet_termites.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS := -std=c++11

LOCAL_MODULE := termites
LOCAL_MODULE_TAGS := optional

include $(BUILD_HOST_EXECUTABLE)


# ========================================================
# termites (device)
# ========================================================
include $(CLEAR_VARS)

LOCAL_SRC_FILES := projet_termites_outils_terminal.cpp projet_termites_common.cpp termite.cpp projet_termites.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_CFLAGS := -std=c++11

LOCAL_MODULE := termites
LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := libstlport

include external/stlport/libstlport.mk

include $(BUILD_EXECUTABLE)

