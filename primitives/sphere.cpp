#include "sphere.h"
#include <vtkSphere.h>
#include <boost/make_shared.hpp>

Sphere::Sphere(double r):Primitive(-r,r,-r,r,-r,r) {
	vtkSmartPointer<vtkSphere> m = vtkSmartPointer<vtkSphere>::New();	
	m->SetRadius( r );
	m_func = m;
}

Primitive::Pointer Sphere::getCopy() const {
	double r = vtkSphere::SafeDownCast(m_func)->GetRadius();
	Pointer cp = boost::make_shared<Sphere>(r);
}

