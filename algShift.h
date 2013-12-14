#ifndef ALG_SHIFT_H
#define ALG_SHIFT_H

#include "baseImage.h"
#include "baseTransform.h"

namespace AlgShift {
    static const int ROTATE_CLOCKWISE = 0;
    static const int ROTATE_COUNTERCLOCKWISE = 1;
    static const int MIRROR_VERTICALLY = 0;
    static const int MIRROR_HORIZONGTALLY = 1;

    class FlipTransform;
    class RotateTransform;
}

class AlgShift::FlipTransform : public baseTransform
{
public:
	FlipTransform(int orientation, baseImage& image);

	void apply();

private:
	int orientation;
	baseImage& image;
};

class AlgShift::RotateTransform: public baseTransform
{
public:
	RotateTransform(int orientation, baseImage& image);

	void apply();

private:
	int orientation;
	baseImage& image;
};

#endif // IMGHDL_H
