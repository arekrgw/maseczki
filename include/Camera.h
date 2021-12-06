#pragma once
#include "MaskDetection.h"
#include "Properties.h"
#include "Executor.h"
#include "DetectionTimer.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
class Camera
{
private:
	Mat frame;
	Mat org;
	Executor exec;
	VideoCapture cap;
	MaskDetection maskDetection;
	Properties props;
	DetectionTimer detectionTimer;
	void paintMessageOnFrame(Mat &frame, DetectionTimer::DetectionStatus status);
	void executeScript(DetectionTimer::DetectionStatus status);
	void manipulateFrame(Mat &raw);

public:
	Camera(Executor &exec);
	void start();
};