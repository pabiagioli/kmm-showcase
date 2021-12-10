package org.pampanet.mobile.myapplication

import kotlinx.cinterop.toCValues
import org.pampanet.native.core.getUint16
import org.pampanet.native.core.read_sfloat
import org.pampanet.native.core.write_sfloat
import platform.posix.`true`

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