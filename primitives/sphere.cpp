#include "sphere.h"
#include <vtkSphere.h>

Sphere::Sphere(double r):Primitive(-r,r,-r,r,-r,r) {
	vtkSmartPointer<vtkSphere> m = vtkSmartPointer<vtkSphere>::New();	
	m->SetRadius( r );
	m_func = m;
}

