#pragma once
#include <opencv2/highgui/highgui.hpp>
#include "MaskDetection.h"
#include "Properties.h"
#include "DetectionTimer.h"

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