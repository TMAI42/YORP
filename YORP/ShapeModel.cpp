#include "ShapeModel.h"

ShapeModel::ShapeModel(std::string pathName) {

	std::ifstream file(pathName);

	if (!file.is_open()) {
		std::cout << "bad file!" << std::endl;
	}
	else {

		file >> this->numberOfVrtices;
		file >> this->numberOfFacets;

		for (int j = 0; j < this->numberOfVrtices; j++) {

			double x, y, z;

			file >> x >> y >> z;

			this->vertices.push_back({ x , y , z });

			this->maxRadius = (maxRadius > this->vertices[j].GetLength()) ? maxRadius : vertices[j].GetLength();
		}


		double volume = 0;

		for (int j = 0; j < this->numberOfFacets; j++) {
			int a, b, c;

			file >> a >> b >> c;

			this->indexes.push_back({ a - 1, b - 1, c - 1 });

			this->pairsVecSurfase.push_back({ (this->vertices[a - 1] + this->vertices[b - 1] + this->vertices[c - 1]) / 3,
				Vec3D::VectorProduct(this->vertices[b - 1] - this->vertices[a - 1], this->vertices[c - 1] - this->vertices[a - 1]) / 2 });

			volume += (this->pairsVecSurfase[j].first * this->pairsVecSurfase[j].second) / 2;
		}

		this->averageRadius = pow(3. * volume / 4. / PI, 1. / 3.);
	}

	file.close();

}

double ShapeModel::CalculateTaus(double epsilon) {

	const int Nintegral = 100;
	double p_z = 0;
	double p_sin = 0;
	double cosetha, sinetha, cosdelta, sindelta, cospsi, sinpsi, psi;

	double tauZTemp = 0.;
	double tauEpsilonTemp = 0.;

	for (const auto& [vecorToSurface, surfaceVector] : this->pairsVecSurfase) {

		sinpsi = surfaceVector[Vertices::Z] / (surfaceVector.GetLength() + 0.0000000001);
		//+0 needed because some asteroids presumably have facets of 0 area
		cospsi = sqrt(1 - sinpsi * sinpsi);
		sinetha = vecorToSurface[Vertices::Z] / (vecorToSurface.GetLength());
		cosetha = sqrt(1 - sinetha * sinetha);
		//ask for this
		sindelta = Vec3D::VectorProduct(surfaceVector, vecorToSurface)[Vertices::Z] /
			sqrt(vecorToSurface[Vertices::X] * vecorToSurface[Vertices::X] +
				vecorToSurface[Vertices::Y] * vecorToSurface[Vertices::Y]) /
			sqrt(surfaceVector[Vertices::X] * surfaceVector[Vertices::X] +
				surfaceVector[Vertices::Y] * surfaceVector[Vertices::Y] + 0.0000000001);

		p_z = 0.;
		p_sin = 0.;
		//TODO: add sin cos 


		for (long int j = 1; j <= Nintegral; j++) {
			double phi = -(PI / 2) + PI * (2. * j - 1.) / 2. / Nintegral;
			p_z += (PI / Nintegral) * sqrt(1 - (sin(phi) * cospsi * sin(epsilon) -
				sinpsi * cos(epsilon)) * (sin(phi) * cospsi * sin(epsilon) - sinpsi * cos(epsilon)));
			p_sin += (PI / Nintegral) * sin(phi) * sqrt(1 - (sin(phi) * cospsi * sin(epsilon) -
				sinpsi * cos(epsilon)) * (sin(phi) * cospsi * sin(epsilon) - sinpsi * cos(epsilon)));
		}

		p_z = 2. / 3. / PI / PI * p_z;
		p_sin = 2. / 3. / PI / PI * p_sin;

		//computing axial and obliquity components of YORP
		// YORP torque axial component
		tauZTemp += (Vec3D::VectorProduct(surfaceVector, vecorToSurface)[Vertices::Z]) * p_z;

		// YORP torque obliquity component
		//tauEpsilonTemp += -sqrt(vecorToSurface.GetLength()) * sqrt(surfaceVector.GetLength()) * sinpsi * cosetha * sindelta * p_sin;

	}

	//this->tauZ.insert({ epsilon, tauZTemp });
	//this->tauEpsilon.insert({ epsilon, tauEpsilonTemp });

	return  tauZTemp * (3.14159265359265 * maxRadius * maxRadius) /
		(averageRadius * averageRadius * averageRadius);
}

std::map<double, double> ShapeModel::GetCalculatedTauZ() {
	return this->tauZ;
}

std::map<double, double> ShapeModel::GetCalculatedTauEpsilon() {
	return this->tauEpsilon;
}
