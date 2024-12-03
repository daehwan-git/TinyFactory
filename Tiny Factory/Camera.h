#pragma once
#include"pch.h"
#include"ObjectDetection.h"
#include"opencv2/opencv.hpp"

class Camera
{

private:
	cv::VideoCapture* videoCapture = nullptr;
	cv::Mat matFrame;
	CStatic* m_videoRect;
	cv::Size winSize;
	CImage imageMfc;
	int fps = 0;
	
	bool isRun = false;
	CWinThread* cameraThread = nullptr;

	ObjectDetection* objectDetction = nullptr;


public:
	Camera(IN CStatic* videoRect, CStatic* detectionRect, int videoNumber);
	~Camera()
	{
		StopCamera();
		ReleaseCamera();
	}

public:
	void DisplayCamera(int fps = 30);
	void StopCamera();
	ObjectDetection* GetObjectDetection() { return objectDetction; }

private:
	void DrawRect();
	void ReleaseCamera();
	static UINT CameraDrawThread(LPVOID lpParam);

};

