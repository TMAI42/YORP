#pragma once

#include "RayEmitter.h"
#include "ShapeModel.h"
template<size_t number>
class Tracer{
public:
	static void Trace(RayEmitter<number>& emitter, ShapeModel& object );

private:
	static bool inline Intersection(Ray& current, ShapeModel& object);
	static void inline ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay);

	static Vec3D Torqe;
};


