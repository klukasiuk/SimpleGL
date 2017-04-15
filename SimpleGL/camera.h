#pragma once

#include "vec.h"

class Camera2D
{
private:
	Vec2D pos;

	float width;
	float height;
	float rotation;

	bool needUpdate;

public:
	Camera2D();
	Camera2D(Vec2D Position, float Width, float Height);

	void setView();

	void translate(float x, float y);
	void translate(Vec2D translation);

	void rotate(float angle);

	void zoom(float rate);

	void lookAt(float x, float y);
	void lookAt(Vec2D point);

	void setRotation(float angle);
	void setSize(float Width, float Height);
};