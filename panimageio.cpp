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
    result.SetMat(cv::imread(str.toStdString()));
    return result;
}


/*  Function:       SaveImage(const QString &str)
 *  Description:    Save image to the assigned path
 *  Input:          Image to be saved & path of QString type
 *  Output:         None
 */
void PanImageIO::SavePanImage(PanImage& ImageToSave, const QString &str){
    cv::imwrite(str.toStdString(), ImageToSave.GetMat());
}


/*  Function:       SetImage(const QString &str)
 *  Description:    Replace specified image with another specified image
 *  Input:          To be replaced image & replace image
 *  Output:         None
 */
void PanImageIO::ReplaceMat(PanImage& initImage, PanImage& replaceImage){
    initImage.SetMat(replaceImage.GetMat());
    initImage.SetChannelChangeState(replaceImage.GetChannelChangeState());
}


/*  Function:       SetImage(const QString &str)
 *  Description:    Replace specified image with another image of specified path
 *  Input:          To be replaced image & replace image file path
 *  Output:         None
 */
void PanImageIO::ReplaceMat(PanImage& initImage, const QString& str){
    initImage.SetMat(cv::imread(str.toStdString()));
    initImage.SetChannelChangeState(false);
}

















































