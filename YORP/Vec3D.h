#pragma once
#include <math.h>

enum class Vertices
{
	X = 1,
	Y = 2, 
	Z = 3 
};


class Vec3D {
public:
	Vec3D(double x, double y, double z);
	~Vec3D() = default;
	
	static Vec3D VectorProduct(const Vec3D& a, const Vec3D& b);

	double operator* (const Vec3D& b) const ;
	Vec3D operator+ (const Vec3D& b);
	Vec3D operator- (const Vec3D& b);
	Vec3D operator/ (double denum);
	Vec3D operator* (double a);

	const double operator[](Vertices vertex) const;
	double operator[](Vertices vertex);

	double GetLength() const;

private:
		double X, Y, Z;
};

