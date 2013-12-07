#ifndef PANIMAGEDETECT_H
#define PANIMAGEDETECT_H


#include "panimage.h"
#include "panimagefilter.h"
#include "transform.h"
#include "transformthread.h"

// detect 
typedef struct
{
	int a;
	int b;
	int r;
	long r2;
	long r2Div;
	bool hasValue;
}_Pan_Circle;

class GlobalParams
{
private:
	GlobalParams();
	GlobalParams(const GlobalParams&);
	GlobalParams& operator = (const GlobalParams&);

	friend class HoughTransformTransform;
	friend class HoughTransformTransform2;
	friend class CicleIncisionDetectionTransform;
	friend class LabelStringTransform;
	friend class UiHoughTransformParam;
	friend class UiMainWindow;

	/*
	/*	Global params for detect algorithms
	*/
	static const int CIRCLE_WIDTH = 3;
	static const int SEARCH_STEP = 4;
	static const int BIG_CIRCLE_MIN = 95;
	static const int BIG_CIRCLE_MAX = 97;
	static const int SMALL_CIRCLE_MIN = 2;
	static const int SMALL_CIRCLE_MAX = 8;

	static const int WIDTH = 752;
	static const int HEIGHT = 480;
	static const int R2DIVNUM = 200;
	static const int WITHIN_CIRCLE = 1;
	static const int NON_WITHIN_CIRCLE = 0;

	static const int sinValue[360];
	static const int cosValue[360];

	static int H[WIDTH][HEIGHT][R2DIVNUM];
};


class HoughTransformTransform : public Transform
{
public:
	HoughTransformTransform(PanImage &image,
							int rMin, 
							int rMax,
							int step,
							int iMin,
							int iMax,
							int jMin,
							int jMax,
							int div,
							_Pan_Circle& circle);

	void apply();

private:
	PanImage& image;

	_Pan_Circle& circle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class HoughTransformTransform2 : public Transform
{
public:
	HoughTransformTransform2(PanImage &image,
							int rMin, 
							int rMax,
							int step,
							int iMin,
							int iMax,
							int jMin,
							int jMax,
							int div,
							_Pan_Circle& bigCircle,
							_Pan_Circle& smallCircle); 

	void apply();

private:
	PanImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class LabelStringTransform : public Transform
{
public:
	LabelStringTransform(PanImage& image, _Pan_Circle& bigCircle, _Pan_Circle& smallCircle);

	void apply();

private:
	PanImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
};


class CicleIncisionDetectionTransform : public Transform
{
public:
	CicleIncisionDetectionTransform(PanImage &image,
									int rMin, 
									int rMax,
									int step,
									int iMin,
									int iMax,
									int jMin,
									int jMax,
									int div,
									_Pan_Circle& bigCircle,
									_Pan_Circle& smallCircle); 

	void apply();

private:
	PanImage& image;

	_Pan_Circle& bigCircle;
	_Pan_Circle& smallCircle;
	int rMin; 
	int rMax;
	int step;
	int iMin;
	int iMax;
	int jMin;
	int jMax;
	int div;
};


class PanImageDetect
{
	PanImageDetect(void);
	~PanImageDetect(void);

	PanImageDetect(const PanImageDetect&);
	PanImageDetect& operator = (const PanImageDetect&);

public:
	static PanImageDetect* GetInstance();
	static void Destroy();

	HoughTransformTransform* HoughTransform(PanImage &image,
											int rMin, 
											int rMax,
											int step,
											int iMin,
											int iMax,
											int jMin,
											int jMax,
											int div,
											_Pan_Circle& circle);

	HoughTransformTransform2* HoughTransform(PanImage &image,
											int rMin, 
											int rMax,
											int step,
											int iMin,
											int iMax,
											int jMin,
											int jMax,
											int div,
											_Pan_Circle& bigCircle,
											_Pan_Circle& smallCircle); 

	LabelStringTransform* LabelString(	PanImage& image, 
										_Pan_Circle& bigCircle, 
										_Pan_Circle& smallCircle);
	
	CicleIncisionDetectionTransform* CicleIncisionDetection(PanImage &image,
															int rMin, 
															int rMax,
															int step,
															int iMin,
															int iMax,
															int jMin,
															int jMax,
															int div,
															_Pan_Circle& bigCircle,
															_Pan_Circle& smallCircle); 

private:
	static PanImageDetect* instance;
};





#endif