#ifndef PANIMAGEHIST_H
#define PANIMAGEHIST_H

#include "panimage.h"


class PanImageHist
{
	static PanImageHist* instance;


public:
	PanImageHist();
	~PanImageHist();

	static PanImageHist* GetInstance();
	static void Destroy();

	PanImage GetHistImage(PanImage& inputImage);
	bool HistEqalization(PanImage& inputImage);
	bool HistMatch(PanImage& inputImage,  float* histR);
	void Enhance(PanImage& image);
};

#endif // PANIMAGEHISTPROC_H
