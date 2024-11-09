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

	if (objectDetection)
	{
		std::ifstream ifs(yoloClassFile.c_str());
		std::string line;
		while (getline(ifs, line))
		{
			objectDetection->classes.push_back(line);
		}
		objectDetection->m_net = readNetFromDarknet(yoloCfg, yoloWeight);
		if (objectDetection->m_net.empty())
		{
			LogManager::GetInstance().WriteLog("������ ���� �ε� ���� �ʾҽ��ϴ�.");
		}
		
		objectDetection->m_net.setPreferableBackend(DNN_BACKEND_OPENCV);
		objectDetection->m_net.setPreferableTarget(DNN_TARGET_CPU);

		while (objectDetection->isRun)
		{
			objectDetection->YOLO();
			Sleep(1);
		}
	}

	return 0;
}


void ObjectDetection::StartObjectDetection(Mat* matFrame)
{
	this->matFrame = matFrame;

	AfxBeginThread(RunThread_YOLO,this);
}

void ObjectDetection::YOLO()
{
	Mat inputBlob = blobFromImage(*matFrame, 1 / 255.f, Size(416, 416), Scalar(), true, false); // blob���� ��ȯ
	m_net.setInput(inputBlob); // YOLO �𵨿� inputBlob�� �Է����� �����Ѵ�.

	std::vector<String > outNames = m_net.getUnconnectedOutLayersNames();

	m_net.forward(outs, outNames);
}


void ObjectDetection::processDetections(const std::vector<Mat>& outs, const Mat& img, const std::vector<std::string>& classes, float confThreshold)
{
	for (size_t i = 0; i < outs.size(); ++i)
	{
		float* data = (float*)outs[i].data;
		for (int j = 0; j < outs[i].rows; ++j, data += outs[i].cols) //Ž���� ��ü�� ���� �ݺ�
		{
			Mat scores = outs[i].row(j).colRange(5, outs[i].cols); //Ŭ���� Ȯ���� ������ �κ�
			Point classIdPoint;
			double confidence;

			//Ŭ���� Ȯ�� �� ���� ���� ���� ã��
			minMaxLoc(scores, 0, &confidence, 0, &classIdPoint);

			if (confidence > confThreshold)
			{
				//��ü�� bounding box ��ǥ ���
				int centerX = (int)(data[0] * img.cols);
				int centerY = (int)(data[1] * img.rows);
				int width = (int)(data[2] * img.cols);
				int height = (int)(data[3] * img.rows);

				//�»�� ��ǥ ���
				int left = centerX - width / 2;
				int top = centerY - height / 2;

				//bounding box �׸���

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
