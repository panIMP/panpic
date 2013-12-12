#ifndef PANIMAGE_IO_H
#define PANIMAGE_IO_H


#include <opencv2/highgui/highgui.hpp>
#include <QString>
#include <QFileInfo>

#include "panimage.h"

enum Read_Method
{
	Read_AS_IT_IS,
	Read_AS_COLOR,
};

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
