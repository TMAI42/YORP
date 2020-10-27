#include "RayEmitter.h"
#include <math.h>

/*divide circle o 4 parts becouse o semetry*/
/*calculate corrent number of rays*/
template<size_t numberOfRays>
RayEmitter<numberOfRays>::RayEmitter(double radius) {
	/*TODO: PI in individual header*/
	double delta = sqrt(3.1459265358979323846 * radius * radius / numberOfRays);

	rays.push_back({ {radius + 10, 0, 0}, {-1, 0,0} });

	for (long n = 1; n * delta <= radius; n++) {
		rays.push_back({ {radius + 10, n * delta, 0}, {-1, 0,0} });
		rays.push_back({ {radius + 10, -n * delta, 0}, {-1, 0,0} });
		rays.push_back({ {radius + 10,  0, n * delta}, {-1, 0,0} });
		rays.push_back({ {radius + 10,  0, -n * delta}, {-1, 0,0} });

	}

	for (long n = 1; n * delta <= radius; n++) {
		for (long m = 1; (n * n + m * m) * delta * delta <= radius * radius; m++) {
			rays.push_back({ {radius + 10, n * delta, m * delta}, {-1, 0, 0} });
			rays.push_back({ {radius + 10, n * delta, -m * delta}, {-1, 0, 0} });
			rays.push_back({ {radius + 10, -n * delta, m * delta}, {-1, 0, 0} });
			rays.push_back({ { radius + 10, -n * delta, -m * delta }, { -1, 0, 0 } });
		}
	}
}

template<size_t numberOfRays>
RayEmitter<numberOfRays>::RayEmitter(double radius, double phi, double teta, double epsilon) :RayEmitter(radius) {
	double delta = sqrt(3.1459265358979323846 * radius * radius / numberOfRays);

	
	/*
	| r[0][0]   r[0][1]   r[0][2]  |
	| r[1][0]   r[1][1]   r[1][2]  |
	| r[2][0]   r[2][1]   r[2][2]  |
	*/

	
		/*Rotation constants*/
		double cosPhi = cos(phi);
		double cosTeta = cos(teta);
		double cosEpsilon = cos(epsilon);

		double sinPhi = sin(phi);
		double sinTeta = sin(teta);
		double sinEpsilon = sin(epsilon);

		double roatrionMatrix[3][3] = {
			{cosPhi * cosTeta - cosEpsilon * sinPhi * sinTeta, -cosTeta * sinPhi - cosPhi * cosEpsilon * sinTeta, sinEpsilon * sinTeta},
			{cosEpsilon * cosTeta * sinPhi + cosPhi * sinTeta, cosPhi * cosEpsilon * cosTeta - sinPhi * sinTeta, -cosTeta * sinEpsilon},
			{sinPhi * sinEpsilon, cosPhi * sinEpsilon, cosEpsilon}
		};
	

	rays.push_back({
		{(radius + 10) * roatrionMatrix[0][0], (radius + 10) * roatrionMatrix[1][0], (radius + 10) * roatrionMatrix[2][0]},
		{-roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0]}
		});

	for (long n = 1; n * delta <= radius; n++) {
		rays.push_back({
			{radius + 10 * roatrionMatrix[0][0] + n * delta * roatrionMatrix[0][1],
			radius + 10 * roatrionMatrix[1][0] + n * delta * roatrionMatrix[1][1],
			radius + 10 * roatrionMatrix[2][0] + n * delta * roatrionMatrix[2][1]},
			{-roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0]} });

		rays.push_back({
			{radius + 10 * roatrionMatrix[0][0] - n * delta * roatrionMatrix[0][1],
			radius + 10 * roatrionMatrix[1][0] - n * delta * roatrionMatrix[1][1],
			radius + 10 * roatrionMatrix[2][0] - n * delta * roatrionMatrix[2][1]},
			{-roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0]} });

		rays.push_back({
			{ radius + 10 * roatrionMatrix[0][0] + n * delta * roatrionMatrix[0][2],
			radius + 10 * roatrionMatrix[1][0] + n * delta * roatrionMatrix[1][2],
			radius + 10 * roatrionMatrix[2][0] + n * delta * roatrionMatrix[2][2] },
			{ -roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0] } });

		rays.push_back({
			{radius + 10 * roatrionMatrix[0][0] - n * delta * roatrionMatrix[0][2],
			radius + 10 * roatrionMatrix[1][0] - n * delta * roatrionMatrix[1][2],
			radius + 10 * roatrionMatrix[2][0] - n * delta * roatrionMatrix[2][2]},
			{-roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0]} });

	}

	for (long n = 1; n * delta <= radius; n++) {
		for (long m = 1; (n * n + m * m) * delta * delta <= radius * radius; m++) {
			rays.push_back({
				{ radius + 10 * roatrionMatrix[0][0] + n * delta * roatrionMatrix[0][1] + m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[1][0] + n * delta * roatrionMatrix[1][1] + m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[2][0] + n * delta * roatrionMatrix[2][1] + m * delta * roatrionMatrix[0][2] },
				{ -roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0] }});

			rays.push_back({
				{ radius + 10 * roatrionMatrix[0][0] + n * delta * roatrionMatrix[0][1] - m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[1][0] + n * delta * roatrionMatrix[1][1] - m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[2][0] + n * delta * roatrionMatrix[2][1] - m * delta * roatrionMatrix[0][2] },
				{ -roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0] }});

			rays.push_back({
				{ radius + 10 * roatrionMatrix[0][0] - n * delta * roatrionMatrix[0][1] + m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[1][0] - n * delta * roatrionMatrix[1][1] + m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[2][0] - n * delta * roatrionMatrix[2][1] + m * delta * roatrionMatrix[0][2] },
				{ -roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0] }});

			rays.push_back({
				{ radius + 10 * roatrionMatrix[0][0] - n * delta * roatrionMatrix[0][1] - m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[1][0] - n * delta * roatrionMatrix[1][1] - m * delta * roatrionMatrix[0][2],
				radius + 10 * roatrionMatrix[2][0] - n * delta * roatrionMatrix[2][1] - m * delta * roatrionMatrix[0][2] },
				{ -roatrionMatrix[0][0], -roatrionMatrix[1][0], -roatrionMatrix[2][0] }});
		}
	}
}
