#include "panimage.h"


PanImage::PanImage()
{
	channelChangeState = false;
	isBinary = false;
	isGray = false;
}

PanImage::~PanImage(){

}


void PanImage::copyTo(PanImage& image){
	image.SetMat(mat);

	image.channelChangeState  = channelChangeState;
	image.isBinary = isBinary;
	image.isGray = isGray;
}


void PanImage::SetMat(cv::Mat& newMat){
	newMat.copyTo(mat);
}


cv::Mat& PanImage::GetMat(){
	return mat;
}


void PanImage::SetChannelChangeState(bool state){
	channelChangeState = state;
}


bool PanImage::GetChannelChangeState(){
	return channelChangeState;
}


void PanImage::SetIsBinary(bool state){
	isBinary = state;
}

bool PanImage::IsBinary(){
	return isBinary;
}

void PanImage::SetIsGray(bool state){
	isGray = state;
}

bool PanImage::IsGray(){
	return isGray;
}

int PanImage::height()
{
	return mat.rows;
}

int PanImage::width()
{
	return mat.cols;
}

QImage PanImage::PanImage2QImage(){
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
