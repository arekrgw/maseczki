#include "Timer.h"
#include <iostream>
#include <chrono>

void Timer::startTimeCounter()
{
    start = std::chrono::high_resolution_clock::now();
    return;
}

bool Timer::checkTimeCounter(int seconds)
{
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() > seconds)return true;
    return false;
}