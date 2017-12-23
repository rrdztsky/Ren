//
//  Matrix4x4.cpp
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 6/19/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#include "Matrix4x4.h"

//Defines the non-inline functions (i.e. constructors)

Matrix4x4::Matrix4x4() //Constructor signature
: m{1.0f, 0.0f, 0.0f, 0.0f,		//initializer list
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f}
{ //nothing else to do, so just empty function body
}

Matrix4x4::Matrix4x4(float xx, float xy, float xz, float xw,
					 float yx, float yy, float yz, float yw,
			  		 float zx, float zy, float zz, float zw,
			  		 float wx, float wy, float wz, float ww)
: m{xx, xy, xz, xw,
	yx, yy, yz, yw,
	zx, zy, zz, zw,
	wx, wy, wz, ww}
{
}