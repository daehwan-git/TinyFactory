#include "Camera.h"

void Camera::DisplayCamera(int fps)
{
    if (!isRun)
    {
        isRun = true;
        this->fps = fps;
        cameraThread = AfxBeginThread(CameraDrawThread, this);
    }
}

void Camera::StopCamera()
{
    if (isRun)
    {
        isRun = false;
    }
}

void Camera::ReleaseCamera()
{
    if (cameraThread != nullptr)
    {
        DWORD exitCode = NULL;
        TerminateJobObject(cameraThread->m_hThread, exitCode);
    }

    if (objectDetction != nullptr)
    {
        delete objectDetction;
    }
}

void Camera::DrawRect()
{
    videoCapture->read(matFrame);

    if (objectDetction != nullptr && WorkManager::GetInstance()->IsDetection())
    {
        objectDetction->YoloDataFrame(matFrame);
    }

    int bpp = 8 * matFrame.elemSize();
    assert(bpp == 8 || bpp == 24 || bpp == 32);

    int padding = 0;

    if (bpp < 32)
        padding = 4 - (matFrame.cols % 4);

    if (padding == 4)
        padding = 0;

    int border = 0;

    if (bpp < 32)
    {
        border = 4 - (matFrame.cols % 4);
    }
   
    Mat matTemp;
    if (border > 0 || matFrame.isContinuous() == false)
    {
        cv::copyMakeBorder(matFrame, matTemp, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
    }
    else
    {
        matTemp = matFrame;
    }

    BITMAPINFO* bitinfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
    bitinfo->bmiHeader.biBitCount = bpp;
    bitinfo->bmiHeader.biWidth = matTemp.cols;
    bitinfo->bmiHeader.biHeight = matTemp.rows;
    bitinfo->bmiHeader.biPlanes = 1;
    bitinfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitinfo->bmiHeader.biCompression = BI_RGB;
    bitinfo->bmiHeader.biClrImportant = 0;
    bitinfo->bmiHeader.biClrUsed = 0;
    bitinfo->bmiHeader.biSizeImage = 0;
    bitinfo->bmiHeader.biXPelsPerMeter = 0;
    bitinfo->bmiHeader.biYPelsPerMeter = 0;

    if (matTemp.cols == winSize.width && matTemp.rows == winSize.height)
    {
        SetDIBitsToDevice(imageMfc.GetDC(),
            0, 0, winSize.width, winSize.height,
            0, 0, 0, matTemp.rows,
            matTemp.data, bitinfo, DIB_RGB_COLORS);
    }
    else
    {
        int destx = 0, desty = 0;
        int destw = winSize.width;
        int desth = winSize.height;

        int imgx = 0, imgy = 0;
        int imgWidth = matTemp.cols - border;
        int imgHeight = matTemp.rows;

        StretchDIBits(imageMfc.GetDC(),
            destx, desty, destw, desth,
            imgx, imgy, imgWidth, imgHeight,
            matTemp.data, bitinfo, DIB_RGB_COLORS, SRCCOPY);
    }

    HDC dc = ::GetDC(videoRect->m_hWnd);
    imageMfc.BitBlt(dc, 0, 0);
    ::ReleaseDC(videoRect->m_hWnd, dc);
}


UINT Camera::CameraDrawThread(LPVOID lpParam)
{
    Camera* camera = (Camera*)lpParam;

    while (camera->isRun)
    {
        camera->DrawRect();
        Sleep(1000 / camera->fps);
    }

    return 0;
}