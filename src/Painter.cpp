#include "Painter.h"
#include "Properties.h"
#include "MaskOn.h"
#include <opencv2/opencv.hpp>

void Painter::paintFaceCharacteristics(Mat &image, Rect &face, Rect &eyePair, Rect &mouth, Rect &nose, MaskOn status)
{
  Scalar color(255, 0, 0);

  if (status == MaskOn::CORRECT)
  {
    color = Scalar(0, 255, 0);
  }
  if (status == MaskOn::NONE)
  {
    color = Scalar(0, 0, 255);
  }

  if (!face.empty())
  {
    rectangle(image, face, color, 7, 8, 0);
    if (!eyePair.empty())
    {
      rectangle(image, Rect(eyePair.x + face.x, eyePair.y + face.y, eyePair.width, eyePair.height), color, 7, 8, 0);
    }

    if (!mouth.empty())
    {
      rectangle(image, Rect(mouth.x + face.x, mouth.y + face.y, mouth.width, mouth.height), color, 7, 8, 0);
    }

    if (!nose.empty())
    {
      rectangle(image, Rect(nose.x + face.x, nose.y + face.y, nose.width, nose.height), color, 7, 8, 0);
    }
  }
}

void Painter::paintText(Mat &image, std::string text, Scalar color)
{
  putText(image, text, Point(18, 40), FONT_HERSHEY_SIMPLEX, 1, color, 2);
}

void Painter::paintOutline(Mat &image, Properties &props)
{
  Point location(image.cols / 2 - (props.faceOutline.cols / 2), image.rows / 2 - (props.faceOutline.rows / 2));

  for (int y = max(location.y, 0); y < image.rows; ++y)
  {
    int fY = y - location.y;

    if (fY >= props.faceOutline.rows)
      break;

    for (int x = max(location.x, 0); x < image.cols; ++x)
    {
      int fX = x - location.x;

      if (fX >= props.faceOutline.cols)
        break;

      double opacity = ((double)props.faceOutline.data[fY * props.faceOutline.step + fX * props.faceOutline.channels() + 3]) / 255;

      for (int c = 0; opacity > 0 && c < image.channels(); ++c)
      {
        unsigned char overlayPx = props.faceOutline.data[fY * props.faceOutline.step + fX * props.faceOutline.channels() + c];
        unsigned char srcPx = image.data[y * image.step + x * image.channels() + c];
        image.data[y * image.step + image.channels() * x + c] = srcPx * (1. - opacity) + overlayPx * opacity;
      }
    }
  }
}
