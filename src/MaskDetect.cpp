#include "../include/MaskDetect.h"
#include "../include/Resources.h"
#include <iostream>

using namespace cv;

MaskDetect::MaskDetect()
{
    LoadFaceCascade();
}

Mat MaskDetect::DetectFace(Mat image)
{
    if (image.empty())
    {
        throw std::invalid_argument("Image not provided");
    }

    std::vector<Rect> faces;

    faceCascade.detectMultiScale(image, faces, 1.2, 2, CASCADE_DO_CANNY_PRUNING, Size(100, 100));

    for (int i = 0; i < faces.size(); i++)
    {
        Point center(faces[i].x + faces[i].width * 0.5, faces[i].y + faces[i].height * 0.5);
        ellipse(image, center, Size(faces[i].width * 0.5, faces[i].height * 0.5), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
    }

    return image;
}

void MaskDetect::LoadFaceCascade()
{
    if (faceCascade.empty())
    {
        faceCascade.load(FACE_CASCADE);
    }
}