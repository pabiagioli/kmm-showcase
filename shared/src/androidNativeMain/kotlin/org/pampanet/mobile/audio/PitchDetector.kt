package org.pampanet.mobile.audio

import org.pampanet.mobile.pitch.McLeodPitchMethod

class PitchDetector(sampleRate: Float, bufferSize:Int) : McLeodPitchMethod(sampleRate, bufferSize)