#include "NoseDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

NoseDetection::NoseDetection(Properties &props)
{
    loadNoseCascade();
    this->props = props;
}

int NoseDetection::detect(Mat &image, Rect &coords)
{
    if (image.empty())
    {
        throw std::invalid_argument("Image not provided");
    }

    std::vector<Rect> nose;

    findAllNose(image, nose);

    if (!nose.size())
    {
        return 1;
    }

    coords = nose[0];

    return 0;
}

void NoseDetection::findAllNose(Mat &image, std::vector<Rect> &nose)
{
    noseCascade.detectMultiScale(image, nose, 1.4, 4, CASCADE_DO_CANNY_PRUNING, Size(props.faceOutlineWidth * 0.15, props.faceOutlineWidth * 0.15), Size(props.faceOutlineWidth * 0.30, props.faceOutlineWidth * 0.30));
}

void NoseDetection::loadNoseCascade()
{
    noseCascade.load(NOSE_CASCADE);
}