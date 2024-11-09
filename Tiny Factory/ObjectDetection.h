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
	Net m_net;
	std::vector<std::string> classes;
	std::vector<Mat> outs;
	bool isRun = false;
	
	CStatic* detectionRect;
	
	std::queue<Mat> matQueue;

public:
	ObjectDetection(CStatic* detectionRect):detectionRect(detectionRect)
	{
		InitTrainSet();
		isRun = true;
		AfxBeginThread(RunThread_YOLO,this);
	}


public:
	void YoloDataFrame(Mat matFrame);
	void StopObjectDetection();

private:
	void DrawObjectdetection(const Mat& img);
	void YOLO(Mat matFrame);
	void InitTrainSet();
	static UINT RunThread_YOLO(LPVOID pParam);
	void processDetections(const std::vector<Mat>& outs, const Mat& img,
		const std::vector<std::string>& classes, float confThreshold);
};

