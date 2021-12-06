
#include "DetectionTimer.h"
#include "Painter.h"

DetectionTimer::DetectionTimer()
{
	correctCount = 0;
	frameCount = 1;
	start = false;
	isOn = false;
	detectionFin = true;
}

void DetectionTimer::checkFrame(MaskOn result)
{

	if (result == MaskOn::CORRECT)
	{
		if (!start && timer.checkTimeCounter(3))
		{

			std::cout << "start wykrywania" << std::endl;
			frameCount = 1;
			correctCount = 0;
			start = true;
			isOn = false;
			timer.startTimeCounter();
		}
		else
		{
			frameCount++;
			correctCount++;
		}
	}

	if (start && result == MaskOn::NONE)
	{
		frameCount++;
	}
}

DetectionTimer::DetectionStatus DetectionTimer::checkTimer()
{

	if (timer.checkTimeCounter(3) && !start)
	{
		detectionFin = true;
	}

	if (start && timer.checkTimeCounter(5))
	{

		int percent = (correctCount * 100) / frameCount;
		if (percent >= PASS_PRECENTAGE_THRESHOLD && frameCount + correctCount > MINIMAL_FRAME_THRESHOLD)
		{
			isOn = true;
		}
		else
		{
			isOn = false;
		}
		timer.startTimeCounter();
		start = false;
		detectionFin = false;
	}

	return getResult();
}

DetectionTimer::DetectionStatus DetectionTimer::getResult()
{
	if (start)
	{
		return STARTED;
	}
	else if (detectionFin)
	{
		return WAIT_FOR_FACE;
	}
	else if (isOn && !start)
	{
		return DETECTED;
	}

	return NOT_DETECTED;
}