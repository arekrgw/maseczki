#pragma once
#include "MaskOn.h"
#include "Properties.h"
#include <opencv2/opencv.hpp>

using namespace cv;

class Painter
{
public:
  static void paintFaceCharacteristics(Mat &image, Rect &face, Rect &eyes, Rect &mouth, Rect &nose, MaskOn status);
  static void paintText(Mat &image, std::string text, Scalar color);
  static void paintOutline(Mat &image, Properties &props);
};