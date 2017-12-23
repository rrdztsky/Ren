//
//  Camera.h
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 12/31/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Vec3.h"
#include "Quat.h"
#include "Matrix4x4.h"

class Camera
{
public:
	Camera();
	Matrix4x4 getProjection();
	Matrix4x4 getView();
	void keyboard(unsigned char key, int x, int y);
	void keyboardUp(unsigned char key, int x, int y);
	void motion(int x, int y);
	void mouse(int button, int state, int x, int y);
	void tick(float dt);
private:
	Vec3 position;
	Quat rotation;
	float fov;
	float aspect;
	float far;
	float near;
	bool track;
	int centerX;
	int centerY;
	bool moveLeft;
	bool moveRight;
	bool moveForward;
	bool moveBack;
	bool moveUp;
	bool moveDown;
};

#endif /* Camera_h */
