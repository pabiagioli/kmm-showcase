package org.pampanet.mobile.pitch

data class PitchDetectionResult(
    var pitch: Float = -1f,
    var probability: Float = -1f,
    var pitched: Boolean = false
)