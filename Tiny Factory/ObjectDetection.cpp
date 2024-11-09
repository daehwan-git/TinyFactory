#include "ObjectDetection.h"

#include "pch.h"
#include "opencv2/opencv.hpp"
#include "opencv2//dnn/dnn.hpp"
#include "vector"
#include<string>
#include <fstream>

using namespace cv;

UINT ObjectDetection::RunThread_YOLO(LPVOID pParam)
{
	ObjectDetection* objectDetection = (ObjectDetection*)pParam;

	while (objectDetection->isRun)
	{
		if (!objectDetection->matQueue.empty())
		{
			Mat matFrame = objectDetection->matQueue.front();
			objectDetection->matQueue.pop();
			objectDetection->YOLO(matFrame);
		}
		Sleep(10);
	}
	return 0;
}


void ObjectDetection::StartObjectDetection(Mat matFrame)
{
	if (!matFrame.empty())
	{
		matFrame.copyTo(this->matFrame);
		matQueue.push(this->matFrame);
		isRun = true;
		AfxBeginThread(RunThread_YOLO, this);
	}
}

void ObjectDetection::YOLO(Mat matFrame)
{
	if (!matFrame.empty() && !m_net.empty()) {
		Mat inputBlob = blobFromImage(matFrame, 1 / 255.f, Size(416, 416), Scalar(), true, false);
		m_net.setInput(inputBlob);

		std::vector<String> outNames = m_net.getUnconnectedOutLayersNames();
		m_net.forward(outs, outNames);

		//processDetections(outs, matFrame, classes, THRESHOLD);
	}
}

void ObjectDetection::InitTrainSet()
{
	std::ifstream ifs(yoloClassFile.c_str());
	std::string line;

	while (getline(ifs, line))
	{
		classes.push_back(line);
	}

	m_net = readNetFromDarknet(yoloCfg, yoloWeight);

	if (m_net.empty())
	{
		LogManager::GetInstance().WriteLog("데이터 셋이 로드 되지 않았습니다.");
	}
	else {
		LogManager::GetInstance().WriteLog("데이터 셋 준비 완료.");
	}

	m_net.setPreferableBackend(DNN_BACKEND_OPENCV);
	m_net.setPreferableTarget(DNN_TARGET_CPU);
}


void ObjectDetection::processDetections(const std::vector<Mat>& outs, const Mat& img, const std::vector<std::string>& classes, float confThreshold)
{
	for (size_t i = 0; i < outs.size(); ++i)
	{
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) //탐지된 객체에 대해 반복
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols); //클래스 확률을 저장한 부분
			Point classIdPoint;
			double confidence;

			//클래스 확률 중 가장 높은 값을 찾음
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

			if (confidence > confThreshold)
			{
				//객체의 bounding box 좌표 계산
				int centerX = (int)(data[0] * img.cols);
				int centerY = (int)(data[1] * img.rows);
				int width = (int)(data[2] * img.cols);
				int height = (int)(data[3] * img.rows);

				//좌상단 좌표 계산
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				//bounding box 그리기

				rectangle(img, Point(left, top), Point(left + width, top + height), Scalar(0, 255, 0), 3);
				String label = format("%.2f", confidence);
				if (!classes.empty())
				{
					CV_Assert(classIdPoint.x < (int)classes.size());
					label = classes[classIdPoint.x] + ":" + label;
				}

				int baseLine;
				Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				top = max(top, labelSize.height);
				rectangle(img, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
				putText(img, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);

			}
		}
	}
}
