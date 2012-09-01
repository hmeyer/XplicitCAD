#ifndef BOOLEAN_H
#define BOOLEAN_H

#include "primitive.h"
#include <list>

class Boolean : public Primitive {
public:
    	typedef boost::shared_ptr<Boolean> Pointer;
	Boolean(Primitive::Pointer object, int operationType=0);
	void addObject(Primitive::Pointer object);
    	virtual BoundingBox getBoundingBox() const = 0;
	virtual Primitive::Pointer getCopy() const;
protected:
	std::list<Primitive::Pointer> m_children;
};

class Union : public Boolean {
public:
	Union(Primitive::Pointer object);
    	virtual BoundingBox getBoundingBox() const;
}; 

class Intersection : public Boolean {
public:
	Intersection(Primitive::Pointer object);
    	virtual BoundingBox getBoundingBox() const;
}; 
class Difference : public Boolean {
public:
	Difference(Primitive::Pointer object);
    	virtual BoundingBox getBoundingBox() const;
}; 

#endif
