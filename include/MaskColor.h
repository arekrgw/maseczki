#pragma once
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
using namespace cv;

class MaskColor {
	private:
		Mat upperHalf(Mat& image);
		Mat lowerHalf(Mat& image);
		float count(Mat& image);

	public:
		int detect(Mat& image);

};