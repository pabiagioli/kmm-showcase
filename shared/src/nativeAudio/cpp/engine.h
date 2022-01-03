//
// Created by Pablo Biagioli on 12/12/2021.
//

#ifndef NATIVEAUDIO_ENGINE_H
#define NATIVEAUDIO_ENGINE_H

#include "CAPI.h"
#include "oboe/Oboe.h"
#include "mpm.h"

#ifdef __cplusplus
extern "C" {
#endif

//using namespace oboe;
class AudioCallback : public oboe::AudioStreamDataCallback {
    public:
        explicit AudioCallback(engine_configuration_t *engineConfiguration);
        oboe::DataCallbackResult onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;
        float currentPitch = -1;
    private:
        engine_configuration_t *engineConfiguration;
        MPM *mpm;
};

class Engine : public oboe::AudioStreamErrorCallback {
public:
    Engine() = default;

    virtual ~Engine() = default;

    int32_t start_audio(engine_configuration_t *engineConfiguration);

    //oboe::DataCallbackResult
    //onAudioReady(oboe::AudioStream *audioStream, void *audioData, int32_t numFrames) override;

    bool onError(oboe::AudioStream *as, oboe::Result result) override;

    int32_t stop_audio();

    float getPitch();

private:
    AudioCallback *callback;
    std::shared_ptr<oboe::AudioStream> mStream;
    float currentPitch = -1;
    //MPM *mpm;
};
#ifdef __cplusplus
}
#endif
#endif //NATIVEAUDIO_ENGINE_H
