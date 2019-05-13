#include "ArAPI.h"
#include "opencv2\core.hpp"
#include "opencv2\imgproc.hpp"
#include "opencv2\highgui.hpp"
#include "opencv2\aruco.hpp"
#include "opencv2\calib3d.hpp"
#include<sstream>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;
using namespace cv;

float arucoSquareDimension = 0.035f;

Mat cameraMatrix = (Mat_<double>(3, 3) << 576.24f, 0, 336.028f, 0, 551.223f, 217.193f, 0, 0, 1);
Mat distanceCoefficient = (Mat_<double>(5, 1) << 0.0275974f, -0.269153, -0.00151854, -0.00468928, 0.348432);

MYSHARED_API int add(int a, int b)
{
	return a + b;
}

MYSHARED_API int startWebcamMonitoring(Color32* raw, int width, int height, myValues* outvalues)
{

	int rotx, roty, rotz;
	int dispx, dispy, dispz;
	Mat frame(height, width, CV_8UC4, raw);
	Mat frame2;
	cvtColor(frame, frame, CV_BGR2RGB);
	cv::flip(frame, frame, 0);
	vector<int> markerIds;
	vector<vector<Point2f>> markerCorners, rejectedCandidates;
	aruco::DetectorParameters parameters;
	Ptr<aruco::Dictionary> markerDictionary = aruco::getPredefinedDictionary(aruco::PREDEFINED_DICTIONARY_NAME::DICT_4X4_50);
	string rotvalue;

	vector<Vec3d> rotationVectors, translationvectors;
	try {
		aruco::detectMarkers(frame, markerDictionary, markerCorners, markerIds);

		aruco::estimatePoseSingleMarkers(markerCorners, arucoSquareDimension, cameraMatrix, distanceCoefficient, rotationVectors, translationvectors);

		if (rotationVectors.size() > 0 && translationvectors.size() > 0) {

			outvalues[0] = myValues(translationvectors[0][0], translationvectors[0][1] , translationvectors[0][2], rotationVectors[0][0] , rotationVectors[0][1] , rotationVectors[0][2]);

			
		}
		else
		{//rtnStr = " ";
			return 0;
		}
			
	}
	catch (cv::Exception & e)
	{
		return 0;

	}
	return 0;
}

ArAPI::ArAPI()
{
}


ArAPI::~ArAPI()
{
}

