#include "boolean.h"
#include <vtkObjectFactory.h>
#include <vtkImplicitFunctionCollection.h>
#include <vtkVersion.h>

template<>
vtkStandardNewMacro( Boolean );

#if (VTK_MAJOR_VERSION>5)
const int OP_UNION = vtkImplicitBoolean::VTK_UNION;
const int OP_INTERSECTION = vtkImplicitBoolean::VTK_INTERSECTION;
const int OP_DIFFERENCE = vtkImplicitBoolean::VTK_DIFFERENCE;
#else
const int OP_UNION = VTK_UNION;
const int OP_INTERSECTION = VTK_INTERSECTION;
const int OP_DIFFERENCE = VTK_DIFFERENCE;
#endif


Boolean::Pointer MakeBoolean(int operationType, Primitive::Pointer a=Primitive::Pointer(), Primitive::Pointer b=Primitive::Pointer()) {
	vtkSmartPointer< Boolean > bf(new Boolean());
	if (a) bf->AddFunction(a->vtk());
	if (b) bf->AddFunction(b->vtk());
	bf->SetOperationType(operationType);
	bf->updateBounds();
	return bf->smartP();
}

Boolean::Pointer MakeUnion(Primitive::Pointer a, Primitive::Pointer b) { return MakeBoolean(OP_UNION, a, b); }
Boolean::Pointer MakeIntersection(Primitive::Pointer a, Primitive::Pointer b) { return MakeBoolean(OP_INTERSECTION, a, b); }
Boolean::Pointer MakeDifference(Primitive::Pointer a, Primitive::Pointer b) { return MakeBoolean(OP_DIFFERENCE, a, b); }

template<> void Boolean::updateBounds() {
	setBounds(-100,100,-100,100,-100,100);
}

template <> Primitive::Pointer Boolean::copyWithoutTransform() const {
	Boolean::Pointer cp = MakeBoolean( const_cast<Boolean*>(this)->GetOperationType() );
	vtkImplicitFunctionCollection *fc = const_cast<Boolean*>(this)->GetFunction();
	vtkImplicitFunction *f;
	vtkCollectionSimpleIterator sit;
	for (fc->InitTraversal(sit); (f=fc->GetNextImplicitFunction(sit)); )
		cp->AddFunction(f);
	cp->updateBounds();
	return cp;
}

/*

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

*/
