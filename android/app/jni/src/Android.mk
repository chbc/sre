LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

DEPENDENCIES := ../SRE/dependencies

LOCAL_C_INCLUDES := \
		$(LOCAL_PATH)/$(DEPENDENCIES) \
		$(LOCAL_PATH)/$(DEPENDENCIES)/SDL2/include \
		$(LOCAL_PATH)/$(DEPENDENCIES)/SDL2_image \
		$(LOCAL_PATH)/../SRE/include

LOCAL_SRC_FILES :=  \
		application/SampleApplication.cpp \
		application/events/EventReceiver.cpp \
		main.cpp

# LOCAL_SRC_FILES :=  testgles2.cpp

LOCAL_SHARED_LIBRARIES := \
		SDL2 \
		SDL2_image \
		SRE

LOCAL_CFLAGS += -DSRE_ANDROID

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
