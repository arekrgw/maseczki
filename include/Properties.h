#pragma once
#include <opencv2/opencv.hpp>

using namespace cv;

class Properties
{
public:
  Mat faceOutline;
  int width;
  int height;
  int faceOutlineHeight;
  int faceOutlineWidth;

  Properties();
  void calculateProperties(double width, double height);
  void calculateOutline();
};