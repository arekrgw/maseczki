#include "Camera.h"
#include "Painter.h"
#include "Executor.h"
#include <iostream>

Camera::Camera(Executor &exec)
{
  this->exec = exec;
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

    if (status == DetectionTimer::DetectionStatus::WAIT_FOR_FACE)
      exec.resetExecutor();

    paintMessageOnFrame(frame, status);
    executeScript(status);

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
  if (status == DetectionTimer::DetectionStatus::STARTED)
  {
    Painter::paintText(frame, "Detection started", Scalar(0, 120, 255));
  }
  else if (status == DetectionTimer::DetectionStatus::WAIT_FOR_FACE)
  {
    Painter::paintText(frame, "Fit face into outline...", Scalar(255, 255, 255));
  }
  else if (status == DetectionTimer::DetectionStatus::DETECTED)
  {
    Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
  }
  else if (status == DetectionTimer::DetectionStatus::NOT_DETECTED)
  {
    Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
  }
}

void Camera::executeScript(DetectionTimer::DetectionStatus status)
{
  if (status == DetectionTimer::DetectionStatus::DETECTED)
  {
    exec.executeCommand(Executor::CommandType::SUCCESS);
  }
  else if (status == DetectionTimer::DetectionStatus::NOT_DETECTED)
  {
    exec.executeCommand(Executor::CommandType::FAILURE);
  }
}