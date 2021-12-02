#pragma once
#include <opencv2/opencv.hpp>
#include "MaskOn.h"
#include "Properties.h"

using namespace cv;

class Painter
{
public:
  static void paintFaceCharacteristics(Mat &image, Rect &face, Rect &eyes, Rect &mouth, Rect &nose, MaskOn status);
  static void paintText(Mat &image, std::string text, Scalar color);
  static void Painter::paintTextxy(Mat& image, Point& point, std::string text, Scalar color);
  static void paintOutline(Mat &image, Properties &props);
};