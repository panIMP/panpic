#include "panimagedetect.h"

PanImageDetect* PanImageDetect::instance = 0;

unsigned int PanImageDetect::H[WIDTH][HEIGHT][R2DIVNUM] = {{{0}}};

// init the r-¦È space
int PanImageDetect::sinValue[360] = 
{
	0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,  
	259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,  
	500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,  
	707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,  
	866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,  
	966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

	1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
	966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
	866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
	707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
	500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
	259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

	0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,  
	259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,  
	500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,  
	707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,  
	866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,  
	966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

	1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
	966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
	866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
	707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
	500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
	259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,
};

// init the r-¦È space
int PanImageDetect::cosValue[360] = 
{
	1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
	966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
	866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
	707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
	500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
	259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

	0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,  
	259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,  
	500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,  
	707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,  
	866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,  
	966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,

	1000, 1000, 999, 999, 998, 996, 995, 993, 990, 988, 985, 982, 978, 974,  970,
	966,  961,  956, 951, 946, 940, 934, 927, 921, 914, 906, 899, 891, 883,  875,
	866,  857,  848, 839, 829, 819, 809, 799, 788, 777, 766, 755, 743, 731,  719,
	707,  695,  682, 669, 656, 643, 629, 616, 602, 588, 574, 559, 545, 530,  515,
	500,  485,  469, 454, 438, 423, 407, 391, 375, 358, 342, 326, 309, 292,  276,
	259,  242,  225, 208, 191, 174, 156, 139, 122, 104, 87,  70,  52,  34,   17,

	0,    17,	34,   52,  70,  87,  104, 122, 139, 156, 174, 191, 208, 225, 242,  
	259,  276,  292,  309, 326, 342, 358, 375, 391, 407, 423, 438, 454, 469, 485,  
	500,  515,  530,  545, 559, 574, 588, 602, 616, 629, 643, 656, 669, 682, 695,  
	707,  719,  731,  743, 755, 766, 777, 788, 799, 809, 819, 829, 839, 848, 857,  
	866,  875,  883,  891, 899, 906, 914, 921, 927, 934, 940, 946, 951, 956, 961,  
	966,  970,  974,  978, 982, 985, 988, 990, 993, 995, 996, 998, 999, 999, 1000,
};


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

void PanImageDetect::LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	unsigned int r2MinThresh = (bigCircle.r - 3* CIRCLE_WIDTH) * (bigCircle.r - 3*CIRCLE_WIDTH);
	unsigned int r2MaxThresh = (bigCircle.r - CIRCLE_WIDTH) * (bigCircle.r - CIRCLE_WIDTH);

	unsigned int i, j;

	unsigned int iMax = bigCircle.a + bigCircle.r;
	unsigned int iMin = bigCircle.a - bigCircle.r;
	unsigned int jMax = bigCircle.b + bigCircle.r;
	unsigned int jMin = bigCircle.b - bigCircle.r;
	unsigned int distance = 0;
	int iDist, jDist;

	unsigned int stringCenterX = 0;
	unsigned int stringCenterY = 0;
	unsigned int stringPointNum = 1;

	unsigned int iMaxSmall = smallCircle.a + smallCircle.r;
	unsigned int iMinSmall = smallCircle.a - smallCircle.r;
	unsigned int jMaxSmall = smallCircle.b + smallCircle.r;
	unsigned int jMinSmall = smallCircle.b - smallCircle.r;
	unsigned int distanceSmall = 0;
	int iDistSmall, jDistSmall;

	uchar* data;

	double time_start = clock();

	// unlabel the big circle and label the string
	if (bigCircle.hasValue)
	{
		for (j = 0; j < height; j++)
		{
			data = mat.ptr<uchar>(j);

			for (i = 0; i < width; i++)
			{
				if (i >= iMin && i <= iMax && j >= jMin && j <= jMax)
				{

					if (*data != 0)
					{
						iDist = (int)i - (int)bigCircle.a;
						jDist = (int)j - (int)bigCircle.b;
						distance = iDist * iDist + jDist * jDist;

						if (distance > r2MinThresh && distance < r2MaxThresh)
						{
							*data = 255;
							stringCenterX += i;
							stringCenterY += j;
							stringPointNum ++;
						}
						else
						{
							*data = 30;
						}
					}
				}
				else
				{
					*data = 0;
				}

				data ++;
			}
		}
		stringCenterX /= stringPointNum;
		stringCenterY /= stringPointNum;
	}

	// label the small circle within the big circle
	if (smallCircle.hasValue)
	{
		for (j = jMinSmall; j < jMaxSmall; j++)
		{
			uchar* data = mat.ptr<uchar>(j);
			data += iMinSmall;
			for (i = iMinSmall; i < iMaxSmall; i++)
			{
				if (*data++ != 0)
				{
					iDistSmall = (int)i - (int)smallCircle.a;
					jDistSmall = (int)j - (int)smallCircle.b;
					distanceSmall = iDistSmall * iDistSmall + jDistSmall * jDistSmall;

					if (distanceSmall <= smallCircle.r2)
					{
						mat.at<uchar>(j, i) = 255;
					}
					else
					{
						mat.at<uchar>(j, i) = 0;
					}
				}		
			}
		}
	}

	double time_end = clock();
	double interval = time_end - time_start;

	// label big circle center point
	if (bigCircle.hasValue)
	{
		mat.at<uchar>(bigCircle.b, bigCircle.a) = 255;
	}
}

void PanImageDetect::CicleIncisionDetection(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	_Pan_Circle bigCircle;
	bigCircle.hasValue = false;
	_Pan_Circle smallCircle;
	smallCircle.hasValue = false;

	double time_start = clock();

	PanImageFilter::GetInstance()->SobelSharpen(image);
	PanImageFilter::GetInstance()->MedianFilter(image);
	bigCircle = PanImageDetect::GetInstance()->HoughTransform(image, BIG_CIRCLE_MIN, BIG_CIRCLE_MAX, SEARCH_STEP, 0, width, 0, height, 100);
	if (bigCircle.hasValue)
	{
		smallCircle = PanImageDetect::GetInstance()->HoughTransform(image, 
									SMALL_CIRCLE_MIN, 
									SMALL_CIRCLE_MAX, 
									1, 
									bigCircle.a - bigCircle.r, 
									bigCircle.a + bigCircle.r,
									bigCircle.b - bigCircle.r, 
									bigCircle.b + bigCircle.r,
									2,
									bigCircle);
	}

	LabelString(image, bigCircle, smallCircle);

	if (! smallCircle.hasValue)
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "Reverse the chip");
		warning.exec();	
	}

	double time_end = clock();
	double interval = time_end - time_start;
	printf("the time cost is %f", interval);
}
