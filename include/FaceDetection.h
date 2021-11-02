#pragma once

#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;

class FaceDetection
{
private:
  CascadeClassifier faceCascade;
  void loadFaceCascade();
  int findIndexOfBestFace(Mat &image, std::vector<Rect> &faces);
  void findAllFaces(Mat &image, std::vector<Rect> &faces);
  Mat getRoi(Rect &face, Mat &image);

public:
  FaceDetection();
  int detect(Mat &image, Mat &output, Rect &coords);
};
