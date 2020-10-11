#pragma once
#include "Vec3D.h"
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

class ShapeModel {
	friend class Tracer;

public:
	ShapeModel(std::string pathName);
	~ShapeModel() = default;

	std::pair<double, double> CalculateTaus(double epsilon);

	std::map<double, double> GetCalculatedTauZ();
	std::map<double, double> GetCalculatedTauEpsilon();
	
private:

	const double PI = 3.141592653589793238;

	int numberOfVrtices, numberOfFacets;

	double averageRadius;

	std::vector<Vec3D> vertices;
	std::vector<std::tuple<int, int, int>> indexes;

	std::vector<std::pair<Vec3D, Vec3D>> pairsVecSurfase;
	std::map<double, double> tauZ, tauEpsilon;

};

