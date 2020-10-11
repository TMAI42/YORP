#include "Vec3D.h"

Vec3D::Vec3D(double x, double y, double z) :X(x), Y(y), Z(z) {}

Vec3D Vec3D::VectorProduct(const Vec3D& a, const Vec3D& b) {
	return { a.Y * b.Z - a.Z * b.Y,
		a.X * b.Z - a.Z * b.X,
		a.X * b.Y - a.Y * b.X };
}

double Vec3D::operator*(const Vec3D& b) const {
	return X * X + Y * Y + Z * Z;
}

Vec3D Vec3D::operator+(const Vec3D& b) {
	return { X + b.X, Y + b.Y, Z + b.Z };
}

Vec3D Vec3D::operator-(const Vec3D& b) {
	return { X - b.X, Y - b.Y, Z - b.Z };
}

Vec3D Vec3D::operator/(double denum) {
	return { X / denum, Y / denum, Z / denum };;
}

Vec3D Vec3D::operator*(double a)
{
	return {a*X, a*Y, a*Z};
}

const double Vec3D::operator[](Vertices vertex) const {
	switch (vertex) {
	case Vertices::X:
		return X;
	case Vertices::Y:
		return Y;
	case Vertices::Z:
		return Z;
	default:
		return 0.0;
	}
}

double Vec3D::operator[](Vertices vertex) {
	switch (vertex) {
	case Vertices::X:
		return X;
	case Vertices::Y:
		return Y;
	case Vertices::Z:
		return Z;
	default:
		return 0.0;
	}
}

double Vec3D::GetLength() const {
	return sqrt(*this * *this);
}

