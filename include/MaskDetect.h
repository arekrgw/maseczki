#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;

class MaskDetect
{
private:
    CascadeClassifier faceCascade;
    void LoadFaceCascade();

public:
    MaskDetect();
    Mat DetectFace(Mat image);
};