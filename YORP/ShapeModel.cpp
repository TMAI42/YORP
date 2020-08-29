#include "ShapeModel.h"

ShapeModel::ShapeModel(std::string pathName)
{
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

			vertices.push_back({ x*1000, y*1000, z*1000 });
		}

		double volume = 0;

		for (int j = 0; j < this->numberOfFacets; j++) {
			int a, b, c;

			for (int i = 0; i < 3; i++)
				file >> a >> b >> c;

			indexes.push_back({ a, b, c });

			pairsVecSurfase.push_back({ (vertices[a] + vertices[b] + vertices[c]) / 3,
				Vec3D::VectorProduct(vertices[b] - vertices[a], vertices[c] - vertices[a]) / 2 });

			volume += (pairsVecSurfase[j].first * pairsVecSurfase[j].second) / 2;
		}
		//aver
		maxRadius = pow(3. * volume / 4. / PI, 1. / 3.);
	}

	file.close();
}

std::pair<double, double> ShapeModel::CalculateTaus(double epsilon) {

	const int Nintegral = 100;
	double p_z = 0;
	double p_sin = 0;
	double cosetha, sinetha, cosdelta, sindelta, cospsi, sinpsi, psi;

	double tauZTemp = 0.;
	double tauEpsilonTemp = 0.;

	for (const auto& surf : pairsVecSurfase) {

		sinpsi = surf.second[Vertices::Z] / sqrt(surf.second.GetLength() + 0.0000000001);
		//+0 needed because some asteroids presumably have facets of 0 area
		cospsi = sqrt(1 - sinpsi * sinpsi);
		sinetha = surf.first[Vertices::Z] / sqrt(surf.first.GetLength());
		cosetha = sqrt(1 - sinetha * sinetha);
		//ask for this
		sindelta = Vec3D::VectorProduct(surf.second, surf.first)[Vertices::Z] /
			sqrt(surf.first[Vertices::X] * surf.first[Vertices::X] +
				surf.first[Vertices::Y] * surf.first[Vertices::Y]) /
			sqrt(surf.second[Vertices::X] * surf.second[Vertices::X] +
			surf.second[Vertices::Y] * surf.second[Vertices::Y] + 0.0000000001);

		p_z = 0.;
		p_sin = 0.;
		//add sin cos 
		//phhi-> phi

		for (long int j = 1; j <= Nintegral; j++)
		{
			double phhi = -(PI / 2) + PI * (2. * j - 1.) / 2. / Nintegral;
			p_z += (PI / Nintegral) * sqrt(1 - (sin(phhi) * cospsi * sin(epsilon) -
				sinpsi * cos(epsilon)) * (sin(phhi) * cospsi * sin(epsilon) - sinpsi * cos(epsilon)));
			p_sin += (PI / Nintegral) * sin(phhi) * sqrt(1 - (sin(phhi) * cospsi * sin(epsilon) - 
				sinpsi * cos(epsilon)) * (sin(phhi) * cospsi * sin(epsilon) - sinpsi * cos(epsilon)));
		}

		p_z = 2. / 3. / PI / PI * p_z;
		p_sin = 2. / 3. / PI / PI * p_sin;

		//computing axial and obliquity components of YORP
		tauZTemp += (Vec3D::VectorProduct(surf.second, surf.first)[Vertices::Z]) * p_z; // YORP torque axial component

		tauEpsilonTemp += -sqrt(surf.first.GetLength()) * sqrt(surf.second.GetLength()) * sinpsi * cosetha * sindelta * p_sin;// YORP torque obliquity component
	
	}

	tauZ.insert({ epsilon, tauZTemp });
	tauEpsilon.insert({ epsilon, tauEpsilonTemp });

	return { tauZTemp, tauEpsilonTemp };
}

std::map<double, double> ShapeModel::GetCalculatedTauZ()
{
	return tauZ;
}

std::map<double, double> ShapeModel::GetCalculatedTauEpsilon()
{
	return tauEpsilon;
}
