#ifndef PANIMAGEFILTER_H
#define PANIMAGEFILTER_H

#include "panimage.h"
#include "panimagehist.h"
#include "transform.h"


class GrayTransform : public Transform
{
public: 
	GrayTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class MedianBlurTransform : public Transform
{
public:
	MedianBlurTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class GuassinBlurTransform : public Transform
{
public:
	GuassinBlurTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class ComFogTransform : public Transform
{
public:
	ComFogTransform(PanImage& image, int randRange);

	void apply();

private:
	PanImage& image;
	int randRange;
};

class SketchTransform : public Transform
{
public:
	SketchTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class SobelSharpenTransform : public Transform
{
public:
	SobelSharpenTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class LaplaceSharpenTransform : public Transform
{
public:
	LaplaceSharpenTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class MedianFilterTransform : public Transform
{
public:
	MedianFilterTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class ErodeTransform : public Transform
{
public:
	ErodeTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class DilateTransform : public Transform
{
public:
	DilateTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class OtsuBinaryTransform : public Transform
{
public:
	OtsuBinaryTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class EngraveTransform : public Transform
{
public:
	EngraveTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class NegativeTransform : public Transform
{
public:
	NegativeTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class HoleFillTransform : public Transform
{
public:
	HoleFillTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};

class PanImageFilter
{
	PanImageFilter();
	~PanImageFilter();
	PanImageFilter(const PanImageFilter&);
	PanImageFilter& operator = (const PanImageFilter&);

public:
	static PanImageFilter* GetInstance();
	static void Destroy();

	int CalcCombosX2Y2R2(int r2);
	int TempltExcuteCl(cv::Mat& mat, int* templt, int tw, int x, int y);

	GrayTransform* Gray(PanImage& image);
	MedianBlurTransform* MedianBlur(PanImage& image);
	GuassinBlurTransform* GuassinBlur(PanImage& image);
	ComFogTransform* ComFog(PanImage& image, unsigned int randRange);
	SketchTransform* Sketch(PanImage& image);
	SobelSharpenTransform* SobelSharpen(PanImage& image);
	LaplaceSharpenTransform* LaplaceSharpen(PanImage& image);
	MedianFilterTransform* MedianFilter(PanImage& image);
	ErodeTransform* Erode(PanImage& image);
	DilateTransform* Dilate(PanImage& image);
	OtsuBinaryTransform* OtsuBinary(PanImage& image);
	EngraveTransform* Engrave(PanImage& image);
	NegativeTransform* Negative(PanImage& image);
	HoleFillTransform* HoleFill(PanImage& image);

private:
	static PanImageFilter* instance;
};




#endif // PANIMAGEFILTER_H
