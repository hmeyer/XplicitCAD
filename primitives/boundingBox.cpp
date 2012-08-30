#include "boundingBox.h"

BoundingBox::BoundingBox():vtkBoundingBox() {}
BoundingBox::BoundingBox(const BoundingBox &bbox):vtkBoundingBox(bbox) {}
BoundingBox::BoundingBox (double bounds[6]):vtkBoundingBox(bounds) {}
BoundingBox::BoundingBox (double xMin, double xMax, double yMin, double yMax, double zMin, double zMax)
	:vtkBoundingBox(xMin,xMax,yMin,yMax,zMin,zMax) {}

