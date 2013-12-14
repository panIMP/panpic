#ifndef ALG_DETECT_H
#define ALG_DETECT_H


#include "baseImage.h"
#include "baseThread.h"
#include "baseTransform.h"

#include "algFilter.h"


namespace AlgDetect {
	typedef struct
	{
		int a;
		int b;
		int r;
		long r2;
		long r2Div;
		bool hasValue;
	}_Pan_Circle;

	typedef struct
	{
		bool isInited;
		int CIRCLE_WIDTH;
		int SEARCH_STEP;
		int BIG_CIRCLE_MIN;
		int BIG_CIRCLE_MAX;
		int SMALL_CIRCLE_MIN;
		int SMALL_CIRCLE_MAX;
		int NON_WITHIN_CIRCLE;
		int WITHIN_CIRCLE;
		int _r2DivNum;

		static int*** H;

		void InitGlobalVaribles(baseImage&);
	}_Hough_Param;

	class Hough;
	class Hough2;
	class CicleIncisionDetection;
	class LabelString;
}


class AlgDetect::Hough : public baseTransform
{
public:
	Hough(  baseImage &image,
			int rMin,
			int rMax,
			int step,
			int iMin,
			int iMax,
			int jMin,
			int jMax,
			int div,
			_Pan_Circle& circle,
			_Hough_Param& hParam);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& circle;
	_Hough_Param& hParam;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class AlgDetect::Hough2 : public baseTransform
{
public:
	Hough2( baseImage &image,
			int rMin,
			int rMax,
			int step,
			int iMin,
			int iMax,
			int jMin,
			int jMax,
			int div,
			_Pan_Circle& bigCircle,
			_Pan_Circle& smallCircle,
			_Hough_Param& hParam);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	_Hough_Param& hParam;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class AlgDetect::LabelString : public baseTransform
{
public:
	LabelString(baseImage& image, _Pan_Circle& bigCircle, _Pan_Circle& smallCircle, _Hough_Param& hParam);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	_Hough_Param& hParam;
};


class AlgDetect::CicleIncisionDetection : public baseTransform
{
public:
	CicleIncisionDetection( baseImage &image,
							int rMin,
							int rMax,
							int step,
							int iMin,
							int iMax,
							int jMin,
							int jMax,
							int div,
							_Pan_Circle& bigCircle,
							_Pan_Circle& smallCircle,
							_Hough_Param& hParam);

	void apply();

private:
	baseImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	_Hough_Param& hParam;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


#endif
