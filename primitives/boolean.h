#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "primitive.h"
#include <vtkImplicitBoolean.h>
#include <list>
#include <boost/make_shared.hpp>

class Boolean : public Primitive {
protected:
	typedef std::list<Primitive::Const_Pointer> PrimCon;
public:
    	typedef boost::shared_ptr<Boolean> Pointer;
    	typedef boost::shared_ptr<const Boolean> Const_Pointer;
	Boolean(int operationType=0);
	Boolean(Primitive::Const_Pointer object1, Primitive::Const_Pointer object2, int operationType);
	Boolean(const PrimCon &children, int operationType);
	void addObject(Primitive::Const_Pointer object);
    	virtual BoundingBox getBoundingBox() const = 0;
protected:
	PrimCon m_children;
	void copyChildren(Boolean::Const_Pointer other);
};

template <int operationType>
class SpecificBoolean : public Boolean {
public:
	SpecificBoolean();
	SpecificBoolean(Primitive::Pointer object1, Primitive::Pointer object2);
	SpecificBoolean(const PrimCon &children);
    	virtual BoundingBox getBoundingBox() const;
    	virtual Primitive::Pointer getCopy() const;
protected:
}; 

template<int operationType>
SpecificBoolean<operationType>::SpecificBoolean():Boolean(operationType) {}
template<int operationType>
SpecificBoolean<operationType>::SpecificBoolean(Primitive::Pointer object1, Primitive::Pointer object2)
	:Boolean(object1, object2, operationType) {}
template<int operationType>
SpecificBoolean<operationType>::SpecificBoolean(const PrimCon &children):Boolean(children, operationType) {}
template<int operationType>
BoundingBox SpecificBoolean<operationType>::getBoundingBox() const {}
template<int operationType>
Primitive::Pointer SpecificBoolean<operationType>::getCopy() const {
	return boost::make_shared< SpecificBoolean<operationType> >(m_children); }

typedef SpecificBoolean<VTK_UNION> Union;
typedef SpecificBoolean<VTK_INTERSECTION> Intersection;
typedef SpecificBoolean<VTK_DIFFERENCE> Difference;

Boolean::Pointer MakeUnion(Primitive::Pointer object1, Primitive::Pointer object2);
Boolean::Pointer MakeIntersection(Primitive::Pointer object1, Primitive::Pointer object2);
Boolean::Pointer MakeDifference(Primitive::Pointer object1, Primitive::Pointer object2);

#endif
