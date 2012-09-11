#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include <vtkSphere.h>

typedef PrimitiveTemplate<vtkSphere> Sphere;
template<> void Sphere::updateBounds();
template <> Primitive::Pointer Sphere::copyWithoutTransform() const;

/*
class Sphere : public Primitive {
public:
    	typedef boost::shared_ptr<Sphere> Pointer;
	Sphere(double r);
protected:
    virtual Primitive::Pointer getCopy() const;
};*/

Primitive::Pointer MakeSphere(double r);

#endif
