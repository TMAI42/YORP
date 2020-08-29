#include "ShapeModel.h"

int main() {

	std::string path = "";//set your path

	ShapeModel astro1(path);

	auto [tauZ, tauEpsilon] = astro1.CalculateTaus(0);//set epsilon 

	std::cout << tauZ << " " << tauEpsilon << std::endl;

}