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

	Vec2D operator* (int s);
	Vec2D operator* (double s);

	void operator*= (int s);
	void operator*= (double s);

	// Angle must be in degrees
	void rotate_deg(double angle);

	// Angle must be in radians
	void rotate_rad(double angle);
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

	Vec3D operator* (int s);
	Vec3D operator* (double s);

	void operator*= (int s);
	void operator*= (double s);
};


double to_rad(double degrees);
double to_deg(double radians);

double dot(Vec2D a, Vec2D b);
double dot(Vec3D a, Vec3D b);

double cross(Vec2D a, Vec2D b);
Vec3D cross(Vec3D a, Vec3D b);