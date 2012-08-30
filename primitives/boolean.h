#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "primitive.h"
#include <list>

class Boolean : public Primitive {
public:
	Boolean(Primitive::Pointer object, int operationType=0);
	void addObject(Primitive::Pointer object);
    	virtual BoundingBox getBoundingBox() const = 0;
protected:
	std::list<Primitive::Pointer> m_children;
};

class Union : public Boolean { }; 
class Intersection : public Boolean {
	Intersection(Primitive::Pointer object);
}; 
class Difference : public Boolean {
	Difference(Primitive::Pointer object);
}; 

#endif
