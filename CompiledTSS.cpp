//#include	<opencv2/opencv.hpp>
//#include	<opencv2/highgui/highgui.hpp>
//#include	<opencv2/imgproc.hpp>
//#include	<iostream>
//#include	<stdlib.h>
//#include	<string>
//#include	<filesystem>
//#include	"Supp.h"
//
//using namespace cv;
//using namespace std;
//
//namespace efs = filesystem; // make use of the filesystem library
//
////use morphy --> canny -->douglass peucker algo
////c=4 rect, c=3 tri,c=15 circle,c=8 oct
//void shapeseg(Mat src, Mat dst) {
//
//}
//
//vector<Scalar> randomColorGenerator() {
//	// get MAXfPt random but brighter colors
//	RNG			rng(0);
//	int			t1, t2, t3, t4;
//	vector<Scalar> colors;
//	int const MAXfPt = 200;
//	for (int i = 0; i < MAXfPt; i++) {
//		for (;;) {
//			t1 = rng.uniform(0, 255); // blue
//			t2 = rng.uniform(0, 255); // green
//			t3 = rng.uniform(0, 255); // red
//			t4 = t1 + t2 + t3;
//			// get random colors that are not too dim
//			if (t4 > 255) break;
//		}
//		colors.push_back(Scalar(t1, t2, t3));
//	}
//	return colors;
//}
//
//Mat HSVRedProcessing(Mat srcI) {
//
//	Mat lower_red_hue_range;
//	Mat upper_red_hue_range;
//
//	cvtColor(srcI, srcI, COLOR_BGR2HSV);
//
//	cv::inRange(srcI, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lower_red_hue_range);
//	cv::inRange(srcI, cv::Scalar(173, 100, 55), cv::Scalar(179, 255, 255), upper_red_hue_range);
//	cv::Mat red_hue_mask;
//	cv::addWeighted(lower_red_hue_range, 1.0, upper_red_hue_range, 1.0, 0.0, red_hue_mask);
//
//	return red_hue_mask;//mask is in one channel only
//	// propose the threshold value
//}
//
//Mat HSVBlueProcessing(Mat srcI) {
//
//	Mat blueMask;
//	cvtColor(srcI, srcI, COLOR_BGR2HSV);
//	Scalar minBlue(80, 150, 60), maxBlue(140, 255, 255);
//	inRange(srcI, minBlue, maxBlue, blueMask);
//
//	return blueMask;
//}
//
//Mat HSVYellowProcessing(Mat srcI) {
//
//	Mat yellowMask;
//
//	cvtColor(srcI, srcI, COLOR_BGR2HSV);
//	Scalar minYellow(10, 80, 66), maxYellow(37, 255, 255);
//	inRange(srcI, minYellow, maxYellow, yellowMask);
//
//	return yellowMask;
//}
//
//void findCenter(Mat img, Point2i& center) {
//	Moments M = moments(img);
//	center.x = M.m10 / M.m00;
//	center.y = M.m01 / M.m00;
//
//}
//
//vector<Point> contoursConvexHull(vector<vector<Point> > contours)
//{
//	vector<Point> result;
//	vector<Point> pts;
//	int index = 0, max = contours[0].size();
//
//	for (size_t i = 0; i < contours.size(); i++)
//		for (size_t j = 0; j < contours[i].size(); j++)
//			pts.push_back(contours[i][j]);
//	convexHull(pts, result);
//	return result;
//}
//
////find the list longest contour
//vector<vector<Point>> edgeDetection(vector<vector<Point>> contours, Mat& canvasGray, Mat& canvasColor) {
//	Point2i center;
//	int max = 0, index;
//	char str[256];
//	vector<vector<Point>> contour_list;
//
//	for (int i = 0; i < contours.size(); i++) {
//		canvasGray = 0;
//
//		// look for the longest contour
//		if (max < contours[i].size()) {
//			max = contours[i].size();
//			index = i;
//		}
//
//		drawContours(canvasColor, contours, i, randomColorGenerator()[i]); // draw boundaries
//		drawContours(canvasGray, contours, i, 255);
//
//		findCenter(canvasGray, center);
//
//		// If found center is not inside contour, the result will be incorrect
//		floodFill(canvasGray, center, 255); // fill inside sign boundary
//	}
//	contour_list.push_back(contours[index]);
//	return contour_list;
//}
//
//int main(int argc, char** argv) {
//
//	string		inputDirName, sign, imageName, windowName;
//	Mat			srcI, mask;
//	bool		select = false;
//	
//	//============================== USER INPUT ======================================================
//
//	//user input to select traffic sign color(aderwin)
//	while (!select) {
//		cout << " Please enter the color of traffic sign (r=red, b=blue, y=yellow) : ";
//		cin >> sign;
//
//		if (sign == "r" || sign == "R") {
//			inputDirName = "Inputs/TrafficSigns/RedSigns";
//			select = true;
//		}
//		else if (sign == "b" || sign == "B") {
//			inputDirName = "Inputs/TrafficSigns/BlueSigns";
//			select = true;
//		}
//		else if (sign == "y" || sign == "Y") {
//			inputDirName = "Inputs/TrafficSigns/YellowSigns";
//			select = true;
//		}
//		else
//			cout << "Please enter correct value" << endl;
//	}
//
//	//================================= READING INPUT FOLDERS ======================================================
//
//	// Process each imageName as a file name ended with .png inside the directory "inputDirName"
//	for (const auto& p : efs::directory_iterator(inputDirName)) { // an iterator to the contents of the directory
//		
//		if (p.path().extension() == ".png") { // For each file, check its post script type is .png or not
//			
//			imageName = p.path().string(); // obtain the image file name
//			
//			srcI = imread(imageName);           //read input image
//			//temp.convertTo(srcI, -1,1.4, 0);
//
//			if (srcI.empty()) {
//				cout << "cannot open image for reading" << endl;
//				return -1;
//			}
//
//			//======================================= LARGEWINDOW 1 =================================================================
//			
//			resize(srcI, srcI, Size(150, 150));
//
//			// Open 2 large windows to diaplay the results. One gives the detail. Other give only the results
//			int const	noOfImagePerCol = 2, noOfImagePerRow = 3;
//			Mat			detailResultWin, win[noOfImagePerRow * noOfImagePerCol], legend[noOfImagePerRow * noOfImagePerCol];
//			createWindowPartition(srcI, detailResultWin, win, legend, noOfImagePerCol, noOfImagePerRow);
//
//			putText(legend[0], "Original", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend[1], "HSV Mask", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend[2], "Contour", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend[3], "Longest contour", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend[4], "Mask", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend[5], "Sign segmented", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//
//			//======================================= LARGEWINDOW 2 =================================================================
//
//			int const	noOfImagePerCol2 = 1, noOfImagePerRow2 = 2;
//			Mat			resultWin, win2[noOfImagePerRow2 * noOfImagePerCol2], legend2[noOfImagePerRow2 * noOfImagePerCol2];
//			createWindowPartition(srcI, resultWin, win2, legend2, noOfImagePerCol2, noOfImagePerRow2);
//
//			putText(legend2[0], "Original", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//			putText(legend2[1], "Sign segmented", Point(5, 11), 1, 1, Scalar(250, 250, 250), 1);
//
//
//			//Display original input image to the windows
//			srcI.copyTo(win[0]);
//			srcI.copyTo(win2[0]);
//
//			//============================= PREPROCESSING ===============================================================================
//			
//			GaussianBlur(srcI, srcI, Size(3, 3), 0);
//			
//
//			//============================= COLOR PROCESSING HSV =========================================================================
//
//			//create mask with HSV threshold (aderwin)
//			if (sign == "r" || sign == "R") { //Kimyu mask fixed
//				mask = HSVRedProcessing(srcI);
//
//				// a little bit of fine tuning
//				erode(mask, mask, Mat());
//				dilate(mask, mask, Mat());
//			}
//			else if (sign == "b" || sign == "B") {  //Doomjo mask fixed
//				mask = HSVBlueProcessing(srcI);
//				
//				// a little bit of fine tuning
//				erode(mask, mask, Mat());
//				dilate(mask, mask, Mat());
//			}
//			else if (sign == "y" || sign == "Y") {
//				mask = HSVYellowProcessing(srcI);
//
//				// a little bit of fine tuning
//				erode(mask, mask, Mat());
//				dilate(mask, mask, Mat());
//			}
//
//			//display mask in the window
//			cvtColor(mask, win[1], COLOR_GRAY2BGR);
//
//			//================================ FINDING CONTOURS =====================================================================
//			
//			// create blank images to draw contours
//			Mat ctr, canvasColor, canvasGray;
//			canvasColor.create(srcI.rows, srcI.cols, CV_8UC3);
//			canvasGray.create(srcI.rows, srcI.cols, CV_8U);
//			ctr.create(srcI.rows, srcI.cols, CV_8U);
//			ctr = 0;
//			canvasColor = Scalar(0, 0, 0);
//
//			vector<vector<Point> >	contours, contours_list; // to store the contours and longest contours
//
//			findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
//
//			// find the longest contour
//			contours_list = edgeDetection(contours, canvasGray, canvasColor);
//
//			canvasColor.copyTo(win[2]); // contours detected using multiple color
//
//			// draw a contour using convexhull to close the contour
//			vector<Point> ConvexHullPoints = contoursConvexHull(contours_list);
//			polylines(ctr, ConvexHullPoints, true, Scalar(255, 255, 255), 1); //ctr is the contour using convexhull
//
//			cvtColor(ctr, win[3], COLOR_GRAY2BGR); //contour drawn using convexHull
//
//			// use the contour to make a mask
//			Point2i center;
//			findCenter(ctr, center);
//
//			floodFill(ctr, center, 255); // ctr is still in grayscale here
//			cvtColor(ctr, win[4], COLOR_GRAY2BGR); // mask created
//
//			canvasColor = win[4] & win[0];
//			canvasColor.copyTo(win[5]); //segmented image
//			win[5].copyTo(win2[1]); //display result
//
//			windowName = "Segmentation of " + imageName + " (detail)";
//			imshow(windowName, detailResultWin);
//			imshow("Traffic sign segmentation", resultWin);
//
//			waitKey(0);
//			destroyAllWindows();
//		}
//	}
//	return 0;
//}