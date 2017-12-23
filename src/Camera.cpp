//
//  Camera.cpp
//  GLTutorial1
//
//  Created by Rachel Radeztsky on 12/31/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//

#include "Camera.h"
#include <cmath>
#include <iostream>
#include <ApplicationServices/ApplicationServices.h>
#include "rrgl.h"

Camera::Camera()
: position(Vec3(0, 0, 5)) //initializer list for constructor
, rotation(Quat::quatWithAngleAxis(0.0f, Vec3(1.0f, 0.0f, 0.0f)))
, fov(1.0f)
, aspect(1.0f)
, near(0.01f)
, far(100.0f)
, track(false)
, centerX(300)
, centerY(300)
, moveLeft(false)
, moveRight(false)
, moveForward(false)
, moveBack(false)
, moveUp(false)
, moveDown(false)
{
	
}

Matrix4x4 Camera::getProjection()
{
	return Matrix4x4(1.0f/(aspect*std::tan(0.5f*fov)), 0.0f, 0.0f, 0.0f,
					 0.0f, 1/(std::tan(0.5f*fov)), 0.0f, 0.0f,
					 0.0f, 0.0f, -(far + near)/(far - near), -(2.0f*far*near)/(far - near),
					 0.0f, 0.0f, -1.0f, 0.0f);
}

Matrix4x4 Camera::getView()
{
	Matrix4x4 invr = conj(rotation).getMatrix4x4(); //constructing inverse rotation from conjugate of quaternion rotation
	Matrix4x4 invt = Matrix4x4::translation(-position);
	return invr*invt;
}

void Camera::keyboard(unsigned char key, int x, int y)
{
	std::cout << key << " down\n";
	switch (key)
	{
		case 'w':
			moveForward = true;
			break;
		case 's':
			moveBack = true;
			break;
		case 'a':
			moveLeft = true;
			break;
		case 'd':
			moveRight = true;
			break;
		case 'q':
			moveDown = true;
			break;
		case 'e':
			moveUp = true;
			break;
		default:
			break;
	}
}

void Camera::keyboardUp(unsigned char key, int x, int y)
{
	std::cout << key << " up\n";
	switch (key)
	{
		case 'w':
			moveForward = false;
			break;
		case 's':
			moveBack = false;
			break;
		case 'a':
			moveLeft = false;
			break;
		case 'd':
			moveRight = false;
			break;
		case 'q':
			moveDown = false;
			break;
		case 'e':
			moveUp = false;
			break;
		default:
			break;
	}
}

void Camera::motion(int x, int y)
{
	if (!track)
	{
		return;
	}
	int dx = x - centerX;
	int dy = y - centerY;
	Quat dPitch = Quat::quatWithAngleAxis(0.001f*dy, Vec3(1.0f, 0.0f, 0.0f));
	Quat dYaw = Quat::quatWithAngleAxis(0.001f*dx, Vec3(0.0f, -1.0f, 0.0f));
	rotation = normalize(dYaw*rotation*dPitch);
	std::cout << x << " " << y << "\n";
	CGSetLocalEventsSuppressionInterval(0.0); //reduce delay on camera motion
	//non-deprecated attempt at reducing delay
		//CGPoint warpPoint = CGPointMake(centerX, centerY);
		//CGWarpMouseCursorPosition(warpPoint);
		//CGAssociateMouseAndMouseCursorPosition(true);
	glutWarpPointer(centerX, centerY);
}

void Camera::mouse(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
			{
				glutSetCursor(GLUT_CURSOR_NONE);
				glutWarpPointer(centerX, centerY);
				track = true;
				std::cout << "right mouse button down\n";
			}
			else if (state == GLUT_UP)
			{
				glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
				track = false;
				std::cout << "right mouse button up\n";
			}
	}
}

void Camera::tick(float dt)
{
	const float speed = 1.0f;
	if (moveForward)
	{
		Vec3 d(0.0f, 0.0f, -speed*dt);
		position += rotation.rotate(d); //use camera's rotation quaterinon to convert to global space
	}
	if (moveBack)
	{
		Vec3 d(0.0f, 0.0f, speed*dt);
		position += rotation.rotate(d);
	}
	if (moveLeft)
	{
		Vec3 d(-speed*dt, 0.0f, 0.0f);
		position += rotation.rotate(d);
	}
	if (moveRight)
	{
		Vec3 d(speed*dt, 0.0f, 0.0f);
		position += rotation.rotate(d);
	}
	if (moveUp)
	{
		Vec3 d(0.0f, speed*dt, 0.0f);
		position += d; //globally move up
	}
	if (moveDown)
	{
		Vec3 d(0.0f, -speed*dt, 0.0f);
		position += d; //globally move down
	}
}
