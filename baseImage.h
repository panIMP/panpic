#ifndef BASE_IMAGE_H
#define BASE_IMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <QImage>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <time.h>

enum _FEAT_TYPE{
    _COLOR_HIST,
    _ACCUM_COLOR_HIST,
    _COLOR_SET,
    _COLOR_CO_VEC,

    _GRAY_LEV_CO_MATRIX,
    _TAMURA_TEXTURES,

    _FOURIER_SHAPE_DESCRIPT,
    _INVARIANT_MOMENTS,

    _SPACIAL_FEATS,


    _FEAT_TYPE_END,
};

typedef struct _FEAT_GET_STATE
{
    bool getColorHist;
    bool getAccumColorHist;
    bool getColorSet;
    bool getColorCoVec;

    bool getGrayLevCoMatrix;
    bool getTamuraTextures;

    bool getFourierShapeDescript;
    bool getInvariantMoments;

    bool getSpacialFeat;

}featGetState;


typedef struct _FEAT
{
    cv::Mat histMat;

    featGetState state;

}imageFeat;

class baseImage
{
private:
    baseImage& operator= (const baseImage&);
    baseImage(const baseImage&);

    cv::Mat mat;
    bool channelChanged;
	bool isBinary;
	bool isGray;
    imageFeat feat;


public:    
    baseImage();
    ~baseImage();


	int height();
	int width();

	void copyTo(baseImage& image) const;

	void SetMat(const cv::Mat& newMat);
	cv::Mat* GetMat();

	void SetChannelChangeState(bool state);
	bool GetChannelChangeState();

	void SetIsBinary(bool state);
	bool IsBinary();

	void SetIsGray(bool state);
	bool IsGray();

    void SetImageFeat(const imageFeat& feat);
    imageFeat* GetImageFeat();

	//  Image input and output
    bool static ReadPanImage(const QString& str, baseImage* image);
	void static SavePanImage(baseImage& ImageToSave, const QString& str);

	//  PanImage --> QImage
	QImage PanImage2QImage();
};

#endif
