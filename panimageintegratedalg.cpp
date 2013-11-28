#include "panimageintegratedalg.h"

PanImageIntegratedAlg* PanImageIntegratedAlg::instance = 0;

PanImageIntegratedAlg::PanImageIntegratedAlg(void)
{
}


PanImageIntegratedAlg::~PanImageIntegratedAlg(void)
{
}

PanImageIntegratedAlg* PanImageIntegratedAlg::GetInstance()
{
	if (instance == 0)
	{
		instance = new PanImageIntegratedAlg();
	}

	return instance;
}

void PanImageIntegratedAlg::Destroy()
{
	if (instance != 0)
	{
		delete instance;
		instance = 0;
	}
}

void PanImageIntegratedAlg::LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	unsigned int r2MinThresh = (bigCircle.r - 3*CIRCLE_WIDTH) * (bigCircle.r - 3*CIRCLE_WIDTH);
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

void PanImageIntegratedAlg::CicleIncisionDetection(PanImage& image)
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
