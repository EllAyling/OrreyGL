#include "planet.h"
PlanetClass::PlanetClass(GLdouble startX, GLdouble startZ, GLfloat tilt, GLfloat rotationSpeed, GLdouble xVel, GLdouble zVel, GLdouble mass, GLfloat size, GLfloat colour[]) : m_grav_const(6.6742e-11), m_scaleG(10.0)	//Constants
{
	m_sphere = new SolidSphere(size, 12, 24);	//Create the planet spheare

	//Set up planet variables
	m_radius = 0.0;
	m_angle = 0.0;
	m_grav_accel = 0;
	m_mass = mass;
	m_xPosG = startX;
	m_zPosG = startZ;
	m_xVel = xVel;
	m_zVel = zVel;
	m_scale = 1.0;

	//Set Colour values
	m_colour[0] = colour[0];
	m_colour[1] = colour[1];
	m_colour[2] = colour[2];

	//Set up variables for drawing orbit.
	m_firstPushDone = false;
	m_lineInit = false;
	m_lineCount = 0;
	if (startZ > 20 || startZ < -20) { m_lineStepInc = 20; } //Update the outer planets orbit line less for performance reasons.
	else { m_lineStepInc = 2; }
	if (startZ > 0) { m_isClockwise = true; }
	else { m_isClockwise = false; }

	//Axies rotation variables
	m_rotationSpeed = rotationSpeed;
	m_xAngle = tilt;
	m_theta = 0.0f;

	//Moon variables
	hasMoon = false;
	m_moon_xPos = 0.0f;
	m_moon_yPos = 0.0f;
	m_moon_zPos = 0.0f;
	m_moon_angle = 0.0f;
}

PlanetClass::~PlanetClass()
{

}

void PlanetClass::Render()
{
	m_sphere->Draw(m_xPos, m_yPos, m_zPos, m_xAngle, m_yAngle, m_zAngle, m_colour, m_theta, m_scale);		//Draw the planet

	//Update the rotation value
	m_theta += m_rotationSpeed;
	if (m_theta >= (2 * M_PI))
	{
		m_theta = 0;
	}

}

void PlanetClass::setPosition(GLfloat xPositionT, GLfloat yPositionT, GLfloat zPositionT) //Set the planet position to the values passed to the function.
{
	m_xPos = xPositionT;
	m_yPos = yPositionT;
	m_zPos = zPositionT;
}

void PlanetClass::setColour(GLfloat red, GLfloat green, GLfloat blue)					//Set the planet colour to the values passed to the function.
{
	m_colour[0] = red;
	m_colour[1] = green;
	m_colour[2] = blue;
}

void PlanetClass::gravMath()
{
	//Update the planet position in relation to the gravity acting on it as stated by F = GMm /r ^2.
	m_radius = sqrt(pow(m_xPosG, 2) + pow(m_zPosG, 2));						//Find the distance between the planet and the origin
	m_grav_accel = (m_grav_const * (m_mass / pow(m_radius, 2)));			//Calculate its acceleration
	m_angle = atan2(m_xPosG, m_zPosG);										//Calculate angle.
	m_xVel += (sin(m_angle) * m_grav_accel);								//Update the x velocity.
	m_zVel += (cos(m_angle) * m_grav_accel);								//Update the z velocity.

	m_xPosG -= m_xVel;														//Update the x position.
	m_zPosG -= m_zVel;														//Update the z position.
}

void PlanetClass::Update(bool gravToggle)
{
	GLdouble xT;
	GLdouble zT;
	if (m_mass != 0.0)					//If the planet has mass. I.E if it isn't the sun.
	{
		if (gravToggle) { gravMath(); } //Toggle gravity on and off.
		xT = m_xPosG * m_scaleG;		//Update positions to the scale.
		zT = m_zPosG * m_scaleG;
		DrawOrbit(xT, zT);				//Draw the orbit.
	}
	else
	{									//If no mass, set position to the origin.
		xT = 0.0;						
		zT = 0.0;
	}
	setPosition(xT, 0.0f, zT);			//Update position.
	m_scale = 1.0f;						//Set scale
	Render();
	if (hasMoon)
	{
		UpdateMoon(xT, 0.0f, zT);		//If the planet has a moon, update the position in relation to the planet.
	}
}

void PlanetClass::UpdateMoon(GLdouble x, GLdouble y, GLdouble z)
{
	m_moon_xPos = x + sin(((m_moon_angle*180)/ M_PI) * 2.0f) * 1.5f;				//Set the oribt of the moon to fixed values.
	m_moon_yPos = y + sin(((m_moon_angle * 180) / M_PI) * 2.0f) * 1.5f;
	m_moon_zPos = z + cos(((m_moon_angle * 180) / M_PI) * 2.0f) * 1.5f;

	m_moon_angle += 0.0008f;

	setPosition(m_moon_xPos, m_moon_yPos, m_moon_zPos);
	m_scale = 0.2f;
	Render();
}

void PlanetClass::GetPosition(GLdouble cameraPos[])									//Used for focusing the camera on planet.
{
	cameraPos[0] = m_xPosG * m_scaleG;
	cameraPos[1] = m_zPosG * m_scaleG;
}

void PlanetClass::DrawOrbit(GLdouble xPos, GLdouble zPos)
{
	if (!m_lineInit && m_lineCount >= m_lineStepInc)								//If the line has yet to draw completely and the count is greater than the increment value.
	{
		m_Line.push_back(xPos);														//Store the current position in the vector.
		m_Line.push_back(zPos);
		if (!m_firstPushDone)														//First push will skip the line finished check so as not to try to derefence a vector value that doesn't excist.
		{
			m_firstPushDone = true;
		}
		else if (*(m_Line.begin()) < *(m_Line.end() - 2) && *(m_Line.begin() + 1) < *(m_Line.end() - 1) && m_isClockwise)		//if it isn't the first push, check to see if the full orbit has finished. If it has, set the initalise
		{																														//otherwise the vector will continue to fill, slowing the frame time and crashing after a certain amount of time.
			m_lineInit = true;
		}
		else if (*(m_Line.begin()) < *(m_Line.end() - 2) && *(m_Line.begin() + 1) > *(m_Line.end() - 1) && !m_isClockwise)		//check for a planet going counter clockwise.
		{
			m_lineInit = true;
		}
		m_lineCount = 0;															//Reset the line increment count.
	}

	if (m_Line.size()  > 4)															//If there are enough values to draw a line segment.
	{
		glDisable(GL_LIGHTING);

		glBegin(GL_LINE_STRIP);														//Draw a line between a current point and the next point stored in the vector.
		for (std::vector<GLdouble>::iterator it = m_Line.begin(); (it + 4) != m_Line.end(); it += 2)
		{
			GLdouble startX = *it;
			GLdouble startZ = *(it + 1);
			GLdouble endX = *(it + 2);
			GLdouble endZ = *(it + 3);


			glVertex3d(startX, 0.0, startZ);
			glVertex3d(endX, 0.0, endZ);
		}
		if (m_lineInit)																//Round off the orbit line
		{
			glVertex3d(*(m_Line.end() - 2), 0.0, *(m_Line.end() - 1));
			glVertex3d(*(m_Line.begin()), 0.0, *(m_Line.begin() + 1));
		}
		glEnd();

		glEnable(GL_LIGHTING);
	}

	m_lineCount += 1;

}


