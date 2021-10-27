#ifndef MASK_DETECT
#define MASK_DETECT

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "MaskOn.h"

using namespace cv;

class MaskDetect
{
private:
    CascadeClassifier faceCascade;
    CascadeClassifier mouthCascade;
    CascadeClassifier eyeCascade;
    void LoadFaceCascade();
    void LoadMouthCascade();
    void LoadEyeCascade();

public:
    MaskDetect();
    Mat DetectFace(Mat image);
    MaskOn DetectMask(Mat image);
};

#endif