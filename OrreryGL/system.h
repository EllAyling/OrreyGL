#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "planet.h"
#include "camera.h"
#include "gfx.h"

class SystemClass
{
public:
	SystemClass();
	~SystemClass();

	bool Init(int);
	void Run();
	WPARAM Stop();

private:
	HRESULT InitWindow(HINSTANCE, HWND, int);

	HGLRC m_RenderContext;
	HINSTANCE m_hInstance;
	HDC m_DeviceContext;
	HWND m_window;
	MSG m_msg;
	bool needToQuit;

	//Planets
	PlanetClass* m_sun;
	PlanetClass* m_mercury;
	PlanetClass* m_venus;
	PlanetClass* m_earth;
	PlanetClass* m_mars;
	PlanetClass* m_jupiter;
	PlanetClass* m_saturn;
	PlanetClass* m_uranus;
	PlanetClass* m_neptune;

	CameraClass* m_camera;
	GFXClass* m_gfx;

	bool m_wireframeToggle;
	bool m_gravToggle;
	bool m_planetSelect[8];

	void CheckControls();

	GLdouble m_cameraPos[];


};
static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

#endif