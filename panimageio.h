#ifndef PANIMAGEIO_H
#define PANIMAGEIO_H


#include <opencv2/highgui/highgui.hpp>
#include <QString>

#include "panimage.h"

class PanImageIO
{
	PanImageIO();
	~PanImageIO();
	PanImageIO(const PanImageIO&);
	PanImageIO& operator = (const PanImageIO&);

public:

	// Instance get and destroy
	static PanImageIO* GetInstance();
	static void Destroy();

	// Image input and output
	PanImage ReadPanImage(const QString& str);
	void SavePanImage(PanImage& ImageToSave, const QString& str);

private:
	// instance attribute -- only one instance can be created
	static PanImageIO* instance;
};

#endif // IMAGEIO_H
