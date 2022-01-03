package org.pampanet.mobile.core.android

import android.app.Application
import android.os.StrictMode.VmPolicy

import android.os.StrictMode


class MyApp : Application() {
    override fun onCreate() {
        StrictMode.setVmPolicy(
            VmPolicy.Builder()
                .detectLeakedClosableObjects()
                .penaltyLog()
                .build()
        )
        super.onCreate()
    }
}