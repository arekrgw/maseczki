#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


class MaskDetect {
    public:
    cv::Mat image;
    MaskDetect(cv::Mat file){
        image = file;
    }
    cv::Mat DetectFace();
};

