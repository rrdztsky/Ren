//
//  Matrix3x3.cpp
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 8/28/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#include "Matrix3x3.h"

Matrix3x3::Matrix3x3()
: m{1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f}
{
}

Matrix3x3::Matrix3x3(
	float xx, float xy, float xz,
	float yx, float yy, float yz,
	float zx, float zy, float zz)
: m{xx, xy, xz,
	yx, yy, yz,
	zx, zy, zz}
{
}
