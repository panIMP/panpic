#ifndef IMAGEHANDL_H
#define IMAGEHANDL_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QImage>

class ImageHandle
{
public:
    ImageHandle();

    static QImage cvMat2QImage(const cv::Mat& image);

    void MirrorV(cv::Mat& image);
    void MirrorH(cv::Mat& image);
    void RotateClockWise(cv::Mat& image);
    void RotateCntrClockWise(cv::Mat& image);


private:
    cv::Mat result;
};

#endif // IMGHDL_H
