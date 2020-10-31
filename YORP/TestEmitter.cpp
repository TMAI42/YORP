#include "TestEmitter.h"

template<size_t numberOfRays>
TestEmitter<numberOfRays>::TestEmitter(double radius){
	double delta = sqrt(3.1459265358979323846 * radius * radius / numberOfRays);

	rays.push_back({ {radius + 10, 0, 0}, {-1, 0,0} });

	for (long n = 1; n * delta <= radius; n++) {
		rays.push_back({ {radius + 10, n * delta, 0}, {-1, 0,0} });
		rays.push_back({ {radius + 10, -n * delta, 0}, {-1, 0,0} });
		rays.push_back({ {radius + 10,  0, n * delta}, {-1, 0,0} });
		rays.push_back({ {radius + 10,  0, -n * delta}, {-1, 0,0} });

	}
}