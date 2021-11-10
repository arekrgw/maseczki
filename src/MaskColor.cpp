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
	if (color >= 30)
		return 0;
	return 1;
}

Mat MaskColor::upperHalfFn(Mat &image)
{
	Mat croppedImage = image(Rect(0, 0, image.cols, image.rows / 2));
	return croppedImage;
}

Mat MaskColor::lowerHalfFn(Mat &image)
{
	Mat croppedImage = image(Rect(0, image.rows / 2, image.cols, image.rows / 2));
	return croppedImage;
}

Scalar MaskColor::count(Mat &image)
{
	Scalar tab;
	tab = mean(image);
	return tab;
}
