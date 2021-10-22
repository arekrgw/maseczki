#include "../include/MaskDetect.h"

cv::Mat MaskDetect::DetectFace()
{
    cv::Mat image = cv::imread(filePath, cv::IMREAD_COLOR);
    cv::Mat imgToFindFace;

    if (image.empty())
    {
        std::cout << "Could not find or open the image." << std::endl;
        exit(-1);
    }

    cv::cvtColor(image, imgToFindFace, cv::COLOR_BGR2GRAY);

    cv::CascadeClassifier faceCascade;
    faceCascade.load("/Users/adamglowacz/Desktop/C++Project/TeamProject/maseczeki-pk/opencv-4.5.4/data/haarcascades/haarcascade_frontalface_alt2.xml");

    std::vector<cv::Rect> faces;

    faceCascade.detectMultiScale(imgToFindFace, faces, 1.2, 2, cv::CASCADE_DO_CANNY_PRUNING, cv::Size(100, 100));

    for (int i = 0; i < faces.size(); i++)
    {
        cv::Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
        ellipse(imgToFindFace, center, cv::Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, cv::Scalar(255, 0, 255), 4, 8, 0);
    }

    return imgToFindFace;
}