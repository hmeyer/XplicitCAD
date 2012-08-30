#include "primitive.h"

Primitive::Primitive() {}
Primitive::Primitive(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
	:m_bbox(xMin,xMax,yMin,yMax,zMin,zMax) {}

