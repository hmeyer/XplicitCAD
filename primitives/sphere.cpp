#include "sphere.h"
#include <vtkObjectFactory.h>


template<>
vtkStandardNewMacro( Sphere );

Primitive::Pointer MakeSphere(double r) {
	vtkSmartPointer< Sphere > sp = Sphere::New();
	sp->SetRadius( r );
	sp->updateBounds();
	return sp;
}

template<> void Sphere::updateBounds() {
	double r = GetRadius();
	setBounds(-r,r,-r,r,-r,r);
}

template <> Primitive::Pointer Sphere::copyWithoutTransform() const {
	Primitive::Pointer cp = MakeSphere( vtkThis()->GetRadius() );
	return cp;
}
/*
//template<>
Sphere::Sphere(double r):Primitive(-r,r,-r,r,-r,r) {
	vtkSmartPointer<vtkSphere> m = vtkSmartPointer<vtkSphere>::New();	
	m->SetRadius( r );
	m_func = m;
}

Primitive::Pointer Sphere::getCopy() const {
	double r = vtkSphere::SafeDownCast(m_func)->GetRadius();
	Pointer cp = boost::make_shared<Sphere>(r);
	return cp;
}
*/
