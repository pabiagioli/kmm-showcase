package org.pampanet.mobile.myapplication

import kotlinx.cinterop.convert
import platform.android.*

data class JniClass(val jclass: jclass)
data class JniObject(val jobject: jobject)
data class JniMethod(val jmethod: jmethodID)

fun asJniClass(jclass: jclass?) =
    if (jclass != null) JniClass(jclass) else null

fun asJniObject(jobject: jobject?) =
    if (jobject != null) JniObject(jobject) else null

fun asJniMethod(jmethodID: jmethodID?) =
    if (jmethodID != null) JniMethod(jmethodID) else null


fun logError(tag: String, message: String) {
    __android_log_write(ANDROID_LOG_ERROR.convert(), tag, message)
}

fun logInfo(tag: String, message: String) {
    __android_log_write(ANDROID_LOG_INFO.convert(), tag, message)
}
