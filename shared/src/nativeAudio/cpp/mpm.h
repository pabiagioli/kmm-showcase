//
// Created by Pablo Biagioli on 27/12/2021.
//

#ifndef NATIVEAUDIO_MPM_H
#define NATIVEAUDIO_MPM_H

#include <vector>

class MPM {
public:
    MPM(int sampleRate, double cutoff);
    ~MPM() = default;
    float getPitch(const float *audioBuffer, int32_t bufferSize);
private:
    double sampleRate;
    double cutoff;
    std::vector<double> nsdf{0, 1024};
    /**
     * The x and y coordinate of the top of the curve (nsdf).
     */
    double turningPointX, turningPointY;

    /**
     * A list with minimum and maximum values of the nsdf curve.
     */
    std::vector<int32_t> maxPositions;// = new ArrayList<Integer>();

    /**
     * A list of estimates of the period of the signal (in samples).
     */
    std::vector<double> periodEstimates{};// = new ArrayList<Float>();

    /**
     * A list of estimates of the amplitudes corresponding with the period
     * estimates.
     */
    std::vector<double> ampEstimates{}; // = new ArrayList<Float>();

    void normalized_square_difference(const float *audioBuffer, int32_t bufferSize);

    void peak_picking();

    void parabolic_interpolation(int tau);
    //std::pair<float, float> parabolic_interpolation(const std::vector<float> &array, int x_);
};


#endif //NATIVEAUDIO_MPM_H
