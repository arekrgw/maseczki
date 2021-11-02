#include "EyesDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

EyesDetection::EyesDetection()
{
    loadEyesCascade();
}

int EyesDetection::detect(Mat &image, Rect &coords)
{
    if (image.empty())
    {
        throw std::invalid_argument("Image not provided");
    }

    std::vector<Rect> eyes;

    findAllEyes(image, eyes);

    if (!eyes.size())
        return 1;

    coords = eyes[0];

    return 0;
}

void EyesDetection::findAllEyes(Mat &image, std::vector<Rect> &eyes)
{
    eyesCascade.detectMultiScale(image, eyes, 1.2, 10, CASCADE_DO_CANNY_PRUNING, Size(250, 75));
}

void EyesDetection::loadEyesCascade()
{
    eyesCascade.load(EYE_PAIR_CASCADE);
}