#include <opencv2/opencv.hpp>
#include "Painter.h"
#include "MaskOn.h"

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
    }else{
      putText(image, "nosek lalaala", Point(18, 70), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 0), 2);
    }
  }
}

void Painter::paintText(Mat &image, std::string text, Scalar color)
{
  putText(image, text, Point(18, 40), FONT_HERSHEY_SIMPLEX, 1, color, 2);
}
