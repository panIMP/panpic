#ifndef PANIMAGE_HIST_H
#define PANIMAGE_HIST_H

#include "panimage.h"
#include "transform.h"


class GetHistImageTransform : public Transform
{
public:
	GetHistImageTransform(PanImage& image, PanImage& histImage);

	void apply();

private:
	PanImage& image;
	PanImage& histImage;
};


class HistEqualizeTransform : public Transform
{
public:
	HistEqualizeTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};


class HistMatchTransform : public Transform
{
public:
	HistMatchTransform(PanImage& image, float* histMatch);

	void apply();

private:
	PanImage& image;
	float* histMatch;
};


class EnhanceTransform : public Transform
{
public:
	EnhanceTransform(PanImage& image);

	void apply();

private:
	PanImage& image;
};


class PanImageHist
{
	PanImageHist();
	~PanImageHist();
	PanImageHist(const PanImageHist&);
	PanImageHist& operator = (const PanImageHist&);

public:
	static PanImageHist* GetInstance();
	static void Destroy();

	GetHistImageTransform* GetHistImage(PanImage& image, PanImage& histImage);
	HistEqualizeTransform* HistEqalization(PanImage& image);
	HistMatchTransform* HistMatch(PanImage& image,  float* histMatch);
	EnhanceTransform* Enhance(PanImage& image);

private:
	static PanImageHist* instance;
};

#endif // PANIMAGEHISTPROC_H
