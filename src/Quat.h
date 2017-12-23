//
//  Quat.h
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 11/13/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#ifndef Quat_h
#define Quat_h
#include "Vec3.h"
#include "Matrix4x4.h"

class Quat
{
public:
	float x, y, z, w;
	Quat() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}; //constructor with no arguments, initializes xyzw, empty body
	Quat(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}; //constructor with args, initializes, empty body
	Vec3 rotate(const Vec3 &a) const; //member function, given quat and vec, q.rotate(v) returns rotated v
	Quat rotate(const Quat &a) const; //member function, given quat and quat, q.rotate(q) returns rotated q
	Matrix4x4 getMatrix4x4() const; //returns the 4x4 matrix that represents the rotation of q
	static Quat quatWithAngleAxis(float angle, const Vec3 &axis);
};

inline Quat operator*(const Quat &a, const Quat &b)
{
	return Quat(
				a.w*b.x + a.x*b.w + a.y*b.z - a.z*b.y,
				a.w*b.y + a.y*b.w + a.z*b.x - a.x*b.z,
				a.w*b.z + a.z*b.w + a.x*b.y - a.y*b.x,
				a.w*b.w - a.x*b.x - a.y*b.y - a.z*b.z);
}

inline Quat conj(const Quat &q)
{
	return Quat(-q.x, -q.y, -q.z, q.w);
}

inline Quat normalize(const Quat &q)
{
	float mag = std::sqrt(q.x*q.x + q.y*q.y + q.z*q.z + q.w*q.w);
	if (mag == 0.0f)
		mag = 1.0f;
	float oom = 1.0f/mag;
	return Quat(q.x*oom, q.y*oom, q.z*oom, q.w*oom);
}

inline Vec3 Quat::rotate(const Vec3 &a) const
{
	Quat p(a.x, a.y, a.z, 0.0f);
	Quat r = (*this)*p*conj(*this);
	return Vec3(r.x, r.y, r.z);
}

inline Quat Quat::rotate(const Quat &a) const
{
	Quat r = (*this)*a*conj(*this);
	return r;
}




#endif /* Quat_h */
