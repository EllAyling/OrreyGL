#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>	
#include <math.h>

#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glu32.lib")

class CameraClass
{
public:
	CameraClass();
	~CameraClass();

	void Update(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, bool spacePressed, GLdouble planetPosition[]);

private:
	GLfloat m_xPos;
	GLfloat m_yPos;
	GLfloat m_zPos;
	GLfloat m_xRot;
	GLfloat m_yRot;
	GLfloat m_angle;
	GLfloat m_cameraSpeed;

	GLfloat m_xLookat;
	GLfloat m_yLookat;
	GLfloat m_zLookat;

	GLfloat m_radius;

	bool m_cameraLock;
	void CameraReset();
};

#endif