#ifndef PANIMAGEFILTER_H
#define PANIMAGEFILTER_H

#include "panimage.h"
#include "panimagehistproc.h"


class PanImageFilter
{
	static PanImageFilter* instance;

public:
	PanImageFilter();
	~PanImageFilter();

	static PanImageFilter* GetInstance();
	static void Destroy();

	unsigned int CalcCombosX2Y2R2(unsigned int r2);

	void Gray(PanImage& image);
	void MedianBlur(PanImage& image);
	void GuassinBlur(PanImage& image);
	void SobelSharpen(PanImage& image);
	void MedianFilter(PanImage& image);
	void Erode(PanImage& image);
	void Dilate(PanImage& image);
	void OtsuBinary(PanImage& image);
	void Engrave(PanImage& image);
	void Negative(PanImage& image);
	void HoleFill(PanImage& image);
};

#endif // PANIMAGEFILTER_H
