#include "panimageshift.h"


/*
/*	Important! Never foget -- five steps for a single instance pattern
*/
//	Step1:
PanImageShift* PanImageShift::instance = 0;

//	Step2:
PanImageShift::PanImageShift()
{

}

//	Step3:
PanImageShift::~PanImageShift(){

}

//	Step4:
PanImageShift* PanImageShift::GetInstance(){
	if (instance == 0){
		instance = new PanImageShift();
	}
	return instance;
}

//	Step5:
void PanImageShift::Destroy(){
	if (instance != 0){
		delete instance;
		instance = 0;
	}
}

//	Interface to create corresponding transform
FlipTransform* PanImageShift::MirrorV(PanImage& image)
{
	return new FlipTransform(0, image);
}

FlipTransform* PanImageShift::MirrorH(PanImage& image)
{
	return new FlipTransform(1, image);
}

RotateTransform* PanImageShift::RotateClockWise(PanImage& image)
{
	return new RotateTransform(0, image);
}

RotateTransform* PanImageShift::RotateCntrClockWise(PanImage& image)
{
	return new RotateTransform(1, image);
}


/*
/*	Function definitions for transform class RotateTransform;
*/
RotateTransform::RotateTransform(int orientation, PanImage& image) : image(image)
{
	this->orientation = orientation;
}

void RotateTransform::apply()
{
	cv::transpose(image.GetMat(), image.GetMat());
	cv::flip(image.GetMat(), image.GetMat(), orientation);
}


/*
/*	Function definitions for transform class FlipTransForm;
*/
FlipTransform::FlipTransform(int orientation, PanImage& image) : image(image)
{
	this->orientation = orientation;
}

void FlipTransform::apply()
{
	cv::flip(image.GetMat(), image.GetMat(), orientation);
}
