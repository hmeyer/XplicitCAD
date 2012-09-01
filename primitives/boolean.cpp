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

void Boolean::addObject(Primitive::Const_Pointer object) {
	vtkImplicitBoolean::SafeDownCast(m_func)->AddFunction(object->getFunction());
	m_children.push_back(object);
}

Primitive::Pointer Boolean::getCopy() const {
	Pointer cp = getCopyBase();
	BOOST_FOREACH( Primitive::Const_Pointer i, m_children ) {
		cp->addObject( i );
	}
	return cp;
}

Union::Union(Primitive::Pointer object1, Primitive::Pointer object2)
	:Boolean(object1, object2, VTK_UNION) { }

BoundingBox Union::getBoundingBox() const { }

Intersection::Intersection(Primitive::Pointer object1, Primitive::Pointer object2)
	:Boolean(object1, object2, VTK_INTERSECTION) { } 
BoundingBox Intersection::getBoundingBox() const { }

Difference::Difference(Primitive::Pointer object1, Primitive::Pointer object2)
	:Boolean(object1, object2, VTK_DIFFERENCE) { } 
BoundingBox Difference::getBoundingBox() const { }

Boolean::Pointer Union::getCopyBase() const { return boost::make_shared<Union>(); }
Boolean::Pointer Intersection::getCopyBase() const { return boost::make_shared<Intersection>(); }
Boolean::Pointer Difference::getCopyBase() const { return boost::make_shared<Difference>(); }

Union::Union():Boolean(VTK_UNION) { }
Intersection::Intersection():Boolean(VTK_INTERSECTION) { }
Difference::Difference():Boolean(VTK_DIFFERENCE) { }

Boolean::Pointer MakeUnion(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Union>(object1, object2);
}
Boolean::Pointer MakeIntersection(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Intersection>(object1, object2);
}
Boolean::Pointer MakeDifference(Primitive::Pointer object1, Primitive::Pointer object2) {
	return boost::make_shared<Difference>(object1, object2);
}
