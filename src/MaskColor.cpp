#include "MaskColor.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/core/base.hpp>
#include <opencv2/core/mat.hpp>
#include "Painter.h"

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int MaskColor::detect(Mat& image) {
	if (image.empty())
	{
		throw std::invalid_argument("Image not provided");
	}
cv:Mat imgToFindFace2;
	cv::resize(image, imgToFindFace2, cv::Size(), 0.2, 0.2);
	Mat upperHalf = MaskColor::upperHalf(imgToFindFace2);
	//Mat lowerHalf = MaskColor::lowerHalf(imgToFindFace2);

	
	
	imshow("Image", upperHalf);
	waitKey(0);
	//float countUpper = MaskColor::count(upperHalf);
	//float countLower = MaskColor::count(lowerHalf);
	//std::cout << countLower << std::endl << countUpper;
	return 0;
}


Mat MaskColor::upperHalf(Mat& image) {
	Mat croppedImage = image(Rect(0, 0, image.cols, image.rows / 2));
	return croppedImage;
}
Mat MaskColor::lowerHalf(Mat& image) {
	Mat croppedImage = image(Rect(0, image.rows / 2, image.cols, image.rows / 2));
	return croppedImage;
}
float MaskColor::count(Mat& image) {
	return 0;
}
