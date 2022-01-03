package org.pampanet.mobile.core

actual object FloatUtils {
    init {
        System.loadLibrary("nativecore")
    }

    private external fun toNativeSFloat(byteArray: ByteArray, offset: Int): Float
    private external fun fromNativeSFloat(num: Float): Int

    actual fun toSFloat(byteArray: ByteArray, offset: Int): Float =
        toNativeSFloat(byteArray, offset)
    actual fun fromSFloat(num: Float): Int = fromNativeSFloat(num)
}