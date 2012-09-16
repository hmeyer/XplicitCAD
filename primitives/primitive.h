#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vtkImplicitFunction.h>
#include <vtkBoundingBox.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include "boundingBox.h"
#include <limits>
#include <boost/shared_ptr.hpp>

class vtkImplicitFunction;
class PrimitiveDeleter;

class VTK_FILTERING_EXPORT Primitive {
public:
	typedef boost::shared_ptr<Primitive> PPointer;
	Primitive();
	virtual ~Primitive();
    	virtual BoundingBox getBounds() const;
	void setBounds(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
	virtual void updateBounds() = 0;
    	virtual Primitive::PPointer copy() const;
    	virtual Primitive::PPointer copyWithoutTransform() const = 0;
    	Primitive::PPointer translate(double x, double y, double z) const;
    	Primitive::PPointer scale(double x, double y=std::numeric_limits< double >::quiet_NaN(), double z=std::numeric_limits< double >::quiet_NaN()) const;
    	Primitive::PPointer rotateX(double a) const;
    	Primitive::PPointer rotateY(double a) const;
    	Primitive::PPointer rotateZ(double a) const;
    	Primitive::PPointer rotateAxis(double a, double x, double y, double z) const;
	const vtkImplicitFunction *vtk() const;
	vtkImplicitFunction *vtk();
protected:
    	BoundingBox m_bbox;
};

class PrimitiveDeleter {
public:
  void operator()(Primitive *p) {
    std::cerr << "Deleter Called:" << p << " refcount:" << p->vtk()->GetReferenceCount() << std::endl;
    p->vtk()->Delete();
  }
};


template< class vtkImplicit >
class VTK_FILTERING_EXPORT PrimitiveTemplate: public vtkImplicit, public Primitive {
public:
	typedef boost::shared_ptr<PrimitiveTemplate> PTPointer;
	PrimitiveTemplate() {}
    	PrimitiveTemplate(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
		:Primitive(xMin,xMax,yMin,yMax,zMin,zMax) {}
	static PrimitiveTemplate *New();
	virtual double EvaluateFunction(double x[3]);
	virtual void EvaluateGradient(double x[3], double g[3]);
	virtual void updateBounds();
    	virtual Primitive::PPointer copyWithoutTransform() const;
	PTPointer smartP();
};

template< class vtkImplicit >
double PrimitiveTemplate< vtkImplicit >::EvaluateFunction(double x[3]) {
	if (m_bbox.ContainsPoint(x)) return vtkImplicit::EvaluateFunction(x);
	else return std::numeric_limits<double>::max();
}

template< class vtkImplicit >
void PrimitiveTemplate< vtkImplicit >::EvaluateGradient(double x[3], double g[3]) {
	if (m_bbox.ContainsPoint(x)) vtkImplicit::EvaluateGradient(x, g);
	else { g[0] = g[1] = g[2] = 0; }
}


template< class vtkImplicit >
typename PrimitiveTemplate< vtkImplicit >::PTPointer PrimitiveTemplate< vtkImplicit >::smartP() {
  PrimitiveDeleter d;
  PTPointer p(this, d);
  return p;
}


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
