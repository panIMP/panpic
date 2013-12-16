#include "algShift.h"

AlgShift::RotateTransform::RotateTransform(int orientation, baseImage& image) : image(image)
{
	this->orientation = orientation;
}

void AlgShift::RotateTransform::apply()
{
	cv::transpose(*image.GetMat(), *image.GetMat());
	cv::flip(*image.GetMat(), *image.GetMat(), orientation);
}


AlgShift::FlipTransform::FlipTransform(int orientation, baseImage& image) : image(image)
{
	this->orientation = orientation;
}

void AlgShift::FlipTransform::apply()
{
	cv::flip(*image.GetMat(), *image.GetMat(), orientation);
}
