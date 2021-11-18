#pragma once
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>

using namespace cv;

class MaskColor
{
private:
	Mat upperHalfFn(Mat &image);
	Mat lowerHalfFn(Mat &image);
	Scalar count(Mat &image);

public:
	int detect(Mat &image);
};