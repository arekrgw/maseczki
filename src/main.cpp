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

int main(int argc, char **argv)
{
	
	Mat frame, org;
	VideoCapture cap;
	cap.open(0);

	if (!cap.isOpened())
	{
		std::cerr << "ERROR! Unable to open camera\n";
		return -1;
	}

	Properties props;
	

	props.calculateProperties(cap.get(CAP_PROP_FRAME_WIDTH), cap.get(CAP_PROP_FRAME_HEIGHT));
	MaskDetection maskDetection(props);

	DetectionTimer detectionTimer;

	for (;;)
	{
		Mat raw, rawBlurred;

		cap.read(raw);
		GaussianBlur(raw, rawBlurred, Size(1, 1), 0);
		flip(rawBlurred, frame, 1);

		if (frame.empty())
		{
			std::cerr << "ERROR! blank frame grabbed\n";
			break;
		}
		Rect face, eyePair, mouth, nose;

		MaskOn result = maskDetection.detect(frame, face, eyePair, mouth, nose);

		Painter::paintOutline(frame, props);

		Painter::paintFaceCharacteristics(frame, face, eyePair, mouth, nose, result);


		DetectionTimer::DetectionStatus status = detectionTimer.checkTimer();
		
		if (status == DetectionTimer::STARTED) {
			Painter::paintText(frame, "Detection started", Scalar(0, 120, 255));
		}
		else if (status == DetectionTimer::WAIT_FOR_FACE) {
			Painter::paintText(frame, "Fit face into outline...", Scalar(255, 255, 255));
		}
		else if (status == DetectionTimer::DETECTED) {
			Painter::paintText(frame, "Mask detected", Scalar(0, 255, 0));
		}
		else if (status == DetectionTimer::NOT_DETECTED) {
			Painter::paintText(frame, "Mask not detected", Scalar(0, 0, 255));
		}

		detectionTimer.checkFrame(result);


		imshow("Live", frame);
		if (waitKey(5) >= 0)
			break;
	}

	return 0;
}