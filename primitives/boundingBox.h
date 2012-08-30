#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <vtkBoundingBox.h>

class BoundingBox: public vtkBoundingBox {
public:
	BoundingBox();
	BoundingBox(const BoundingBox &bbox);
	BoundingBox (double bounds[6]);
	BoundingBox (double xMin, double xMax, double yMin, double yMax, double zMin, double zMax);
};

#endif
