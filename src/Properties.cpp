#include "Properties.h"
#include "Resources.h"
#include <cmath>
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

Properties::Properties()
{
  faceOutline = imread(ASSET_PATH("/faceoutline.png"), IMREAD_UNCHANGED);
}

void Properties::calculateProperties(double width, double height)
{
  this->width = static_cast<int>(width);
  this->height = static_cast<int>(height);
  calculateOutline();
}

void Properties::calculateOutline()
{
  faceOutlineHeight = floor(height * 0.6);
  float hRatio = faceOutline.rows / faceOutlineHeight;

  faceOutlineWidth = faceOutline.cols * hRatio;
  Mat resizedOutline;
  resize(faceOutline, resizedOutline, Size(faceOutlineWidth, faceOutlineHeight));

  faceOutline = resizedOutline;
}
