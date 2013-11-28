#include "panimagefilter.h"
#include <qstring.h>
#include <qmessagebox.h>
#include <qicon.h>
#include <time.h>

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

void PanImageFilter::Gray(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int channels = mat.channels();
	
	if (channels < 3)
	{
		return;
	}

	if (image.GetChannelChangeState())
	{
		cv::cvtColor(mat, mat, CV_RGB2GRAY);
	}
	else
	{
		cv::cvtColor(mat, mat, CV_BGR2GRAY);
	}

	image.SetIsGray(true);
	image.SetMat(mat);
}

void PanImageFilter::SobelSharpen(PanImage &image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	cv::Mat result;
	result.create(mat.rows, mat.cols, CV_8UC1);

	double time_start = clock();

	for(unsigned int i = 1; i < width - 1; i++)
	{
		for (unsigned int j = 1; j < height - 1; j++)
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

	double time_end = clock();
	double interval = time_end - time_start;

	for(unsigned int i = width - 100; i < width; ++i)
	{
		for(unsigned int j = 0; j < height; ++j)
		{
			mat.at<uchar>(j, i) = 0;
		}
	}
}

void PanImageFilter::MedianBlur(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::medianBlur(mat, mat, 5);
}

void PanImageFilter::GuassinBlur(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	cv::GaussianBlur(mat, mat, cv::Size(5,5), 0.0);
}

void PanImageFilter::MedianFilter(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	cv::Mat tmpMat;

	double time_start = clock();

	mat.copyTo(tmpMat);

	for (unsigned int j = 1; j < height - 1; j++)
	{
		for (unsigned int i = 1; i <width - 1; i++)
		{
			if (( tmpMat.at<uchar>(j, i)
				 +tmpMat.at<uchar>(j-1, i) 
				 +tmpMat.at<uchar>(j, i-1) 
				 +tmpMat.at<uchar>(j-1, i-1) 
				 +tmpMat.at<uchar>(j+1, i) 
				 +tmpMat.at<uchar>(j, i+1) 
				 +tmpMat.at<uchar>(j+1, i+1) 
				 +tmpMat.at<uchar>(j-1, i+1) 
				 +tmpMat.at<uchar>(j+1, i-1)) < 5*255) 
			{
				mat.at<uchar>(j, i) = 0;
			}
			else
			{
				mat.at<uchar>(j, i) = 255;
			}
		}
	}

	double time_end = clock();
	double interval = time_end - time_start;

	// extra
	image.SetIsBinary(true);
}

void PanImageFilter::Engrave(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;
	unsigned int channels = mat.channels();

	std::vector<cv::Mat> v(channels);
	cv::split(mat, v);

	for (unsigned int k = 0; k < channels; k++)
	{
		for (unsigned int j = 0; j < height - 1; j ++)
		{
			for (unsigned int i = 0; i < width - 1; i++)
			{
				v[k].at<uchar>(j,i) = cv::saturate_cast<uchar>(
									fabsf(v[k].at<uchar>(j,i) - v[k].at<uchar>(j+1,i+1)));
			}
		}
	}

	cv::merge(v, mat);
}

void PanImageFilter::OtsuBinary(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;

	cv::MatND hist;
	int histSize[] = {256};
	float hRanges[] = {0.0, 255.0};
	const float* ranges[] = {hRanges};
	const int channels[] = {0};
	cv::calcHist(&mat, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	uchar* data;

	double equ=0.0;				    // ʹ�ô��ԭʼ��ʽequ=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u)
	double max=0.0;				    // equ�����ֵ���ô���Ӧ�ĺ�����ֵ��Ӧ��������ֵ
	double u0=0.0;					// ǰ��ƽ���Ҷ�
	double u1=0.0;					// ����ƽ���Ҷ�
	double u=0.0;

	int w0=0;					    // ǰ��ռͼ������������
	int w1=0;					    // ����ռͼ������������
	int sum = 0;			        // ֱ��ͼ������
	int moment = 0;		            // ֱ��ͼ��������
	int start,end;
	int threshold;				    // ��ֵ
	int temp = 0;

	start = 0;
	while (hist.at<float>(start) == 0)   start++;

	end = 255;
	while (hist.at<float>(end) == 0)   end--;

	for(int i = start; i <= end; i++)
	{
		sum += hist.at<float>(i);	         // ����ֱ��ͼ������
		moment += i * hist.at<float>(i);     // ����ֱ��ͼ��������
	}

	// ���
	for(int i = start; i <= end; i++)
	{
		// n1�൱��w0��n2�൱��w1
		// w0 += histogram[i]/sum;  ��ʵ����ֵ��ʵ����δ����һ��������Ӱ�����ս��
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

	for (unsigned int j = 0; j < height - 1; j++)
	{
		data = mat.ptr<uchar>(j);

		for(unsigned int i = 0; i < width - 1; i++)
		{
			if(*data >= threshold)
			{
				*data = 255;
			}
			else
			{
				*data = 0;
			}

			data ++;
		}
	}

	for(unsigned int i = width - 100; i < width; ++i)
	{
		for(unsigned int j = 0; j < height; ++j)
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

void PanImageFilter::Negative(PanImage& image)
{
	cv::Mat mat = image.GetMat();
	unsigned int height = mat.rows;
	unsigned int width = mat.cols;	
	unsigned int channels = mat.channels();
	
	std::vector<cv::Mat> v(channels);
	cv::split(mat, v);
	uchar* data;

	for (unsigned int k = 0; k < channels; k++)
	{
		for (unsigned int j = 0; j < height; j ++)
		{
			data = v[k].ptr<uchar>(j);

			for (unsigned int i = 0; i < width; i++)
			{
				*data = 255 - *data;
				data ++;
			}
		}
	}

	cv::merge(v, mat);
}

