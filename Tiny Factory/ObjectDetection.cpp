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
		if (!WorkManager::GetInstance()->IsDetection())continue;
		if(!objectDetection->isFinishYolo)
			objectDetection->YOLO(objectDetection->matFrame);
		Sleep(500);
	}

	return 0;
}


void ObjectDetection::YoloDataFrame(Mat matFrame)
{
	if (!matFrame.empty())
	{
		cvtColor(matFrame, matFrame, COLOR_BGRA2BGR);
		matFrame.copyTo(this->matFrame);
	}
}

void ObjectDetection::StopObjectDetection()
{
	if (isRun) {
		isRun = false;
	}
}

void ObjectDetection::StartObjectDetection()
{
	if (!isRun) {
		isRun = true;
		detectionThread = AfxBeginThread(RunThread_YOLO, this);
	}
}

void ObjectDetection::ReleaseObjectDetection()
{
	if (detectionThread) {
		WaitForSingleObject(detectionThread->m_hThread, INFINITE);
		detectionThread = nullptr;  
	}
	matFrame.release();
}



void ObjectDetection::YOLO(Mat matFrame)
{
	if (!matFrame.empty() && !m_net.empty()) {
		Mat inputBlob = blobFromImage(matFrame, 1 / 255.f, Size(416, 416), Scalar(), true, false);
		m_net.setInput(inputBlob);

		std::vector<String> outNames = m_net.getUnconnectedOutLayersNames();
		m_net.forward(outs, outNames);

		processDetections(outs, matFrame, classes, THRESHOLD);
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

	try {
		m_net = readNetFromDarknet(yoloCfg, yoloWeight);

		if (m_net.empty())
		{
			LogManager::GetInstance()->WriteLog("데이터 셋이 로드 되지 않았습니다.");
		}
		else {
			LogManager::GetInstance()->WriteLog("데이터 셋 준비 완료.");
		}

		m_net.setPreferableBackend(DNN_BACKEND_OPENCV);
		m_net.setPreferableTarget(DNN_TARGET_CPU);
	}catch(Exception e)
	{
		LogManager::GetInstance()->WriteLog("데이터 셋이 존재하지 않음.");
	}
}


void ObjectDetection::processDetections(const std::vector<Mat>& outs, const Mat& img, const std::vector<std::string>& classes, float confThreshold)
{
	bool flag = false;
	std::vector<String> classNames;

	for (size_t i = 0; i < outs.size(); ++i)
	{
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) //탐지된 객체에 대해 반복
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols); //클래스 확률을 저장한 부분
			Point classIdPoint;
			double confidence;

			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

			if (confidence > confThreshold)
			{
				flag = true;

				int centerX = (int)(data[0] * img.cols);
				int centerY = (int)(data[1] * img.rows);
				int width = (int)(data[2] * img.cols);
				int height = (int)(data[3] * img.rows);
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				rectangle(img, Point(left, top), Point(left + width, top + height), Scalar(0, 255, 0), 3);
				String label = format("%.2f", confidence);
				if (!classes.empty())
				{
					CV_Assert(classIdPoint.x < (int)classes.size());
					label = classes[classIdPoint.x] + ":" + label;
					classNames.push_back(classes[classIdPoint.x]);
				}

				int baseLine;
				Size labelSize = getTextSize(label, FONT_HERSHEY_SIMPLEX, 0.5, 1, &baseLine);
				top = max(top, labelSize.height);
				rectangle(img, Point(left, top - round(1.5 * labelSize.height)), Point(left + round(1.5 * labelSize.width), top + baseLine), Scalar(255, 255, 255), FILLED);
				putText(img, label, Point(left, top), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0, 0, 0), 1);

			}
		}
	}

	if (flag)
	{
		DrawObjectdetection(img);
		isFinishYolo = true;
		WorkManager::GetInstance()->FinishYOLO(classNames);
	}
}

void ObjectDetection::DrawObjectdetection(const Mat& img)
{
	if (img.empty()) return;

	CRect rect;
	detectionRect->GetClientRect(&rect);
	int width = rect.Width();
	int height = rect.Height();


	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biWidth = img.cols;
	bitInfo.bmiHeader.biHeight = -img.rows; 
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biBitCount = 24;
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biClrImportant = 0;

	CDC* pDC = detectionRect->GetDC();
	StretchDIBits(pDC->m_hDC,
		0, 0, width, height,
		0, 0, img.cols, img.rows,
		img.data, &bitInfo, DIB_RGB_COLORS, SRCCOPY);
	detectionRect->ReleaseDC(pDC);
}
