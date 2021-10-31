#include "EyesDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

EyesDetection::EyesDetection() {
	loadEyesCascade();
}


int EyesDetection::detect(Mat& image, Rect& coords)
{
    if (image.empty())
    {
        throw std::invalid_argument("Image not provided");
    }

    std::vector<Rect> eyes;

    findAllEyes(image, eyes);

    if (!eyes.size())
        return 1;

    int indexOfBestEyes = findIndexOfBestEyes(image, eyes);

    
    coords = eyes[indexOfBestEyes];

    return 0;
}

int EyesDetection::findIndexOfBestEyes(Mat& image, std::vector<Rect>& eyes)
{
    if (eyes.size() == 1)
        return 0;

    int imgCenterX = image.rows * 0.5;
    int imgCenterY = image.cols * 0.5;

    int bestEyes = -1;
    float smallestDistance = 9999999;
    for (int i = 0; i < eyes.size(); ++i)
    {
        int centerY = eyes[i].x + eyes[i].width * 0.5;
        int centerX = eyes[i].y + eyes[i].height * 0.5;

        float distance = sqrt(pow(imgCenterX - centerX, 2) + pow(imgCenterY - centerY, 2));

        if (distance < smallestDistance)
        {
            smallestDistance = distance;
            bestEyes = i;
        }
    }

    return bestEyes;
}

void EyesDetection::findAllEyes(Mat& image, std::vector<Rect>& eyes)
{
    eyesCascade.detectMultiScale(image, eyes, 1.2, 2, CASCADE_DO_CANNY_PRUNING, Size(100, 100));
}




void EyesDetection::loadEyesCascade()
{
	eyesCascade.load(EYE_PAIR_CASCADE);
}