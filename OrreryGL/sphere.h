#ifndef _SPHERE_H_
#define _SPHERE_H_
#define _USE_MATH_DEFINES

#include <vector>
#include <cmath>

#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>	
#include <math.h>

#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glu32.lib")

class SolidSphere
{
protected:
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> normals;
	std::vector<GLushort> indices;

public:
	SolidSphere();
	SolidSphere(float radius, unsigned int rings, unsigned int sectors);
	~SolidSphere();

	void Draw(GLfloat x, GLfloat y, GLfloat z, GLfloat ax, GLfloat ay, GLfloat az, GLfloat colour[], GLfloat theta, GLfloat scale);

private:
	void AxisRotation(GLfloat theta);
};

#endif