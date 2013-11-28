#include "panimagedetect.h"

PanImageDetect* PanImageDetect::instance = 0;
unsigned int PanImageDetect::H[WIDTH][HEIGHT][R2DIVNUM] = {{{0}}};

PanImageDetect::PanImageDetect(void)
{
}


PanImageDetect::~PanImageDetect(void)
{
}

PanImageDetect* PanImageDetect::GetInstance()
{
	if (instance == 0)
	{
		instance = new PanImageDetect();
	}

	return instance;
}

void PanImageDetect::Destroy()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

_Pan_Circle PanImageDetect::HoughTransform(PanImage &image,
									unsigned int rMin, 
									unsigned int rMax,
									unsigned int step,
									unsigned int iMin,
									unsigned int iMax,
									unsigned int jMin,
									unsigned int jMax,
									unsigned int div)
{
	cv::Mat mat = image.GetMat();
	
	_Pan_Circle circle;
	circle.a = 0;
	circle.b = 0;
	circle.hasValue = false;
	circle.r = 0;
	circle.r2 = 0;
	circle.r2Div = 0;

	unsigned int r2Min = rMin * rMin;
	unsigned int r2Max = rMax * rMax;
	unsigned int r2MinDiv = r2Min / div;
	unsigned int r2MaxDiv = r2Max / div;
	int aMin = (int)iMin + (int)rMin;
	int aMax = (int)iMax - (int)rMin;
	int bMin = (int)jMin + (int)rMin;
	int bMax = (int)jMax - (int)rMin;
	int aMinTmp, aMaxTmp, bMinTmp, bMaxTmp;
	int aStart, aEnd, bStart, bEnd;

	unsigned int div2 = div / 2;

	unsigned int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;

	unsigned int maxVal = 0;
	unsigned int maxValNeighbourSum = 0;
	unsigned int tmpMaxValNeighbourSum = 0;

	uchar* data;

	double time_start = clock();

	memset(H, 0, mat.cols*mat.rows*R2DIVNUM*sizeof(unsigned int));

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		data = mat.ptr<uchar>(j);
		data += iMin;

		for (i = iMin; i < iMax; i+=step)
		{
			// if pixel is black
			if (*data != 0)
			{
				aMinTmp = (int)i - (int)rMax;
				aMaxTmp = (int)i + (int)rMax;
				bMinTmp = (int)j - (int)rMax;
				bMaxTmp = (int)j + (int)rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = (int)i - (int)a;
						jDist = (int)j - (int)b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							H[a][b][r2Div] ++;
						}
					}
				}
			}
			data += step;
		}
	}

	// modification -- second scanning -- by hp 
	for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
	{
		for (a = aMin; a < aMax; a ++)
		{
			for (b = bMin; b < bMax; b++)
			{
				tmpMaxValNeighbourSum =	  H[a][b][r2Div] 
										+ H[a-1][b][r2Div]
										+ H[a][b-1][r2Div]
										+ H[a-1][b-1][r2Div]
										+ H[a+1][b][r2Div]
										+ H[a][b+1][r2Div]
										+ H[a+1][b+1][r2Div]
										+ H[a-1][b+1][r2Div]
										+ H[a+1][b-1][r2Div];
				if (tmpMaxValNeighbourSum > maxValNeighbourSum)
				{
					maxValNeighbourSum = tmpMaxValNeighbourSum;
					maxVal = H[a][b][r2Div];
					circle.a= a;
					circle.b = b;
					circle.r2Div = r2Div;
				}
			}
		}
	}


	if (maxVal >= 8)
	{
		circle.r2 = circle.r2Div * div - div2;
		circle.r = (unsigned int)sqrtf(circle.r2);
		circle.hasValue = true;	
	}

	double time_end = clock();
	double interval = time_end - time_start;

	return circle;
}

_Pan_Circle PanImageDetect::HoughTransform(PanImage &image,
									unsigned int rMin, 
									unsigned int rMax,
									unsigned int step,
									unsigned int iMin,
									unsigned int iMax,
									unsigned int jMin,
									unsigned int jMax,
									unsigned int div,
									_Pan_Circle bigCircle)
{
	cv::Mat mat = image.GetMat();

	_Pan_Circle circle;
	circle.a = 0;
	circle.b = 0;
	circle.hasValue = false;
	circle.r = 0;
	circle.r2 = 0;
	circle.r2Div = 0;

	unsigned int r2Min = rMin * rMin;
	unsigned int r2Max = rMax * rMax;
	unsigned int r2MaxInsidebigCircle = (bigCircle.r - CIRCLE_WIDTH) * (bigCircle.r - CIRCLE_WIDTH);
	unsigned int r2MinDiv = r2Min / div;
	unsigned int r2MaxDiv = r2Max / div;

	int aMin = (int)iMin + (int)rMin;
	int aMax = (int)iMax - (int)rMin;
	int bMin = (int)jMin + (int)rMin;
	int bMax = (int)jMax - (int)rMin;
	int aMinTmp, aMaxTmp, bMinTmp, bMaxTmp;
	int aStart, aEnd, bStart, bEnd;

	unsigned int div2 = div / 2;

	unsigned int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;
	int iDistBorder = 0;
	int jDistBorder = 0;

	unsigned int tmpVal = 0;
	unsigned int maxVal = 0;

	uchar* data;

	double time_start = clock();

	memset(H, 0, mat.cols*mat.rows*R2DIVNUM*sizeof(unsigned int));

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		jDistBorder = (int)j - (int)bigCircle.b;
		data = mat.ptr<uchar>(j);
		data += iMin;

		for (i = iMin; i < iMax; i+=step)
		{
			iDistBorder = (int)i - (int)bigCircle.a;
			r2 = iDistBorder*iDistBorder + jDistBorder*jDistBorder;
			if (r2 >= r2MaxInsidebigCircle)
			{
				data += step;
				continue;
			}
			// if pixel is black
			if (*data != 0)
			{

				aMinTmp = (int)i - (int)rMax;
				aMaxTmp = (int)i + (int)rMax;
				bMinTmp = (int)j - (int)rMax;
				bMaxTmp = (int)j + (int)rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = (int)i - (int)a;
						jDist = (int)j - (int)b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							H[a][b][r2Div] ++;
						}
					}
				}
			}
			data += step;
		}
	}

	// get the r, a & b
	for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
	{
		for (a = aMin; a < aMax; a ++)
		{
			for (b = bMin; b < bMax; b++)
			{
				tmpVal = H[a][b][r2Div];
				if (tmpVal > maxVal)
				{
					maxVal = tmpVal;
					circle.a= a;
					circle.b = b;
					circle.r2Div = r2Div;
				}
			}
		}
	}

	if (maxVal >= 8)
	{
		circle.r2 = circle.r2Div * div - div2;
		circle.r = (unsigned int)sqrtf(circle.r2);
		circle.hasValue = true;	
	}

	double time_end = clock();
	double interval = time_end - time_start;

	return circle;
}