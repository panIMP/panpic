#include "imagehandle.h"

ImageHandle::ImageHandle()
{

}

QImage ImageHandle::cvMat2QImage(const cv::Mat& image){
    cv::cvtColor(image, image, CV_BGR2RGB);
    QImage qimage = QImage((const unsigned char*)(image.data),
                           image.cols, image.rows, QImage::Format_RGB888);
    return qimage;
}

void ImageHandle::MirrorV(cv::Mat& image){
    cv::flip(image, image, 0);
}

void ImageHandle::MirrorH(cv::Mat& image){
    cv::flip(image, image, 1);
}

void ImageHandle::RotateClockWise(cv::Mat &image){
    cv::transpose(image, image);
    cv::flip(image, image, 1);
}

void ImageHandle::RotateCntrClockWise(cv::Mat &image){
    cv::transpose(image, image);
    cv::flip(image, image, 0);
}
