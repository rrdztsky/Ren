//
//  Matrix4x4.h
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 6/19/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#ifndef Matrix4x4_h
#define Matrix4x4_h
#include <cmath>
#include "Vec3.h"
#include "Matrix3x3.h"

class Matrix4x4
{
public:
	Matrix4x4(); //Default constructor
	Matrix4x4(
				float xx, float xy, float xz, float xw,
			 	float yx, float yy, float yz, float yw,
			  	float zx, float zy, float zz, float zw,
			  	float wx, float wy, float wz, float ww
			  );
	
	static Matrix4x4 zero();
	static Matrix4x4 identity();
	static Matrix4x4 translation(const Vec3 &v);
	static Matrix4x4 inverseTranslation(const Vec3 &v);
	static Matrix4x4 rotation(float angle, const Vec3 &axis);
	static Matrix4x4 inverseRotation(float angle, const Vec3 &axis);
	static Matrix4x4 scale(float s);
	static Matrix4x4 scale(const Vec3 &s);
	static Matrix4x4 transpose(const Matrix4x4 &m);
	static Matrix4x4 orthoNormalize(const Matrix4x4 &m);
	
	float &operator()(int i, int j) { return m[(4*i) + j]; } //overloads () operator for referencing
									 						 //and indexing matrix location
	const float &operator()(int i, int j) const { return m[(4*i) + j]; }
	
	float *get() { return &m[0]; } //returns address of the first element of m
	const float *get() const { return &m[0]; }
	
private:
	float m[16];
};

inline Matrix4x4 operator*(const Matrix4x4 &a, const Matrix4x4 &b)
{
	Matrix4x4 r;
	for (int i = 0; i < 4; ++i) //looping over rows of result
	{
		for (int j = 0; j < 4; ++j) //looping over columns of result
		{
			r(i,j) = 0.0f;
			for (int k = 0; k < 4; ++k)
			{
				r(i,j) += a(i,k)*b(k,j);
			}
		}
	}
	return r;
}

inline Matrix4x4 Matrix4x4::zero()
{
	return Matrix4x4(
					 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 0.0f);
}

inline Matrix4x4 Matrix4x4::identity()
{
	return Matrix4x4(
					 1.0f, 0.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 Matrix4x4::translation(const Vec3 &v)
{
	return Matrix4x4(
					 1.0f, 0.0f, 0.0f, v.x,
					 0.0f, 1.0f, 0.0f, v.y,
					 0.0f, 0.0f, 1.0f, v.z,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 Matrix4x4::inverseTranslation(const Vec3 &v)
{
	return Matrix4x4(
					 1.0f, 0.0f, 0.0f, -v.x,
					 0.0f, 1.0f, 0.0f, -v.y,
					 0.0f, 0.0f, 1.0f, -v.z,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 Matrix4x4::rotation(float angle, const Vec3 &axis)
{
	Matrix3x3 M = Matrix3x3::rotation(angle, axis);
	Matrix4x4 r = Matrix4x4::identity();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			r(i,j) = M(i,j);
		}
	}
	return r;
}

inline Matrix4x4 Matrix4x4::inverseRotation(float angle, const Vec3 &axis)
{
	return Matrix4x4::rotation(-angle, axis);
}

inline Matrix4x4 Matrix4x4::scale(float s)
{
	return Matrix4x4(
					 s, 0.0f, 0.0f, 0.0f,
					 0.0f, s, 0.0f, 0.0f,
					 0.0f, 0.0f, s, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 Matrix4x4::scale(const Vec3 &s)
{
	return Matrix4x4(
					 s.x, 0.0f, 0.0f, 0.0f,
					 0.0f, s.y, 0.0f, 0.0f,
					 0.0f, 0.0f, s.z, 0.0f,
					 0.0f, 0.0f, 0.0f, 1.0f);
}

inline Matrix4x4 Matrix4x4::transpose(const Matrix4x4 &m)
{
	return Matrix4x4(m(0,0), m(1,0), m(2,0), m(3,0),
					 m(0,1), m(1,1), m(2,1), m(3,1),
					 m(0,2), m(1,2), m(2,2), m(3,2),
					 m(0,3), m(1,3), m(2,3), m(3,3));
}

inline Matrix4x4 Matrix4x4::orthoNormalize(const Matrix4x4 &m)
{
	Vec3 x(m(0,0), m(1,0), m(2,0)); //object's local x axis
	Vec3 y(m(0,1), m(1,1), m(2,1)); //object's local y axis
	Vec3 z(m(0,2), m(1,2), m(2,2)); //object's local z axis
	y = normalize(y); //normalize into unit vectors
	x = normalize(cross(y,z));
	z = normalize(cross(x,y)); //x,y,z all unit length and perpendicular
	return Matrix4x4(x.x, y.x, z.x, m(0,3),
					 x.y, y.y, z.y, m(1,3),
					 x.z, y.z, z.z, m(2,3),
					 0.0f, 0.0f, 0.0f, 1.0f); //retain the translation
}


#endif /* Matrix4x4_h */
