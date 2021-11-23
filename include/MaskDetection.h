#pragma once
#include <opencv2/opencv.hpp>
#include "MaskOn.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "MouthDetection.h"
#include "NoseDetection.h"
#include "MaskColor.h"
#include "Properties.h"

using namespace cv;

class MaskDetection
{
private:
  FaceDetection faceDetection;
  EyesDetection eyesDetection;
  MouthDetection mouthDetection;
  NoseDetection noseDetection;
  MaskColor maskColor;
  Properties props;

public:
  MaskDetection(Properties &props);
  MaskOn detect(Mat &image, Rect &face, Rect &eyePair, Rect &mouth, Rect &nose);
};
