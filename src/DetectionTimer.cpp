
#include "DetectionTimer.h"
#include "Painter.h"

DetectionTimer::DetectionTimer() {
	correctCount = 0;
	frameCount = 1;
	start = false;
	isOn = false;
	detectionFin = true;
	
}

void DetectionTimer::checkFrame(MaskOn result) {

	if (result == MaskOn::CORRECT) {
		if (!start && timer.CheckTimeCounter(3))
		{

			std::cout << "start wykrywania" << std::endl;
			frameCount = 1;
			correctCount = 0;
			start = true;
			isOn = false;
			timer.StartTimeCounter();
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

void DetectionTimer::checkTimer(Mat frame) {
	if (start) {
		Painter::paintText(frame, "Detection started", Scalar(0, 120, 255));
	}
	else if (detectionFin) {
		Painter::paintText(frame, "Fit face into outline...", Scalar(255, 255, 255));
	}
	else if (isOn && !start)
	{
		Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
	}
	else if (!isOn && !start)
	{
		Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
	}


	if (timer.CheckTimeCounter(3) && !start) {
		detectionFin = true;
	}

	if (start)
	{


		if (timer.CheckTimeCounter(5))
		{
			int percent = (correctCount * 100) / frameCount;
			std::cout << percent << "% " << frameCount + correctCount << std::endl;
			if (percent >= PASS_PRECENTAGE_THRESHOLD && frameCount + correctCount > MINIMAL_FRAME_THRESHOLD)
			{
				isOn = true;
				std::cout << "maska jest zalozona" << std::endl;
			}
			else
			{
				std::cout << "maski nie wykryto" << std::endl;
				isOn = false;
			}
			timer.StartTimeCounter();
			start = false;
			detectionFin = false;
		}
	}


}