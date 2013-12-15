#ifndef ALG_FILTER_H
#define ALG_FILTER_H

#include "baseImage.h"
#include "algHistProc.h"
#include "baseTransform.h"


namespace AlgFilter {
	class Gray;
	class MedianBlur;
	class MedianBlur2;
	class GuassinBlur;
	class ComFog;
	class Sketch;
	class SobelSharpen;
	class LaplaceSharpen;
	class Erode;
	class Dilate;
	class Otsu;
	class Engrave;
	class Negative;
	class HoleFill;

	int CalcCombosX2Y2R2(int r2);
	int TempltExcuteCl(cv::Mat& mat, int* templt, int tw, int x, int y);
}

class AlgFilter::Gray : public baseTransform
{
public: 
	Gray(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::MedianBlur : public baseTransform
{
public:
	MedianBlur(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::GuassinBlur : public baseTransform
{
public:
	GuassinBlur(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::ComFog : public baseTransform
{
public:
	ComFog(baseImage& image, int randRange);

	void apply();

private:
	baseImage& image;
	int randRange;
};

class AlgFilter::Sketch : public baseTransform
{
public:
	Sketch(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::SobelSharpen : public baseTransform
{
public:
	SobelSharpen(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::LaplaceSharpen : public baseTransform
{
public:
	LaplaceSharpen(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::MedianBlur2 : public baseTransform
{
public:
	MedianBlur2(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::Erode : public baseTransform
{
public:
	Erode(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::Dilate : public baseTransform
{
public:
	Dilate(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::Otsu : public baseTransform
{
public:
	Otsu(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::Engrave : public baseTransform
{
public:
	Engrave(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::Negative : public baseTransform
{
public:
	Negative(baseImage& image);

	void apply();

private:
	baseImage& image;
};

class AlgFilter::HoleFill : public baseTransform
{
public:
	HoleFill(baseImage& image);

	void apply();

private:
	baseImage& image;
};


#endif // PANIMAGEFILTER_H
