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
  faceOutline = imread(ASSET_PATH("/faceoutline.png"), cv::IMREAD_COLOR);
}

void Properties::calculateProperties(double width, double height)
{
  width = static_cast<int>(width);
  height = static_cast<int>(height);
}

void Properties::calculateOutline()
{
  faceOutlineHeight = floor(height * 0.6);
}
