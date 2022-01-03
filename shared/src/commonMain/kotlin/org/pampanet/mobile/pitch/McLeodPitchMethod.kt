package org.pampanet.mobile.pitch

open class McLeodPitchMethod constructor(
    /**
     * The audio sample rate. Most audio has a sample rate of 44.1kHz.
     */
    private val sampleRate: Float,
    audioBufferSize: Int = DEFAULT_BUFFER_SIZE,
    cutoffMPM: Double = DEFAULT_CUTOFF
) {
    /**
     * Defines the relative size the chosen peak (pitch) has.
     */
    private val cutoff: Double

    /**
     * Contains a normalized square difference function value for each delay
     * (tau).
     */
    private val nsdf: FloatArray

    /**
     * The x and y coordinate of the top of the curve (nsdf).
     */
    private var turningPointX = 0f
    private var turningPointY = 0f

    /**
     * A list with minimum and maximum values of the nsdf curve.
     */
    private val maxPositions: MutableList<Int> = ArrayList()

    /**
     * A list of estimates of the period of the signal (in samples).
     */
    private val periodEstimates: MutableList<Float> = ArrayList()

    /**
     * A list of estimates of the amplitudes corresponding with the period
     * estimates.
     */
    private val ampEstimates: MutableList<Float> = ArrayList()

    /**
     * The result of the pitch detection iteration.
     */
    private val result: PitchDetectionResult

    /**
     * Implements the normalized square difference function. See section 4 (and
     * the explanation before) in the MPM article. This calculation can be
     * optimized by using an FFT. The results should remain the same.
     *
     * @param audioBuffer
     * The buffer with audio information.
     */
    private fun normalizedSquareDifference(audioBuffer: FloatArray) {
        for (tau in audioBuffer.indices) {
            var acf = 0f
            var divisorM = 0f
            for (i in 0 until audioBuffer.size - tau) {
                acf += audioBuffer[i] * audioBuffer[i + tau]
                divisorM += audioBuffer[i] * audioBuffer[i] + audioBuffer[i + tau] * audioBuffer[i + tau]
            }
            nsdf[tau] = 2 * acf / divisorM
        }
    }

    /*
	 * (non-Javadoc)
	 *
	 * @see be.tarsos.pitch.pure.PurePitchDetector#getPitch(float[])
	 */
    fun getPitch(audioBuffer: FloatArray): PitchDetectionResult {
        val pitch: Float

        // 0. Clear previous results (Is this faster than initializing a list
        // again and again?)
        maxPositions.clear()
        periodEstimates.clear()
        ampEstimates.clear()

        // 1. Calculate the normalized square difference for each Tau value.
        normalizedSquareDifference(audioBuffer)
        // 2. Peak picking time: time to pick some peaks.
        peakPicking()
        var highestAmplitude = Double.NEGATIVE_INFINITY
        for (tau in maxPositions) {
            // make sure every annotation has a probability attached
            highestAmplitude = kotlin.math.max(highestAmplitude, nsdf[tau].toDouble())
            if (nsdf[tau] > SMALL_CUTOFF) {
                // calculates turningPointX and Y
                parabolicInterpolation(tau)
                // store the turning points
                ampEstimates.add(turningPointY)
                periodEstimates.add(turningPointX)
                // remember the highest amplitude
                highestAmplitude = kotlin.math.max(highestAmplitude, turningPointY.toDouble())
            }
        }
        if (periodEstimates.isEmpty()) {
            pitch = -1f
        } else {
            // use the overall maximum to calculate a cutoff.
            // The cutoff value is based on the highest value and a relative
            // threshold.
            val actualCutoff = cutoff * highestAmplitude

            // find first period above or equal to cutoff
            var periodIndex = 0
            for (i in ampEstimates.indices) {
                if (ampEstimates[i] >= actualCutoff) {
                    periodIndex = i
                    break
                }
            }
            val period = periodEstimates[periodIndex].toDouble()
            val pitchEstimate = (sampleRate / period).toFloat()
            pitch = if (pitchEstimate > LOWER_PITCH_CUTOFF) {
                pitchEstimate
            } else {
                -1f
            }
        }
        result.probability = highestAmplitude.toFloat()
        result.pitch = pitch
        result.pitched = pitch != -1f
        return result
    }

    /**
     *
     *
     * Finds the x value corresponding with the peak of a parabola.
     *
     *
     *
     * a,b,c are three samples that follow each other. E.g. a is at 511, b at
     * 512 and c at 513; f(a), f(b) and f(c) are the normalized square
     * difference values for those samples; x is the peak of the parabola and is
     * what we are looking for. Because the samples follow each other
     * `b - a = 1` the formula for [parabolic interpolation](http://fizyka.umk.pl/nrbook/c10-2.pdf)
     * can be simplified a lot.
     *
     *
     *
     * The following ASCII ART shows it a bit more clear, imagine this to be a
     * bit more curvaceous.
     *
     *
     * <pre>
     * nsdf(x)
     * ^
     * |
     * f(x)  |------ ^
     * f(b)  |     / |\
     * f(a)  |    /  | \
     * |   /   |  \
     * |  /    |   \
     * f(c)  | /     |    \
     * |_____________________> x
     * a  x b  c
    </pre> *
     *
     * @param tau
     * The delay tau, b value in the drawing is the tau value.
     */
    private fun parabolicInterpolation(tau: Int) {
        val nsdfa = nsdf[tau - 1]
        val nsdfb = nsdf[tau]
        val nsdfc = nsdf[tau + 1]
        val bValue = tau.toFloat()
        val bottom = nsdfc + nsdfa - 2 * nsdfb
        if (bottom.toDouble() == 0.0) {
            turningPointX = bValue
            turningPointY = nsdfb
        } else {
            val delta = nsdfa - nsdfc
            turningPointX = bValue + delta / (2 * bottom)
            turningPointY = nsdfb - delta * delta / (8 * bottom)
        }
    }

    /**
     *
     *
     * Implementation based on the GPL'ED code of [Tartini](http://tartini.net) This code can be found in the file
     * `general/mytransforms.cpp`.
     *
     *
     *
     * Finds the highest value between each pair of positive zero crossings.
     * Including the highest value between the last positive zero crossing and
     * the end (if any). Ignoring the first maximum (which is at zero). In this
     * diagram the desired values are marked with a +
     *
     *
     * <pre>
     * f(x)
     * ^
     * |
     * 1|               +
     * | \      +     /\      +     /\
     * 0| _\____/\____/__\/\__/\____/_______> x
     * |   \  /  \  /      \/  \  /
     * -1|    \/    \/            \/
     * |
    </pre> *
     *
     * @param nsdf
     * The array to look for maximum values in. It should contain
     * values between -1 and 1
     * @author Phillip McLeod
     */
    private fun peakPicking() {
        var pos = 0
        var curMaxPos = 0

        // find the first negative zero crossing
        while (pos < (nsdf.size - 1) / 3 && nsdf[pos] > 0) {
            pos++
        }

        // loop over all the values below zero
        while (pos < nsdf.size - 1 && nsdf[pos] <= 0.0) {
            pos++
        }

        // can happen if output[0] is NAN
        if (pos == 0) {
            pos = 1
        }
        while (pos < nsdf.size - 1) {
            //assert(nsdf[pos] >= 0)
            if (nsdf[pos] > nsdf[pos - 1] && nsdf[pos] >= nsdf[pos + 1]) {
                if (curMaxPos == 0) {
                    // the first max (between zero crossings)
                    curMaxPos = pos
                } else if (nsdf[pos] > nsdf[curMaxPos]) {
                    // a higher max (between the zero crossings)
                    curMaxPos = pos
                }
            }
            pos++
            // a negative zero crossing
            if (pos < nsdf.size - 1 && nsdf[pos] <= 0) {
                // if there was a maximum add it to the list of maxima
                if (curMaxPos > 0) {
                    maxPositions.add(curMaxPos)
                    curMaxPos = 0 // clear the maximum position, so we start
                    // looking for a new ones
                }
                while (pos < nsdf.size - 1 && nsdf[pos] <= 0.0f) {
                    pos++ // loop over all the values below zero
                }
            }
        }
        if (curMaxPos > 0) { // if there was a maximum in the last part
            maxPositions.add(curMaxPos) // add it to the vector of maxima
        }
    }

    companion object {
        /**
         * The expected size of an audio buffer (in samples).
         */
        const val DEFAULT_BUFFER_SIZE = 1024

        /**
         * Overlap defines how much two audio buffers following each other should
         * overlap (in samples). 75% overlap is advised in the MPM article.
         */
        const val DEFAULT_OVERLAP = 768

        /**
         * Defines the relative size the chosen peak (pitch) has. 0.93 means: choose
         * the first peak that is higher than 93% of the highest peak detected. 93%
         * is the default value used in the Tartini user interface.
         */
        private const val DEFAULT_CUTOFF = 0.97

        /**
         * For performance reasons, peaks below this cutoff are not even considered.
         */
        private const val SMALL_CUTOFF = 0.5

        /**
         * Pitch annotations below this threshold are considered invalid, they are
         * ignored.
         */
        private const val LOWER_PITCH_CUTOFF = 80.0 // Hz
    }
    /**
     * Create a new pitch detector.
     *
     * @param sampleRate
     * The sample rate of the audio.
     * @param audioBufferSize
     * The size of one audio buffer 1024 samples is common.
     * @param cutoffMPM
     * The cutoff (similar to the YIN threshold). In the Tartini
     * paper 0.93 is used.
     */
    /**
     * Initializes the normalized square difference value array and stores the
     * sample rate.
     *
     * @param sampleRate
     * The sample rate of the audio to check.
     */
    /**
     * Create a new pitch detector.
     *
     * @param audioSampleRate
     * The sample rate of the audio.
     * @param audioBufferSize
     * The size of one audio buffer 1024 samples is common.
     */
    init {
        nsdf = FloatArray(audioBufferSize)
        cutoff = cutoffMPM
        result = PitchDetectionResult()
    }
}