//
//  Quat.cpp
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 11/13/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#include "Quat.h"
#include <cmath>

using namespace std;

Quat Quat::quatWithAngleAxis(float angle, const Vec3 &axis)
{
	float halfAngle = 0.5f*angle;
	float c = cos(halfAngle);
	float s = sin(halfAngle);
	return Quat(s*axis.x, s*axis.y, s*axis.z, c);
}

//rotation matrix from a quaternion
Matrix4x4 Quat::getMatrix4x4() const
{
	return Matrix4x4(
					 //row 0
					 1.0f - 2.0f*(y*y + z*z),
					 2.0f*(x*y - w*z),
					 2.0f*(x*z + w*y),
					 0.0f,
					 //row 1
					 2.0f*(y*x + w*z),
					 1.0f - 2.0f*(x*x + z*z),
					 2.0f*(y*z - w*x),
					 0.0f,
					 //row 2
					 2.0f*(z*x - w*y),
					 2.0f*(z*y + w*x),
					 1.0f - 2.0f*(x*x + y*y),
					 0.0f,
					 //row 3
					 0.0f,
					 0.0f,
					 0.0f,
					 1.0f);
}