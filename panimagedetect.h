#ifndef PANIMAGEDETECT_H
#define PANIMAGEDETECT_H


#include "panimage.h"
#include "panimagefilter.h"


typedef struct
{
	unsigned int a;
	unsigned int b;
	unsigned int r;
	unsigned long r2;
	unsigned long r2Div;
	bool hasValue;
}_Pan_Circle;


class PanImageDetect
{
	static PanImageDetect* instance;

public:
	PanImageDetect(void);
	~PanImageDetect(void);

	static PanImageDetect* GetInstance();
	static void Destroy();

	_Pan_Circle HoughTransform(PanImage &image,
										unsigned int rMin, 
										unsigned int rMax,
										unsigned int step,
										unsigned int iMin,
										unsigned int iMax,
										unsigned int jMin,
										unsigned int jMax,
										unsigned int div);
	_Pan_Circle HoughTransform(PanImage &image,
										unsigned int rMin, 
										unsigned int rMax,
										unsigned int step,
										unsigned int iMin,
										unsigned int iMax,
										unsigned int jMin,
										unsigned int jMax,
										unsigned int div,
										_Pan_Circle bigCircle); 

	void LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle);
	void CicleIncisionDetection(PanImage& image);

	friend class UiHoughTransformParam;

private:
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
	static unsigned int H[WIDTH][HEIGHT][R2DIVNUM];

	static int sinValue[360];
	static int cosValue[360];
};

#endif