#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include <vtkSphere.h>

typedef PrimitiveTemplate<vtkSphere> Sphere;
template<> void Sphere::updateBounds();
template <> Primitive::PPointer Sphere::copyWithoutTransform() const;
Sphere::PTPointer MakeSphere(double r);

#endif
