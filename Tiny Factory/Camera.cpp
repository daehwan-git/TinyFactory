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

        if (cameraThread != nullptr)
        {
            WaitForSingleObject(cameraThread->m_hThread, INFINITE);
            cameraThread = nullptr;  
        }
    }
}

void Camera::ReleaseCamera()
{

    if (imageMfc.GetDC() != nullptr)
    {
        imageMfc.ReleaseDC();
    }

    if(imageMfc)imageMfc.Destroy();


    if (objectDetction != nullptr)
    {
        delete objectDetction;
        objectDetction = nullptr;
    }

    matFrame.release();

    if (videoCapture != nullptr)
    {
        videoCapture->release();
        delete videoCapture;
        videoCapture = nullptr;
    }
}


void Camera::DrawRect()
{
    videoCapture->read(matFrame);

    if (matFrame.empty())return;

    if (objectDetction != nullptr)
    {
        objectDetction->YoloDataFrame(matFrame);
    }

    HDC dc = ::GetDC(videoRect->m_hWnd);
    if (dc == nullptr)return;

    int bpp = 8 * matFrame.elemSize();
    assert((bpp == 8 || bpp == 24 || bpp == 32));

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

    BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
    bitInfo->bmiHeader.biBitCount = bpp;
    bitInfo->bmiHeader.biWidth = matTemp.cols;
    bitInfo->bmiHeader.biHeight = -matTemp.rows;
    bitInfo->bmiHeader.biPlanes = 1;
    bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitInfo->bmiHeader.biCompression = BI_RGB;
    bitInfo->bmiHeader.biClrImportant = 0;
    bitInfo->bmiHeader.biClrUsed = 0;
    bitInfo->bmiHeader.biSizeImage = 0;
    bitInfo->bmiHeader.biXPelsPerMeter = 0;
    bitInfo->bmiHeader.biYPelsPerMeter = 0;


    if (matTemp.cols == winSize.width && matTemp.rows == winSize.height)
    {

        SetDIBitsToDevice(imageMfc.GetDC(),
            0, 0, winSize.width, winSize.height,
            0, 0, 0, matTemp.rows,
            matTemp.data, bitInfo, DIB_RGB_COLORS);
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
            matTemp.data, bitInfo, DIB_RGB_COLORS, SRCCOPY);
    }

    imageMfc.BitBlt(dc, 0, 0);
    ::ReleaseDC(videoRect->m_hWnd, dc);
    imageMfc.ReleaseDC();
    free(bitInfo);
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
