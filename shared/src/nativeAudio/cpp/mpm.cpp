//
// Created by Pablo Biagioli on 27/12/2021.
//

#include "mpm.h"

#include <utility>
#include "logging.h"

#define MPM_SMALL_CUTOFF 0.5
#define MPM_LOWER_PITCH_CUTOFF 80.0

MPM::MPM(int sampleRate, double cutoff) {
    this->sampleRate = sampleRate;
    this->cutoff = cutoff;
}

void MPM::normalized_square_difference(const float *audioBuffer, int32_t bufferSize) {

    for (int tau = 0; tau < bufferSize; tau++) {
        double acf = 0;
        double divisorM = 0;
        for (int i = 0; i < bufferSize - tau; i++) {
            acf += audioBuffer[i] * audioBuffer[i + tau];
            divisorM += audioBuffer[i] * audioBuffer[i] + audioBuffer[i + tau] * audioBuffer[i + tau];
        }
        nsdf[tau] = 2 * acf / divisorM;
    }
}

void MPM::peak_picking() {
    int pos = 0;
    int curMaxPos = 0;

    // find the first negative zero crossing
    while (pos < (nsdf.size() - 1) / 3 && nsdf[pos] > 0) {
        pos++;
    }

    // loop over all the values below zero
    while (pos < nsdf.size() - 1 && nsdf[pos] <= 0.0) {
        pos++;
    }

    // can happen if output[0] is NAN
    if (pos == 0) {
        pos = 1;
    }

    while (pos < nsdf.size() - 1) {
        //assert(nsdf[pos] >= 0);
        if (nsdf[pos] > nsdf[pos - 1] && nsdf[pos] >= nsdf[pos + 1]) {
            if (curMaxPos == 0) {
                // the first max (between zero crossings)
                curMaxPos = pos;
            } else if (nsdf[pos] > nsdf[curMaxPos]) {
                // a higher max (between the zero crossings)
                curMaxPos = pos;
            }
        }
        pos++;
        // a negative zero crossing
        if (pos < nsdf.size() - 1 && nsdf[pos] <= 0) {
            // if there was a maximum add it to the list of maxima
            if (curMaxPos > 0) {
                maxPositions.push_back(curMaxPos);
                curMaxPos = 0; // clear the maximum position, so we start
                // looking for a new ones
            }
            while (pos < nsdf.size() - 1 && nsdf[pos] <= 0.0f) {
                pos++; // loop over all the values below zero
            }
        }
    }
    if (curMaxPos > 0) { // if there was a maximum in the last part
        maxPositions.push_back(curMaxPos); // add it to the vector of maxima
    }
}

void MPM::parabolic_interpolation(const int32_t tau) {
    const float nsdfa = nsdf[tau - 1];
    const float nsdfb = nsdf[tau];
    const float nsdfc = nsdf[tau + 1];
    const float bValue = tau;
    const float bottom = nsdfc + nsdfa - 2 * nsdfb;
    if (bottom == 0.0) {
        turningPointX = bValue;
        turningPointY = nsdfb;
    } else {
        const float delta = nsdfa - nsdfc;
        turningPointX = bValue + delta / (2 * bottom);
        turningPointY = nsdfb - delta * delta / (8 * bottom);
    }
}

float MPM::getPitch(const float *audioBuffer, int32_t bufferSize) {
    double pitch;
    // 0. Clear previous results (Is this faster than initializing a list
    // again and again?)
    nsdf.resize(bufferSize);
    maxPositions.clear();
    periodEstimates.clear();
    ampEstimates.clear();
    // 1. Calculate the normalized square difference for each Tau value.
    normalized_square_difference(audioBuffer, bufferSize);
    //LOGD("normalized_square_diff check!");
    // 2. Peak picking time: time to pick some peaks.
    peak_picking();
    //LOGD("peak picking check!");
    double highestAmplitude = -std::numeric_limits<double>::infinity();

    for (int tau : maxPositions) {
        // make sure every annotation has a probability attached
        highestAmplitude = std::max(highestAmplitude, (double) nsdf[tau]);

        if (nsdf[tau] > MPM_SMALL_CUTOFF) {
            // calculates turningPointX and Y
            parabolic_interpolation(tau);
            // store the turning points
            ampEstimates.push_back(turningPointY);
            periodEstimates.push_back(turningPointX);
            // remember the highest amplitude
            highestAmplitude = std::max(highestAmplitude, (double) turningPointY);
        }
    }

    if (periodEstimates.empty()) {
        pitch = -1;
    } else {
        // use the overall maximum to calculate a cutoff.
        // The cutoff value is based on the highest value and a relative
        // threshold.
        const double actualCutoff = cutoff * highestAmplitude;

        // find first period above or equal to cutoff
        int periodIndex = 0;
        for (int i = 0; i < ampEstimates.size(); i++) {
            if (ampEstimates[i] >= actualCutoff) {
                periodIndex = i;
                break;
            }
        }

        const double period = periodEstimates[periodIndex];
        const auto pitchEstimate = (float) (sampleRate / period);
        if (pitchEstimate > MPM_LOWER_PITCH_CUTOFF) {
            pitch = pitchEstimate;
        } else {
            pitch = -1;
        }

    }

    //result.setProbability((float) highestAmplitude);
    //result.setPitch(pitch);
    //result.setPitched(pitch != -1);
    LOGD("probability = %f pitch = %f, pitched %d", (float)highestAmplitude, pitch, pitch != -1);
    return pitch;
}