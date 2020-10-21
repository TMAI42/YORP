#pragma once

#include "RayEmitter.h"
#include "ShapeModel.h"
template<size_t numberOfRays, size_t integralSteps>
class Tracer{
public:
	static void Trace( ShapeModel& object, double epsilon = 0);

private:
	static bool inline Intersection(Ray& current, ShapeModel& object, Vec3D& torqe);
	static void inline ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay, Vec3D& torqe,
		const Vec3D& surfaceNormal, const Vec3D& vectorInSurf);

};


