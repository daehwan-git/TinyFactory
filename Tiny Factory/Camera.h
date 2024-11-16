#pragma once
#include"pch.h"
#include"ObjectDetection.h"
#include"opencv2/opencv.hpp"

class Camera
{

private:
	cv::VideoCapture* videoCapture;
	cv::Mat matFrame;
	CStatic* videoRect;
	cv::Size winSize;
	CImage imageMfc;
	int fps;
	
	bool isRun = false;
	CWinThread* cameraThread;

	ObjectDetection* objectDetction;


public:
	Camera(IN CStatic* videoRect,CStatic* detectionRect ,int videoNumber):winSize(),imageMfc(),cameraThread(nullptr),fps(0),
		videoCapture(nullptr),objectDetction(nullptr)
	{
		this->videoRect = videoRect;

		RECT r;
		videoRect->GetClientRect(&r);
		winSize = cv::Size(r.right, r.bottom);
		imageMfc.Create(winSize.width, winSize.height, 24);

		videoCapture = new cv::VideoCapture(videoNumber);

		if (!videoCapture->isOpened())
		{
			LogManager::GetInstance()->WriteLog("카메라를 연결 할 수 없습니다.");
			return;
		}
		else {
			LogManager::GetInstance()->WriteLog("카메라를 연결 완료했습니다.");

			if (objectDetction == nullptr)
			{
				objectDetction = new ObjectDetection(detectionRect);
			}
		}

		videoCapture->set(CAP_PROP_FRAME_WIDTH, CAMERA_WIDTH);
		videoCapture->set(CAP_PROP_FRAME_HEIGHT, CAMERA_HEIGHT);


		DisplayCamera();
	}


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
	void SetBitMapInfo(DWORD bpp, Mat matTemp);
	void DrawRect();
	void ReleaseCamera();
	static UINT CameraDrawThread(LPVOID lpParam);

};

