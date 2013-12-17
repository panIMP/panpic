#ifndef ALG_FEAT_SEARCH_H
#define ALG_FEAT_SEARCH_H

#include "baseTransform.h"
#include "baseImage.h"

namespace AlgFeatSearch {
    typedef void (*GetFeatFunc) (baseImage&);
    typedef void (*CompareFeatFunc) (baseImage&, baseImage&);

    void GetColorHist(baseImage& image);
    void GetAccumColorHist(baseImage& image);
    void GetColorSet(baseImage& image);
    void GetColorCoVec(baseImage& image);
    void GetGrayLevCoMatrix(baseImage& image);
    void GetTamuraTextures(baseImage& image);
    void GetFourierShapeDescript(baseImage& image);
    void GetInvariantMoments(baseImage& image);
    void GetSpacialFeats(baseImage& image);

    void CompareColorHist(baseImage& image, baseImage& compImage);
    void CompareColorAccumHist(baseImage& image, baseImage& compImage);
    void CompareColorSet(baseImage& image, baseImage& compImage);
    void CompareColorCoVec(baseImage& image, baseImage& compImage);
    void CompareGrayLevCoMatrix(baseImage& image, baseImage& compImage);
    void CompareTamuraTextures(baseImage& image, baseImage& compImage);
    void CompareFourierShapeDescript(baseImage& image, baseImage& compImage);
    void CompareInvariantMoments(baseImage& image, baseImage& compImage);
    void CompareSpacialFeats(baseImage& image, baseImage& compImage);

    class GetFeat;
    class CompareFeat;
}


class AlgFeatSearch::GetFeat : public baseTransform
{
public:
    GetFeat(baseImage& image, baseImage** nImage, int imageNum, _FEAT_TYPE featType);

    void apply();

private:
    static GetFeatFunc* gfFuncList;
    static bool isInitialized;

    baseImage& image;
    baseImage** nImage;
    int imageNum;
    _FEAT_TYPE featType;
};


class AlgFeatSearch::CompareFeat : public baseTransform
{
public:
    CompareFeat(const baseImage& image, baseImage**& nImage, int imageNum, _FEAT_TYPE featType);

    void apply();

private:
    static CompareFeatFunc* cfFuncList;
    static bool isInitialized;

    baseImage& image;
    baseImage**& nImage;
    int imageNum;
    _FEAT_TYPE featType;
};






#endif




