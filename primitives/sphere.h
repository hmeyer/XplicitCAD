#ifndef SPHERE_H
#define SPHERE_H

#include "primitive.h"
#include <vtkSphere.h>

typedef PrimitiveTemplate<vtkSphere> Sphere;
template<> void Sphere::updateBounds();
template <> Primitive::Pointer Sphere::copyWithoutTransform() const;
Sphere::Pointer MakeSphere(double r);

#endif
