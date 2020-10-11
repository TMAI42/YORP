#include "Tracer.h"

template<size_t number>
void Tracer<number>::Trace(RayEmitter<number>& emitter, ShapeModel& object) {
	Torqe = { 0, 0, 0 };
	while (!emitter.rays.empty()) {
		for (std::list<Ray>::iterator current = emitter.rays.begin();
			current != emitter.rays.end(); current++) {
			if (!Intersection())
				emitter.rays.erase(current);
		}
	}
}

template<size_t number>
inline bool Tracer<number>::Intersection(Ray& current, ShapeModel& object) {
	for (int i = 0; i < object.numberOfFacets, ++i) {
		if (object.pairsVecSurfase[i].second * current.direction > 0)
			return false;

		Vec3D firstVectorOfSurf = object.vertices[std::get<1>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];
		Vec3D secondVectorOfSurf = object.vertices[std::get<2>(object.indexes[i])] - object.vertices[std::get<0>(object.indexes[i])];

		double det = firstVectorOfSurf * (current.direction - secondVectorOfSurf);

		/*intersection point */
		double u, v, t;

		u = Vec3D::VectorProduct(current.direction, current.startPoint - object.vertices[std::get<0>(object.indexes[i])];
		if (u < 0.0 || u > det)
			return false;

		v = current.direction * Vec3D::VectorProduct(current.startPoint - object.vertices[std::get<0>(object.indexes[i]));
		if (v < 0.0 || u + v > det)
			return false;

		t = secondVectorOfSurf * Vec3D::VectorProduct(current.startPoint - object.vertices[std::get<0>(object.indexes[i]));

		u *= (1 / det);
		v *= (1 / det);
		t *= (1 / det);

		ReflectLambert({ u, v, t }, current);
		return true;

	}
	return false;
}

template<size_t number>
inline void Tracer<number>::ReflectLambert(const Vec3D& intersectionPoint, Ray& reflectingRay) {

	Vec3D momentum = reflectingRay.startPoint * (3.14159265359265 * Rmax * Rmax) / (averageRadius * averageRadius * averageRadius);




	Torqe += Vec3D::VectorProduct(intersectionPoint, momentum);
}

