#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <memory>
#include <vtkImplicitFunction.h>
#include <vtkSmartPointer.h>
#include <boost/scoped_ptr.hpp>

class vtkSphere;

class Primitive {
public:
    typedef boost::scoped_ptr<Primitive> Pointer;
    virtual vtkImplicitFunction *getFunction(void) const {return m_func;}

protected:
    vtkSmartPointer< vtkImplicitFunction > m_func;
};

class Sphere : public Primitive {
public:
	typedef boost::scoped_ptr<Sphere> Pointer;
	Sphere(double r);
};




/*

class CubeNode : public PrimitiveNode {
	bool center;
	Float3 dim;
public:
	CubeNode(const Float3 &dim, bool center=false, const Props p=Props())
	  :PrimitiveNode(1,p), center(center), dim(dim) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class SphereNode : public PrimitiveNode, public Accuracy {
	double r;
public:
	typedef shared_ptr<SphereNode> Pointer;
	SphereNode(double r, const Accuracy &acc=Accuracy(), const Props p=Props())
	  :PrimitiveNode(1,p), Accuracy(acc), r(r) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class CylinderNode : public PrimitiveNode, public Accuracy {
	bool center;
	double r1,r2;
	double h;
public:
	typedef shared_ptr<CylinderNode> Pointer;
	CylinderNode(double r1, double r2, double h, bool center=false, const Accuracy &acc=Accuracy(), const Props p=Props())
	  :PrimitiveNode(1,p), Accuracy(acc), center(center), r1(r1), r2(r2), h(h) {}
	CylinderNode(double r, double h, bool center=false, const Accuracy &acc=Accuracy(), const Props p=Props())
	  :PrimitiveNode(1,p), Accuracy(acc), center(center), r1(r), r2(r), h(h) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class PolyhedronNode : public PrimitiveNode {
	Vec3D points;
	VecPaths triangles;
public:
	PolyhedronNode(const Vec3D &points, const VecPaths &triangles, int convexity, const Props p=Props())
	  :PrimitiveNode(convexity,p), points(points), triangles(triangles) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class SquareNode : public PrimitiveNode {
	bool center;
	Float2 dim;
public:
	SquareNode(const Float2 &dim, bool center, const Props p=Props())
	  :PrimitiveNode(1,p), center(center), dim(dim) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class CircleNode : public PrimitiveNode, public Accuracy {
	double r;
public:
	typedef shared_ptr<CircleNode> Pointer;
	CircleNode(double r, const Accuracy &acc=Accuracy(), const Props p=Props())
	  :PrimitiveNode(1,p), Accuracy(acc), r(r) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

class PolygonNode : public PrimitiveNode {
	Vec2D points;
	VecPaths paths;
public:
	PolygonNode(const Vec2D &points, const VecPaths &paths, int convexity, const Props p=Props())
	  :PrimitiveNode(convexity,p), points(points), paths(paths) {}
	virtual PolySet *render_polyset(render_mode_e mode) const;
	virtual QString dump(QString indent) const;
};

*/
#endif
