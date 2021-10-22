#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

class MaskDetect
{
public:
    cv::Mat image;
    MaskDetect(cv::Mat file)
    {
        if (image.empty())
        {
            std::cout << "Could not find or open the image." << std::endl;
            exit(-1);
        }
        image = file;
    }
    cv::Mat DetectFace();
};
