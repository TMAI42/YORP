#pragma once

#include "Vec3D.h"
#include "Ray.h"
#include <list>

template<size_t numberOfRays>
class RayEmitter {
public:
	RayEmitter(double radius);
	RayEmitter(double radius, double phi, double teta, double epsilon);

	~RayEmitter() = default;

	std::list<Ray> rays;
};

