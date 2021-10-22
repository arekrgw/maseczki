#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>


class MaskDetect {
    public:
    std::string filePath;
    MaskDetect(std::string file){
        std::cout << file << std::endl;
        filePath = file;
    }
    cv::Mat DetectFace();
};

