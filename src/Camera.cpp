#include "Camera.h"
#include "Painter.h"
#include <iostream>

Camera::Camera()
{
  cap.open(0);

  if (!cap.isOpened())
  {
    throw std::runtime_error("Unable to open camera");
  }

  props.calculateProperties(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
  maskDetection = MaskDetection(props);
}

void Camera::start()
{
  for (;;)
  {
    Mat raw;

    cap.read(raw);

    if (raw.empty())
    {
      throw std::runtime_error("Blank frame grabbed");
    }

    manipulateFrame(raw);

    Rect face, eyePair, mouth, nose;

    MaskOn result = maskDetection.detect(frame, face, eyePair, mouth, nose);

    Painter::paintOutline(frame, props);

    Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, nose, result);

    DetectionTimer::DetectionStatus status = detectionTimer.checkTimer();

    paintMessageOnFrame(frame, status);

    detectionTimer.checkFrame(result);

    imshow("Mask detection camera", frame);
    if (waitKey(5) >= 0)
      break;
  }
}

void Camera::manipulateFrame(Mat &raw)
{
  Mat rawBlurred;
  GaussianBlur(raw, rawBlurred, Size(1, 1), 0);
  flip(rawBlurred, frame, 1);
}

void Camera::paintMessageOnFrame(Mat &frame, DetectionTimer::DetectionStatus status)
{
  if (status == DetectionTimer::STARTED)
  {
    Painter::paintText(frame, "Detection started", Scalar(0, 120, 255));
  }
  else if (status == DetectionTimer::WAIT_FOR_FACE)
  {
    Painter::paintText(frame, "Fit face into outline...", Scalar(255, 255, 255));
  }
  else if (status == DetectionTimer::DETECTED)
  {
    Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
  }
  else if (status == DetectionTimer::NOT_DETECTED)
  {
    Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
  }
}