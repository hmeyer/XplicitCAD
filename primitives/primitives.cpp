#include "primitives.h"

#include <vtkSphere.h>

Sphere::Sphere(double r) {
	vtkSmartPointer<vtkSphere> m = vtkSmartPointer<vtkSphere>::New();	
	m_func = m;
	m->SetRadius( r );
	m->SetCenter(0,0,0);
}

