#include "vector_SGL.h"

#include <math.h>


Vec2D::Vec2D()
{
	x = 0.0f;
	y = 0.0f;
}

Vec2D::Vec2D(float X, float Y)
{
	x = X;
	y = Y;
}

float Vec2D::getLength()
{
	return sqrt(x*x + y*y);
}

float Vec2D::getQuadLength()
{
	return x*x + y*y;
}

void Vec2D::normalize()
{
	float length = this->getLength();

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

void Vec2D::operator*(float s)
{
	x *= s;
	y *= s;
}



Vec3D::Vec3D()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

Vec3D::Vec3D(float X, float Y, float Z)
{
	x = X;
	y = Y;
	z = Z;
}

float Vec3D::getLength()
{
	return sqrt(x*x + y*y + z*z);
}

float Vec3D::getQuadLength()
{
	return x*x + y*y + z*z;
}

void Vec3D::normalize()
{
	float length = this->getLength();

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

void Vec3D::operator*(float s)
{
	x *= s;
	y *= s;
	z *= s;
}
