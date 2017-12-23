//
//  App.cpp
//
//  Created by Rachel Radeztsky on 6/19/16.
//  Copyright © 2016 Rachel Radeztsky. All rights reserved.
//


#include "App.h"
#include "Vec3.h"
#include "Matrix4x4.h"
#include <iostream>
#include <cmath>
#include "rrgl.h"

App::App()
: time(0.0f) //initializer list
, indices{0, 1, 2, 0, 2, 3, 1, 3, 2, 1, 0, 3}
{
	verts.emplace_back(0.0f, 0.0f, 1.0f); //template thingies forward arguments
	verts.emplace_back(1.0f, 0.0f, 0.0f);
	verts.emplace_back(0.0f, 1.0f, 0.0f);
	verts.emplace_back(-1.0f, 0.0f, 0.0f);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo); //generate buffers at address of vbo (pointer)
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, verts.size()*sizeof(Vec3), &verts[0], GL_STATIC_DRAW); //sends OpenGL the number of verts.
	
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); //this is the array buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	
	shaderProgram = glCreateProgram();
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	const char *vsText =
	R"(
#version 150
	in vec3 Position; //from vertex buffer
	uniform mat4 world; //vec3, mat4, vec4 are already part of the shader language. built in.
	out vec4 color; //put out color in addition to glposition, interpolate
	void main()
	{
		gl_Position = world*vec4(Position, 1.0); // 4x4 matrix times a 4x1 vector
		color = vec4(clamp(0.5*(Position + 1.0), 0.0, 1.0), 1.0); //prevents colors from exceeding 0-1
	}
	)";
	const GLchar *p[1] = {(const GLchar *) vsText}; //array of pointers, one of them, one char cast as a GLchar
	GLint l[1] = {(GLint) strlen(vsText)}; //array of one int, initiaized to strlen at vsText. strlen function counts strings
	glShaderSource(vs, 1, p, l); //p and l are passing addresses of the arrays. Shader id'd by vs, one line.
	glCompileShader(vs); //integer id for the shader
	
	//tests if compiler ran successfully, 1 if successful, 0 if not
	GLint success;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(vs, sizeof(infoLog), nullptr, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_VERTEX_SHADER, infoLog);
	}
	glAttachShader(shaderProgram, vs); //attach the vertex shader to the shader program
	
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	const char *fsText =
	R"(
#version 150
	in vec4 color;
	out vec4 FragColor;
	void main()
	{
		FragColor = color; //send through whatever color we got
	}
	)";
	const GLchar *fp[1] = {(const GLchar *) fsText}; //array of pointers, one of them, one char cast as a GLchar
	GLint fl[1] = {(GLint) strlen(fsText)}; //array of one int, initiaized to strlen at fsText. strlen function counts strings
	glShaderSource(fs, 1, fp, fl); //fp and fl are passing addresses of the arrays. Shader id'd by vs, one line.
	glCompileShader(fs); //integer id for the shader
	
	//tests if compiler ran successfully, 1 if successful, 0 if not
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(fs, sizeof(infoLog), nullptr, infoLog);
		fprintf(stderr, "Error compiling shader type %d: '%s'\n", GL_FRAGMENT_SHADER, infoLog);
	}
	glAttachShader(shaderProgram, fs); //attach the fragment shader to the shader program
	
	glLinkProgram(shaderProgram);
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[1024];
		glGetShaderInfoLog(fs, sizeof(infoLog), nullptr, infoLog);
		fprintf(stderr, "Error linking shader program: '%s'\n", infoLog);
	}
	
	worldLocation = glGetUniformLocation(shaderProgram, "world"); //tell us the integer id for the location of the scale variable in OpenGL
		
}

void App::render()
{
	//std::cout << "display\n"; // print out to tell us it got called
	glBindVertexArray(vao);
	// make some test calls to show that it works
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // colors: red green blue alpha(transparency)0-1, none-full
	glClear(GL_COLOR_BUFFER_BIT); // clear the main color buffer to set color
	glValidateProgram(shaderProgram);
	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST); //enable the depth/z buffer
	glClear(GL_DEPTH_BUFFER_BIT); //clear the depth buffer
	
	
	const float scale = 0.2f;
	const float radius = 0.5f;
	Matrix4x4 r = Matrix4x4::rotation(time, Vec3(0.0f, 1.0f, 0.0f)); //changes the axis of rotation
	Matrix4x4 s = Matrix4x4::scale(scale);
	Matrix4x4 t = Matrix4x4::translation(Vec3(radius*std::cos(time), radius*std::sin(time), 0.0f));
	Matrix4x4 m = t*r*s;
	Matrix4x4 v = camera.getView();
	Matrix4x4 p = camera.getProjection();
	Matrix4x4 world = p*v*m;
	glUniformMatrix4fv(worldLocation, 1, GL_TRUE, world.get());
	
	glEnableVertexAttribArray(0); //enable the first slot
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //for the bound buffer and attribArray, here is what you're getting: three at a time, they're floats, don't normalize them, tightly packed (stride is zero), first one is at zero(beginning)
	glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(0); //shuts down the attrib array
	glBindVertexArray(0);
}

void App::reshape(int w, int h)
{
	//std::cout << "reshape " << w  << " " << h << "\n";
}

void App::keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'x':
			exit(0);
			break;
		default:
			break;
	}
	camera.keyboard(key, x, y); //will call camera if it passes switch
}

void App::keyboardUp(unsigned char key, int x, int y)
{
	camera.keyboardUp(key, x, y);
}

void App::motion(int x, int y)
{
	camera.motion(x, y);
}

void App::mouse(int button, int state, int x, int y)
{
	camera.mouse(button, state, x, y);
}

void App::tick(float dt)
{
	//std::cout << "tick " << dt << "\n";
	//time += dt;
	camera.tick(dt);
	glutPostRedisplay();
}
