#include "panimage.h"



/*  Function:        CvImage()
 *  Description:     Initiation for attributes of class CvImage
 *  Input:           None
 *  Output:          None
 */
PanImage::PanImage()
{
    channelChangeState = false;
}
/*  Function:        ~CvImage()
 *  Description:     Release of attributes allocation of class CvImage
 *  Input:           None
 *  Output:          None
 */
PanImage::~PanImage(){

}


/*  Function:        SetMat(cv::Mat &newMat)
 *  Description:     Set the mat attribute
 *  Input:           cv::Mat instance
 *  Output:          None
 */
void PanImage::SetMat(cv::Mat& newMat){
    mat.create(newMat.cols, newMat.rows, newMat.type());
    mat = newMat;
}


/*  Function:        GetMat()
 *  Description:     Get the mat attribute
 *  Input:           None
 *  Output:          cv::Mat instance
 */
cv::Mat& PanImage::GetMat(){
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
