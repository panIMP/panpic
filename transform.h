#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QtCore/QString>
#include "panimage.h"

class Transform
{
public:
	virtual ~Transform(void)
	{
	}

	virtual void apply() = 0;
};

#endif