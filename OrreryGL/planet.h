#ifndef _PLANET_H_
#define _PLANET_H_
#define _USE_MATH_DEFINES


#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include <vector>

#pragma comment(lib, "opengl32.lib")	
#pragma comment(lib, "glu32.lib")

#include "sphere.h"

class PlanetClass
{
public:
	PlanetClass(GLdouble startX, GLdouble startZ, GLfloat tilt, GLfloat rotationSpeed, GLdouble xVel, GLdouble zVel, GLdouble mass, GLfloat size, GLfloat colour[]);
	~PlanetClass();

	void Update(bool gravToggle);
	void GetPosition(GLdouble cameraPos[]);
	bool hasMoon;
	
private:

	SolidSphere* m_sphere;

	const GLdouble m_grav_const;
	const GLdouble m_scaleG;		//Coordinate scaling

	//Planet Variables
	GLfloat m_xAngle;
	GLfloat m_yAngle;
	GLfloat m_zAngle;
	
	GLdouble m_xPos;
	GLdouble m_yPos;
	GLfloat m_zPos;
	
	GLdouble m_xPosG;
	GLdouble m_zPosG;
	GLdouble m_mass;
	GLdouble m_radius;
	GLdouble m_angle;
	GLdouble m_grav_accel;
	GLdouble m_xVel;
	GLdouble m_zVel;
	GLfloat m_theta;			//Used for axis rotation
	
	GLfloat m_scale;			//Size scaling
	GLfloat m_colour[3];		//RGB colour values
	GLfloat m_rotationSpeed;

	//Moon Variables
	GLfloat m_moon_xPos;
	GLfloat m_moon_yPos;
	GLfloat m_moon_zPos;
	GLfloat m_moon_angle;

	//Orbit Line Variables
	std::vector<GLdouble> m_Line;
	GLint m_lineCount;
	GLint m_lineStepInc;
	bool m_isClockwise;
	bool m_firstPushDone;
	bool m_lineInit;

	//Functions
	void gravMath();
	void Render();
	void setPosition(GLfloat xPositionT, GLfloat yPositionT, GLfloat zPositionT);
	void setColour(GLfloat red, GLfloat green, GLfloat blue);
	void UpdateMoon(GLdouble x, GLdouble y, GLdouble z);
	void DrawOrbit(GLdouble xPos, GLdouble zPos);
};


#endif