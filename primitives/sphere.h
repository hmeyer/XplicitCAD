#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"

class Sphere : public Primitive {
public:
    	typedef boost::shared_ptr<Sphere> Pointer;
	Sphere(double r);
protected:
    virtual Primitive::Pointer getCopy() const;
};

Sphere::Pointer MakeSphere(double r);

#endif
