#pragma once

#include "pch.h"
#include "opencv2/opencv.hpp"
#include "opencv2//dnn/dnn.hpp"
#include "vector"
#include<string>
#include <fstream>

using namespace cv::dnn;
using namespace cv;

class ObjectDetection
{


private:
	Mat* matFrame;
	std::vector<std::string> classes;
	std::vector<Mat> outs;
	Net m_net;
	float confThreshold = 0.5;
	bool isRun = false;



public:
	void StartObjectDetection(Mat* matFrame);
	bool IsRun() { return isRun; }

private:
	void YOLO();
	static UINT RunThread_YOLO(LPVOID pParam);
	void processDetections(const std::vector<Mat>& outs, const Mat& img,
		const std::vector<std::string>& classes, float confThreshold);
};

