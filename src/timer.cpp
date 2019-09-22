#include "timer.h"


Timer::Timer() :
    deltaTime(0),
    frames(0),
    frameRate(60.0f),
    avgFrameTimeMs(16.666f),
    ready(false)
{};

void Timer::calcFps() {
    deltaTime += endFrame - beginFrame;
    frames ++;
    if(clockToMs(deltaTime)>1000.0f) { //every second
        frameRate = (float)frames;
        frames = 0;
        deltaTime -= CLOCKS_PER_SEC;
        avgFrameTimeMs  = 1000.0f/(frameRate==0?0.001f:frameRate);
        ready = true;
    }
}

float Timer::clockToMs(clock_t ticks){
    return (ticks/(float)CLOCKS_PER_SEC)*1000.0f;
}
