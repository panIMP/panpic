#ifndef PANIMAGE_H
#define PANIMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <QImage>
#include <QMessageBox>

class PanImage
{
private:
    cv::Mat mat;
    bool channelChangeState;


public:
    PanImage();
    ~PanImage();

    void SetMat(cv::Mat& newMat);
    cv::Mat& GetMat();

    void SetChannelChangeState(bool state);
    bool GetChannelChangeState();

    QImage PanImage2QImage();
};

#endif // CVIMAGE_H
