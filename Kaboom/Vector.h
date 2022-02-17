#pragma once

struct Vector
{
	int x, y;

	Vector(int x = 0, int y = 0);
	Vector & operator=(const Vector&);

	bool operator==(const Vector&) const;
	bool operator!=(const Vector&) const;

	Vector operator+(const Vector&) const;
	Vector & operator+=(const Vector&);
    
    Vector operator-() const;
    Vector operator-(const Vector&) const;
	Vector & operator-=(const Vector&);
    
    int operator*(const Vector&) const;
    int operator%(const Vector&) const;
    
    int operator!() const;
    Vector & operator~();
};
