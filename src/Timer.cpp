#include "Timer.h"
#include <iostream>
#include <chrono>

void Timer::StartTimeCounter()
{
    Timer::start = std::chrono::high_resolution_clock::now();
    return;
}

bool Timer::CheckTimeCounter(int secounds)
{
    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - start).count() > secounds)return true;
    return false;
}