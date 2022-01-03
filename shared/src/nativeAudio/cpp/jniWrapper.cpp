// Write C++ code here.
//
// Do not forget to dynamically load the C++ library into your application.
//
// For instance,
//
// In MainActivity.java:
//    static {
//       System.loadLibrary("shared");
//    }
//
// Or, in MainActivity.kt:
//    companion object {
//      init {
//         System.loadLibrary("shared")
//      }
//    }
#include <jni.h>
#include "CAPI.h"
#include "mpm.h"
#include <android/log.h>

Engine *audioEngine;

extern "C" {

    JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
        audioEngine = newEngine();
        return JNI_VERSION_1_6;
    }

    JNIEXPORT void JNICALL JNI_OnUnload(JavaVM *vm, void *reserved) {
        stopEngine(audioEngine);
        deleteEngine(audioEngine);
    }

    JNIEXPORT jint JNICALL
    Java_org_pampanet_mobile_audio_OboeEngine_startAudioEngine(JNIEnv *env, jobject thiz) {
        engine_configuration_t config = {
                .sample_rate = 48000,
                .channel_count = 1,
                .filters = {}
        };

        startEngine(audioEngine, &config);
        return true;
    }

    JNIEXPORT jint JNICALL
    Java_org_pampanet_mobile_audio_OboeEngine_stopAudioEngine(JNIEnv *env, jobject thiz) {
        stopEngine(audioEngine);
        return true;
    }

    JNIEXPORT jfloat JNICALL
    Java_org_pampanet_mobile_audio_OboeEngine_currentPitch(JNIEnv *env, jobject thiz) {
        return currentPitch(audioEngine);
    }
}
