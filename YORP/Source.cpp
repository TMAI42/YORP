#include "ShapeModel.h"

int main() {
	Vec3D a{ 3, 5,7 };
	for (int i = 1; i < 4; i++)
		a[static_cast<Vertices>(i)];
	ShapeModel q("qqqqq");
	auto f = q.CalculateTaus(0);
	f.first;
	f.second;
}