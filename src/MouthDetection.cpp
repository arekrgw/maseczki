#include "MouthDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

MouthDetection::MouthDetection() {
	loadMouthCascade();
}

int MouthDetection::detect(Mat& image, Rect& coords)
{
	if (image.empty())
	{
		throw std::invalid_argument("Image not provided");
	}

	std::vector<Rect> mouths;

	Mat croppedImage = image(Rect(0,image.rows/2, image.cols, image.rows/2));
	//imshow("test", croppedImage);

	findAllMouth(croppedImage, mouths);

	if (!mouths.size())
		return 1;
	int indexOfBestMouth = findIndexOfBestMouth(croppedImage, mouths);

	coords = mouths[indexOfBestMouth];

	return 0;
}

void MouthDetection::findAllMouth(Mat& image, std::vector<Rect>& mouths)
{
	mouthCascade.detectMultiScale(image, mouths);
}

int MouthDetection::findIndexOfBestMouth(Mat& image, std::vector<Rect>& mouths)
{
	int imgCenterY = image.cols * 0.5;
	float minDistance = 999999999;
	int bestMouth = -1;
	for (int i = 0; i < mouths.size(); ++i)
	{
		int centerY = mouths[i].x + mouths[i].width * 0.5;
		int centerX = mouths[i].y + mouths[i].height * 0.5;

		float distance = sqrt(pow(imgCenterY - centerY, 2));

		if (distance < minDistance)
		{
			minDistance = distance;
			bestMouth = i;
		}
	}


	return bestMouth;
}

void MouthDetection::loadMouthCascade()
{
	mouthCascade.load(MOUTH_CASCADE);
}