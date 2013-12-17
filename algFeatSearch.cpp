#include "algFeatSearch.h"

AlgFeatSearch::GetFeatFunc* AlgFeatSearch::GetFeat::gfFuncList = 0;
bool AlgFeatSearch::GetFeat::isInitialized = false;
AlgFeatSearch::CompareFeatFunc* AlgFeatSearch::CompareFeat::cfFuncList = 0;
bool AlgFeatSearch::CompareFeat::isInitialized = false;

AlgFeatSearch::GetFeat::GetFeat(baseImage& image, baseImage** nImage, int imageNum, _FEAT_TYPE featType) : image(image)
{
    if (!isInitialized){
        gfFuncList = new GetFeatFunc[_FEAT_TYPE_END];

        gfFuncList[_COLOR_HIST] = GetColorHist;
    }

    this->nImage = nImage;
    this->imageNum = imageNum;
    this->featType = featType;
}

void AlgFeatSearch::GetFeat::apply()
{
    gfFuncList[featType](image);
    for (int i = 0; i < imageNum; ++i)
    {
        gfFuncList[featType](*nImage[i]);
    }
}

void AlgFeatSearch::GetColorHist(baseImage& image)
{
    if (image.GetImageFeat()->state.getColorHist)
    {
        return;
    }

    // change the mat format
    cv::Mat* mat = image.GetMat();
	cv::Mat newMat;
    cv::Mat* histMat = &image.GetImageFeat()->histMat;
    unsigned int channels = mat->channels();
    double maxVal,minVal;

    switch (channels) {
    case 1:
        {
            int histSize[] = {256};
            float hRanges[] = {0.0, 255.0};
            const float* ranges[] = {hRanges};
            const int channels[] = {0};

            mat->copyTo(newMat);
            cv::calcHist(&newMat, 1, channels, cv::Mat(), *histMat, 1, histSize, ranges);

            cv::minMaxLoc(*histMat, &minVal, &maxVal);

        }
        break;

    case 3:
        if (image.GetChannelChangeState()){
            cv::cvtColor(*mat, newMat, CV_RGB2HSV);
        }else{
            cv::cvtColor(*mat, newMat, CV_BGR2HSV);
        }


        break;

    case 4:
        break;
    }
}
