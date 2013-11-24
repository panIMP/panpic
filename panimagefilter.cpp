#include "panimagefilter.h"
#include <qstring.h>
#include <qmessagebox.h>
#include <qicon.h>

PanImageFilter* PanImageFilter::instance = 0;

PanImageFilter::PanImageFilter()
{
}


PanImageFilter::~PanImageFilter()
{

}

PanImageFilter* PanImageFilter::GetInstance()
{
	if (instance == 0)
	{
		instance = new PanImageFilter();
	}

	return instance;
}


void PanImageFilter::Destroy()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void PanImageFilter::SobelSharpen(PanImage &image)
{
	cv::Mat mat = image.GetMat();
	cv::Mat result;
	result.create(mat.rows, mat.cols, CV_8UC1);

	for(int i = 1; i < WIDTH - 1; i++)
	{
		for (int j = 1; j < HEIGHT - 1; j++)
		{
			result.at<uchar>(j, i) = cv::saturate_cast<uchar>(
						fabs((float)(mat.at<uchar>(j+1, i-1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j+1, i)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j-1, i+1) - 2*mat.at<uchar>(j-1, i)))
					    +fabs((float)(mat.at<uchar>(j-1, i+1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j, i+1)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j+1, i-1) - 2*mat.at<uchar>(j, i-1)))
						);
		}
	}

	result.copyTo(mat);

	for(int i = mat.cols - 100; i < mat.cols; ++i)
	{
		for(int j = 0; j < mat.rows; ++j)
		{
			mat.at<uchar>(j, i) = 0;
		}
	}
}

void PanImageFilter::MedianFilter(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::Mat tmpMat;
	mat.copyTo(tmpMat);

	for (int j = 1; j < HEIGHT - 1; j++)
	{
		for (int i = 1; i <WIDTH - 1; i++)
		{
			if (( tmpMat.at<uchar>(j, i)
				 +tmpMat.at<uchar>(j-1, i) 
			     +tmpMat.at<uchar>(j, i-1) 
			     +tmpMat.at<uchar>(j-1, i-1) 
			     +tmpMat.at<uchar>(j+1, i) 
			     +tmpMat.at<uchar>(j, i+1) 
			     +tmpMat.at<uchar>(j+1, i+1) 
			     +tmpMat.at<uchar>(j-1, i+1) 
			     +tmpMat.at<uchar>(j+1, i-1)) < 4*255 + 128) 
			{
				mat.at<uchar>(j, i) = 0;
			}
			else
			{
				mat.at<uchar>(j, i) = 255;
			}
		}
	}

	// extra
	image.SetIsBinary(true);
}

void PanImageFilter::OtsuBinary(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::MatND hist;
	int histSize[] = {256};
	float hRanges[] = {0.0, 255.0};
	const float* ranges[] = {hRanges};
	const int channels[] = {0};
	cv::calcHist(&mat, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	double equ=0.0;				    // 使用大津法原始公式equ=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u)
	double max=0.0;				    // equ的最大值，该处相应的横坐标值对应着最后的阈值
	double u0=0.0;					// 前景平均灰度
	double u1=0.0;					// 背景平均灰度
	double u=0.0;

	int w0=0;					    // 前景占图像比例即其概率
	int w1=0;					    // 背景占图像比例即其概率
	int sum = 0;			        // 直方图的质量
	int moment = 0;		            // 直方图的质量矩
	int start,end;
	int threshold;				    // 阈值
	int temp = 0;

	start = 0;
	while (hist.at<float>(start) == 0)   start++;

	end = 255;
	while (hist.at<float>(end) == 0)   end--;

	for(int i = start; i <= end; i++)
	{
		sum += hist.at<float>(i);	         // 计算直方图的质量
		moment += i * hist.at<float>(i);     // 计算直方图的质量矩
	}

	// 大津法
	for(int i = start; i <= end; i++)
	{
		// n1相当与w0，n2相当与w1
		// w0 += histogram[i]/sum;  真实概率值，实现上未作归一化，但不影响最终结果
		w0 += hist.at<float>(i);             // *sum
		w1 = sum - w0;						 // *sum
		temp += i * hist.at<float>(i);       // *sum

		u0 = temp/(double)w0;                // *1
		u1 = (moment - temp)/(double)w1;     // *1
		u = moment;

		equ = w0 * (u0-u) * (u0-u) + w1 * (u1-u) * (u1-u);          // *sum^2

		if(equ > max)
		{
			threshold = i;
			max = equ;
		}
	}

	for(int i = 0; i < WIDTH - 1; i++)
	{
		for (int j = 0; j < HEIGHT - 1; j++)
		{
			if(mat.at<uchar>(j, i) >= threshold)
			{
				mat.at<uchar>(j, i) = 255;
			}
			else
			{
				mat.at<uchar>(j, i) = 0;
			}
		}
	}

	for(int i = mat.cols - 100; i < mat.cols; ++i)
	{
		for(int j = 0; j < mat.rows; ++j)
		{
			mat.at<uchar>(j, i) = 0;
		}
	}

	// extra
	image.SetIsBinary(true);
}

unsigned int PanImageFilter::CalcCombosX2Y2R2(unsigned int r2)
{
	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int comboNum = 0;
	for (x = 0; x <= r2; x ++)
	{
		for (y = 0; y <= r2; y++)
		{
			if (x*x + y*y == r2*r2)
			{
				comboNum ++;
			}
		}
	}

	return comboNum;
}

_Pan_Circle PanImageFilter::HoughTransform(PanImage &image,
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

	unsigned int div2 = div > 1;

	unsigned int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;

	memset(H, 0, WIDTH*HEIGHT*R2DIVNUM*sizeof(unsigned int));
	memset(r2ValArray, 0, R2DIVNUM*sizeof(unsigned int));

	// do by algorithm by every step pixels
	for (j = jMin; j < jMax; j+=step)
	{
		uchar* data = mat.ptr<uchar>(j);
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

				// calculate only those within the frame
				for (a = (aMinTmp > aMin ? aMinTmp : aMin); a < (aMaxTmp < aMax ? aMaxTmp : aMax); a++)  
				{
					for (b = (bMinTmp > bMin ? bMinTmp : bMin); b < (bMaxTmp < bMax ? bMaxTmp : bMax); b++)
					{
						iDist = (int)i - (int)a;
						jDist = (int)j - (int)b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							H[a][b][r2Div] ++;
							r2ValArray[r2Div] = r2;
						}
					}
				}
			}
			data += step;
		}
	}

	unsigned int maxVal = 0;
	unsigned int tmpVal = 0;

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
		circle.r2 = r2ValArray[circle.r2Div];
		circle.r = (unsigned int)sqrtf(circle.r2);
		circle.hasValue = true;	
	}

	return circle;
}

_Pan_Circle PanImageFilter::HoughTransform(PanImage &image,
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

	unsigned int div2 = div / 2;

	memset(H, 0, WIDTH*HEIGHT*R2DIVNUM*sizeof(unsigned int));
	memset(r2ValArray, 0, R2DIVNUM*sizeof(unsigned int));

	unsigned int i,j,r2,r2Div;
	int a,b;
	int iDist = 0;
	int jDist = 0;
	int iDistBorder = 0;
	int jDistBorder = 0;

	uchar* data;

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

				// calculate only those within the frame
				for (a = (aMinTmp > aMin ? aMinTmp : aMin); a < (aMaxTmp < aMax ? aMaxTmp : aMax); a++)  
				{
					for (b = (bMinTmp > bMin ? bMinTmp : bMin); b < (bMaxTmp < bMax ? bMaxTmp : bMax); b++)
					{
						iDist = (int)i - (int)a;
						jDist = (int)j - (int)b;
						r2 = iDist*iDist + jDist*jDist;

						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max)
						{   
							r2Div = (r2 + div2) / div;
							H[a][b][r2Div] ++;
							r2ValArray[r2Div] = r2;
						}
					}
				}
			}
			data += step;
		}
	}

	unsigned int maxVal = 0;
	unsigned int tmpVal = 0;

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
		circle.r2 = r2ValArray[circle.r2Div];
		circle.r = (unsigned int)sqrtf(circle.r2);
		circle.hasValue = true;	
	}

	return circle;
}

void PanImageFilter::LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle)
{
	cv::Mat mat = image.GetMat();

	unsigned int r2MinThresh = (bigCircle.r - 2*CIRCLE_WIDTH) * (bigCircle.r - 2*CIRCLE_WIDTH);
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

	// unlabel the big circle and label the string
	if (bigCircle.hasValue)
	{
		for (j = 0; j < HEIGHT; j++)
		{
			data = mat.ptr<uchar>(j);

			for (i = 0; i < WIDTH; i++)
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

	// label big circle center point
	if (bigCircle.hasValue)
	{
		mat.at<uchar>(bigCircle.b, bigCircle.a) = 255;
	}
}

void PanImageFilter::Erode(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::erode(mat, mat, cv::Mat());
}

void PanImageFilter::Dilate(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::dilate(mat, mat, cv::Mat());
}

void PanImageFilter::HoleFill(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int width	= mat.cols;
	unsigned int height = mat.rows;
	unsigned int xStart = 0;
	unsigned int xEnd	= 0;
	unsigned int x		= 0;

	unsigned int i, j;

	for (j = 0; j < height; j++)
	{
		uchar* data = mat.ptr<uchar>(j);

		x = 0;
		while(*(data + x) == 0)
		{
			x++;
			if (x == width - 1)
			{
				break;
			}
		}
		if (x == width - 1)
		{
			continue;
		}
		else 
		{
			if (*(data + x + 1) != 0)
			{
				xStart = x;
			}
		}

		x = width - 1;
		while (*(data + x) == 0)
		{
			x--;
			if (x == 0)
			{
				break;
			}
		}
		if (x == 0)
		{
			continue;
		}
		else
		{
			if (*(data + x - 1) != 0)
			{
				xEnd = x;
			}
		}

		for (i = xStart; i < xEnd; i++)
		{
			*(data + i) = 255;
		}
	}
}

void PanImageFilter::TotalProcessing(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	PanImage tmpImage;
	image.copyTo(tmpImage);

	_Pan_Circle bigCircle;
	_Pan_Circle smallCircle;

	SobelSharpen(image);
	MedianFilter(image);
	bigCircle = HoughTransform(image, BIG_CIRCLE_MIN, BIG_CIRCLE_MAX, SEARCH_STEP, 0, WIDTH, 0, HEIGHT, 100);
	if (bigCircle.hasValue)
	{
		smallCircle = HoughTransform(image, 
								    SMALL_CIRCLE_MIN, 
									SMALL_CIRCLE_MAX, 
									1, 
									bigCircle.a - bigCircle.r, 
									bigCircle.a + bigCircle.r,
									bigCircle.b - bigCircle.r, 
									bigCircle.b + bigCircle.r,
					                1,
									bigCircle);
	}

	LabelString(image, bigCircle, smallCircle);

	if (! smallCircle.hasValue)
	{
		QMessageBox warning(QMessageBox::Warning, "Alert!", "Reverse the chip");
		warning.exec();	
	}
}
