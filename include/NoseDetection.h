#pragma once
#include "Properties.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
class NoseDetection
{
private:
	CascadeClassifier noseCascade;
	void loadNoseCascade();
	int findIndexOfBestNose(Mat &image, std::vector<Rect> &nose);
	void findAllNose(Mat &image, std::vector<Rect> &nose);
	Properties props;

public:
	NoseDetection(Properties &props);
	NoseDetection() = default;
	int detect(Mat &image, Rect &coords);
};