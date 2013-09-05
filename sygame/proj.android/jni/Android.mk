LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := hellocpp_shared

LOCAL_MODULE_FILENAME := libhellocpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../SyClient/AppDelegate.cpp \
                   ../../SyClient/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../SyClient

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_SHARED_LIBRARY)

$(call import-module,cocos2dx)

