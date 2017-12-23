//
//  Matrix3x3.h
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 8/28/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#ifndef Matrix3x3_h
#define Matrix3x3_h
#include <cmath>
#include "Vec3.h"

class Matrix3x3
{
public:
	Matrix3x3(); //Default constructor (gives identity matrix)
	Matrix3x3(									//second constructor
			  float xx, float xy, float xz,
			  float yx, float yy, float yz,
			  float zx, float zy, float zz
			  );
	
	static Matrix3x3 zero(); //called zero, takes no arguments, returns a Matrix3x3 object; pseudoconstructor
							 //used static because we already have a constructor that takes no arguments
							 //and need an easy way to get a zero matrix; named constructor
	static Matrix3x3 identity(); //explicitly creates an identity matrix
	static Matrix3x3 skew(const Vec3 &u); //represents a cross product with u on the left side (ex:skew(u)*v -> u x v)
	static Matrix3x3 outerProduct(const Vec3 &a, const Vec3 &b); //multiply all elements, arrayed into a matrix
	static Matrix3x3 rotation(float angle, const Vec3 &axis); //creates a rotation matrix of an angle about an axis
	static Matrix3x3 inverseRotation(float angle, const Vec3 &axis); //rotates the opposite way
	static Matrix3x3 scale(float s); //scales by one scalar
	static Matrix3x3 scale(const Vec3 &s); //scales by a vector (nonuniform scaling)
	static Matrix3x3 transpose(const Matrix3x3 &m); //transposes m
	static Matrix3x3 orthoNormalize(const Matrix3x3 &m); //returns orthonormalized matrix
	
	float &operator()(int i, int j) { return m[(3*i) + j]; } //overloads () operator for referencing
	//and indexing matrix location
	const float &operator()(int i, int j) const { return m[(3*i) + j]; }
	
	float *get() { return &m[0]; } //returns address of the first element of m
	const float *get() const { return &m[0]; }
	
private:
	float m[9];
};

inline Matrix3x3 operator+(const Matrix3x3 &a, const Matrix3x3 &b) //matrix addition operator
{
	return Matrix3x3(a(0,0) + b(0,0), a(0,1) + b(0,1), a(0,2) + b(0,2),
					 a(1,0) + b(1,0), a(1,1) + b(1,1), a(1,2) + b(1,2),
					 a(2,0) + b(2,0), b(2,1) + b(2,1), a(2,2) + b(2,2)
					 );
}

inline Matrix3x3 operator-(const Matrix3x3 &a, const Matrix3x3 &b) //matrix subtraction operator
{
	return Matrix3x3(a(0,0) - b(0,0), a(0,1) - b(0,1), a(0,2) - b(0,2),
					 a(1,0) - b(1,0), a(1,1) - b(1,1), a(1,2) - b(1,2),
					 a(2,0) - b(2,0), b(2,1) - b(2,1), a(2,2) - b(2,2)
					 );
}

inline Matrix3x3 operator*(float f, const Matrix3x3 &a) //matrix scaling
{
	return Matrix3x3(f*a(0,0), f*a(0,1), f*a(0,2),
					 f*a(1,0), f*a(1,1), f*a(1,2),
					 f*a(2,0), f*a(2,1), f*a(2,2)
					 );
}

inline Vec3 operator*(const Matrix3x3 &m, const Vec3 &v) //matrix times vector
{
	return Vec3(m(0,0)*v.x + m(0,1)*v.y + m(0,2)*v.z,
				m(1,0)*v.x + m(1,1)*v.y + m(1,2)*v.z,
				m(2,0)*v.x + m(2,1)*v.y + m(2,2)*v.z
				);
}

inline Matrix3x3 operator*(const Matrix3x3 &a, const Matrix3x3 &b)
{
	Matrix3x3 r;
	for (int i = 0; i < 3; ++i) //looping over rows of result
	{
		for (int j = 0; j < 3; ++j) //looping over columns of result
		{
			r(i,j) = 0.0f;
			for (int k = 0; k < 3; ++k)
			{
				r(i,j) += a(i,k)*b(k,j);
			}
		}
	}
	return r;
}

inline Matrix3x3 Matrix3x3::zero() //creates a zero matrix
{
	return Matrix3x3(0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f,
					 0.0f, 0.0f, 0.0f
					 );
}

inline Matrix3x3 Matrix3x3::identity() //creates an identity matrix
{
	return Matrix3x3(1.0f, 0.0f, 0.0f,
					 0.0f, 1.0f, 0.0f,
					 0.0f, 0.0f, 1.0f
					 );
}

inline Matrix3x3 Matrix3x3::skew(const Vec3 &u) //creates cross product
{
	Matrix3x3 s = Matrix3x3::zero();
	s(0,1) = -u.z;
	s(0,2) = u.y;
	s(1,0) = u.z;
	s(1,2) = -u.x;
	s(2,0) = -u.y;
	s(2,1) = u.x;
	return s;
}

inline Matrix3x3 Matrix3x3::outerProduct(const Vec3 &a, const Vec3 &b) //tensors
{
	return Matrix3x3(a.x*b.x, a.x*b.y, a.x*b.z,
					 a.y*b.x, a.y*b.y, a.y*b.z,
					 a.z*b.x, a.z*b.y, a.z*b.z
					 );
}

inline Matrix3x3 Matrix3x3::rotation(float angle, const Vec3 &axis)
{
	Matrix3x3 w = Matrix3x3::skew(axis);
	Matrix3x3 uu = Matrix3x3::outerProduct(axis, axis);
	Matrix3x3 I = Matrix3x3::identity();
	Matrix3x3 M = uu + std::cos(angle)*(I - uu) + std::sin(angle)*w;
	return M;
}

inline Matrix3x3 Matrix3x3::inverseRotation(float angle, const Vec3 &axis)
{
	return Matrix3x3::rotation(-angle, axis);
}

inline Matrix3x3 Matrix3x3::scale(float s)
{
	return Matrix3x3(s, 0.0f, 0.0f,
					 0.0f, s, 0.0f,
					 0.0f, 0.0f, s);
}

inline Matrix3x3 Matrix3x3::scale(const Vec3 &s)
{
	return Matrix3x3(s.x, 0.0f, 0.0f,
					 0.0f, s.y, 0.0f,
					 0.0f, 0.0f, s.z);
}

inline Matrix3x3 Matrix3x3::transpose(const Matrix3x3 &m)
{
	return Matrix3x3(m(0,0), m(1,0), m(2,0),
					 m(0,1), m(1,1), m(2,1),
					 m(0,2), m(1,2), m(2,2));
}

inline Matrix3x3 Matrix3x3::orthoNormalize(const Matrix3x3 &m) //given orthonormalized matrix, removes fuzz, returns precise version, works on things that do NOT contain scale
{
	Vec3 x(m(0,0), m(1,0), m(2,0)); //object's local x axis
	Vec3 y(m(0,1), m(1,1), m(2,1)); //object's local y axis
	Vec3 z(m(0,2), m(1,2), m(2,2)); //object's local z axis
	y = normalize(y); //normalize into unit length
	x = normalize(cross(y,z));
	z = normalize(cross(x,z)); //x,y,z all unit length and perpendicular
	return Matrix3x3(x.x, y.x, z.x,
					 x.y, y.y, z.y,
					 x.z, y.z, z.z);
}

#endif /* Matrix3x3_h */
