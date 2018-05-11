#pragma once

#include "vector_SGL.h"

class Camera2D
{
private:
	Vec2D pos;													// Camera parameters

	float width;
	float height;
	float rotation;

	bool needUpdate;											// Flag for updating projection matrix

public:
	Camera2D();
	Camera2D(Vec2D Position, float Width, float Height);

	void setView();

	void translate(float x, float y);
	void translate(Vec2D translation);

	void rotate(float angle);									// Rotating view by angle in degrees

	void zoom(float rate);										// Zooming view by given rate, rate greater than 1 is zooming in

	void lookAt(float x, float y);								// Sets camera center at given point
	void lookAt(Vec2D point);

	void setRotation(float angle);								// Sets rotation to given value
	void setSize(float Width, float Height);					// Sets camera size to given values

	float get_rotation();
	Vec2D get_position();
	Vec2D get_viewsize();
};