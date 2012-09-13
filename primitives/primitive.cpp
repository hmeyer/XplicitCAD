#include "primitive.h"
#include <vtkTransform.h>
#include <vtkImplicitFunction.h>

int objs=0;

Primitive::Primitive() {
  objs++;
  std::cerr << "Primitive():" << this << " " << objs << std::endl;
}

Primitive::~Primitive() {
  objs--;
  std::cerr << "~Primitive():" << this << " " << objs << std::endl;
}

const vtkImplicitFunction *Primitive::vtk() const {
  return dynamic_cast<const vtkImplicitFunction*>(this);
}

vtkImplicitFunction *Primitive::vtk() {
  return dynamic_cast<vtkImplicitFunction*>(this);
}



void Primitive::setBounds(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax) {
	m_bbox.SetBounds(xMin, xMax, yMin, yMax, zMin, zMax);
	m_bbox.Inflate(1);
}

BoundingBox Primitive::getBounds() const { return m_bbox;}

Primitive::Pointer Primitive::translate(double x, double y, double z) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->Translate(x,y,z);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}

Primitive::Pointer Primitive::scale(double x, double y, double z) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	if (z != z) { // NaN
	  z = x;
	  if (y != y) // NaN
	    y = x;
	}
	trans->Scale(1./x,1./y,1./z);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}

Primitive::Pointer Primitive::rotateX(double a) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->RotateX(a);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}
Primitive::Pointer Primitive::rotateY(double a) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->RotateY(a);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}
Primitive::Pointer Primitive::rotateZ(double a) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->RotateZ(a);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}
Primitive::Pointer Primitive::rotateAxis(double a, double x, double y, double z) const {
	Primitive::Pointer transformed = this->copy();
	vtkSmartPointer<vtkTransform> trans = vtkTransform::SafeDownCast(transformed->vtk()->GetTransform());
	if (!trans) trans = vtkSmartPointer<vtkTransform>::New();
	trans->RotateWXYZ(a,x,y,z);
	transformed->vtk()->SetTransform(trans);
	return transformed;
}

Primitive::Pointer Primitive::copy() const {
	Primitive::Pointer cp = copyWithoutTransform();
	cp->vtk()->SetTransform( const_cast<Primitive*>(this)->vtk()->GetTransform() );
	return cp;
}

