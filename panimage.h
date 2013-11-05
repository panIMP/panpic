#ifndef PANIMAGE_H
#define PANIMAGE_H

#include <opencv2/core/core.hpp>

class PanImage
{
private:
    cv::Mat mat;
    bool channelChangeState;


public:
    PanImage(int colorType = CV_8UC3);
    ~PanImage();

    void SetMat(cv::Mat& newMat);
    cv::Mat& GetMat();

    void SetChannelChangeState(bool state);
    bool GetChannelChangeState();
};

#endif // CVIMAGE_H
