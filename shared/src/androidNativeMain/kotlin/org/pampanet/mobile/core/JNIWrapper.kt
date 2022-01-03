package org.pampanet.mobile.core

import kotlinx.cinterop.*
import org.pampanet.native.core.getUint16
import org.pampanet.native.core.read_sfloat
import org.pampanet.native.core.write_sfloat
import platform.android.*
import platform.posix.`true`


/**
 * JNI functions need to be Top-Level functions,
 * otherwise they don't get the JavaVMVar nor the JNIEnvVar attached
 */

@CName("JNI_OnLoad")
fun JNI_OnLoad(
    vm: CPointer<JavaVMVar>,
    preserved: COpaquePointer
): jint {
    logInfo(JniBridge::class.simpleName?:"JNI Bridge","JNI On Load")
    return JNI_VERSION_1_6
}

@CName("Java_org_pampanet_mobile_core_FloatUtils_toNativeSFloat")
fun toNativeSFloat(
    env: CPointer<JNIEnvVar>,
    clazz: jclass,
    byteArray: jbyteArray,
    offset: jint
): jfloat = jniWith(env) {
    return@toNativeSFloat memScoped {
        val jni = this@jniWith
        val arrayLen = jni.fGetArrayLength(jni.env, byteArray)
        val jByteArray = alloc<jbyteVar>().ptr
        // https://developer.ibm.com/articles/j-jni/#triggering
        jni.fGetInt8ArrayRegion(jni.env, byteArray, 0, arrayLen, jByteArray)
        // it's easier to cast int8* -> uint8* than sending a uint8* from Android
        val data = getUint16(jByteArray.reinterpret(), offset, `true`)
        val result = read_sfloat(data)
        logInfo(NdkBridge::class.simpleName?:"NDK Bridge","result is $result")
        return result
    }
}

@CName("Java_org_pampanet_mobile_core_FloatUtils_fromNativeSFloat")
fun fromNativeSFloat(env: CPointer<JNIEnvVar>, clazz: jclass, num: jfloat): jint = jniWith(env) {
    return write_sfloat(num).toInt()
}

/*
@CName("Java_org_pampanet_mobile_audio_OboeEngine_startAudioEngine")
fun startOboeEngine(env: CPointer<JNIEnvVar>, clazz: jclass) : jint = jniWith(env) {
    return memScoped {
        val configRequest = cValue<engine_configuration_t> {
            channel_count = 2
            sample_rate = 48000
            filters[0] = staticCFunction { p1, p2 ->
                //val jni = this@jniWith
                val arrayLen = arrayLength(p1).convert<Int>()
                val kArray = (0 until arrayLen).map { i-> p1!![i] }.toFloatArray()
                if(pitchDetector == null)
                    pitchDetector = McLeodPitchMethod(p2.toFloat(), arrayLen)
                currentPitchDetectionResult = pitchDetector!!.getPitch(kArray)
                logInfo("PitchDetector", "$currentPitchDetectionResult")
                0
            }
        }
        startEngine(oboeEngine ,configRequest)
    }
}

@CName("Java_org_pampanet_mobile_audio_OboeEngine_stopAudioEngine")
fun stopOboeEngine(env: CPointer<JNIEnvVar>, clazz: jclass) : jint = jniWith(env) {
    return memScoped { stopEngine(oboeEngine) }
}

@CName("Java_org_pampanet_mobile_audio_OboeEngine_currentPitch")
fun currentPitch(env: CPointer<JNIEnvVar>, clazz: jclass) : jfloat = jniWith(env) {
    return memScoped { currentPitchDetectionResult.pitch }
}
*/