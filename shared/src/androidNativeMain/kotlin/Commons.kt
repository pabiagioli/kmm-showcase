package org.pampanet.mobile.myapplication

import kotlinx.cinterop.convert
import platform.android.ANDROID_LOG_ERROR
import platform.android.ANDROID_LOG_INFO
import platform.android.__android_log_write

object Commons {

    fun logError(message: String) {
        __android_log_write(ANDROID_LOG_ERROR.convert(), "KonanActivity", message)
    }

    fun logInfo(message: String) {
        __android_log_write(ANDROID_LOG_INFO.convert(), "KonanActivity", message)
    }

}