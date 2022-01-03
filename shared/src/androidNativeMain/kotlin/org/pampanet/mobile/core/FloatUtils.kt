package org.pampanet.mobile.core

import kotlinx.cinterop.toCValues
import org.pampanet.native.core.getUint16
import org.pampanet.native.core.read_sfloat
import org.pampanet.native.core.write_sfloat
import platform.posix.`true`

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
