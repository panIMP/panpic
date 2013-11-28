#ifndef PANIMAGEINTEGRATEDALG_H
#define PANIMAGEINTEGRATEDALG_H

#include "panimage.h"
#include "panimagedetect.h"


class PanImageIntegratedAlg
{
	static PanImageIntegratedAlg* instance;

public:
	PanImageIntegratedAlg(void);
	~PanImageIntegratedAlg(void);

	static PanImageIntegratedAlg* GetInstance();
	static void Destroy();

	void LabelString(PanImage& image, _Pan_Circle bigCircle, _Pan_Circle smallCircle);
	void CicleIncisionDetection(PanImage& image);
};

#endif
