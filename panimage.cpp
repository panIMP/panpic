#include "panimage.h"



/*  Function:        CvImage()
 *  Description:     Initiation for attributes of class CvImage
 *  Input:           None
 *  Output:          None
 */
PanImage::PanImage()
{
	channelChangeState = false;
	isBinary = false;
	isGray = false;
}
/*  Function:        ~CvImage()
 *  Description:     Release of attributes allocation of class CvImage
 *  Input:           None
 *  Output:          None
 */
PanImage::~PanImage(){

}


void PanImage::copyTo(PanImage& image){
	image.SetMat(mat);

	image.channelChangeState  = channelChangeState;
	image.isBinary = isBinary;
	image.isGray = isGray;
}

/*  Function:        SetMat(cv::Mat &newMat)
 *  Description:     Set the mat attribute
 *  Input:           cv::Mat instance
 *  Output:          None
 */
void PanImage::SetMat(cv::Mat& newMat){
	newMat.copyTo(mat);
}


/*  Function:        GetMat()
 *  Description:     Get the mat attribute
 *  Input:           None
 *  Output:          cv::Mat instance
 */
cv::Mat PanImage::GetMat(){
	return mat;
}


/*  Function:        SetModifyState(bool state)
 *  Description:     Change CvImage instance modified state
 *  Input:           True or False, isModified value
 *  Output:          None
 */
void PanImage::SetChannelChangeState(bool state){
	channelChangeState = state;
}


/*  Function:        ModifyState()
 *  Description:     Get the CvImage instance modified state
 *  Input:           None
 *  Output:          True or False, isModified value
 */
bool PanImage::GetChannelChangeState(){
	return channelChangeState;
}


void PanImage::SetIsBinary(bool state){
	isBinary = state;
}

bool PanImage::IsBinary(){
	return isBinary;
}

void PanImage::SetIsGray(bool state){
	isGray = state;
}

bool PanImage::IsGray(){
	return isGray;
}



/*  Function:       CvMat2QImage(const cv::Mat& image)
 *  Description:    Convert the cv::Mat format to QImage Format
 *  Input:          cv::Mat object
 *  Output:         QImage object
 */
QImage PanImage::PanImage2QImage(){
	QImage qimage;

	switch (mat.channels()){
		case 1:     qimage = QImage((const unsigned char*)(mat.data),
								mat.cols,
								mat.rows,
								static_cast<int>(mat.step),
								QImage::Format_Indexed8);
					break;

		case 3:     if (channelChangeState == false){
						cv::cvtColor(mat, mat, CV_BGR2RGB);
						channelChangeState = true;
					}
					qimage = QImage((const unsigned char*)(mat.data),
										   mat.cols,
										   mat.rows,
										   static_cast<int>(mat.step),
										   QImage::Format_RGB888);
					break;

		case 4:     if (channelChangeState == false){
						cv::cvtColor(mat, mat, CV_BGR2RGB);
						channelChangeState = true;
					}
					qimage = QImage((const unsigned char*)(mat.data),
										   mat.cols,
										   mat.rows,
										   static_cast<int>(mat.step),
										   QImage::Format_ARGB32);
					break;
	}

	return qimage;
}
