#include "MaskDetection.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "MouthDetection.h"
#include <iostream>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

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

  return MaskOn::CORRECT;
}