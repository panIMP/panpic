#include <qstring.h>
#include <qmessagebox.h>
#include <qicon.h>
#include <time.h>

#include "algFilter.h"


AlgFilter::Gray::Gray(baseImage& image) : image(image)
{

}

void AlgFilter::Gray::apply()
{
	cv::Mat* mat = image.GetMat();
	
    switch (mat->channels()) {
    case 1:
        return;

    case 2:
        return;

    case 3:
        if (image.GetChannelChangeState())
        {
            cv::cvtColor(*mat, *mat, CV_RGB2GRAY);
        }
        else
        {
            cv::cvtColor(*mat, *mat, CV_BGR2GRAY);
        }
        break;

    case 4:
        if (image.GetChannelChangeState())
        {
            cv::cvtColor(*mat, *mat, CV_RGBA2GRAY);
        }
        else
        {
            cv::cvtColor(*mat, *mat, CV_BGRA2GRAY);
        }
        break;
    }

	image.SetIsGray(true);
}

AlgFilter::MedianBlur::MedianBlur(baseImage& image) : image(image)
{

}
	
void AlgFilter::MedianBlur::apply()
{
	cv::Mat* mat = image.GetMat();
	cv::medianBlur(*mat, *mat, 5);
}

AlgFilter::GuassinBlur::GuassinBlur(baseImage& image) : image(image)
{

}

void AlgFilter::GuassinBlur::apply()
{
	cv::Mat* mat = image.GetMat();
	cv::GaussianBlur(*mat, *mat, cv::Size(5,5), 1.5, 1.5);
}

AlgFilter::ComFog::ComFog(baseImage& image, int randRange) : image(image)
{
	this->randRange = randRange;
}

void AlgFilter::ComFog::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int width = mat->cols;
	unsigned int height = mat->rows;
	unsigned int channels = mat->channels();
	cv::Mat tmpMat;
	mat->copyTo(tmpMat);

    int randNum, randDirection, m, n;

	std::vector<cv::Mat> v(channels);
	cv::split(*mat, v);
	std::vector<cv::Mat> tmpV(channels);
	cv::split(*mat, tmpV);

    for (unsigned int k = 0; k < channels; k++)
	{
        for (unsigned int j = 0; j < height; j++)
		{	
            for (unsigned int i = 0; i < width; i++)
			{
				randNum = rand() % randRange;
				randDirection = rand() % 4;
				
				switch (randDirection)
				{
				case 0:		
					m = i + randNum;
					n = j + randNum;
					break;

				case 1:
					m = i - randNum;
					n = j - randNum;
					break;

				case 2:
					m = i + randNum;
					n = j - randNum;
					break;

				case 3:
					m = i - randNum;
					n = j + randNum;
					break;

				default:
					break;
				}

                if ((unsigned int)m >= width)
				{
					m = width - 1;
				}
                if ((unsigned int)n >= height)
				{
					n = height - 1;
				}
				if (m < 0)
				{
					m = 0;
				}
				if (n < 0)
				{
					n = 0;
				}

				v[k].at<uchar>(j, i) = tmpV[k].at<uchar>(n, m);
			}
		}
	}

	cv::merge(v, *mat);
}

AlgFilter::Sketch::Sketch(baseImage& image) : image(image)
{

}

void AlgFilter::Sketch::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;

	cv::Mat tmpMat1, tmpMat2;
	mat->copyTo(tmpMat1);
	mat->copyTo(tmpMat2);

	int templt[9] = {1, 1, 1, 1, -8, 1, 1, 1, 1};
	int templtTest1[9] = {1, 1, -1, 1, 0, -1, -1, 1, -1};
	int templtTest2[9] = {1, 1, 1, -1, 0, -1, -1, -1, 1};
	int templtAve[9] = {1, 1, 1, 1, 4, 1, 1, 1, 1};
	int a,b,b1,b2;

	for (unsigned int j = 1; j < height - 1; j++)
	{
		for (unsigned int i = 1; i < width - 1; i++)
		{
			a = AlgFilter::TempltExcuteCl(tmpMat1, templt, 3, i, j);
			b1 = AlgFilter::TempltExcuteCl(tmpMat1, templtTest1, 3, i, j);
			b2 = AlgFilter::TempltExcuteCl(tmpMat1, templtTest2, 3, i, j);
			b = b1 > b2 ? b1 : b2;
			if (b < 25)
			{
				a = 0;
			}
			else
			{
				a = (int)(a*2);
				if (a > 255)
				{
					a = 255;
				}
				else if (a < 32)
				{
					a = 0;
				}
			}
			a = 255 - a;
			tmpMat2.at<uchar>(j, i) = a;
		}
	}	

	for (unsigned int j = 1; j < height - 1; j++)
	{
		for (unsigned int i = 1; i < width - 1; i++)
		{
			a = AlgFilter::TempltExcuteCl(tmpMat2, templtAve, 3, i, j) / 12;
			mat->at<uchar>(j, i) = a;
		}
	}
}

AlgFilter::SobelSharpen::SobelSharpen(baseImage& image) : image(image)
{
	
}

void AlgFilter::SobelSharpen::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;

	cv::Mat result;
	result.create(mat->rows, mat->cols, CV_8UC1);

	//double time_start = clock();

	for(unsigned int i = 1; i < width - 1; i++)
	{
		for (unsigned int j = 1; j < height - 1; j++)
		{
			result.at<uchar>(j, i) = cv::saturate_cast<uchar>(
						fabs((float)(mat->at<uchar>(j+1, i-1) + mat->at<uchar>(j+1, i+1) + 2*mat->at<uchar>(j+1, i)
									-mat->at<uchar>(j-1, i-1) - mat->at<uchar>(j-1, i+1) - 2*mat->at<uchar>(j-1, i)))
						+fabs((float)(mat->at<uchar>(j-1, i+1) + mat->at<uchar>(j+1, i+1) + 2*mat->at<uchar>(j, i+1)
									-mat->at<uchar>(j-1, i-1) - mat->at<uchar>(j+1, i-1) - 2*mat->at<uchar>(j, i-1)))
						);
		}
	}

	result.copyTo(*mat);

	//double time_end = clock();
	//double interval = time_end - time_start;

    /*for(unsigned int i = width - 100; i < width; ++i)
	{
		for(unsigned int j = 0; j < height; ++j)
		{
			mat->at<uchar>(j, i) = 0;
		}
    }*/

	/*cv::Mat mat = image.GetMat();
	cv::Mat mat1, mat2;
	mat.copyTo(mat1);
	mat.copyTo(mat2);

	cv::Mat kernel0, kernel1;
	kernel0 = (cv::Mat_<int>(3,3) << -1, -2, -1, 0, 0, 0, 1, 2, 1);
	kernel1 = (cv::Mat_<int>(3,3) << -1, 0, 1, -2, 0, 2, -1, 0, 1);

	cv::filter2D(mat1, mat1, CV_8U, kernel0);
	cv::filter2D(mat2, mat2, CV_8U, kernel1);

	cv::add(mat1, mat2, mat);*/
}

AlgFilter::LaplaceSharpen::LaplaceSharpen(baseImage& image) : image(image)
{

}

void AlgFilter::LaplaceSharpen::apply()
{
	cv::Mat* mat = image.GetMat();
	cv::Laplacian(*mat, *mat, CV_8U);
}

AlgFilter::MedianBlur2::MedianBlur2(baseImage& image) : image(image)
{

}

void AlgFilter::MedianBlur2::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;

	cv::Mat tmpMat;

	//double time_start = clock();

	mat->copyTo(tmpMat);

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
				mat->at<uchar>(j, i) = 0;
			}
			else
			{
				mat->at<uchar>(j, i) = 255;
			}
		}
	}

	//double time_end = clock();
	//double interval = time_end - time_start;

	// extra
	image.SetIsBinary(true);
}


AlgFilter::Erode::Erode(baseImage& image) : image(image)
{

}

void AlgFilter::Erode::apply()
{
	cv::Mat* mat = image.GetMat();
	cv::erode(*mat, *mat, cv::Mat());
}

AlgFilter::Dilate::Dilate(baseImage& image) : image(image)
{

}

void AlgFilter::Dilate::apply()
{
	cv::Mat* mat = image.GetMat();
	cv::dilate(*mat, *mat, cv::Mat());
}

AlgFilter::Otsu::Otsu(baseImage& image) : image(image)
{

}

void AlgFilter::Otsu::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;

    cv::Mat rawMat;
    mat->copyTo(rawMat);

	cv::MatND hist;
	int histSize[] = {256};
	float hRanges[] = {0.0, 255.0};
	const float* ranges[] = {hRanges};
	const int channels[] = {0};
	cv::calcHist(mat, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	uchar* data;

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

	for (unsigned int j = 0; j < height - 1; j++)
	{
		data = mat->ptr<uchar>(j);

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

    /*for(unsigned int i = width - 100; i < width; ++i)
	{
		for(unsigned int j = 0; j < height; ++j)
		{
			mat->at<uchar>(j, i) = 0;
		}
    }*/

    cv::bitwise_and(*mat, rawMat, *mat);


	// extra
	image.SetIsBinary(true);
}

AlgFilter::Engrave::Engrave(baseImage& image) : image(image)
{

}

void AlgFilter::Engrave::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;
	unsigned int channels = mat->channels();

	std::vector<cv::Mat> v(channels);
	cv::split(*mat, v);

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

	cv::merge(v, *mat);
}

AlgFilter::Negative::Negative(baseImage& image) : image(image)
{

}

void AlgFilter::Negative::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int height = mat->rows;
	unsigned int width = mat->cols;	
	unsigned int channels = mat->channels();
	
	std::vector<cv::Mat> v(channels);
	cv::split(*mat, v);
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

	cv::merge(v, *mat);
}

AlgFilter::HoleFill::HoleFill(baseImage& image) : image(image)
{

}

void AlgFilter::HoleFill::apply()
{
	cv::Mat* mat = image.GetMat();
	unsigned int width	= mat->cols;
	unsigned int height = mat->rows;
	unsigned int xStart = 0;
	unsigned int xEnd	= 0;
	unsigned int x		= 0;

	unsigned int i, j;

	for (j = 0; j < height; j++)
	{
		uchar* data = mat->ptr<uchar>(j);

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

int AlgFilter::CalcCombosX2Y2R2(int r2)
{
	int x = 0;
	int y = 0;
	int comboNum = 0;

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

int AlgFilter::TempltExcuteCl(cv::Mat& mat, int* templt, int tw, int x, int y)
{
	int i, j, px, py, m;
	m = 0;

	for (j = 0; j < tw; j++)
	{
		for (i = 0; i < tw; i++)
		{
			px = x - tw / 2 + i;
			py = y - tw / 2 + j;
			m += mat.at<uchar>(py, px) * templt[j*tw + i];
		}
	}

	if (m < 0)
	{
		m = -m;
	}

	return m;
}
