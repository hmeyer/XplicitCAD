#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive {
public:
	Sphere(double r);
protected:
    virtual Pointer getCopy() const;
};

#endif
