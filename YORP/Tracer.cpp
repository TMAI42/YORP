#include "Tracer.h"
#include <ctime>
#include <limits>

template<size_t numberOfRays, size_t integralSteps>
void Tracer<numberOfRays, integralSteps>::Trace(ShapeModel& object, double epsilon) {
	Vec3D torqe = { 0, 0, 0 };

	double angleStep = 2 * 3.14159265358979323846 / integralSteps;
	for (int i = 0; i < integralSteps; i++) {
		for (int j = 0; j < integralSteps; j++) {

			RayEmitter<numberOfRays> emitter{ object.maxRadius, i * angleStep, j * angleStep, epsilon };

			while (!emitter.rays.empty()) {
				int num = emitter.rays.size();
				for (std::list<Ray>::iterator current = emitter.rays.begin();
					current != emitter.rays.end();) {
					if (!Intersection(*current, object, torqe)) {
						current = emitter.rays.erase(current);
					}
				}
			}
		}
	}

	torqe = torqe * (3.14159265359265 * object.maxRadius * object.maxRadius) / (object.averageRadius * object.averageRadius * object.averageRadius);
	object.tauZ.insert({ epsilon, torqe[Vertices::Z] });
}

template<size_t numberOfRays, size_t integralSteps>
double Tracer<numberOfRays, integralSteps>::TraceTest(ShapeModel& object) {
	Vec3D torqe = { 0, 0, 0 };
	RayEmitter<numberOfRays> emitter{ object.maxRadius };
	int num = emitter.rays.size();
	while (!emitter.rays.empty()) {
		
		for (std::list<Ray>::iterator current = emitter.rays.begin();
			current != emitter.rays.end();) {
			if (!Intersection(*current, object, torqe)) {
				current = emitter.rays.erase(current);
			}
		}
	}
	return torqe[Vertices::Z] *
		(3.14159265359265 * object.maxRadius * object.maxRadius) /
		(object.averageRadius * object.averageRadius * object.averageRadius)/num;
}

template<size_t numberOfRays, size_t integralSteps>
inline bool Tracer<numberOfRays, integralSteps>::Intersection(Ray& current, ShapeModel& object, Vec3D& torqe) {

	double u{ 0 }, v{ 0 }, t{ DBL_MAX }, tempT{ 0 };
	bool intersectionFlag{ false };
	Vec3D intersectionPoint{ 0,0,0 };
	Vec3D normilizedInetrsectSurf{ 0,0,0 };
	Vec3D normilizedVecInSurf{ 0,0,0 };

	for (int i = 0; i < object.numberOfFacets; ++i) {
		if (object.pairsVecSurfase[i].second * current.direction > 0)
			continue;

		Vec3D firstVectorOfSurf = object.vertices[std::get<1>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];
		Vec3D secondVectorOfSurf = object.vertices[std::get<2>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];
		Vec3D tVector = current.startPoint - object.vertices[std::get<0>(object.indexes[i])];
		Vec3D pVector = Vec3D::VectorProduct(current.direction, secondVectorOfSurf);
		Vec3D qVector = Vec3D::VectorProduct(tVector, firstVectorOfSurf);

		double det = firstVectorOfSurf * pVector;

		tempT = secondVectorOfSurf * qVector / det;
		if (tempT < 0.0 || t < tempT) continue;


		u = pVector * tVector / det;
		if (u < 0.0) continue;

		v = qVector * current.direction / det;
		if (v < 0.0 || u + v > 1)
			continue;

		t = tempT;
		intersectionFlag = true;
		intersectionPoint = object.vertices[std::get<0>(object.indexes[i])] * (1 - u - v) +
			object.vertices[std::get<1>(object.indexes[i])] * u +
			object.vertices[std::get<2>(object.indexes[i])] * v;

		normilizedInetrsectSurf = object.pairsVecSurfase[i].second / object.pairsVecSurfase[i].second.GetLength();
		normilizedVecInSurf = firstVectorOfSurf / firstVectorOfSurf.GetLength();
	}
	if (intersectionFlag) {
		ReflectLambert(intersectionPoint, current, torqe, normilizedInetrsectSurf, normilizedVecInSurf);
		return true;
	}

	return false;
}

template<size_t numberOfRays, size_t integralSteps>
inline void Tracer<numberOfRays, integralSteps>::ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay, Vec3D& torqe,
	const Vec3D& surfaceNormal, const Vec3D& vectorInSurf) {

	const double PI = 3.14159265358979232846;

	Vec3D momentum = reflectingRay.direction * (-1);

	reflectingRay.startPoint = intersectionPoint;

	std::srand(time(nullptr));
	double randomVariable1 = std::rand() % 100 / 100.;
	double randomVariable2 = std::rand() % 100 / 100.;

	/*
	Diatribution for angles in Lambert`s reflection
	For phi is 2PI multiplied by random value in interval [0;1]
	For teta, because of irregularity caused by surface os sphere is 1/2 * arccos(1 - 2 * p), where p is random value in interval [0;1]
	*/
	double phi = 2 * PI * randomVariable1;
	double teta = acos(1 - 2 * randomVariable2) / 2.;

	/*
	Create normilized refleted vector with shpere cordenates
	This relection equivalent to generating random vector with random teta and phi
	*/
	double nonRotetedX = sin(teta) * cos(phi);
	double nonRotetedY = sin(teta) * sin(phi);
	double nonRotetedZ = cos(teta);

	/*
	Transform random vector with rotatin matrix represented by transformation of (XYZ) to (X`Y`Z`)
	X` - normilize vector in reflectin surface
	Y` - vector product of normilized vector of reflection surface and normilize vector in reflectin surface
	Z` - normilized vector of reflection surface
	*/
	Vec3D newEY = Vec3D::VectorProduct(surfaceNormal, vectorInSurf);
	double transformaionMatrix[3][3] =
	{ {vectorInSurf[Vertices::X], newEY[Vertices::X], surfaceNormal[Vertices::X]},
		{vectorInSurf[Vertices::Y], newEY[Vertices::Y], surfaceNormal[Vertices::Y]},
		{vectorInSurf[Vertices::Z], newEY[Vertices::Z], surfaceNormal[Vertices::Z]} };

	reflectingRay.direction = {
		transformaionMatrix[0][0] * nonRotetedX + transformaionMatrix[0][1] * nonRotetedY + transformaionMatrix[0][2] * nonRotetedZ,
		transformaionMatrix[1][0] * nonRotetedX + transformaionMatrix[1][1] * nonRotetedY + transformaionMatrix[1][2] * nonRotetedZ,
		transformaionMatrix[2][0] * nonRotetedX + transformaionMatrix[2][1] * nonRotetedY + transformaionMatrix[2][2] * nonRotetedZ
	};

	momentum = momentum + reflectingRay.direction;

	torqe = torqe + Vec3D::VectorProduct(intersectionPoint, momentum);
}

