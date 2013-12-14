#include "algHistProc.h"


AlgHistProc::GetHistImage::GetHistImage(baseImage& image, baseImage& histImage) : image(image), histImage(histImage)
{

}


void AlgHistProc::GetHistImage::apply()
{
	cv::Mat mat = image.GetMat();
	cv::MatND hist;

	if (mat.channels() == 1){
		int histSize[] = {256};
		float hRanges[] = {0.0, 255.0};
		const float* ranges[] = {hRanges};
		const int channels[] = {0};
		cv::calcHist(&mat, 1, channels, cv::Mat(), hist, 1, histSize, ranges);
		double maxVal = 0;
		double minVal = 0;
		cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);
		cv::Mat histMat(histSize[0], histSize[0], CV_8UC1, cv::Scalar(255));
		int hpt = static_cast<int>(0.9 * histSize[0]);
		for (int h = 0; h < histSize[0]; h ++){
			float binVal = hist.at<float>(h);
			int intensity = static_cast<int>(binVal * hpt / maxVal);
			cv::line(histMat, cv::Point(h, histSize[0]),
					cv::Point(h, histSize[0] - intensity),
					cv::Scalar(0));
		}
		histImage.SetMat(histMat);
	}

	else if (mat.channels() == 3){
		cv::Mat hsv;
		cv::cvtColor(mat, hsv, CV_BGR2HSV);
		std::vector<cv::Mat> v(hsv.channels());
		cv::split(hsv, v);
		std::vector<cv::Mat> temp(hsv.channels() - 1);
		temp[0] = v[0];
		temp[1] = v[1];
		cv::Mat hs;
		cv::merge(temp, hs);

		int hbins = 30;
		int sbins = 20;
		int histSize[] = {hbins, sbins};
		float hranges[] = {0, 180};
		float sranges[] = {0, 255};
		const float* ranges[] = {hranges, sranges};
		int channels[] = {0, 1};
		cv::MatND hist;
		cv::calcHist(&hs, 1, channels, cv::Mat(), hist,
					 2, histSize, ranges, true, false);
		double maxVal;
		cv::minMaxLoc(hist, 0, &maxVal, 0, 0);
		int height = 360;
		int width = (hbins*sbins*1);
		cv::Mat histMat(height, width, CV_8UC3, cv::Scalar(0, 0, 0));
		cv::Mat hsv_color(1,1,CV_8UC3, cv::Scalar(0,0,0));
		cv::Mat rgb_color(1,1,CV_8UC3, cv::Scalar(0,0,0));
		int bin_w = width / (hbins * sbins);
		for (int h = 0; h < hbins; h++){
			for (int s = 0; s < sbins; s++){
				float binVal = hist.at<float>(h,s);
				int intensity = cvRound(binVal * 255 / maxVal);
				int i = h*sbins + s;
				hsv_color.setTo(cv::Scalar(h*180.f / hbins,s*255.f/sbins, 255));
				cv::cvtColor(hsv_color,rgb_color,CV_HSV2BGR);
				cv::Scalar color = rgb_color.at<cv::Vec3b>(0,0);
				cv::rectangle(histMat, cv::Point(i*bin_w,height),
							  cv::Point((i+1)*bin_w,height - intensity),
							  color, -1);
			}
		}
		histImage.SetMat(histMat);
	}
}


AlgHistProc::HistEqualize::HistEqualize(baseImage& image) : image(image)
{

}


void AlgHistProc::HistEqualize::apply()
{
	cv::Mat mat = image.GetMat();
	if (mat.channels() == 1){
		cv::equalizeHist(mat, mat);
	}
	else if (mat.channels() == 3){
		std::vector<cv::Mat> v(mat.channels());
		cv::split(mat, v);
		cv::equalizeHist(v[0], v[0]);
		cv::equalizeHist(v[1], v[1]);
		cv::equalizeHist(v[2], v[2]);
		cv::merge(v, mat);
	}
}


AlgHistProc::HistMatch::HistMatch(baseImage& image, float* histMatch) : image(image)
{
	this->histMatch = histMatch;
}


void AlgHistProc::HistMatch::apply()
{
	cv::Mat mat = image.GetMat();
	unsigned int width = mat.cols;
	unsigned int height = mat.rows;
	unsigned int channelNum = mat.channels();
	
	std::vector<cv::Mat> v(channelNum);
	cv::split(mat, v);

	cv::Mat hist;
	int histSize[] = {256};
	float hRanges[] = {0.0, 255.0};
	const float* ranges[] = {hRanges};
	const int channels[] = {0};

	for (unsigned int k = 0; k < channelNum; k++)
	{
		float histMatchAccum[256] = {0.0};
		
		for (int i = 0; i < 256; i++)
		{
			if (i == 0)
			{
				histMatchAccum[0] = histMatch[0];
			}
			else 
			{
				histMatchAccum[i] = histMatchAccum[i - 1] + histMatch[i];
			}
		}

		cv::calcHist(&v[k], 1, channels, cv::Mat(), hist, 1, histSize, ranges);

		float histAccum[256] = {0.0};

		for (int i = 0; i < 256; i++)
		{
			if (i == 0)
			{
				histAccum[0] = hist.at<float>(i);
			}
			else
			{
				histAccum[i] = histAccum[i - 1] + hist.at<float>(i);
			}
		}

		int histMap[256] = {};

		for (int i = 0; i < 256; i++)
		{
			int m = 0;
			float min_value = 500.0f;
			for (int j = 0; j < 256; j++)
			{
				float now_value = fabs(histMatchAccum[j] - histAccum[i]);
				if (now_value < min_value)
				{
					m = j;
					min_value = now_value;
				}
			}
			histMap[i] = (uchar)m;
		}

		for (unsigned int j = 0; j < height; j++)
		{
			uchar* data = v[k].ptr<uchar>(j);
			for (unsigned int i = 0; i < width; i++)
			{
				*data = histMap[*data];
				data ++;
			}
		}
	}
	
	cv::merge(v, mat);
}


AlgHistProc::Enhance::Enhance(baseImage& image) : image(image)
{

}

void AlgHistProc::Enhance::apply()
{
	cv::Mat mat = image.GetMat();
	unsigned int width = mat.cols;
	unsigned int height = mat.rows;
	unsigned int channels = mat.channels();

	std::vector<cv::Mat> v(channels);
	std::vector<double> maxValue(channels);
	std::vector<double> minValue(channels);
	std::vector<double> enhanceRate(channels);

	cv::split(mat, v);

	for (unsigned int k = 0; k < channels; k++)
	{
		cv::minMaxLoc(v[k], &minValue[k], &maxValue[k]);
		enhanceRate[k] = 255 / (maxValue[k] - minValue[k]);
	}

	for (unsigned int k = 0; k < channels; k++)
	{
		for (unsigned int j = 0; j < height; j++)
		{
			uchar* data = v[k].ptr<uchar>(j);
			
			for (unsigned int i = 0; i < width; i++)
			{
				*data = (*data - minValue[k]) * enhanceRate[k]; 
				data ++;
			}
		}
	}

	cv::merge(v, mat);
}

