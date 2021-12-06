#pragma once

#include "DetectionTimer.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include "Resources.h"
#include "Timer.h"
#include "MaskOn.h"
using namespace cv;

class DetectionTimer
{

private:
	Timer timer;
	int correctCount;
	int frameCount;
	bool start;
	bool isOn;
	bool detectionFin;
	

public:
	enum DetectionStatus {
		STARTED = 1,WAIT_FOR_FACE,DETECTED,NOT_DETECTED
	};
	DetectionTimer();
	DetectionTimer::DetectionStatus checkTimer();
	void checkFrame(MaskOn result);
	DetectionTimer::DetectionStatus getResult();
};