//
//  Vec3.h
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 6/5/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#ifndef Vec3_h
#define Vec3_h
#include <cmath>

class Vec3
{
public:
	float x, y, z;
	Vec3() : x(0.0f), y(0.0f), z(0.0f) {} //declares and defines an (automatically) inline default constructor (no .cpp needed)
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {} // second constructor; make x from x, etc
	Vec3 &operator+=(const Vec3 &a);
	Vec3 &operator-=(const Vec3 &a);
	Vec3 &operator*=(float f);
	Vec3 &operator/=(float f);
};

inline Vec3 &Vec3::operator+=(const Vec3 &a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this; //dereferences 'this' with *(pointer to value) in reference context to return a reference
}

inline Vec3 &Vec3::operator-=(const Vec3 &a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}

inline Vec3 &Vec3::operator*=(float f)
{
	x*=f;
	y*=f;
	z*=f;
	return *this;
}

inline Vec3 &Vec3::operator/=(float f)
{
	x/=f;
	y/=f;
	z/=f;
	return *this;
}

inline Vec3 operator+(const Vec3 &a, const Vec3 &b) //reference to a and b, will not change
{
	return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); //return sum of two vectors
}

inline Vec3 operator-(const Vec3 &a)
{
	return Vec3(-a.x, -a.y, -a.z); 
}

inline Vec3 operator-(const Vec3 &a, const Vec3 &b) //reference to a and b, will not change
{
	return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); //return subtraction of two vectors
}

inline Vec3 operator/(const Vec3 &v, float f)
{
	return Vec3(v.x/f, v.y/f, v.z/f);
}

inline float dot(const Vec3 &a, const Vec3 &b)
{
	return (a.x*b.x) + (a.y*b.y) + (a.z*b.z);
}

inline float magnitude(const Vec3 &V)
{
	return std::sqrt(dot(V,V));
}

inline Vec3 normalize(const Vec3 &V)
{
	return V/magnitude(V);
}

inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}


#endif /* Vec3_h */
