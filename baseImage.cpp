#include "baseImage.h"


baseImage::baseImage()
{
	mat.create(0,0,CV_8UC1);
	channelChangeState = false;
	isBinary = false;
	isGray = false;
}

baseImage::~baseImage(){

}

baseImage::baseImage(const baseImage& image){
	SetMat(image.mat);
	SetChannelChangeState(image.channelChangeState);
	SetIsBinary(image.isBinary);
	SetIsGray(image.isGray);
}

baseImage& baseImage::operator=(const baseImage& image){
	SetChannelChangeState(image.channelChangeState);
	SetMat(image.mat);
	SetIsBinary(image.isBinary);
	SetIsGray(image.isGray);

	return *this;
}


void baseImage::copyTo(baseImage& image) const{
	image.SetMat(mat);

	image.channelChangeState  = channelChangeState;
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
	channelChangeState = state;
}


bool baseImage::GetChannelChangeState(){
	return channelChangeState;
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

int baseImage::height()
{
	return mat.rows;
}

int baseImage::width()
{
	return mat.cols;
}


baseImage baseImage::ReadPanImage(const QString& str)
{
	baseImage result;
	result.SetChannelChangeState(false);
	// Since here you want to read the image as it is,
	// you should set the flag to be -1, so,
	// if there exits alpha channel, it will also be read.

	cv::Mat mat1, mat2;

	mat1 = cv::imread(str.toStdString(), CV_LOAD_IMAGE_UNCHANGED);

	if (mat1.depth() == CV_USRTYPE1)
	{
		mat2 = cv::imread(str.toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
		result.SetIsGray(true);
		result.SetMat(mat2);
	}
	else
	{
		result.SetMat(mat1);

		if (mat1.channels() == 1)
		{
			result.SetIsGray(true);
		}
	}

	return result;
}


void baseImage::SavePanImage(baseImage& ImageToSave, const QString &str){
	if (ImageToSave.GetMat()->channels() == 3){
		// transform the image back to opencv style channel order, since
		// it has been converted to RGB format when loaded for QImage display
		if (ImageToSave.GetChannelChangeState())
		{
			cv::cvtColor(*ImageToSave.GetMat(), *ImageToSave.GetMat(), CV_RGB2BGR);
		}
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

		case 3:     if (channelChangeState == false){
						cv::cvtColor(mat, mat, CV_BGR2RGB);
						channelChangeState = true;
					}
					qimage = QImage((const unsigned char*)(mat.data),
										   mat.cols,
										   mat.rows,
										   static_cast<int>(mat.step),
										   QImage::Format_RGB888);
					break;

		case 4:     if (channelChangeState == false){
						cv::cvtColor(mat, mat, CV_BGR2RGB);
						channelChangeState = true;
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
