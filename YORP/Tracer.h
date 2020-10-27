#pragma once

#include "RayEmitter.h"
#include "RayEmitter.cpp"
#include "ShapeModel.h"
template<size_t numberOfRays, size_t integralSteps>
class Tracer{
public:
	void Trace( ShapeModel& object, double epsilon = 0);
	double TraceTest(ShapeModel& object);

private:
	bool inline Intersection(Ray& current, ShapeModel& object, Vec3D& torqe);
	void inline ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay, Vec3D& torqe,
		const Vec3D& surfaceNormal, const Vec3D& vectorInSurf);

};


