#include "panimage.h"


/*  Function:        CvImage()
 *  Description:     Initiation for attributes of class CvImage
 *  Input:           None
 *  Output:          None
 */
PanImage::PanImage(int colorType)
{
    mat.create(0, 0, colorType);
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
