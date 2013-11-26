#ifndef PANIMAGE_H
#define PANIMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <QImage>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <time.h>

class PanImage
{
private:
	cv::Mat mat;
	bool channelChangeState;
	bool isBinary;
	bool isGray;

public:
	PanImage();
	~PanImage();

	void copyTo(PanImage& image);

	void SetMat(cv::Mat& newMat);
	cv::Mat& GetMat();

	void SetChannelChangeState(bool state);
	bool GetChannelChangeState();

	void SetIsBinary(bool state);
	bool IsBinary();

	void SetIsGray(bool state);
	bool IsGray();

	QImage PanImage2QImage();
};

#endif // CVIMAGE_H
