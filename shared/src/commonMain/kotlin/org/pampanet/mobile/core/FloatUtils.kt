package org.pampanet.mobile.core

expect object FloatUtils {
    fun toSFloat(byteArray: ByteArray, offset: Int): Float
    fun fromSFloat(num: Float): Int
}