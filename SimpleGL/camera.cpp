#include "camera.h"

#include "SimpleGL.h"

#include <math.h>

Camera2D::Camera2D()
{
	pos = Vec2D(0.0f, 0.0f);
	rotation = 0.0f;
	width = 1.0f;
	height = 1.0f;

	needUpdate = true;
}

Camera2D::Camera2D(Vec2D Position, float Width, float Height)
{
	pos = Position;
	width = Width;
	height = Height;

	rotation = 0.0f;

	needUpdate = true;
}

void Camera2D::setView()
{
	if (needUpdate == false)
		return;

	float left   = pos.x - width  / 2.0f;
	float right  = pos.x + width  / 2.0f;
	float top    = pos.y + height / 2.0f;
	float bottom = pos.y - height / 2.0f;

	view(left, right, bottom, top);
	viewRotate(rotation);


	needUpdate = false;
}

void Camera2D::translate(float x, float y)
{
	pos.x += x;
	pos.y += y;

	needUpdate = true;
}

void Camera2D::translate(Vec2D translation)
{
	pos += translation;

	needUpdate = true;
}

void Camera2D::rotate(float angle)
{
	rotation += angle;

	needUpdate = true;
}

void Camera2D::zoom(float rate)
{
	if (rate < 0.01f)
		return;

	width  =  width / rate;
	height = height / rate;

	needUpdate = true;
}

void Camera2D::lookAt(float x, float y)
{
	pos = Vec2D(x, y);

	needUpdate = true;
}

void Camera2D::lookAt(Vec2D point)
{
	pos = point;

	needUpdate = true;
}

void Camera2D::setRotation(float angle)
{
	rotation = angle;

	needUpdate = true;
}

void Camera2D::setSize(float Width, float Height)
{
	width = Width;
	height = Height;

	needUpdate = true;
}
