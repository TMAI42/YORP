#include "RayEmitter.h"
#include <math.h>

/*divide circle o 4 parts becouse o semetry*/
/*calculate corrent number of rays*/
template<size_t numberOfRays>
RayEmitter<numberOfRays>::RayEmitter(double radius) {
	/*TODO: PI in individual header*/
	double delta =sqrt(3.1459265358979323846 * radius * radius / numberOfRays);

	rays.emplace({ {radius + 10, 0, 0}, {-1, 0,0} });

	for (long n = 1; n * delta <= radius; n++) {
		rays.emplace({ {radius + 10, n * delta, 0}, {-1, 0,0} });
		rays.emplace({ {radius + 10, -n * delta, 0}, {-1, 0,0} });
		rays.emplace({ {radius + 10,  0, n * delta}, {-1, 0,0} });
		rays.emplace({ {radius + 10,  0, -n * delta}, {-1, 0,0} });
		
	}

	for (long n = 1; n * delta <= radius; n++) {
		for (long m = 1; (n * n + m * m) * delta * delta <= radius * radius; m++) {
			rays.emplace({ {radius + 10, n * delta, m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, n * delta, -m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, -n * delta, m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, -n * delta, -m * delta}, {-1, 0, 0} });
		}
	}
}

template<size_t numberOfRays>
RayEmitter<numberOfRays>::RayEmitter(double radius, double phi, double teta, double epsilon) :RayEmitter(radius) {
	double delta = sqrt(3.1459265358979323846 * radius * radius / numberOfRays);

	double RoatrionMatrix[3][3];
	/*  
	| r[0][0]   r[0][1]   r[0][2]  |
	| r[1][0]   r[1][1]   r[1][2]  |
	| r[2][0]   r[2][1]   r[2][2]  |
	*/

	{
		/*Rotation constants*/
		double cosPhi = cos(phi);
		double cosTeta = cos(teta);
		double cosEpsilon = cos(epsilon);

		double sinPhi = sin(phi);
		double sinTeta = sin(teta);
		double sinEpsilon = sin(epsilon);

		RoatrionMatrix = {
			{cosPhi * cosTeta - cosEpsilon * sinPhi * sinTeta, -cosTeta * sinPhi - cosPhi * cosEpsilon * sinTeta, sinEpsilon * sinTeta},
			{cosEpsilon * cosTeta * sinPhi + cosPhi * sinTeta, cosPhi * cosEpsilon * cosTeta - sinPhi * sinTeta, -cosTeta * sinEpsilon},
			{sinPhi * sinEpsilon, cosPhi * sinEpsilon, cosEpsilon}
		}
	}


	rays.emplace({ {radius + 10, 0, 0}, {-1, 0, 0} });

	for (long n = 1; n * delta <= radius; n++) {
		rays.emplace({ {radius + 10, n * delta, 0}, {-1, 0,0} });
		rays.emplace({ {radius + 10, -n * delta, 0}, {-1, 0,0} });
		rays.emplace({ {radius + 10,  0, n * delta}, {-1, 0,0} });
		rays.emplace({ {radius + 10,  0, -n * delta}, {-1, 0,0} });

	}

	for (long n = 1; n * delta <= radius; n++) {
		for (long m = 1; (n * n + m * m) * delta * delta <= radius * radius; m++) {
			rays.emplace({ {radius + 10, n * delta, m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, n * delta, -m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, -n * delta, m * delta}, {-1, 0, 0} });
			rays.emplace({ {radius + 10, -n * delta, -m * delta}, {-1, 0, 0} });
		}
	}
}
