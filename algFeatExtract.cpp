#include "algFeatExtract.h"

AlgFeatExtract::GetColorHist::GetColorHist(baseImage &image, baseImage &histImage) :
image(image), histImage(histImage){
}

void AlgFeatExtract::GetColorHist::apply(){
	cv::Mat* mat = image.GetMat();
	cv::Mat newMat;

	if (mat->channels() == 3)
	{
		cv::cvtColor(*mat, newMat, CV_RGB2HSV);
	}
	else
	{
		mat->copyTo(newMat);
	}

	std::vector<cv::Mat> v(newMat.channels());
	cv::split(newMat, v);
	std::vector<cv::Mat> histV(v.size());
	cv::Mat hist;
	hist.create(newMat.rows, newMat.cols, newMat.type());

	int histSize[] = {256};
	float hRanges[] = {0.0, 255.0};
	const float* ranges[] = {hRanges};
	const int channels[] = {0};

    for (unsigned int i = 0; i < v.size(); ++i){
		cv::calcHist(&v[i], 1, channels, cv::Mat(), histV[i], 1, histSize, ranges);
	}

	cv::merge(histV,hist);
	histImage.SetMat(hist);
}
