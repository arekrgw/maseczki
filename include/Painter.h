#pragma once
#include <opencv2/opencv.hpp>
#include "MaskOn.h"

using namespace cv;

class Painter
{
public:
  static void paintFaceCharacteristics(Mat &image, Rect &face, Rect &eyes, Rect &mouth, MaskOn status);
  static void paintText(Mat &image, std::string text, Scalar color);
};