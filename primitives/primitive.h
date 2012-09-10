#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vtkImplicitFunction.h>
#include <vtkBoundingBox.h>
#include <vtkSmartPointer.h>
#include "boundingBox.h"
#include <limits>

class Primitive {
public:
	typedef vtkSmartPointer< vtkImplicitFunction > Pointer;
	typedef vtkSmartPointer< const vtkImplicitFunction > Const_Pointer;
	Primitive();
    	virtual BoundingBox getBounds() const;
	void setBounds(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
	virtual void updateBounds() = 0;
    	virtual Pointer copy() = 0;
//    	virtual Pointer translate(double x, double y, double z) const = 0;
protected:
    	BoundingBox m_bbox;
};

template< class vtkImplicit >
class VTK_FILTERING_EXPORT PrimitiveTemplate: public vtkImplicit, public Primitive {
public:
	PrimitiveTemplate() {}
    	PrimitiveTemplate(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
		:Primitive(xMin,xMax,yMin,yMax,zMin,zMax) {}
	static PrimitiveTemplate *New();
	virtual double EvaluateFunction(double x[3]);
	virtual void EvaluateGradient(double x[3], double g[3]);
	virtual void updateBounds();
    	virtual Pointer copy();
    	Pointer copyWithoutTransform();
//    	virtual Pointer translate(double x, double y, double z) const;
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
Primitive::Pointer PrimitiveTemplate< vtkImplicit >::copy() {
	Pointer cp = copyWithoutTransform();
	cp->SetTransform( this->GetTransform() );
	return cp;
}

/*

class Primitive {
public:
    typedef boost::shared_ptr<Primitive> Pointer;
    typedef boost::shared_ptr<const Primitive> Const_Pointer;
    Primitive();
    Primitive(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
    virtual vtkImplicitFunction *getFunction(void) const {return m_func;}
    virtual BoundingBox getBoundingBox() const { return m_bbox;}
    virtual ~Primitive() {}
    Pointer copy() const;
    Pointer translate(double x, double y, double z) const;

protected:
    virtual Pointer getCopy() const = 0;
    Primitive(const Primitive &other);
    void copyTransform(const Primitive &source);
    vtkSmartPointer< vtkImplicitFunction > m_func;
    BoundingBox m_bbox;
};

*/

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
