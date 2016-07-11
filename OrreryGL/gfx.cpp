#include "gfx.h"

GFXClass::GFXClass()
{
	fov = 50.0f;
	farplane = 100000.0f;
	nearplane = 1.0f;
}
GFXClass::~GFXClass()
{

}

void GFXClass::StartScene(float width, float height)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		//Clear buffers
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float)width / (float)height, nearplane, farplane);	// set up fov, and near / far clipping planes

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void GFXClass::EndScene(HDC devcon)
{
	SwapBuffers(devcon);		//Swap buffers
}

void GFXClass::SetLight()
{
	GLfloat light_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };			//Last value denotes light type 0 for directional, non 0 for positional.

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

}