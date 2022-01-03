package org.pampanet.mobile.audio

object Freq2NoteUtils {
    const val A4 = 440.0
    const val A4_INDEX = 57
    val notes = arrayOf(
        "C0", "C#0", "D0", "D#0", "E0", "F0", "F#0", "G0", "G#0", "A0", "A#0", "B0",
        "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1", "A1", "A#1", "B1",
        "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2", "A2", "A#2", "B2",
        "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3", "A3", "A#3", "B3",
        "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4", "A4", "A#4", "B4",
        "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5", "A5", "A#5", "B5",
        "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6", "A6", "A#6", "B6",
        "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7", "A7", "A#7", "B7",
        "C8", "C#8", "D8", "D#8", "E8", "F8", "F#8", "G8", "G#8", "A8", "A#8", "B8",
        "C9", "C#9", "D9", "D#9", "E9", "F9", "F#9", "G9", "G#9", "A9", "A#9", "B9"
    )

    fun getNote(pitch: Float, cents: Boolean): String {
        val MINUS = 0
        val PLUS = 1
        var frequency = A4
        val r = Math.pow(2.0, 1.0 / 12.0)
        val cent = Math.pow(2.0, 1.0 / 1200.0)
        var r_index = 0
        var cent_index = 0
        val side: Int
        if (pitch < 0) {
            return "NaN"
        }
        if (pitch >= frequency) {
            while (pitch >= r * frequency) {
                frequency = r * frequency
                r_index++
            }
            while (pitch > cent * frequency) {
                frequency = cent * frequency
                cent_index++
            }
            if (cent * frequency - pitch < pitch - frequency) cent_index++
            if (cent_index > 50) {
                r_index++
                cent_index = 100 - cent_index
                side = if (cent_index != 0) MINUS else PLUS
            } else side = PLUS
        } else {
            while (pitch <= frequency / r) {
                frequency = frequency / r
                r_index--
            }
            while (pitch < frequency / cent) {
                frequency = frequency / cent
                cent_index++
            }
            if (pitch - frequency / cent < frequency - pitch) cent_index++
            if (cent_index >= 50) {
                r_index--
                cent_index = 100 - cent_index
                side = PLUS
            } else {
                side = if (cent_index != 0) MINUS else PLUS
            }
        }
        var result = notes[(A4_INDEX + r_index) % notes.size]
        if (cents) {
            result = if (side == PLUS) "$result plus " else "$result minus "
            result = "$result$cent_index cents"
        }
        return result
    }

    fun getAngleFromHz(hz: Float): Float {
        val MIN = 16.35f
        val MAX = 7902.13f
        // the constrain
        var progress = calculateProgressForValue(hz, MIN, MAX)
        progress = Math.max(0.0, Math.min(1.0, calculateProgressForValue(hz, MIN, MAX).toDouble()))
            .toFloat()

        //Log.d(Freq2NoteUtils.class.getName(),String.format("hz = %f, progress = %f, result = %f", hz, progress, 360 * progress));
        return 360 * progress
    }

    private fun calculateProgressForValue(value: Float, start: Float, end: Float): Float {
        val diff = value - start
        val scope = end - start
        val progress: Float
        progress = if (diff.toDouble() != 0.0) {
            diff / scope
        } else {
            0.0f
        }
        return progress
    }
}