package org.pampanet.mobile.myapplication

import kotlinx.cinterop.*

import org.pampanet.native.core.getUint16
import org.pampanet.native.core.read_sfloat
import org.pampanet.native.core.write_sfloat
import platform.android.*
import platform.posix.`false`
import platform.posix.`true`

/**
 * JNI functions need to be Top-Level functions,
 * otherwise they don't get the JavaVMVar nor the JNIEnvVar attached
 */

lateinit var mJniBridge : JniBridge

@CName("JNI_OnLoad")
fun JNI_OnLoad(
    vm: CPointer<JavaVMVar>,
    preserved: COpaquePointer
): jint {
    logInfo(JniBridge::class.simpleName?:"JNI Bridge","JNI On Load")
    mJniBridge = JniBridge(vm)
    return JNI_VERSION_1_6
}

@CName("Java_org_pampanet_mobile_myapplication_FloatUtils_toNativeSFloat")
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

@CName("Java_org_pampanet_mobile_myapplication_FloatUtils_fromNativeSFloat")
fun fromNativeSFloat(env: CPointer<JNIEnvVar>, clazz: jclass, num: jfloat): jint = memScoped {
    return write_sfloat(num).toInt()
}


/**
 * This class is totally misleading, and clearly not needed for exposing JNI methods to an external library,
 * but will be useful if the library has a main entry point and is compiled as an executable
 */
actual object FloatUtils {

    actual fun toSFloat(byteArray: ByteArray, offset: Int): Float {
        val cArray = byteArray.toUByteArray().toCValues()
        val data = getUint16(cArray, offset, `true`)
        return read_sfloat(data)
    }

    actual fun fromSFloat(num: Float): Int {
        return write_sfloat(num).toInt()
    }
}
