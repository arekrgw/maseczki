#include "MaskColor.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include "Painter.h"
#include <opencv2/opencv.hpp>

#include <opencv2/highgui/highgui.hpp>

using namespace cv;

int MaskColor::detect(Mat &image)
{
	if (image.empty())
	{
		throw std::invalid_argument("Image not provided");
	}

	Mat imgToFindFace2;
	resize(image, imgToFindFace2, Size(), 0.2, 0.2);
	Mat upperHalf = upperHalfFn(imgToFindFace2);
	Mat lowerHalf = lowerHalfFn(imgToFindFace2);

	Scalar countUpper = count(upperHalf);
	Scalar countLower = count(lowerHalf);
	int color = 0;
	for (int i = 0; i < 3; i++)
	{
		if (countUpper[i] - countLower[i] < 0)
			color += countLower[i] - countUpper[i];
		else
			color += countUpper[i] - countLower[i];
	}
	color /= 3;
	if (color >= 50)
		return 0;
	return 1;
}

Mat MaskColor::upperHalfFn(Mat &image)
{
	Mat croppedImage = image(Rect(image.cols * 0.4, image.rows * 0.1, image.cols * 0.2, image.rows * 0.2));
	return croppedImage;
}

Mat MaskColor::lowerHalfFn(Mat &image)
{
	Mat croppedImage = image(Rect(image.cols * 0.4, image.rows * 0.7, image.cols * 0.2, image.rows * 0.2));
	return croppedImage;
}

Scalar MaskColor::count(Mat &image)
{
	Scalar tab;
	tab = mean(image);
	return tab;
}
