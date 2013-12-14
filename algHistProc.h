#ifndef ALG_HIST_PROC_H
#define ALG_HIST_PROC_H

#include "baseImage.h"
#include "baseTransform.h"

namespace AlgHistProc {
    class GetHistImage;
    class HistEqualize;
    class HistMatch;
    class Enhance;
}


class AlgHistProc::GetHistImage : public baseTransform
{
public:
    GetHistImage(baseImage& image, baseImage& histImage);

	void apply();

private:
	baseImage& image;
	baseImage& histImage;
};


class AlgHistProc::HistEqualize : public baseTransform
{
public:
    HistEqualize(baseImage& image);

	void apply();

private:
	baseImage& image;
};


class AlgHistProc::HistMatch : public baseTransform
{
public:
    HistMatch(baseImage& image, float* histMatch);

	void apply();

private:
	baseImage& image;
	float* histMatch;
};


class AlgHistProc::Enhance : public baseTransform
{
public:
    Enhance(baseImage& image);

	void apply();

private:
	baseImage& image;
};

#endif // PANIMAGEHISTPROC_H
