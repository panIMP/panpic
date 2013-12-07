#ifndef PANIMAGESHIFT_H
#define PANIMAGESHIFT_H

#include "panimage.h"
#include "transform.h"

class FlipTransform : public Transform
{
public:
	FlipTransform(int orientation, PanImage& image);

	void apply();

private:
	int orientation;
	PanImage& image;
};

class RotateTransform: public Transform
{
public:
	RotateTransform(int orientation, PanImage& image);

	void apply();

private:
	int orientation;
	PanImage& image;
};

class PanImageShift
{
	PanImageShift();
	~PanImageShift();
	PanImageShift(const PanImageShift&);
	PanImageShift& operator = (const PanImageShift&);

public:
	// Instance get and destroy
	static PanImageShift* GetInstance();
	static void Destroy();

	// Processing functions
	FlipTransform* MirrorV(PanImage& image);
	FlipTransform* MirrorH(PanImage& image);
	RotateTransform* RotateClockWise(PanImage& image);
	RotateTransform* RotateCntrClockWise(PanImage& image);

private:
	// Instance attribute
	static PanImageShift *instance;
};


#endif // IMGHDL_H
