//
// Created by Pablo Biagioli on 13/12/2021.
//

#include "CAPI.h"
#include "engine.h"

extern "C" {
    Engine* newEngine() {
        return new Engine();
    }

    int32_t startEngine(Engine *engine, engine_configuration_t *configuration) {
        return engine->start_audio(configuration);
    }

    int32_t stopEngine(Engine *engine){
        return engine->stop_audio();
    }

    void deleteEngine(Engine *engine) {
        delete engine;
    }

    size_t arrayLength(float buffer []) {
            return *(&buffer + 1) - buffer;
        }

    float currentPitch(Engine *engine) {
        return engine->getPitch();
    }
}