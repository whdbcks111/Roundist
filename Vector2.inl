#pragma once
#include "Vector2.h"


inline Vector2::Vector2()
{
	x = y = 0.0f;
}

inline Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

inline Vector2 Vector2::operator+(const Vector2& v) const
{
	return Vector2(x + v.x, y + v.y);
}

inline Vector2 Vector2::operator-(const Vector2& v) const
{
	return Vector2(x - v.x, y - v.y);
}

inline Vector2 Vector2::operator/(const Vector2& v) const
{
	return Vector2(x / v.x, y / v.y);
}

inline Vector2 Vector2::operator*(const Vector2& v) const
{
	return Vector2(x * v.x, y * v.y);
}

inline Vector2 Vector2::operator*(float f) const
{
	return Vector2(x * f, y * f);
}

inline Vector2 Vector2::operator/(float f) const
{
	return Vector2(x / f, y / f);
}

inline Vector2 Vector2::operator-(void) const
{
	return Vector2(-x, -y);
}

inline Vector2& Vector2::operator+=(const Vector2& v)
{
	x += v.x;
	y += v.y;
	return *this;
}

inline Vector2& Vector2::operator-=(const Vector2& v)
{
	x -= v.x;
	y -= v.y;
	return *this;
}

inline Vector2& Vector2::operator/=(const Vector2& v)
{
	x /= v.x;
	y /= v.y;
	return *this;
}

inline Vector2& Vector2::operator*=(const Vector2& v)
{
	x *= v.x;
	y *= v.y;
	return *this;
}

inline Vector2& Vector2::operator+=(float f)
{
	x += f;
	y += f;
	return *this;
}

inline Vector2& Vector2::operator-=(float f)
{
	x -= f;
	y -= f;
	return *this;
}

inline Vector2& Vector2::operator*=(float f)
{
	x *= f;
	y *= f;
	return *this;
}

inline Vector2& Vector2::operator/=(float f)
{
	x /= f;
	y /= f;
	return *this;
}

inline bool Vector2::operator==(const Vector2& v) const
{

	return ((x == v.x) && (y == v.y));
}

inline bool Vector2::operator!=(const Vector2& v) const
{
	return ((x != v.x) || (y != v.y));
}

inline float Vector2::DotProduct(const Vector2& v) const
{
	return x * v.x + y * v.y;
}

inline void Vector2::Translate(const Vector2& v)
{
	x += v.x;
	y += v.y;
}

inline void Vector2::Translate(float x, float y)
{
	this->x += x;
	this->y += y;
}

inline void Vector2::SetVector(const Vector2& v)
{
	this->x = v.x;
	this->y = v.y;
}

inline void Vector2::SetVector(float x, float y)
{
	this->x = x;
	this->y = y;
}
