#include "algShift.h"

/*
/*	Function definitions for transform class RotateTransform;
*/
AlgShift::RotateTransform::RotateTransform(int orientation, baseImage& image) : image(image)
{
	this->orientation = orientation;
}

void AlgShift::RotateTransform::apply()
{
	cv::transpose(image.GetMat(), image.GetMat());
	cv::flip(image.GetMat(), image.GetMat(), orientation);
}


/*
/*	Function definitions for transform class FlipTransForm;
*/
AlgShift::FlipTransform::FlipTransform(int orientation, baseImage& image) : image(image)
{
	this->orientation = orientation;
}

void AlgShift::FlipTransform::apply()
{
	cv::flip(image.GetMat(), image.GetMat(), orientation);
}
