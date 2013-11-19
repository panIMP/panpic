#ifndef PANIMAGEHISTPROC_H
#define PANIMAGEHISTPROC_H

#include "panimage.h"


class PanImageHistProc
{
    static PanImageHistProc* instance;


public:
    PanImageHistProc();
    ~PanImageHistProc();

    static PanImageHistProc* GetInstance();
    static void Destroy();

    PanImage GetHistImage(PanImage& inputImage);
    bool HistEqalization(PanImage& inputImage);
    bool HistMatch(PanImage& inputImage,  double* histR);
};

#endif // PANIMAGEHISTPROC_H
