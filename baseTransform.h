#ifndef BASE_TRANSFORM_H
#define BASE_TRANSFORM_H

#include <QtCore/QString>
#include "baseImage.h"

class baseTransform
{
public:
    virtual ~baseTransform(void)
	{
	}

	virtual void apply() = 0;
};

#endif
