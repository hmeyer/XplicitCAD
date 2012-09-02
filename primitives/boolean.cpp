#include "boolean.h"
#include <vtkImplicitBoolean.h>
#include <boost/make_shared.hpp>
#include <boost/foreach.hpp>

Boolean::Boolean(int operationType) {
	vtkSmartPointer<vtkImplicitBoolean> b = vtkSmartPointer<vtkImplicitBoolean>::New();	
	b->SetOperationType( operationType );
	m_func = b;
}

Boolean::Boolean(Primitive::Const_Pointer object1, Primitive::Const_Pointer object2, int operationType) {
	vtkSmartPointer<vtkImplicitBoolean> b = vtkSmartPointer<vtkImplicitBoolean>::New();	
	b->SetOperationType( operationType );
	b->AddFunction(object1->getFunction());
	b->AddFunction(object2->getFunction());
	m_func = b;
	m_children.push_back(object1);
	m_children.push_back(object2);
}
Boolean::Boolean(const Boolean::PrimCon &children, int operationType) {
	vtkSmartPointer<vtkImplicitBoolean> b = vtkSmartPointer<vtkImplicitBoolean>::New();	
	b->SetOperationType( operationType );
	BOOST_FOREACH( Primitive::Const_Pointer i, children ) {
		b->AddFunction(i->getFunction());
		m_children.push_back(i);
	}
	m_func = b;
}

void Boolean::addObject(Primitive::Const_Pointer object) {
	vtkImplicitBoolean::SafeDownCast(m_func)->AddFunction(object->getFunction());
	m_children.push_back(object);
}


Boolean::Pointer MakeUnion(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Union>(object1, object2);
}
Boolean::Pointer MakeIntersection(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Intersection>(object1, object2);
}
Boolean::Pointer MakeDifference(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Difference>(object1, object2);
}
