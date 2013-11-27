
#include <iostream>
#include <highgui/highgui.hpp>
#include <cv.hpp>
#include <opencv.hpp>

using namespace std;
using namespace cv;

void morphOps(Mat &thresh) {

	//create structuring element that will be used to "dilate" and "erode" image.
	Mat erodeElement = getStructuringElement(MORPH_RECT, Size(3, 3));
	Mat dilateElement = getStructuringElement(MORPH_RECT, Size(8, 8));

	// Apply the operations
	erode(thresh, thresh, erodeElement);
	dilate(thresh, thresh, dilateElement);

}

int main() {
	Mat frame;		// The current frame of the camera
	Mat fore;		// The foreground of the image's mask
	Mat back;		// The background model
	Mat HSV;		// The Hue, Saturation, Value tranformed image
	Mat threshold;	// The mask based of the predefind colour threshold
	Mat objectCont; // The frame that contains the current frame with the contours of the objects drawn on.
	vector<vector<Point> > contours;	// vector of contours, the outline around each object
	vector<Vec4i> hierarchy;			// Used in working with the contours

	BackgroundSubtractorMOG2 bg(100, 10, false);

	// Set up the webcam to capture
	VideoCapture capture;
	capture.open(0);

	// Create a windows
	namedWindow("Input");

	for(;;) // or while(1)
	{
		// Read in the current frame.
		capture.read(frame);

		/* BGS
		bg.operator ()(frame, fore);
		bg.getBackgroundImage(back);
		//morphOps(fore);
		imshow("Fore", fore);
		imshow("Background", back);
		*/

		/* Color threshold
		cvtColor(frame,HSV,COLOR_BGR2HSV);

		// Filter out all HSV values that are not within the defined threshold
		// This specific example should isolate my orange highlighter pen.
		inRange(HSV,Scalar(0,82,89),Scalar(13,171,256),threshold);
		imshow("Color", HSV);
		//morphOps(threshold);
		imshow("Threshold", threshold);
		findContours(threshold, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_SIMPLE);
		frame.copyTo(objectCont);
		drawContours(objectCont, contours, -1, cv::Scalar(0, 0, 255), 2);
		imshow("Contours", objectCont);
		*/

		// Show the current frame in the windows
		imshow("Input", frame);

		// Wait 30 seconds and then exit once the Esc key (key 27) is pressed.
		if (waitKey(30) == 27)
					break;
	}


	return 0;
}
