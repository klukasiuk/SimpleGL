#include "vector_SGL.h"

#define _USE_MATH_DEFINES
#include <math.h>


Vec2D::Vec2D()
{
	x = 0.0;
	y = 0.0;
}

Vec2D::Vec2D(double X, double Y)
{
	x = X;
	y = Y;
}

double Vec2D::getLength()
{
	return sqrt(x*x + y*y);
}

double Vec2D::getQuadLength()
{
	return x*x + y*y;
}

void Vec2D::normalize()
{
	double length = this->getLength();

	x = x / length;
	y = y / length;
}

void Vec2D::operator=(Vec2D v)
{
	x = v.x;
	y = v.y;
}

Vec2D Vec2D::operator+(Vec2D v)
{
	return Vec2D(x + v.x, y + v.y);
}

Vec2D Vec2D::operator-(Vec2D v)
{
	return Vec2D(x - v.x, y - v.y);
}

void Vec2D::operator+=(Vec2D v)
{
	x += v.x;
	y += v.y;
}

void Vec2D::operator-=(Vec2D v)
{
	x -= v.x;
	y -= v.y;
}

Vec2D Vec2D::operator*(int s)
{
	return Vec2D(x*s, y*s);
}

Vec2D Vec2D::operator*(double s)
{
	return Vec2D(x*s, y*s);
}

void Vec2D::operator*=(int s)
{
	x *= s;
	y *= s;
}

void Vec2D::operator*=(double s)
{
	x *= s;
	y *= s;
}

void Vec2D::rotate_deg(double angle)
{
	angle = to_rad(angle);

	double sin_angle = sin(angle);
	double cos_angle = cos(angle);

	double x2 = cos_angle * x - sin_angle * y;		// Thats two dimmension case of rotation matrix
	double y2 = sin_angle * x + cos_angle * y;

	x = x2;
	y = y2;
}

void Vec2D::rotate_rad(double angle)
{
	double sin_angle = sin(angle);
	double cos_angle = cos(angle);

	double x2 = cos_angle * x - sin_angle * y;		// Thats two dimmension case of rotation matrix
	double y2 = sin_angle * x + cos_angle * y;

	x = x2;
	y = y2;
}



Vec3D::Vec3D()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Vec3D::Vec3D(double X, double Y, double Z)
{
	x = X;
	y = Y;
	z = Z;
}

double Vec3D::getLength()
{
	return sqrt(x*x + y*y + z*z);
}

double Vec3D::getQuadLength()
{
	return x*x + y*y + z*z;
}

void Vec3D::normalize()
{
	double length = this->getLength();

	x = x / length;
	y = y / length;
	z = z / length;
}

void Vec3D::operator=(Vec3D v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

Vec3D Vec3D::operator+(Vec3D v)
{
	return Vec3D(x + v.x, y + v.y, z + v.z);
}

Vec3D Vec3D::operator-(Vec3D v)
{
	return Vec3D(x - v.x, y - v.y, z - v.z);
}

void Vec3D::operator+=(Vec3D v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void Vec3D::operator-=(Vec3D v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

Vec3D Vec3D::operator*(int s)
{
	return Vec3D(x*s, y*s, z*s);
}

Vec3D Vec3D::operator*(double s)
{
	return Vec3D(x*s, y*s, z*s);
}

void Vec3D::operator*=(int s)
{
	x *= s;
	y *= s;
	z *= s;
}

void Vec3D::operator*=(double s)
{
	x *= s;
	y *= s;
	z *= s;
}

double to_rad(double degrees)
{
	return degrees * (M_PI / 180.0);
}

double to_deg(double radians)
{
	return radians * (180.0 / M_PI);
}

double dot(Vec2D a, Vec2D b)
{
	return a.x * b.x + a.y * b.y;
}

double dot(Vec3D a, Vec3D b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

double cross(Vec2D a, Vec2D b)
{
	return a.x * b.y - a.y * b.x;
}

Vec3D cross(Vec3D a, Vec3D b)
{
	double x = a.y * b.z - a.z * b.y;
	double y = a.z * b.x - a.x * b.z;
	double z = a.x * b.y - a.y * b.x;

	return Vec3D(x, y, z);
}
