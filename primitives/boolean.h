#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "primitive.h"
#include <list>

class Boolean : public Primitive {
public:
    	typedef boost::shared_ptr<Boolean> Pointer;
	Boolean(int operationType=0);
	Boolean(Primitive::Const_Pointer object1, Primitive::Const_Pointer object2, int operationType=0);
	void addObject(Primitive::Const_Pointer object);
    	virtual BoundingBox getBoundingBox() const = 0;
	virtual Primitive::Pointer getCopy() const;
protected:
    	virtual Boolean::Pointer getCopyBase() const = 0;
	std::list<Primitive::Const_Pointer> m_children;
};

class Union : public Boolean {
public:
	Union();
	Union(Primitive::Pointer object1, Primitive::Pointer object2);
    	virtual BoundingBox getBoundingBox() const;
protected:
    	virtual Boolean::Pointer getCopyBase() const;
}; 

class Intersection : public Boolean {
public:
	Intersection();
	Intersection(Primitive::Pointer object1, Primitive::Pointer object2);
    	virtual BoundingBox getBoundingBox() const;
protected:
    	virtual Boolean::Pointer getCopyBase() const;
}; 

class Difference : public Boolean {
public:
	Difference();
	Difference(Primitive::Pointer object1, Primitive::Pointer object2);
    	virtual BoundingBox getBoundingBox() const;
protected:
    	virtual Boolean::Pointer getCopyBase() const;
}; 

Boolean::Pointer MakeUnion(Primitive::Pointer object1, Primitive::Pointer object2);
Boolean::Pointer MakeIntersection(Primitive::Pointer object1, Primitive::Pointer object2);
Boolean::Pointer MakeDifference(Primitive::Pointer object1, Primitive::Pointer object2);

#endif
