#include "MouthDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

MouthDetection::MouthDetection()
{
	loadMouthCascade();
}

int MouthDetection::detect(Mat &image, Rect &coords)
{
	if (image.empty())
	{
		throw std::invalid_argument("Image not provided");
	}

	std::vector<Rect> mouths;

	Mat croppedImage = image(Rect(0, image.rows / 2, image.cols, image.rows / 2));

	findAllMouth(croppedImage, mouths);

	if (!mouths.size())
		return 1;

	coords = Rect(mouths[0].x, mouths[0].y + image.rows / 2, mouths[0].width, mouths[0].height);

	return 0;
}

void MouthDetection::findAllMouth(Mat &image, std::vector<Rect> &mouths)
{
	mouthCascade.detectMultiScale(image, mouths, 1.1, 10, CASCADE_DO_CANNY_PRUNING, Size(200, 75));
}

void MouthDetection::loadMouthCascade()
{
	mouthCascade.load(MOUTH_CASCADE);
}