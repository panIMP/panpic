#include "panimageio.h"



// Important! Never foget
PanImageIO* PanImageIO::instance = 0;


/*  Function:        ImageIO()
 *  Description:     Initiation for attributes of class ImageIO
 *  Input:           None
 *  Output:          None
 */
PanImageIO::PanImageIO()
{

}
/*  Function:        ~ImageIO()
 *  Description:     Release of attributes allocation of class ImageIO
 *  Input:           None
 *  Output:          None
 */
PanImageIO::~PanImageIO(){

}


/*  Funtion:        GetInstance()
 *  Description:    Get the instance of class ImageIO, and avoid duplicate allocation
 *  Input:          None
 *  Output:         ImageIO*
 */
PanImageIO* PanImageIO::GetInstance(){
	if (instance == 0){
		instance = new PanImageIO();
	}
	return instance;
}


/*  Function:       Destroy()
 *  Description:    Destroy the instance of class ImageIO to avoid memory leak
 *  Input:          None
 *  Output:         None
 */
void PanImageIO::Destroy(){
	if (instance != 0){
		delete instance;
		instance = 0;
	}
}


/*  Function:       ReadImage(const QString &str)
 *  Description:    Read/Load an image from an assigned path
 *  Input:          Path of QString type
 *  Output:         Image of cv::Mat format
 */
PanImage PanImageIO::ReadPanImage(const QString& str){
	PanImage result;
	result.SetChannelChangeState(false);
	// Since here you want to read the image as it is,
	// you should set the flag to be -1, so,
	// if there exits alpha channel, it will also be read.
	cv::Mat mat = cv::imread(str.toStdString(), -1);
	result.SetMat(mat);

	if (mat.channels() == 1)
	{
		result.SetIsGray(true);
	}

	return result;
}


/*  Function:       SaveImage(const QString &str)
 *  Description:    Save image to the assigned path
 *  Input:          Image to be saved & path of QString type
 *  Output:         None
 */
void PanImageIO::SavePanImage(PanImage& ImageToSave, const QString &str){
	if (ImageToSave.GetMat().channels() == 3){
		// transform the image back to opencv style channel order, since
		// it has been converted to RGB format when loaded for QImage display
		if (ImageToSave.GetChannelChangeState())
		{
			cv::cvtColor(ImageToSave.GetMat(), ImageToSave.GetMat(), CV_RGB2BGR);
		}
	}
	cv::imwrite(str.toStdString(), ImageToSave.GetMat());
}



