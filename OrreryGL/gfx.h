#ifndef _GFX_H_
#define _GFX_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>	

#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glu32.lib")

class GFXClass
{
public:
	GFXClass();
	~GFXClass();

	void StartScene(float width, float height);
	void EndScene(HDC devcon);
	void SetLight();

private:
	GLfloat fov;
	GLfloat nearplane;
	GLfloat farplane;
};



#endif