#include "Tracer.h"

template<size_t numberOfRays, size_t integralSteps>
void Tracer<numberOfRays, integralSteps>::Trace(ShapeModel& object,double epsilon) {
	Vec3D torqe = { 0, 0, 0 };
	
	double angleStep = 2 * 3.14159265358979323846 / integralSteps;
	for (int i = 0; i < integralSteps; i++) {
		for (int j = 0; j < integralSteps; i++) {

			RayEmitter<numberOfRays> emitter{object.maxRadius, i*angleStep, j*angleStep, epsilon};

			while (!emitter.rays.empty()) {
				for (std::list<Ray>::iterator current = emitter.rays.begin();
					current != emitter.rays.end(); current++) {
					if (!Intersection(*current, object, torqe))
						emitter.rays.erase(current);
				}
			}
		}
	}

	torqe *= (3.14159265359265 * Rmax * Rmax) / (averageRadius * averageRadius * averageRadius);

	
}

template<size_t numberOfRays, size_t integralSteps>
inline bool Tracer<numberOfRays, integralSteps>::Intersection(Ray& current, ShapeModel& object, Vec3D& torqe) {
	for (int i = 0; i < object.numberOfFacets, ++i) {
		if (object.pairsVecSurfase[i].second * current.direction > 0)
			return false;

		Vec3D firstVectorOfSurf = object.vertices[std::get<1>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];
		Vec3D secondVectorOfSurf = object.vertices[std::get<2>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];

		double det = firstVectorOfSurf * (current.direction - secondVectorOfSurf);

		/*intersection point */
		double u, v, t;

		u = Vec3D::VectorProduct(current.direction, current.startPoint - object.vertices[std::get<0>(object.indexes[i]]];
		if (u < 0.0 || u > det)
			return false;

		v = current.direction * Vec3D::VectorProduct(current.startPoint - object.vertices[std::get<0>(object.indexes[i]]);
		if (v < 0.0 || u + v > det)
			return false;

		t = secondVectorOfSurf * Vec3D::VectorProduct(current.startPoint - object.vertices[std::get<0>(object.indexes[i]]);

		u *= (1 / det);
		v *= (1 / det);
		t *= (1 / det);

		ReflectLambert({ u, v, t }, current, torqe);
		return true;

	}
	return false;
}

template<size_t numberOfRays, size_t integralSteps>
inline void Tracer<numberOfRays, integralSteps>::ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay, Vec3D& torqe,
	const Vec3D& surfaceNormal, const Vec3D& vectorInSurf) {

	const double PI = 3.14159265358979232846;

	Vec3D momentum = reflectingRay.startPoint ;

	reflectingRay.startPoint = intersectionPoint;

	std::srand(std::time(NULL));
	double randomVariable1 = std::rand() % 100/100.;
	double randomVariable2 = std::rand() % 100/100.;

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
	double transformaionMatrix[3][3] = { {},{},{} }

	torqe += Vec3D::VectorProduct(intersectionPoint, momentum);
}

