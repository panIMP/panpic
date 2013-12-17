#ifndef ALG_DETECT_H
#define ALG_DETECT_H


#include "baseImage.h"
#include "baseThread.h"
#include "baseTransform.h"

#include "algFilter.h"


namespace AlgDetect {
	typedef struct panCircle
	{
		int a;
		int b;
		int r;
		long r2;
		long r2Div;
		bool hasValue;
	}panCircle;

	typedef struct _Hough_Param
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
	}houghParam;

    typedef struct _String_
    {
        int stringCenterX;
        int stringCenterY;
    }strInfo;

    void PutResultText(AlgDetect::panCircle& bigCircle,
                       AlgDetect::panCircle& smallCircle,
                       baseImage& image,
                       strInfo& stringInfo);

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
            panCircle& circle,
            houghParam& hParam);

	void apply();

private:
	baseImage& image;

	panCircle& circle;
	houghParam& hParam;
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
            panCircle& bigCircle,
            panCircle& smallCircle,
            houghParam& hParam);

	void apply();

private:
	baseImage& image;

	panCircle& bigCircle;
	panCircle& smallCircle;
	houghParam& hParam;
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
    LabelString(baseImage& image,
                panCircle& bigCircle,
                panCircle& smallCircle,
                _Hough_Param& hParam);

	void apply();

private:
	baseImage& image;

	panCircle& bigCircle;
	panCircle& smallCircle;
	houghParam& hParam;
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
							panCircle& bigCircle,
							panCircle& smallCircle,
							houghParam& hParam);

	void apply();

private:
	baseImage& image;

	panCircle& bigCircle;
	panCircle& smallCircle;
	houghParam& hParam;
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
