package org.pampanet.mobile.audio

import kotlinx.coroutines.flow.Flow
import kotlinx.coroutines.flow.flow

class OboeEngine {
    init {
        System.loadLibrary("nativeaudio")
    }

    fun pitchTracker() : Flow<Float> = flow {
        while(true) {
            //emit(-1f)
            emit(currentPitch())
        }
    }

    external fun startAudioEngine() : Int
    external fun stopAudioEngine() : Int
    external fun currentPitch() : Float
}