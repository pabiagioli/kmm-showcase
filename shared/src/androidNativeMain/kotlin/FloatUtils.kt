package org.pampanet.mobile.myapplication

import kotlinx.cinterop.*
import org.pampanet.mobile.myapplication.Commons.logInfo

import org.pampanet.native.core.getUint16
import org.pampanet.native.core.read_sfloat
import org.pampanet.native.core.write_sfloat
import platform.android.*
import platform.posix.`false`
import platform.posix.`true`

lateinit var mJniBridge : JniBridge

@CName("JNI_OnLoad")
fun JNI_OnLoad(
    vm: CPointer<JavaVMVar>,
    preserved: COpaquePointer
): jint {
    logInfo("JNI On Load")
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
    val isCopy: CPointer<jbooleanVar> = nativeHeap.alloc<jbooleanVar> { `false` }.ptr
    val jByteArray =
        this.fGetInt8ArrayElements(this.env, byteArray, isCopy)?.reinterpret<jbooleanVar>()
    val data = getUint16(jByteArray, offset, `true`)
    val result = read_sfloat(data)
    logInfo("result is $result")
    return result
}

@CName("Java_org_pampanet_mobile_myapplication_FloatUtils_fromNativeSFloat")
fun fromNativeSFloat(env: CPointer<JNIEnvVar>, clazz: jclass, num: jfloat): jint = memScoped {
    return write_sfloat(num).toInt()
}

actual class FloatUtils {

    actual fun toSFloat(byteArray: ByteArray, offset: Int): Float {
        val cArray = byteArray.toUByteArray().toCValues()
        val data = getUint16(cArray, offset, `true`)
        return read_sfloat(data)
    }

    actual fun fromSFloat(num: Float): Int {
        return write_sfloat(num).toInt()
    }
}
