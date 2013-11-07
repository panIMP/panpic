#ifndef CVIMAGEIO_H
#define CVIMAGEIO_H


#include <opencv2/highgui/highgui.hpp>
#include <QString>

#include "panimage.h"

class PanImageIO
{
private:
    // instance attribute -- only one instance can be created
    static PanImageIO* instance;


public:
    PanImageIO();
    ~PanImageIO();

    // Instance get and destroy
    static PanImageIO* GetInstance();
    static void Destroy();

    // Image input and output
    PanImage ReadPanImage(const QString& str);
    void SavePanImage(PanImage& ImageToSave, const QString& str);
};

#endif // IMAGEIO_H
