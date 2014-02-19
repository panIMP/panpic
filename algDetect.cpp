#include "algDetect.h"

int*** AlgDetect::houghParam::H = 0;

void AlgDetect::houghParam::InitGlobalVaribles(baseImage& image)
{
	isInited = false;

	CIRCLE_WIDTH = 3;
	SEARCH_STEP = 4;
	BIG_CIRCLE_MIN = 95;
	BIG_CIRCLE_MAX = 97;
	SMALL_CIRCLE_MIN = 2;
	SMALL_CIRCLE_MAX = 8;

	NON_WITHIN_CIRCLE = 0;
	WITHIN_CIRCLE = 1;

	int width = image.width();
	int height = image.height();

	int i,j;

	_r2DivNum = (BIG_CIRCLE_MAX * BIG_CIRCLE_MAX + 50) / 100;
	H = new int**[width];
	for (i = 0; i < width; i++)
	{
		H[i] = new int*[height];
		for (j = 0; j < height; j ++)
		{
		   H[i][j] = new int[_r2DivNum];
		}
	}

	isInited = true;
}

AlgDetect::Hough::Hough(baseImage &image,
						int rMin,
						int rMax,
						int step,
						int iMin,
						int iMax,
						int jMin,
						int jMax,
						int div,
						panCircle& circle,
						houghParam& hParam) : image(image),circle(circle),hParam(hParam)
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

void AlgDetect::Hough::apply()
{
	cv::Mat* mat = image.GetMat();
	int width = mat->cols;
	int height = mat->rows;

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

	//double time_start = clock();
	//	initialize the Hnew
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
			   hParam.H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		data = mat->ptr<uchar>(j);
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
							hParam.H[a][b][r2Div] ++;
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
				tmpMaxValNeighbourSum =	  hParam.H[a][b][r2Div]
										+ hParam.H[a-1][b][r2Div]
										+ hParam.H[a][b-1][r2Div]
										+ hParam.H[a-1][b-1][r2Div]
										+ hParam.H[a+1][b][r2Div]
										+ hParam.H[a][b+1][r2Div]
										+ hParam.H[a+1][b+1][r2Div]
										+ hParam.H[a-1][b+1][r2Div]
										+ hParam.H[a+1][b-1][r2Div];
				if (tmpMaxValNeighbourSum > maxValNeighbourSum)
				{
					maxValNeighbourSum = tmpMaxValNeighbourSum;
					maxVal = hParam.H[a][b][r2Div];
					circle.a= a;
					circle.b = b;
					circle.r2Div = r2Div;
				}
			}
		}
	}

	//double time_end = clock();
	//double interval = time_end - time_start;

	if (maxVal >= 8)
	{
		circle.r2 = circle.r2Div * div - div2;
		circle.r = (int)sqrtf((float)circle.r2);
		circle.hasValue = true;	
	}
}


AlgDetect::Hough2::Hough2(  baseImage &image,
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
							houghParam& hParam) :
							image(image), bigCircle(bigCircle), smallCircle(smallCircle), hParam(hParam)
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

void AlgDetect::Hough2::apply()
{
	cv::Mat* mat = image.GetMat();
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
	int r2MaxInsidebigCircle = (bigCircle.r - hParam.CIRCLE_WIDTH) * (bigCircle.r - hParam.CIRCLE_WIDTH);
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


	//memset(hParam.H, 0, mat.cols*mat.rows*hParam._r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				hParam.H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		jDistBorder = j - bigCircle.b;
		data = mat->ptr<uchar>(j);
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
							hParam.H[a][b][r2Div] ++;
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
				tmpVal = hParam.H[a][b][r2Div];
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


AlgDetect::LabelString::LabelString(baseImage& image,
								   panCircle& bigCircle,
								   panCircle& smallCircle,
								   houghParam& hParam) :
									image(image), bigCircle(bigCircle), smallCircle(smallCircle), hParam(hParam)
{
}

void AlgDetect::LabelString::apply()
{
	cv::Mat* mat = image.GetMat();
	int height = mat->rows;
	int width = mat->cols;

	int r2MinThresh = (bigCircle.r - 3* hParam.CIRCLE_WIDTH) * (bigCircle.r - 3*hParam.CIRCLE_WIDTH);
	int r2MaxThresh = (bigCircle.r - hParam.CIRCLE_WIDTH) * (bigCircle.r - hParam.CIRCLE_WIDTH);

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
			data = mat->ptr<uchar>(j);

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
			uchar* data = mat->ptr<uchar>(j);
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
						mat->at<uchar>(j, i) = 255;
					}
					else
					{
						mat->at<uchar>(j, i) = 0;
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
		mat->at<uchar>(bigCircle.b, bigCircle.a) = 255;
	}
}


AlgDetect::CicleIncisionDetection::CicleIncisionDetection(baseImage &image,
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
														 houghParam& hParam)
														 : image(image),
														 bigCircle(bigCircle),
														 smallCircle(smallCircle),
														 hParam(hParam)
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

void AlgDetect::CicleIncisionDetection::apply()
{
	//double time_start = clock();

	cv::Mat* mat = image.GetMat();
	int height = mat->rows;
	int width = mat->cols;
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
	strInfo stringInfo;
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
	tmpMat1.create(mat->rows, mat->cols, CV_8UC1);

	for(i = 1; i < width - 1; i++)
	{
		for (j = 1; j < height - 1; j++)
		{
			tmpMat1.at<uchar>(j, i) = cv::saturate_cast<uchar>(
						fabs((float)(mat->at<uchar>(j+1, i-1) + mat->at<uchar>(j+1, i+1) + 2*mat->at<uchar>(j+1, i)
									-mat->at<uchar>(j-1, i-1) - mat->at<uchar>(j-1, i+1) - 2*mat->at<uchar>(j-1, i)))
						+fabs((float)(mat->at<uchar>(j-1, i+1) + mat->at<uchar>(j+1, i+1) + 2*mat->at<uchar>(j, i+1)
									-mat->at<uchar>(j-1, i-1) - mat->at<uchar>(j+1, i-1) - 2*mat->at<uchar>(j, i-1)))
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
	tmpMat1.copyTo(*mat);


	//memset(hParam.H, 0, mat.cols*mat.rows*hParam._r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				hParam.H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		data = mat->ptr<uchar>(j);
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
							hParam.H[a][b][r2Div] ++;
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
				tmpMaxValNeighbourSum =	  hParam.H[a][b][r2Div]
										+ hParam.H[a-1][b][r2Div]
										+ hParam.H[a][b-1][r2Div]
										+ hParam.H[a-1][b-1][r2Div]
										+ hParam.H[a+1][b][r2Div]
										+ hParam.H[a][b+1][r2Div]
										+ hParam.H[a+1][b+1][r2Div]
										+ hParam.H[a-1][b+1][r2Div]
										+ hParam.H[a+1][b-1][r2Div];
				if (tmpMaxValNeighbourSum > maxValNeighbourSum)
				{
					maxValNeighbourSum = tmpMaxValNeighbourSum;
					maxVal = hParam.H[a][b][r2Div];
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

	rMin = hParam.SMALL_CIRCLE_MIN;
	rMax = hParam.SMALL_CIRCLE_MAX;
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

	r2MaxInsidebigCircle = (bigCircle.r - hParam.CIRCLE_WIDTH) * (bigCircle.r - hParam.CIRCLE_WIDTH);

	aMin = iMin + rMin;
	aMax = iMax - rMin;
	bMin = jMin + rMin;
	bMax = jMax - rMin;

	div2 = div / 2;

	maxVal = 0;


	//memset(hParam.H, 0, mat.cols*mat.rows*hParam._r2DivNum*sizeof(int));
	for (i = 0; i < width; i++)
	{
		for (j = 0; j < height; j++)
		{
			for (r2Div = r2MinDiv; r2Div < r2MaxDiv; r2Div++)
			{
				hParam.H[i][j][r2Div] = 0;
			}
		}
	}

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		jDistBorder = j - bigCircle.b;
		data = mat->ptr<uchar>(j);
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
							hParam.H[a][b][r2Div] ++;
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
				tmpVal = hParam.H[a][b][r2Div];
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

	r2MinThresh = (bigCircle.r - 3* hParam.CIRCLE_WIDTH) * (bigCircle.r - 3*hParam.CIRCLE_WIDTH);
	r2MaxThresh = (bigCircle.r - hParam.CIRCLE_WIDTH) * (bigCircle.r - hParam.CIRCLE_WIDTH);

	iMax = bigCircle.a + bigCircle.r;
	iMin = bigCircle.a - bigCircle.r;
	jMax = bigCircle.b + bigCircle.r;
	jMin = bigCircle.b - bigCircle.r;
	distance = 0;


	iMaxSmall = smallCircle.a + smallCircle.r;
	iMinSmall = smallCircle.a - smallCircle.r;
	jMaxSmall = smallCircle.b + smallCircle.r;
	jMinSmall = smallCircle.b - smallCircle.r;
	distanceSmall = 0;

	stringInfo.stringCenterX = 0;
	stringInfo.stringCenterY = 0;
	stringPointNum = 0;
	// unlabel the big circle and label the string
	if (bigCircle.hasValue)
	{
		for (j = 0; j < height; j++)
		{
			data = mat->ptr<uchar>(j);

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
							//*data = 255;
							*data = 30;

							stringInfo.stringCenterX += i;
							stringInfo.stringCenterY += j;
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
		
		//	exception -- no string point found
		if (stringPointNum == 0)
		{
			exit(3);
		}

		stringInfo.stringCenterX /= stringPointNum;
		stringInfo.stringCenterY /= stringPointNum;
	}

	// label the small circle within the big circle
	if (smallCircle.hasValue)
	{
		for (j = jMinSmall; j < jMaxSmall; j++)
		{
			uchar* data = mat->ptr<uchar>(j);
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
						mat->at<uchar>(j, i) = 255;
					}
					else
					{
						mat->at<uchar>(j, i) = 0;
					}
				}		
			}
		}
	}

	PutResultText(bigCircle, smallCircle, image, stringInfo);

	//double time_end = clock();
	//double interval = time_end - time_start;
}

void AlgDetect::PutResultText(AlgDetect::panCircle& bigCircle, AlgDetect::panCircle& smallCircle, baseImage& image, strInfo& stringInfo)
{
	cv::Mat* mat = image.GetMat();
	int height = mat->rows;


	cv::cvtColor(*mat, *mat, CV_GRAY2RGB);
	image.SetChannelChangeState(true);
	image.SetIsGray(false);

	cv::line(*mat, cv::Point(stringInfo.stringCenterX, stringInfo.stringCenterY), cv::Point(bigCircle.a, bigCircle.b), cv::Scalar(255,0,0));

	bigCircle.b = height - bigCircle.b;
	stringInfo.stringCenterY = height - stringInfo.stringCenterY;
	double angleValue = atan2(((double)stringInfo.stringCenterY - (double)bigCircle.b), ((double)stringInfo.stringCenterX - (double)bigCircle.a)) * 180.0 / 3.1415926;

	//  write the location of center of the circle
	QString msgChipSide = QString("Chip Side : ");
	cv::putText(*mat, msgChipSide.toStdString(),cv::Point(20,20),cv::FONT_HERSHEY_COMPLEX ,0.4, cv::Scalar(0,255,0), 1, CV_AA);
	QString msgChipCenter = QString("Chip Center : ");
	cv::putText(*mat,msgChipCenter.toStdString(),cv::Point(20,40),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(0,255,0), 1, CV_AA);
	QString msgString = QString("String Center : ");
	cv::putText(*mat, msgString.toStdString(),cv::Point(20,60),cv::FONT_HERSHEY_COMPLEX,0.4, cv::Scalar(0,255,0), 1, CV_AA);
	QString msgAngle = QString("Normal Angle : ");
	cv::putText(*mat, msgAngle.toStdString(),cv::Point(20,80),cv::FONT_HERSHEY_COMPLEX,0.4, cv::Scalar(0,255,0), 1, CV_AA);

	if (smallCircle.hasValue){
		mat->at<cv::Vec3b>(smallCircle.b, smallCircle.a)[0] = 0;
		mat->at<cv::Vec3b>(smallCircle.b, smallCircle.a)[1] = 0;
		mat->at<cv::Vec3b>(smallCircle.b, smallCircle.a)[2] = 255;

		QString msgSideInfo = QString("Front");
		cv::putText(*mat,msgSideInfo.toStdString(),cv::Point(140, 20),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255,255,255), 1, CV_AA);
	}else{
		QString msgSideInfo = QString("Back");
		cv::putText(*mat,msgSideInfo.toStdString(),cv::Point(140, 20),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255,255,255), 1, CV_AA);
	}

	/*mat->at<cv::Vec3b>(bigCircle.b, bigCircle.a)[0] = 0;
	mat->at<cv::Vec3b>(bigCircle.b, bigCircle.a)[1] = 0;
	mat->at<cv::Vec3b>(bigCircle.b, bigCircle.a)[2] = 255;*/
	QString msgChipCenterNum = QString("( %1, %2 )").arg(bigCircle.a).arg(bigCircle.b);
	cv::putText(*mat,msgChipCenterNum.toStdString(),cv::Point(140, 40),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255,255,255), 1, CV_AA);
	
	/*mat->at<cv::Vec3b>(stringInfo.stringCenterY, stringInfo.stringCenterX)[0] = 0;
	mat->at<cv::Vec3b>(stringInfo.stringCenterY, stringInfo.stringCenterX)[1] = 0;
	mat->at<cv::Vec3b>(stringInfo.stringCenterY, stringInfo.stringCenterX)[2] = 255;*/
	QString msgStringCenterNum = QString("( %1, %2 )").arg(stringInfo.stringCenterX).arg(stringInfo.stringCenterY);
	cv::putText(*mat,msgStringCenterNum.toStdString(),cv::Point(140, 60),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255,255,255), 1, CV_AA);	

	QString msgAngleNum = QString("%1").arg(angleValue);
	cv::putText(*mat,msgAngleNum.toStdString(),cv::Point(140, 80),cv::FONT_HERSHEY_COMPLEX, 0.4, cv::Scalar(255,255,255), 1, CV_AA);
}











