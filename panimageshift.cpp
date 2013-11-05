#include "panimageshift.h"



// Important! Never foget
PanImageShift* PanImageShift::instance = 0;


/*  Function:        ImageShift()
 *  Description:     Initiation for attributes of class ImageShift
 *  Input:           None
 *  Output:          None
 */
PanImageShift::PanImageShift()
{

}
/*  Function:        ~ImageShift()
 *  Description:     Release of attributes allocation of class ImageShift
 *  Input:           None
 *  Output:          None
 */
PanImageShift::~PanImageShift(){

}


/*  Funtion:        GetInstance()
 *  Description:    Get the instance of class ImageShift, and avoid duplicate allocation
 *  Input:          None
 *  Output:         ImageShift*
 */
PanImageShift* PanImageShift::GetInstance(){
    if (instance == 0){
        instance = new PanImageShift();
    }
    return instance;
}


/*  Function:       Destroy()
 *  Description:    Destroy the instance of class ImageShift to avoid memory leak
 *  Input:          None
 *  Output:         None
 */
void PanImageShift::Destroy(){
    if (instance != 0){
        delete instance;
        instance = 0;
    }
}


/*  Function:       CvMat2QImage(const cv::Mat& image)
 *  Description:    Convert the cv::Mat format to QImage Format
 *  Input:          cv::Mat object
 *  Output:         QImage object
 */
QImage PanImageShift::CvImage2QImage(PanImage& image){
    if (image.GetChannelChangeState() == false){
        cv::cvtColor(image.GetMat(), image.GetMat(), CV_BGR2RGB);
        image.SetChannelChangeState(true);
    }

    QImage qimage = QImage((const unsigned char*)(image.GetMat().data),
                           image.GetMat().cols,
                           image.GetMat().rows,
                           static_cast<int>(image.GetMat().step),
                           QImage::Format_RGB888);

    return qimage;
}


/*  Function:        MirrorV(cv::Mat& image)
 *  Description:     Mirror the image vertically
 *  Input:           cv::Mat object -- image to be processed and modified
 *  Output:          None
 */
void PanImageShift::MirrorV(PanImage& image){
    cv::flip(image.GetMat(), image.GetMat(), 0);
}


/*  Function:        MirrorH(cv::Mat& image)
 *  Description:     Mirror the image horizontally
 *  Input:           cv::Mat object -- image to be processed and modified
 *  Output:          None
 */
void PanImageShift::MirrorH(PanImage& image){
    cv::flip(image.GetMat(), image.GetMat(), 1);
}


/*  Function:        RotateClockWise(cv::Mat& image)
 *  Description:     Rotate the image clockWise
 *  Input:           cv::Mat object -- image to be processed and modified
 *  Output:          None
 */
void PanImageShift::RotateClockWise(PanImage& image){
    cv::transpose(image.GetMat(), image.GetMat());
    cv::flip(image.GetMat(), image.GetMat(), 0);
}


/*  Function:        RotateClockWise(cv::Mat& image)
 *  Description:     Rotate the image counter clockWise
 *  Input:           cv::Mat object -- image to be processed and modified
 *  Output:          None
 */
void PanImageShift::RotateCntrClockWise(PanImage& image){
    cv::transpose(image.GetMat(), image.GetMat());
    cv::flip(image.GetMat(), image.GetMat(), 1);
}

