#include "EyesDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

EyesDetection::EyesDetection(Properties &props)
{
    loadEyesCascade();
    this->props = props;
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
    eyesCascade.detectMultiScale(image, eyes, 1.4, 4, CASCADE_DO_CANNY_PRUNING, Size(props.faceOutlineWidth * 0.5, props.faceOutlineHeight * 0.1), Size(props.faceOutlineWidth * 0.65, props.faceOutlineHeight * 0.15));
}

void EyesDetection::loadEyesCascade()
{
    eyesCascade.load(EYE_PAIR_CASCADE);
}