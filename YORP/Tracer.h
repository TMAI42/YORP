#pragma once

#include "RayEmitter.h"
#include "RayEmitter.cpp"

#include "TestEmitter.h"
#include "TestEmitter.cpp"

#include "ShapeModel.h"

template<size_t numberOfRays, size_t integralSteps>
class Tracer{
public:
	std::tuple<double,double> Trace( ShapeModel& object, double epsilon = 0);
	double TraceTest(ShapeModel& object);
	double TracerTestWithTestEmitter(ShapeModel& object);

private:
	bool inline Intersection(Ray& current, ShapeModel& object, Vec3D& torqe, double& yarc, const Vec3D& orbit);
	void inline ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay, Vec3D& torqe,
		const Vec3D& surfaceNormal, const Vec3D& vectorInSurf, double& yarc, const Vec3D& orbit);

};


