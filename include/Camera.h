#pragma once
#include "MaskDetection.h"
#include "Properties.h"
#include "DetectionTimer.h"
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
class Camera
{
private:
	Mat frame;
	Mat org;
	VideoCapture cap;
	MaskDetection maskDetection;
	Properties props;
	DetectionTimer detectionTimer;
	void paintMessageOnFrame(Mat &frame, DetectionTimer::DetectionStatus status);
	void manipulateFrame(Mat &raw);

public:
	Camera();
	void start();
};