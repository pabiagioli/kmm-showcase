package org.pampanet.mobile.myapplication

actual class FloatUtils {
    companion object {
        init {
            System.loadLibrary("corenative")
        }
        @JvmStatic
        external fun toNativeSFloat(byteArray: ByteArray, offset: Int): Float
        @JvmStatic
        external fun fromNativeSFloat(num: Float): Int
    }

    actual fun toSFloat(byteArray: ByteArray, offset: Int): Float = Companion.toNativeSFloat(byteArray, offset)
    actual fun fromSFloat(num: Float): Int = Companion.fromNativeSFloat(num)
}