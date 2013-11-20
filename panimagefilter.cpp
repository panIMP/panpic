#include "panimagefilter.h"

PanImageFilter* PanImageFilter::instance = 0;

PanImageFilter::PanImageFilter()
{

}


PanImageFilter::~PanImageFilter(){

}

PanImageFilter* PanImageFilter::GetInstance(){
	if (instance == 0){
		instance = new PanImageFilter();
	}

	return instance;
}


void PanImageFilter::Destroy(){
	if (instance != 0){
		delete instance;
		instance = 0;
	}
}

void PanImageFilter::GradSharpen(PanImage &image){
	cv::Mat mat = image.GetMat();
	cv::Mat result;
	result.create(mat.rows, mat.cols, CV_8UC1);
	uchar gradValue;

	for(int i = 1; i < mat.cols - 2; i++){
		for (int j = 1; j < mat.rows - 2; j++){
			result.at<uchar>(j, i) = cv::saturate_cast<uchar>(
						fabs((float)(mat.at<uchar>(j+1, i-1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j+1, i)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j-1, i+1) - 2*mat.at<uchar>(j-1, i)))
					   +fabs((float)(mat.at<uchar>(j-1, i+1) + mat.at<uchar>(j+1, i+1) + 2*mat.at<uchar>(j, i+1)
									-mat.at<uchar>(j-1, i-1) - mat.at<uchar>(j+1, i-1) - 2*mat.at<uchar>(j, i-1))));
		}
	}

	result.copyTo(mat);
}


void PanImageFilter::OtsuBinary(PanImage &image){
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
		w1 = sum - w0;                  // *sum
		temp += i * hist.at<float>(i);       // *sum

		u0 = temp/(double)w0;                   // *1
		u1 = (moment - temp)/(double)w1;        // *1
		u = moment;

		equ = w0 * (u0-u) * (u0-u) + w1 * (u1-u) * (u1-u);          // *sum^2

		if(equ > max)
		{
			threshold = i;
			max = equ;
		}
	}

	for(int i = 1; i < mat.cols - 2; i++){
		for (int j = 1; j < mat.rows - 2; j++){
			if(mat.at<uchar>(j, i) >= threshold){
				mat.at<uchar>(j, i) = 255;
			}
			else
			{
				mat.at<uchar>(j, i) = 0;
			}
		}
	}

	for(int i = mat.cols - 100; i < mat.cols; i++){
		for(int j = 0; j < mat.rows; j++){
			mat.at<uchar>(j, i) = 0;
		}
	}
}


void PanImageFilter::HoughTransform(PanImage &image){
	cv::Mat mat = image.GetMat();
	unsigned int width = mat.cols;
	unsigned int height = mat.rows;

	unsigned int rMin = 90;
	unsigned int r2Min = rMin * rMin;
	unsigned int rMax = 110;
	unsigned int r2Max = rMax * rMax;
	unsigned int aMin = rMax;
	unsigned int aMax = width - rMin;
	unsigned int bMin = rMax;
	unsigned int bMax = height - rMin;

	static unsigned long H[752][480][110] = {{{0}}};
	memset(H, 0, 752*480*110*sizeof(unsigned long));

	unsigned int i,j,a,b,r,r2;
	unsigned int aVal = 0;
	unsigned int bVal = 0;
	unsigned int rVal = 0;
	int iDist = 0;
	int jDist = 0;
	unsigned int step  = 8;

	// do by algorithm by every step pixels
	for (j = 0; j < height; j+=step){
		uchar* data = mat.ptr<uchar>(j);
		for (i = 0; i < width; i+=step){
			// if pixel is black
			if (*data != 0){
				// calculate only those within the frame
				for (a = aMin; a < aMax; a++){
					for (b = bMin; b < bMax; b++){
						iDist = i - a;
						jDist = j - b;
						r2 = iDist*iDist + jDist*jDist;
						// calculate only those within the circle
						if (r2 > r2Min && r2 < r2Max){
							r = (unsigned int)sqrt((double)r2);   
							H[a][b][r] ++;
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
	for (r = rMin; r < rMax; r++){
		for (a = aMin; a < aMax; a ++){
			for (b = bMin; b < bMax; b++){
				tmpVal = H[a][b][r];
				if (tmpVal > maxVal)
				{
					maxVal = tmpVal;
					aVal = a;
					bVal = b;
					rVal = r;
				}
			}
		}
	}


	unsigned long rThresh = rVal * 9 / 10;
	rThresh = rThresh * rThresh;
	unsigned long r2Val = (rVal - 3) * (rVal - 3);
	unsigned long distance = 0;
	unsigned int rectTop = bVal - rVal;
	unsigned int rectBottom = bVal + rVal;
	unsigned int rectLeft = aVal - rVal;
	unsigned int rectRight = aVal + rVal;

	// label the straight line
	for (i = 0; i < width; i++){
		for (j = 0; j < height; j++){
			if (mat.at<uchar>(j,i) != 0)
			{
				distance = (i - aVal) * (i - aVal) + (j - bVal)*(j - bVal);
				if (distance > rThresh && distance < r2Val)
				{
					mat.at<uchar>(j, i) = 255;
				}
				else
				{
					mat.at<uchar>(j, i) = 60;
				}

			}		
		}
	}
}


































