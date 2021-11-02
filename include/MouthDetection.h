#pragma once
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class MouthDetection
{
private:
	CascadeClassifier mouthCascade;
	void loadMouthCascade();
	void findAllMouth(Mat &image, std::vector<Rect> &mouths);
	int findIndexOfBestMouth(Mat &image, std::vector<Rect> &mouths);

public:
	MouthDetection();
	int detect(Mat &image, Rect &coords);
};