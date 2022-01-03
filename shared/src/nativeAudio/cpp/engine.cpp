//
// Created by Pablo Biagioli on 12/12/2021.
//

#include <jni.h>
#include <thread>
#include "oboe/Oboe.h"
#include "engine.h"
#include "CAPI.h"
#include "logging.h"
#include <vector>

#define size(type) ((char *)(&type+1)-(char*)(&type))

extern "C" {
using namespace oboe;

AudioCallback::AudioCallback(engine_configuration_t *engineConfiguration) {
    this->engineConfiguration = engineConfiguration;
    this->mpm = new MPM(engineConfiguration->sample_rate, 0.97);
}

DataCallbackResult
AudioCallback::onAudioReady(AudioStream *audioStream, void *audioData, int32_t numFrames) {
    // We requested AudioFormat::Float. So if the stream opens
    // we know we got the Float format.
    // If you do not specify a format then you should check what format
    // the stream has and cast to the appropriate type.
    //const int64_t timeoutNanos = 0; // for a non-blocking read
    //auto result = audioStream->read(audioData, numFrames, timeoutNanos);
    //auto samplesPerFrame = audioStream->getChannelCount();
    //if (result == Result::OK) {
    //LOGE("welcome to the callback");
    float *outputData = static_cast<float *>(audioData);
    if(audioStream->getFormat() == oboe::AudioFormat::I16){
        LOGE("format is integer, I should convert from float");
    }
    //if (result.value() < numFrames) {
    //LOGD("replace the missing data with silence");
    // replace the missing data with silence
    //    memset(outputData + result.value() * samplesPerFrame, 0,
    //           (numFrames - result.value()) * audioStream->getBytesPerFrame());

    //}
    size_t bufSize = (numFrames) * audioStream->getBytesPerFrame() / (sizeof(outputData[0]));
    //size_t bufSize = size(outputData) / size(outputData[0]);
    LOGD("bufferSize %d", bufSize);
    this->currentPitch = this->mpm->getPitch(outputData, bufSize);
    //}
    return DataCallbackResult::Continue;
}

bool Engine::onError(AudioStream *as, Result r) {
    LOGE("Error during callback processing %s", convertToText(r));
}

int32_t Engine::start_audio(engine_configuration_t *engineConfiguration) {

    AudioStreamBuilder builder;
    callback = new AudioCallback(engineConfiguration);

    // The builder set methods can be chained for convenience.
    Result result = builder.setSharingMode(SharingMode::Exclusive)
            ->setChannelCount(engineConfiguration->channel_count)
            ->setSampleRate(engineConfiguration->sample_rate)
            ->setFormatConversionAllowed(true)
            ->setSampleRateConversionQuality(SampleRateConversionQuality::Fastest)
            ->setDirection(Direction::Input)
            ->setPerformanceMode(PerformanceMode::LowLatency)
            ->setFormat(AudioFormat::Float)
            ->setDataCallback(callback)
            ->setErrorCallback(this)
            ->setInputPreset(InputPreset::VoicePerformance)
            ->openStream(mStream);

    if (result == Result::OK) {
        // Typically, start the stream after querying some stream information, as well as some input from the user
        result = mStream->requestStart();
        if (result != Result::OK) {
            LOGE("AudioEngine: Error starting stream. %s", convertToText(result));
        }
    } else {
        LOGE("AudioEngine: Failed to create stream. Error: %s", convertToText(result));
        return (int32_t) result;
    }
    //LOGD("AudioEngine: Starting Stream %s", convertToText(result));
    return (int32_t) result;

}

int32_t Engine::stop_audio() {
    Result result = this->mStream->requestStop();
    delete callback;
    return (int32_t) result;
}

float Engine::getPitch() {
    return this->callback->currentPitch;
    //return currentPitch;
}
}



