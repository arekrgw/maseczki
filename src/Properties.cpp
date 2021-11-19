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
  faceOutlineHeight = floor(height * 0.8);
  std::cout << faceOutlineHeight << "\n";
  float hRatio = static_cast<float>(faceOutlineHeight) / faceOutline.rows;

  std::cout << faceOutline.rows << "\n";
  std::cout << hRatio << "\n";

  faceOutlineWidth = faceOutline.cols * hRatio;

  std::cout << faceOutlineWidth << "\n";

  Mat resizedOutline;
  resize(faceOutline, resizedOutline, Size(faceOutlineWidth, faceOutlineHeight), INTER_LINEAR);

  faceOutline = resizedOutline;
}
