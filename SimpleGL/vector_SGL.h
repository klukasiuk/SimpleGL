#pragma once

struct Vec2D
{
	float x;
	float y;

	Vec2D();
	Vec2D(float X, float Y);

	float getLength();
	float getQuadLength();

	void normalize();

	void operator= (Vec2D v);

	Vec2D operator+ (Vec2D v);
	Vec2D operator- (Vec2D v);

	void operator+= (Vec2D v);
	void operator-= (Vec2D v);

	void operator* (float s);
};



struct Vec3D
{
	float x;
	float y;
	float z;

	Vec3D();
	Vec3D(float X, float Y, float Z);

	float getLength();
	float getQuadLength();

	void normalize();

	void operator= (Vec3D v);

	Vec3D operator+ (Vec3D v);
	Vec3D operator- (Vec3D v);

	void operator+= (Vec3D v);
	void operator-= (Vec3D v);

	void operator* (float s);
};