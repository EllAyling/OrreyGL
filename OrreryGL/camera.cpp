#include "camera.h"


CameraClass::CameraClass(void)
{
	m_xPos = 0.0f;
	m_yPos = 100.0f;
	m_zPos = 100.0f;
	m_xRot = -90.0f;
	m_yRot = 0.0f;
	m_angle = 0.0;
	m_radius = 10.0f;
	m_cameraSpeed = 3.0f;

	m_xLookat = 0.0f;
	m_yLookat = 0.0f;
	m_zLookat = 0.0f;
	
	m_cameraLock = false;
}

CameraClass::~CameraClass(void)
{
}


void CameraClass::Update(bool upPressed, bool downPressed, bool leftPressed, bool rightPressed, bool spacePressed, GLdouble planetPosition[])
{


	if (spacePressed)									//If spacebar is pressed, lock the camera to the currently selected planet. If toggled off, reset the camera.
	{
		if (!m_cameraLock) { m_cameraLock = true; }
		else { m_cameraLock = false; CameraReset(); }
		spacePressed = false;
	}

	if (m_cameraLock)									//Lock the camera to the currently selected planet.
	{
		m_xPos = planetPosition[0] * 1.5;
		m_zPos = planetPosition[1] * 1.5;
		m_xLookat = planetPosition[0];
		m_zLookat = planetPosition[1];
		m_yPos = 4.0f;
	}

	else if (upPressed && m_yPos > 5)					//Otherwise update the camera from button pressed.
	{
		m_yPos -= m_cameraSpeed;
	}

	else if (downPressed)
	{
		m_yPos += m_cameraSpeed;
	}

	else if (leftPressed)
	{
		m_zPos += m_cameraSpeed;
	}

	else if (rightPressed && m_zPos > 5)
	{
		m_zPos -= m_cameraSpeed;
	}
	
	gluLookAt(m_xPos, m_yPos, m_zPos, m_xLookat, m_yLookat, m_zLookat, 0.0f, 1.0f, 0.0f);			//Camera update. Same as :glMultMatrixf(M);	glTranslated(-xPos, -yPos, -zPos);

}

void CameraClass::CameraReset()
{
	m_xPos = 0.0f;
	m_yPos = 100.0f;
	m_zPos = 100.0f;
	m_xRot = -90.0f;
	m_yRot = 0.0f;
	m_angle = 0.0;
	m_radius = 10.0f;
	m_cameraSpeed = 3.0f;

	m_xLookat = 0.0f;
	m_yLookat = 0.0f;
	m_zLookat = 0.0f;

	m_cameraLock = false;
}
