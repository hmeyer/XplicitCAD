#include "sphere.h"
#include <boost/make_shared.hpp>
#include <vtkObjectFactory.h>

template<>
vtkStandardNewMacro( Sphere );

Sphere::PTPointer MakeSphere(double r) {
	vtkSmartPointer< Sphere > sp(new Sphere());
	sp->SetRadius( r );
	sp->updateBounds();
	return sp->smartP();
}

template<> void Sphere::updateBounds() {
	double r = GetRadius();
	setBounds(-r,r,-r,r,-r,r);
}

template <> Primitive::PPointer Sphere::copyWithoutTransform() const {
	Sphere::PTPointer cp = MakeSphere( const_cast<Sphere*>(this)->GetRadius() );
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
