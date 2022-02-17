#include "Vector.h"

Vector::Vector(int x, int y)
{
	this->x = x;
	this->y = y;
}

Vector & Vector::operator=(const Vector & v)
{
	x = v.x;
	y = v.y;
	return *this;
}

bool Vector::operator==(const Vector & v) const
{
	return (x == v.x && y == v.y);
}

bool Vector::operator!=(const Vector & v) const
{
	return (x != v.x || y != v.y);
}

Vector Vector::operator+(const Vector & v) const
{
	return Vector(x + v.x, y + v.y);
}

Vector & Vector::operator+=(const Vector & v)
{
	*this = *this + v;
	return *this;
}

Vector Vector::operator-() const
{
	return Vector(-x, -y);
}

Vector Vector::operator-(const Vector & v) const
{
	return *this + -v;
}

Vector & Vector::operator-=(const Vector& v)
{
	*this = *this - v;
	return *this;
}

int Vector::operator*(const Vector & v) const
{
	return x * v.x + y * v.y;
}

int Vector::operator%(const Vector & v) const
{
	return x * v.y - y * v.x;
}

int Vector::operator!() const
{
    return x > y ? x : y;
}

Vector & Vector::operator~()
{
    *this = Vector(y, x);
    return *this;
}
