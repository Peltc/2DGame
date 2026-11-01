#pragma once
#include<time.h>
typedef struct{
    clock_t lasttime;
    float maindelta;
    int frame;
    float framecounter;
}delta;
void FrameRatePerSecond(delta* d);
delta*ini_delta();
void deltatime(delta*d);
