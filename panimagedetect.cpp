#include "panimagedetect.h"


int*** GlobalParams::H = 0;
int GlobalParams::_r2DivNum = 0;

// init the r-¦È space
const int GlobalParams::sinValue[360] = 
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
const int GlobalParams::cosValue[360] = 
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


HoughTransformTransform::HoughTransformTransform(PanImage &image, 
												int rMin, 
												int rMax, 
												int step, 
												int iMin, 
												int iMax, 
												int jMin, 
												int jMax, 
												int div, 
												_Pan_Circle& circle) : image(image),circle(circle)
{
	this->rMin = rMin;
	this->rMax = rMax;
	this->step = step;
	this->iMin = iMin;
	this->iMax = iMax;
	this->jMin = jMin;
	this->jMax = jMax;
	this->div = div;
}

void HoughTransformTransform::apply()
{
	cv::Mat mat = image.GetMat();
	int width = mat.cols;
	int height = mat.rows;

	circle.a = 0;
	circle.b = 0;
	circle.hasValue = false;
	circle.r = 0;
	circle.r2 = 0;
	circle.r2Div = 0;

	int r2Min = rMin * rMin;
	int r2Max = rMax * rMax;
	int r2MinDiv = r2Min / div;
	int r2MaxDiv = r2Max / div;
	int aMin = (int)iMin + (int)rMin;
	int aMax = (int)iMax - (int)rMin;
	int bMin = (int)jMin + (int)rMin;
	int bMax = (int)jMax - (int)rMin;
	int aMinTmp, aMaxTmp, bMinTmp, bMaxTmp;
	int aStart, aEnd, bStart, bEnd;

	int div2 = div / 2;

	int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;

	int maxVal = 0;
	int maxValNeighbourSum = 0;
	int tmpMaxValNeighbourSum = 0;

	uchar* data;

	double time_start = clock();
	//	initialize the Hnew
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				GlobalParams::H[i][j][r2Div] = 0;
			}
		}
	}

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
				aMinTmp = i - rMax;
				aMaxTmp = i + rMax;
				bMinTmp = j - rMax;
				bMaxTmp = j + rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = i - a;
						jDist = j - b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							GlobalParams::H[a][b][r2Div] ++;
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
				tmpMaxValNeighbourSum =	  GlobalParams::H[a][b][r2Div] 
										+ GlobalParams::H[a-1][b][r2Div]
										+ GlobalParams::H[a][b-1][r2Div]
										+ GlobalParams::H[a-1][b-1][r2Div]
										+ GlobalParams::H[a+1][b][r2Div]
										+ GlobalParams::H[a][b+1][r2Div]
										+ GlobalParams::H[a+1][b+1][r2Div]
										+ GlobalParams::H[a-1][b+1][r2Div]
										+ GlobalParams::H[a+1][b-1][r2Div];
				if (tmpMaxValNeighbourSum > maxValNeighbourSum)
				{
					maxValNeighbourSum = tmpMaxValNeighbourSum;
					maxVal = GlobalParams::H[a][b][r2Div];
					circle.a= a;
					circle.b = b;
					circle.r2Div = r2Div;
				}
			}
		}
	}

	double time_end = clock();
	double interval = time_end - time_start;

	if (maxVal >= 8)
	{
		circle.r2 = circle.r2Div * div - div2;
		circle.r = (int)sqrtf((float)circle.r2);
		circle.hasValue = true;	
	}
}


HoughTransformTransform2::HoughTransformTransform2(PanImage &image, 
													int rMin, 
													int rMax, 
													int step, 
													int iMin, 
													int iMax, 
													int jMin, 
													int jMax, 
													int div, 
													_Pan_Circle& bigCircle,
													_Pan_Circle& smallCircle) : image(image), bigCircle(bigCircle), smallCircle(smallCircle)
{
	this->rMin = rMin;
	this->rMax = rMax;
	this->step = step;
	this->iMin = iMin;
	this->iMax = iMax;
	this->jMin = jMin;
	this->jMax = jMax;
	this->div = div;
}

void HoughTransformTransform2::apply()
{
	cv::Mat mat = image.GetMat();
	int width = image.width();
	int height = image.height();

	smallCircle.a = 0;
	smallCircle.b = 0;
	smallCircle.hasValue = false;
	smallCircle.r = 0;
	smallCircle.r2 = 0;
	smallCircle.r2Div = 0;

	int r2Min = rMin * rMin;
	int r2Max = rMax * rMax;
	int r2MaxInsidebigCircle = (bigCircle.r - GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - GlobalParams::CIRCLE_WIDTH);
	int r2MinDiv = r2Min / div;
	int r2MaxDiv = r2Max / div;

	int aMin = iMin + rMin;
	int aMax = iMax - rMin;
	int bMin = jMin + rMin;
	int bMax = jMax - rMin;
	int aMinTmp, aMaxTmp, bMinTmp, bMaxTmp;
	int aStart, aEnd, bStart, bEnd;

	int div2 = div / 2;

	int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;
	int iDistBorder = 0;
	int jDistBorder = 0;

	int tmpVal = 0;
	int maxVal = 0;

	uchar* data;

	//double time_start = clock();


	//memset(GlobalParams::H, 0, mat.cols*mat.rows*GlobalParams::_r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				GlobalParams::H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		jDistBorder = j - bigCircle.b;
		data = mat.ptr<uchar>(j);
		data += iMin;

		for (i = iMin; i < iMax; i+=step)
		{
			iDistBorder = i - bigCircle.a;
			r2 = iDistBorder*iDistBorder + jDistBorder*jDistBorder;
			if (r2 >= r2MaxInsidebigCircle)
			{
				data += step;
				continue;
			}
			// if pixel is black
			if (*data != 0)
			{

				aMinTmp = i - rMax;
				aMaxTmp = i + rMax;
				bMinTmp = j - rMax;
				bMaxTmp = j + rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = i - a;
						jDist = j - b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							GlobalParams::H[a][b][r2Div] ++;
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
				tmpVal = GlobalParams::H[a][b][r2Div];
				if (tmpVal > maxVal)
				{
					maxVal = tmpVal;
					smallCircle.a= a;
					smallCircle.b = b;
					smallCircle.r2Div = r2Div;
				}
			}
		}
	}

	if (maxVal >= 8)
	{
		smallCircle.r2 = smallCircle.r2Div * div - div2;
		smallCircle.r = (int)sqrtf((float)smallCircle.r2);
		smallCircle.hasValue = true;	
	}

	//double time_end = clock();
	//double interval = time_end - time_start;
}


LabelStringTransform::LabelStringTransform(PanImage& image, 
										   _Pan_Circle& bigCircle, 
										   _Pan_Circle& smallCircle) : image(image), bigCircle(bigCircle), smallCircle(smallCircle)
{

}

void LabelStringTransform::apply()
{
	cv::Mat mat = image.GetMat();
	int height = mat.rows;
	int width = mat.cols;

	int r2MinThresh = (bigCircle.r - 3* GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - 3*GlobalParams::CIRCLE_WIDTH);
	int r2MaxThresh = (bigCircle.r - GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - GlobalParams::CIRCLE_WIDTH);

	int i, j;

	int iMax = bigCircle.a + bigCircle.r;
	int iMin = bigCircle.a - bigCircle.r;
	int jMax = bigCircle.b + bigCircle.r;
	int jMin = bigCircle.b - bigCircle.r;
	int distance = 0;
	int iDist, jDist;

	int stringCenterX = 0;
	int stringCenterY = 0;
	int stringPointNum = 1;

	int iMaxSmall = smallCircle.a + smallCircle.r;
	int iMinSmall = smallCircle.a - smallCircle.r;
	int jMaxSmall = smallCircle.b + smallCircle.r;
	int jMinSmall = smallCircle.b - smallCircle.r;
	int distanceSmall = 0;
	int iDistSmall, jDistSmall;

	uchar* data;

	//double time_start = clock();

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
						iDist = i - bigCircle.a;
						jDist = j - bigCircle.b;
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
					iDistSmall = i - smallCircle.a;
					jDistSmall = j - smallCircle.b;
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

	//double time_end = clock();
	//double interval = time_end - time_start;

	// label big circle center point
	if (bigCircle.hasValue)
	{
		mat.at<uchar>(bigCircle.b, bigCircle.a) = 255;
	}
}


CicleIncisionDetectionTransform::CicleIncisionDetectionTransform(PanImage &image, 
																 int rMin, 
																 int rMax, 
																 int step, 
																 int iMin, 
																 int iMax, 
																 int jMin, 
																 int jMax, 
																 int div, 
																 _Pan_Circle& bigCircle, 
																 _Pan_Circle& smallCircle)
																 : image(image),
																 bigCircle(bigCircle),
																 smallCircle(smallCircle)
{
	this->rMax = rMax;
	this->rMin = rMin;
	this->step = step;
	this->iMin = iMin;
	this->iMax = iMax;
	this->jMin = jMin;
	this->jMax = jMax;
	this->div = div;
}

void CicleIncisionDetectionTransform::apply()
{
	//double time_start = clock();

	cv::Mat mat = image.GetMat();
	int height = mat.rows;
	int width = mat.cols;
	uchar* data;

	int r2Min = rMin * rMin;
	int r2Max = rMax * rMax;
	int r2MinDiv = r2Min / div;
	int r2MaxDiv = r2Max / div;
	int aMin = iMin + rMin;
	int aMax = iMax - rMin;
	int bMin = jMin + rMin;
	int bMax = jMax - rMin;
	int aMinTmp, aMaxTmp, bMinTmp, bMaxTmp;
	int r2MaxInsidebigCircle;
	int aStart, aEnd, bStart, bEnd;
	int r2MinThresh, r2MaxThresh;

	int div2 = div / 2;

	int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;
	int iDistBorder = 0;
	int jDistBorder = 0;
	int distance = 0;
	int stringCenterX = 0;
	int stringCenterY = 0;
	int stringPointNum = 1;
	int iMaxSmall;
	int iMinSmall;
	int jMaxSmall;
	int jMinSmall;
	int distanceSmall = 0;
	int iDistSmall, jDistSmall;

	int tmpVal = 0;
	int maxVal = 0;
	int maxValNeighbourSum = 0;
	int tmpMaxValNeighbourSum = 0;

	bigCircle.hasValue = false;
	bigCircle.a = 0;
	bigCircle.b = 0;
	bigCircle.r = 0;
	bigCircle.r2 = 0;
	bigCircle.r2Div = 0;
	smallCircle.hasValue = false;
	smallCircle.a = 0;
	smallCircle.b = 0;
	smallCircle.r = 0;
	smallCircle.r2 = 0;
	smallCircle.r2Div = 0;

	cv::Mat tmpMat1, tmpMat2;
	tmpMat1.create(mat.rows, mat.cols, CV_8UC1);

	for(i = 1; i < width - 1; i++)
	{
		for (j = 1; j < height - 1; j++)
		{
			tmpMat1.at<uchar>(j, i) = cv::saturate_cast<uchar>(
						fabs((float)(mat.at<uchar>(j+1, i-1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j+1, i)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j-1, i+1) - 2*mat.at<uchar>(j-1, i)))
						+fabs((float)(mat.at<uchar>(j-1, i+1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j, i+1)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j+1, i-1) - 2*mat.at<uchar>(j, i-1)))
						);
		}
	}

	for(i = width - 100; i < width; ++i)
	{
		for(j = 0; j < height; ++j)
		{
			tmpMat1.at<uchar>(j, i) = 0;
		}
	}

	tmpMat1.copyTo(tmpMat2);

	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i <width - 1; i++)
		{
			if (( tmpMat2.at<uchar>(j, i)
				 +tmpMat2.at<uchar>(j-1, i) 
				 +tmpMat2.at<uchar>(j, i-1) 
				 +tmpMat2.at<uchar>(j-1, i-1) 
				 +tmpMat2.at<uchar>(j+1, i) 
				 +tmpMat2.at<uchar>(j, i+1) 
				 +tmpMat2.at<uchar>(j+1, i+1) 
				 +tmpMat2.at<uchar>(j-1, i+1) 
				 +tmpMat2.at<uchar>(j+1, i-1)) < 5*255) 
			{
				tmpMat1.at<uchar>(j, i) = 0;
			}
			else
			{
				tmpMat1.at<uchar>(j, i) = 255;
			}
		}
	}

	image.SetIsBinary(true);
	tmpMat1.copyTo(mat);


	//memset(GlobalParams::H, 0, mat.cols*mat.rows*GlobalParams::_r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				GlobalParams::H[i][j][r2Div] = 0;
			}
		}
	}

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
				aMinTmp = i - rMax;
				aMaxTmp = i + rMax;
				bMinTmp = j - rMax;
				bMaxTmp = j + rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = i - a;
						jDist = j - b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							GlobalParams::H[a][b][r2Div] ++;
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
				tmpMaxValNeighbourSum =	  GlobalParams::H[a][b][r2Div] 
										+ GlobalParams::H[a-1][b][r2Div]
										+ GlobalParams::H[a][b-1][r2Div]
										+ GlobalParams::H[a-1][b-1][r2Div]
										+ GlobalParams::H[a+1][b][r2Div]
										+ GlobalParams::H[a][b+1][r2Div]
										+ GlobalParams::H[a+1][b+1][r2Div]
										+ GlobalParams::H[a-1][b+1][r2Div]
										+ GlobalParams::H[a+1][b-1][r2Div];
				if (tmpMaxValNeighbourSum > maxValNeighbourSum)
				{
					maxValNeighbourSum = tmpMaxValNeighbourSum;
					maxVal = GlobalParams::H[a][b][r2Div];
					bigCircle.a= a;
					bigCircle.b = b;
					bigCircle.r2Div = r2Div;
				}
			}
		}
	}


	if (maxVal >= 8)
	{
		bigCircle.r2 = bigCircle.r2Div * div - div2;
		bigCircle.r = (int)sqrtf((float)bigCircle.r2);
		bigCircle.hasValue = true;	
	}
	else
	{
		return;
	}

	rMin = GlobalParams::SMALL_CIRCLE_MIN;
	rMax = GlobalParams::SMALL_CIRCLE_MAX;
	step = 1;
	iMin = bigCircle.a - bigCircle.r;
	iMax = bigCircle.a + bigCircle.r;
	jMin = bigCircle.b - bigCircle.r;
	jMax = bigCircle.b + bigCircle.r;
	div = 2;


	r2Min = rMin * rMin;
	r2Max = rMax * rMax;
	r2MinDiv = r2Min / div;
	r2MaxDiv = r2Max / div;

	r2MaxInsidebigCircle = (bigCircle.r - GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - GlobalParams::CIRCLE_WIDTH);

	aMin = iMin + rMin;
	aMax = iMax - rMin;
	bMin = jMin + rMin;
	bMax = jMax - rMin;

	div2 = div / 2;

	maxVal = 0;


	//memset(GlobalParams::H, 0, mat.cols*mat.rows*GlobalParams::_r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				GlobalParams::H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		jDistBorder = j - bigCircle.b;
		data = mat.ptr<uchar>(j);
		data += iMin;

		for (i = iMin; i < iMax; i+=step)
		{
			iDistBorder = i - bigCircle.a;
			r2 = iDistBorder*iDistBorder + jDistBorder*jDistBorder;
			if (r2 >= r2MaxInsidebigCircle)
			{
				data += step;
				continue;
			}
			// if pixel is black
			if (*data != 0)
			{

				aMinTmp = i - rMax;
				aMaxTmp = i + rMax;
				bMinTmp = j - rMax;
				bMaxTmp = j + rMax;

				aStart = aMinTmp > aMin ? aMinTmp : aMin;
				aEnd = aMaxTmp < aMax ? aMaxTmp : aMax;
				bStart = bMinTmp > bMin ? bMinTmp : bMin;
				bEnd = bMaxTmp < bMax ? bMaxTmp : bMax;

				// calculate only those within the frame
				for (a = aStart; a < aEnd; a++)
				{
					for (b = bStart; b < bEnd; b++)
					{
						iDist = i - a;
						jDist = j - b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							GlobalParams::H[a][b][r2Div] ++;
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
				tmpVal = GlobalParams::H[a][b][r2Div];
				if (tmpVal > maxVal)
				{
					maxVal = tmpVal;
					smallCircle.a= a;
					smallCircle.b = b;
					smallCircle.r2Div = r2Div;
				}
			}
		}
	}

	if (maxVal >= 8)
	{
		smallCircle.r2 = smallCircle.r2Div * div - div2;
		smallCircle.r = (int)sqrtf((float)smallCircle.r2);
		smallCircle.hasValue = true;	
	}

	r2MinThresh = (bigCircle.r - 3* GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - 3*GlobalParams::CIRCLE_WIDTH);
	r2MaxThresh = (bigCircle.r - GlobalParams::CIRCLE_WIDTH) * (bigCircle.r - GlobalParams::CIRCLE_WIDTH);

	iMax = bigCircle.a + bigCircle.r;
	iMin = bigCircle.a - bigCircle.r;
	jMax = bigCircle.b + bigCircle.r;
	jMin = bigCircle.b - bigCircle.r;
	distance = 0;

	stringCenterX = 0;
	stringCenterY = 0;
	stringPointNum = 1;

	iMaxSmall = smallCircle.a + smallCircle.r;
	iMinSmall = smallCircle.a - smallCircle.r;
	jMaxSmall = smallCircle.b + smallCircle.r;
	jMinSmall = smallCircle.b - smallCircle.r;
	distanceSmall = 0;
	iDistSmall, jDistSmall;

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
						iDist = i - bigCircle.a;
						jDist = j - bigCircle.b;
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
					iDistSmall = i - smallCircle.a;
					jDistSmall = j - smallCircle.b;
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

		mat.at<uchar>(smallCircle.b, smallCircle.a) = 255;
		mat.at<uchar>(bigCircle.b, bigCircle.a) = 255;
	}

	//double time_end = clock();
	//double interval = time_end - time_start;
}


/*
/*	PamImageDetect class, singleton pattern	
*/
PanImageDetect* PanImageDetect::instance = 0;


PanImageDetect::PanImageDetect(PanImage& image) : image(image)
{
	int width = image.width();
	int height = image.height();

	int i,j;

	GlobalParams::_r2DivNum = (GlobalParams::BIG_CIRCLE_MAX * GlobalParams::BIG_CIRCLE_MAX + 50) / 100;
	GlobalParams::H = new int**[width];
	for (i = 0; i < width; i++)
	{
		GlobalParams::H[i] = new int*[height];
		for (j = 0; j < height; j ++)
		{
			GlobalParams::H[i][j] = new int[GlobalParams::_r2DivNum];
		}
	}
}

PanImageDetect::~PanImageDetect(void)
{
}

PanImageDetect* PanImageDetect::GetInstance(PanImage& image)
{
	if (instance == 0)
	{
		instance = new PanImageDetect(image);
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

HoughTransformTransform* PanImageDetect::HoughTransform(PanImage &image,
														int rMin, 
														int rMax,
														int step,
														int iMin,
														int iMax,
														int jMin,
														int jMax,
														int div,
														_Pan_Circle& circle)
{
	return new HoughTransformTransform(	image,
										rMin, 
										rMax,
										step,
										iMin,
										iMax,
										jMin,
										jMax,
										div,
										circle);

}

HoughTransformTransform2* PanImageDetect::HoughTransform(PanImage &image,
														int rMin, 
														int rMax,
														int step,
														int iMin,
														int iMax,
														int jMin,
														int jMax,
														int div,
														_Pan_Circle& bigCircle,
														_Pan_Circle& smallCircle)
{
	return new HoughTransformTransform2(image,
										rMin, 
										rMax,
										step,
										iMin,
										iMax,
										jMin,
										jMax,
										div,
										bigCircle,
										smallCircle);
}

LabelStringTransform* PanImageDetect::LabelString(PanImage& image, _Pan_Circle& bigCircle, _Pan_Circle& smallCircle)
{
	return new LabelStringTransform(image, bigCircle, smallCircle);
}

CicleIncisionDetectionTransform* PanImageDetect::CicleIncisionDetection(PanImage &image,
											int rMin, 
											int rMax,
											int step,
											int iMin,
											int iMax,
											int jMin,
											int jMax,
											int div,
											_Pan_Circle& bigCircle,
											_Pan_Circle& smallCircle)
{
	return new CicleIncisionDetectionTransform(	image,
												rMin, 
												rMax,
												step,
												iMin,
												iMax,
												jMin,
												jMax,
												div,
												bigCircle,
												smallCircle);
}

