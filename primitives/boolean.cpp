#include "boolean.h"
#include <vtkImplicitBoolean.h>

Boolean::Boolean(Primitive::Pointer object, int operationType) {
	vtkSmartPointer<vtkImplicitBoolean> b = vtkSmartPointer<vtkImplicitBoolean>::New();	
	b->SetOperationType( operationType );
	b->AddFunction(object->getFunction());
	m_func = b;
	m_children.push_back(object);
}

void Boolean::addObject(Primitive::Pointer object) {
	vtkImplicitBoolean::SafeDownCast(m_func)->AddFunction(object->getFunction());
	m_children.push_back(object);
}

Intersection::Intersection(Primitive::Pointer object):Boolean(object, VTK_INTERSECTION) {
}; 

Difference::Difference(Primitive::Pointer object):Boolean(object, VTK_DIFFERENCE) {
}; 
