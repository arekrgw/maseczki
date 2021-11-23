#include "MaskDetection.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "MouthDetection.h"
#include "MaskColor.h"
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include "Properties.h"

using namespace cv;

MaskDetection::MaskDetection(Properties &props)
{
  this->props = props;
  faceDetection = FaceDetection(props);
  eyesDetection = EyesDetection(props);
  mouthDetection = MouthDetection(props);
  noseDetection = NoseDetection(props);
}

MaskOn MaskDetection::detect(Mat &image, Rect &face, Rect &eyePair, Rect &mouth, Rect &nose)
{
  Mat croppedFace;

  int faceDetected = faceDetection.detect(image, croppedFace, face);

  if (faceDetected)
  {
    return MaskOn::NONE;
  }

  int eyesDetected = eyesDetection.detect(croppedFace, eyePair);

  if (eyesDetected)
  {
    return MaskOn::NONE;
  }

  int mouthDetected = mouthDetection.detect(croppedFace, mouth);

  if (!mouthDetected)
  {
    return MaskOn::NONE;
  }

  int noseDetected = noseDetection.detect(croppedFace, nose);

  if (!noseDetected)
  {
    return MaskOn::NONE;
  }

  int maskCol = maskColor.detect(croppedFace);

  if (maskCol == 1)
  {
    return MaskOn::NONE;
  }

  return MaskOn::CORRECT;
}