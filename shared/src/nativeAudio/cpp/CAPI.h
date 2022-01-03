//
// Created by Pablo Biagioli on 13/12/2021.
//

#ifndef NATIVEAUDIO_CAPI_H
#define NATIVEAUDIO_CAPI_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef int32_t (*audioFX)(float* buffer, int32_t sample_rate);

typedef struct _engine_configuration_t {
    int32_t sample_rate; // 48000
    int32_t channel_count; // 2
    const audioFX *filters; //oboe::AudioStreamDataCallback
} engine_configuration_t;

typedef enum _engine_action {
    START = 1,
    STOP = 2,
    SETUP = 3,
    ERROR = 4
} engine_action;

typedef struct _engine_request_t {
    engine_action type;
} engine_request_t;

typedef struct Engine Engine;
Engine* newEngine();
int32_t startEngine(Engine *engine, engine_configuration_t *configuration);
int32_t stopEngine(Engine *engine);
void deleteEngine(Engine *engine);
size_t arrayLength(float buffer []);
float currentPitch(Engine *engine);

#ifdef __cplusplus
}
#endif

#endif //NATIVEAUDIO_CAPI_H
