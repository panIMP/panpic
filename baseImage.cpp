#include "baseImage.h"


baseImage::baseImage()
{
	mat.create(0,0,CV_8UC1);
    channelChanged = false;
	isBinary = false;
	isGray = false;

    feat.state.getColorHist = false;
    feat.state.getAccumColorHist = false;
    feat.state.getColorCoVec =false;
    feat.state.getColorSet = false;
    feat.state.getFourierShapeDescript = false;
    feat.state.getGrayLevCoMatrix = false;
    feat.state.getInvariantMoments = false;
    feat.state.getSpacialFeat = false;
    feat.state.getTamuraTextures = false;
}

baseImage::~baseImage(){

}

baseImage::baseImage(const baseImage& image){
	SetMat(image.mat);
    SetChannelChangeState(image.channelChanged);
	SetIsBinary(image.isBinary);
	SetIsGray(image.isGray);
}

baseImage& baseImage::operator=(const baseImage& image){
    SetChannelChangeState(image.channelChanged);
	SetMat(image.mat);
	SetIsBinary(image.isBinary);
	SetIsGray(image.isGray);

	return *this;
}


void baseImage::copyTo(baseImage& image) const{
	image.SetMat(mat);

    image.channelChanged  = channelChanged;
	image.isBinary = isBinary;
	image.isGray = isGray;
}


void baseImage::SetMat(const cv::Mat& newMat){
	newMat.copyTo(mat);
}


cv::Mat* baseImage::GetMat(){
	return &mat;
}


void baseImage::SetChannelChangeState(bool state){
    channelChanged = state;
}


bool baseImage::GetChannelChangeState(){
    return channelChanged;
}


void baseImage::SetIsBinary(bool state){
	isBinary = state;
}

bool baseImage::IsBinary(){
	return isBinary;
}

void baseImage::SetIsGray(bool state){
	isGray = state;
}

bool baseImage::IsGray(){
	return isGray;
}

void baseImage::SetImageFeat(const imageFeat &feat)
{
    this->feat = feat;
}

imageFeat* baseImage::GetImageFeat()
{
    return &this->feat;
}

int baseImage::height()
{
	return mat.rows;
}

int baseImage::width()
{
	return mat.cols;
}


bool baseImage::ReadPanImage(const QString& str, baseImage* image)
{
    image->SetChannelChangeState(false);

	cv::Mat mat1, mat2;

    // Since here you want to read the image as it is,
    // you should set the flag to be -1, so,
    // if there exits alpha channel, it will also be read.
	mat1 = cv::imread(str.toStdString(), CV_LOAD_IMAGE_UNCHANGED);
    if(mat1.empty())
    {
        return false;
    }

	if (mat1.depth() == CV_USRTYPE1)
	{
		mat2 = cv::imread(str.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
        if (mat2.empty()){
            return false;
        }

        image->SetIsGray(true);
        image->SetMat(mat2);
	}
	else
	{
        image->SetMat(mat1);

		if (mat1.channels() == 1)
		{
            image->SetIsGray(true);
        }else{
            image->SetIsGray(false);
        }
	}

    return true;
}


void baseImage::SavePanImage(baseImage& ImageToSave, const QString &str){
    switch (ImageToSave.GetMat()->channels()) {
    case 1:
        break;

    case 3:
        // transform the image back to opencv style channel order, since
        // it has been converted to RGB format when loaded for QImage display
        if (ImageToSave.GetChannelChangeState())
        {
            cv::cvtColor(*ImageToSave.GetMat(), *ImageToSave.GetMat(), CV_RGB2BGR);
        }
        break;

    case 4:
        if (ImageToSave.GetChannelChangeState())
        {
            cv::cvtColor(*ImageToSave.GetMat(), *ImageToSave.GetMat(), CV_RGBA2BGRA);
        }
        break;
    }

	cv::imwrite(str.toStdString(), *ImageToSave.GetMat());
}



QImage baseImage::PanImage2QImage(){
	QImage qimage;

	switch (mat.channels()){
		case 1:     qimage = QImage((const unsigned char*)(mat.data),
								mat.cols,
								mat.rows,
								static_cast<int>(mat.step),
								QImage::Format_Indexed8);
					break;

        case 3:     if (channelChanged == false){
						cv::cvtColor(mat, mat, CV_BGR2RGB);
                        channelChanged = true;
					}
					qimage = QImage((const unsigned char*)(mat.data),
										   mat.cols,
										   mat.rows,
										   static_cast<int>(mat.step),
										   QImage::Format_RGB888);
					break;

        case 4:     if (channelChanged == false){
                        cv::cvtColor(mat, mat, CV_BGRA2RGBA);
                        channelChanged = true;
					}
					qimage = QImage((const unsigned char*)(mat.data),
										   mat.cols,
										   mat.rows,
										   static_cast<int>(mat.step),
										   QImage::Format_ARGB32);
					break;
	}

	return qimage;
}
