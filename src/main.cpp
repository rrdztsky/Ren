#include <iostream>
#include <OpenGL/gl3.h>
#define __gl_h_
#include <GLUT/glut.h>
#include "App.h"
#include <memory>
#include <mach/mach_time.h>

std::unique_ptr<App> app;
void display();
void reshape(int w, int h);
void idle();
void keyboard(unsigned char key, int x, int y);
void keyboardUp(unsigned char key, int x, int y);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);


int main(int argc, const char * argv[])
{
	glutInit(&argc, (char **)argv); // start up GLUT and consume command line arguments
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_3_2_CORE_PROFILE); // initialize display mode and add gl3.2 features
	glutInitWindowSize(600, 600); // set initial window size
	glutInitWindowPosition(100, 100); // set initial window position
	glutCreateWindow("rachel"); // create window and name it
	glutDisplayFunc(display); // give GLUT a pointer to my display callback function
	glutReshapeFunc(reshape); // give GLUT a pointer to my reshape callback function
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutMotionFunc(motion);
	glutMouseFunc(mouse);
	app.reset(new App); //new makes a thing in dynamic memory
	std::cout << "hello\n";
	glutIdleFunc(idle);
	glutMainLoop(); // enter the GLUT loop never to return, everything happens via callbacks (typical for graphics)
}

// called by GLUT for drawing
void display()
{
	app->render();
	glutSwapBuffers(); // swaps front and back buffers
}

// called by GLUT when window size changes
void reshape(int w, int h)
{
	app->reshape(w, h);
}

void idle()
{
	static auto ta = mach_absolute_time(); //will only run the first time (called by glut), ta initialized
	auto tb = mach_absolute_time();
	double dt = (double)(tb - ta)*1.0e-9;
	app->tick((float)dt);
	ta = tb;
}

void keyboard(unsigned char key, int x, int y)
{
	app->keyboard(key, x, y);
}

void keyboardUp(unsigned char key, int x, int y)
{
	app->keyboardUp(key, x, y);
}

void motion(int x, int y)
{
	app->motion(x, y);
}

void mouse(int button, int state, int x, int y)
{
	app->mouse(button, state, x, y);
}