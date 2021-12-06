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
	DetectionTimer();
	void checkTimer(Mat frame);
	void checkFrame(MaskOn result);
};