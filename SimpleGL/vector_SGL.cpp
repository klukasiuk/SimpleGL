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
	return sqrtf(x*x + y*y);
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
	return sqrtf(x*x + y*y + z*z);
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

float dot(Vec2D a, Vec2D b)
{
	return a.x * b.x + a.y * b.y;
}

float dot(Vec3D a, Vec3D b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float cross(Vec2D a, Vec2D b)
{
	return a.x * b.y - a.y * b.x;
}

Vec3D cross(Vec3D a, Vec3D b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;

	return Vec3D(x, y, z);
}
