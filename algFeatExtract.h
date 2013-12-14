#ifndef ALG_FEAT_EXTRACT_H
#define ALG_FEAT_EXTRACT_H

#include "baseTransform.h"
#include "baseImage.h"

namespace AlgFeatExtract {
    class GetColorHist;
    class GetColorAccumHist;
    class GetColorMoments;
    class GetColorSet;
    class GetColorCoherVec;
    class GetGrayLevCoocurMatrix;
    class GetTamuraTextures;
    class GetFourierShapeDescript;
    class GetInvariantMoments;
    class GetSpacialFeats;
}

class AlgFeatExtract::GetColorHist : public baseTransform
{
public:
    GetColorHist(baseImage& image);

    void apply();

private:
    baseImage& image;
};


#endif




