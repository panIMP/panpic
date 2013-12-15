#ifndef BASE_IMAGE_H
#define BASE_IMAGE_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/video/tracking.hpp>
#include <QImage>
#include <QMessageBox>
#include <QTime>
#include <QDebug>
#include <time.h>

class baseImage
{
private:
	cv::Mat mat;
	bool channelChangeState;
	bool isBinary;
	bool isGray;

public:
	baseImage();
	~baseImage();
	baseImage& operator= (const baseImage&);
	baseImage(const baseImage&);

	int height();
	int width();

	void copyTo(baseImage& image) const;

	void SetMat(const cv::Mat& newMat);
	cv::Mat* GetMat();

	void SetChannelChangeState(bool state);
	bool GetChannelChangeState();

	void SetIsBinary(bool state);
	bool IsBinary();

	void SetIsGray(bool state);
	bool IsGray();

	//  Image input and output
	static baseImage ReadPanImage(const QString& str);
	void static SavePanImage(baseImage& ImageToSave, const QString& str);

	//  PanImage --> QImage
	QImage PanImage2QImage();
};

#endif
