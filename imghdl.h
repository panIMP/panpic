#ifndef IMGHDL_H
#define IMGHDL_H

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

class imgHdl
{
public:
    imgHdl(cv::Mat& init_cvMatImg);



private:
    cv::Mat result;
};

#endif // IMGHDL_H
