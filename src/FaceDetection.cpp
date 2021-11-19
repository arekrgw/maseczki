#include "FaceDetection.h"
#include "Resources.h"
#include <iostream>
#include <cmath>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/opencv.hpp>
#include <limits>
#include "Properties.h"

using namespace cv;

FaceDetection::FaceDetection(Properties &props)
{
  loadFaceCascade();
  this->props = props;
}

int FaceDetection::detect(Mat &image, Mat &output, Rect &coords)
{
  if (image.empty())
  {
    throw std::invalid_argument("Image not provided");
  }

  std::vector<Rect> faces;

  findAllFaces(image, faces);

  if (!faces.size())
    return 1;

  int indexOfBestFace = findIndexOfBestFace(image, faces);

  output = getRoi(faces[indexOfBestFace], image);
  coords = faces[indexOfBestFace];

  return 0;
}

int FaceDetection::findIndexOfBestFace(Mat &image, std::vector<Rect> &faces)
{
  if (faces.size() == 1)
    return 0;

  int imgCenterX = image.rows * 0.5;
  int imgCenterY = image.cols * 0.5;

  int bestFace = -1;
  float smallestDistance = std::numeric_limits<float>::max();
  for (int i = 0; i < faces.size(); ++i)
  {
    int centerY = faces[i].x + faces[i].width * 0.5;
    int centerX = faces[i].y + faces[i].height * 0.5;

    float distance = sqrt(pow(imgCenterX - centerX, 2) + pow(imgCenterY - centerY, 2));

    if (distance < smallestDistance)
    {
      smallestDistance = distance;
      bestFace = i;
    }
  }

  return bestFace;
}

void FaceDetection::findAllFaces(Mat &image, std::vector<Rect> &faces)
{
  faceCascade.detectMultiScale(image, faces, 1.2, 2, CASCADE_DO_CANNY_PRUNING, Size(props.faceOutlineWidth * 0.9, props.faceOutlineHeight * 0.9));
}

Mat FaceDetection::getRoi(Rect &face, Mat &image)
{
  return image(Range(face.y, face.y + face.height), Range(face.x, face.x + face.width));
}

void FaceDetection::loadFaceCascade()
{
  faceCascade.load(FACE_CASCADE);
}
