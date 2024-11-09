#pragma once

#include "pch.h"
#include "opencv2/opencv.hpp"
#include "opencv2//dnn/dnn.hpp"
#include "vector"
#include<string>
#include <fstream>
#include<queue>

using namespace cv::dnn;
using namespace cv;

class ObjectDetection
{

private:
	Mat matFrame;
	std::vector<std::string> classes;
	std::vector<Mat> outs;
	Net m_net;
	bool isRun = false;
	
	std::queue<Mat> matQueue;

public:
	ObjectDetection()
	{
		InitTrainSet();
	}


public:
	void StartObjectDetection(Mat matFrame);


private:
	void YOLO(Mat matFrame);
	void InitTrainSet();
	static UINT RunThread_YOLO(LPVOID pParam);
	void processDetections(const std::vector<Mat>& outs, const Mat& img,
		const std::vector<std::string>& classes, float confThreshold);
};

