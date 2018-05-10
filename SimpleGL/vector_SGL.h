#pragma once

struct Vec2D
{
	double x;
	double y;

	Vec2D();
	Vec2D(double X, double Y);

	double getLength();
	double getQuadLength();

	void normalize();

	void operator= (Vec2D v);

	Vec2D operator+ (Vec2D v);
	Vec2D operator- (Vec2D v);

	void operator+= (Vec2D v);
	void operator-= (Vec2D v);

	void operator* (double s);

	void rotate(double angle);	// angle in degrees !!!
};



struct Vec3D
{
	double x;
	double y;
	double z;

	Vec3D();
	Vec3D(double X, double Y, double Z);

	double getLength();
	double getQuadLength();

	void normalize();

	void operator= (Vec3D v);

	Vec3D operator+ (Vec3D v);
	Vec3D operator- (Vec3D v);

	void operator+= (Vec3D v);
	void operator-= (Vec3D v);

	void operator* (double s);
};


double dot(Vec2D a, Vec2D b);
double dot(Vec3D a, Vec3D b);

double cross(Vec2D a, Vec2D b);
Vec3D cross(Vec3D a, Vec3D b);