#include "panimagehistproc.h"

PanImageHistProc* PanImageHistProc::instance = 0;

PanImageHistProc::PanImageHistProc()
{

}


PanImageHistProc::~PanImageHistProc(){

}


PanImageHistProc* PanImageHistProc::GetInstance(){
    if (instance == 0){
        instance = new PanImageHistProc();
    }

    return instance;
}


void PanImageHistProc::Destroy(){
    if (instance != 0){
        delete instance;
        instance = 0;
    }
}


/*  Function:        GetHistImage(PanImage& inputImage)
 *  Description:     Calculate the histogram of panimage
 *                   Gray image:  calculate the gray histogram
 *                   Color image: calculate the hsv format image histogram, 2 histograms
 *                                1. h(hue) - s(saturation) histogram
 *                                2. v(value) hitogram
 *  Input:           PanImage instance
 *  Output:          PanImage containing histogram
 */
PanImage PanImageHistProc::GetHistImage(PanImage& inputImage){
    cv::Mat mat = inputImage.GetMat();
    cv::MatND hist;
    PanImage histPanImg;

    if (mat.channels() == 1){
        int histSize[] = {256};
        float hRanges[] = {0.0, 255.0};
        const float* ranges[] = {hRanges};
        const int channels[] = {0};
        cv::calcHist(&mat, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
        double maxVal = 0;
        double minVal = 0;
        cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
        cv::Mat histImg(histSize[0], histSize[0], CV_8UC1, cv::Scalar(255));
        int hpt = static_cast<int>(0.9 * histSize[0]);
        for (int h = 0; h < histSize[0]; h ++){
            float binVal = hist.at<float>(h);
            int intensity = static_cast<int>(binVal * hpt / maxVal);
            cv::line(histImg, cv::Point(h, histSize[0]),
                    cv::Point(h, histSize[0] - intensity),
                    cv::Scalar(0));
        }
        histPanImg.SetMat(histImg);
    }

    else if (mat.channels() == 3){
        cv::Mat hsv;
        cv::cvtColor(mat, hsv, CV_BGR2HSV);
        std::vector<cv::Mat> v(hsv.channels());
        cv::split(hsv, v);
        std::vector<cv::Mat> temp(hsv.channels() - 1);
        temp[0] = v[0];
        temp[1] = v[1];
        cv::Mat hs;
        cv::merge(temp, hs);

        int hbins = 30;
        int sbins = 20;
        int histSize[] = {hbins, sbins};
        float hranges[] = {0, 180};
        float sranges[] = {0, 255};
        const float* ranges[] = {hranges, sranges};
        int channels[] = {0, 1};
        cv::MatND hist;
        cv::calcHist(&hs, 1, channels, cv::Mat(), hist, 2, histSize, ranges, true, false);
        double maxVal;
        cv::minMaxLoc(hist, 0, &maxVal, 0, 0);
        int height = 360;
        int width = (hbins*sbins*1);
        cv::Mat histImg(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
        cv::Mat hsv_color(1,1,CV_8UC3, cv::Scalar(0,0,0));
        cv::Mat rgb_color(1,1,CV_8UC3, cv::Scalar(0,0,0));
        int bin_w = width / (hbins * sbins);
        for (int h = 0; h < hbins; h++){
            for (int s = 0; s < sbins; s++){
                float binVal = hist.at<float>(h,s);
                int intensity = cvRound(binVal * 255 / maxVal);
                int i = h*sbins + s;
                hsv_color.setTo(cv::Scalar(h*180.f / hbins, s*255.f/sbins, 255));
                cv::cvtColor(hsv_color,rgb_color,CV_HSV2BGR);
                cv::Scalar color = rgb_color.at<cv::Vec3b>(0,0);
                cv::rectangle(histImg, cv::Point(i*bin_w,height),
                              cv::Point((i+1)*bin_w,height - intensity),
                              color, -1);
            }
        }
        histPanImg.SetMat(histImg);
    }

    return histPanImg;
}


/*  Function:        HistEqalization(PanImage& inputImage)
 *  Description:     Calculate histogram equalization:
 *                   Gray image:    equalize the gray histogram
 *                   Color image:   equalize R, G, B channel independently
 *  Input:           PanImage instance
 *  Output:          PanImage histogram equalized
 */
bool PanImageHistProc::HistEqalization(PanImage &inputImage){
    cv::Mat mat = inputImage.GetMat();
    if (mat.channels() == 1){
        cv::equalizeHist(mat, mat);
    }
    else if (mat.channels() == 3){
        std::vector<cv::Mat> v(mat.channels());
        cv::split(mat, v);
        cv::equalizeHist(v[0], v[0]);
        cv::equalizeHist(v[1], v[1]);
        cv::equalizeHist(v[2], v[2]);
        cv::merge(v, mat);
    }

    return true;
}

bool PanImageHistProc::HistMatch(PanImage &inputImage, double* histR){
    cv::Mat mat = inputImage.GetMat();
    cv::Mat histGray;
    if (mat.channels() == 1){
        int histSize[] = {256};
        float hRanges[] = {0.0, 255.0};
        const float* ranges[] = {hRanges};
        const int channels[] = {0};
        cv::calcHist(&mat, 1, channels, cv::Mat(), histGray, 1, histSize, ranges);
        double histAccumR[256] = {0.0};
        for (int i = 0; i < 256; i++){
            if (i == 0){
                histAccumR[0] = histR[0];
            }
            else {
                histAccumR[i] = histAccumR[i - 1] + histR[i];
            }
        }
        double histAccumS[256] = {0.0};
        for (int i = 0; i < 256; i++){
            if (i == 0){
                histAccumS[0] = histGray.at<double>(i);
            }
            else {
                histAccumS[i] = histAccumS[i - 1] + histGray.at<double>(i);
            }
        }
        int histMap[256] = {};
        for (int i = 0; i < 256; i++){
            int m = 0;
            long double min_value = 1.0f;
            for (int j = 0; j < 256; j++){
                long double now_value = fabs(long double(histAccumR[j] - histAccumS[i]));
                if (now_value < min_value){
                    m = j;
                    min_value = now_value;
                }
            }
            histMap[i] = (uchar)m;
        }
        for (int i =0; i < mat.rows; i ++){
            uchar* data = mat.ptr<uchar>(i);
            for (int j=0; j < mat.cols; j++){
                data[j] = histMap[data[j]];
            }
        }
    }
    else if (mat.channels() == 3){
        std::vector<cv::Mat> v(mat.channels());
        cv::split(mat, v);
        cv::Mat histV1, histV2, histV3;
    }

    return true;
}








