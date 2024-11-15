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
	bool isFinishYolo = false;
	
	CStatic* detectionRect;
	
	CWinThread* detectionThread;

public:
	ObjectDetection(CStatic* detectionRect):detectionRect(detectionRect)
	{
		InitTrainSet();
		StartObjectDetection();
	}


	~ObjectDetection()
	{
		StopObjectDetection();
		ReleaseObjectDetection();	
	}


public:
	void YoloDataFrame(Mat matFrame);
	void StopObjectDetection();
	void StartObjectDetection();
	void ResetFinishFlag() { isFinishYolo = false; }

private:
	void InitTrainSet();
	void YOLO(Mat matFrame);
	void ReleaseObjectDetection();
	void DrawObjectdetection(const Mat& img);
	static UINT RunThread_YOLO(LPVOID pParam);
	void processDetections(const std::vector<Mat>& outs, const Mat& img,
		const std::vector<std::string>& classes, float confThreshold);
};

