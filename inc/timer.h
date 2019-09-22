#pragma once
#include <ctime>
#include "types.h"

struct Timer {
    clock_t deltaTime;
    uint32_t frames;
    float frameRate;
    float avgFrameTimeMs;
    float beginFrame;
    float endFrame;
    bool ready;

    Timer();
    void calcFps();
    float clockToMs(clock_t ticks);
};
