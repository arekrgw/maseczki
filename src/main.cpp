#include "Resources.h"
#include "FaceDetection.h"
#include "EyesDetection.h"
#include "Properties.h"
#include "MaskDetection.h"
#include "MaskColor.h"
#include "Painter.h"
#include "Timer.h"
#include <iostream>
#include <string>
#include <opencv2/highgui/highgui.hpp>
#include "DetectionTimer.h"
#include "Camera.h"

int main(int argc, char **argv)
{
	try
	{
		Camera camera;
		camera.start();
	}
	catch (std::exception error)
	{
		std::cout << error.what();
		return 1;
	}

	return 0;
}