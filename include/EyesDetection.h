#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class EyesDetection
{

private:
	CascadeClassifier eyesCascade;
	void loadEyesCascade();
	int findIndexOfBestEyes(Mat &image, std::vector<Rect> &eyes);
	void findAllEyes(Mat &image, std::vector<Rect> &eyes);

public:
	EyesDetection();
	int detect(Mat &image, Rect &coords);
};