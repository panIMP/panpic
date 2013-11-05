#ifndef CVIMAGESHIFT_H
#define CVIMAGESHIFT_H

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <QImage>

#include "panimage.h"

class PanImageShift
{
private:
    // Instance attribute
    static PanImageShift *instance;


public:
    PanImageShift();
    ~PanImageShift();

    // Instance get and destroy
    static PanImageShift* GetInstance();
    static void Destroy();

    // Processing functions
    void MirrorV(PanImage& image);
    void MirrorH(PanImage& image);
    void RotateClockWise(PanImage& image);
    void RotateCntrClockWise(PanImage& image);

    // Auxilary functions
    QImage CvImage2QImage(PanImage& image);
};



#endif // IMGHDL_H
