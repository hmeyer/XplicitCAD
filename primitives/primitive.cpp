#include "primitive.h"
#include <vtkTransform.h>

Primitive::Primitive() {}
Primitive::Primitive(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
	:m_bbox(xMin,xMax,yMin,yMax,zMin,zMax) {}

Primitive::Primitive(const Primitive &other) {}

Primitive::Pointer Primitive::copy() const {
	Pointer cp = getCopy();
	cp->copyTransform(*this);
	return cp;
}

Primitive::Pointer Primitive::translate(double x, double y, double z) const {
	Pointer translated = copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(translated->getFunction()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->Translate(x,y,z);
	translated->getFunction()->SetTransform(trans);
	return translated;
}

void Primitive::copyTransform(const Primitive &source) {
	if (m_func) 
		m_func->SetTransform( source.getFunction()->GetTransform() );
}
/*
Primitive::Pointer Primitive::translate(double x, double y, double z) const {
	
}
*/
