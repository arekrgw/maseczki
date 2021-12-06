#include <chrono>

class Timer
{
private:
	std::chrono::steady_clock::time_point start;
	int frameCount;
	int correctFrameCount;


public:
	void startTimeCounter();
	bool checkTimeCounter(int seconds);

};
