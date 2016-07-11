#include "system.h"

// Window globals
#define WIDTH		1920
#define HEIGHT		1080
#define TOPLEFTX	50
#define TOPLEFTY	50

//Initalise buttons
bool upPressed = false;
bool downPressed = false;
bool leftPressed = false;
bool rightPressed = false;
bool spacePressed = false;
bool wPressed = false;
bool gPressed = false;
bool onePressed, twoPressed, threePressed, fourPressed, fivePressed, sixPressed, sevenPressed, eightPressed = false;

SystemClass::SystemClass()
{

}

SystemClass::~SystemClass()
{

}

bool SystemClass::Init(int iCmdShow)
{
	HRESULT result;
	result = InitWindow(m_hInstance, m_window, iCmdShow);		//Create the window
	if (result != S_OK)
	{
		return false;
	}

	needToQuit = false;
	m_wireframeToggle = false;
	m_gravToggle = true;


	//Colour values
	GLfloat colour_white[] = { 255.0f, 255.0f, 255.0f };
	GLfloat colour_green[] = { 0.0f, 128.0f, 0.0f };
	GLfloat colour_blue[] = { 0.0f, 0.0f, 255.0f };
	GLfloat colour_grey[] = { 164.0f, 164.0f, 164.0f };
	GLfloat colour_purple[] = { 102.0f, 0.0f, 102.0f };
	GLfloat colour_red[] = { 153.0f, 0.0f, 0.0f };
	GLfloat colour_yellow[] = { 102.0f, 75.0f, 0.0f };
	GLfloat colour_orange[] = { 255.0f, 128.0f, 0.0f };
	GLfloat colour_lightblue[] = { 0.0f, 255.0f, 255.0f };

	//Set up planets. StartX, StartZ, tilt, rotationSpeed, xVel, zVel, mass, size, colour.
	m_sun = new PlanetClass(0.0, 0.0, 0.0f, 0.0f, 0.0, 0.0, 0.0, 2.0f, colour_yellow);
	m_mercury = new PlanetClass(0.0, 0.387, 0.012f, 0.001f, 0.025, 0.0, 3834600, 0.383f, colour_grey);
	m_venus = new PlanetClass(0.0, -0.723, 3.39f, 0.0001f, 0.068, 0.0, 56821800, 0.949f, colour_orange);
	m_earth = new PlanetClass(0.0, 1.0, 30.0f, 0.01f, 0.07, 0.00, 6.972E7, 1.0f, colour_green);
	m_mars = new PlanetClass(0.0, 1.52, 32.1f, 0.015f, 0.02, 0.0, 7460040, 0.532f, colour_red);
	m_jupiter = new PlanetClass(0.0, -5.2, 4.02f, 0.0266f, 0.7, 0.0, 2.2157016e10, 11.21f, colour_lightblue);
	m_saturn = new PlanetClass(0.0, 9.58, 34.2f, 0.0228f, 0.25, 0.0, 6637344000, 9.45f, colour_white);
	m_uranus = new PlanetClass(0.0, 19.2, 125.1f, 0.01391f, 0.05, 0.0, 1010940000, 4.01f, colour_purple);
	m_neptune = new PlanetClass(0.0, 30.05, 36.f, 0.015f, 0.05, 0.0, 1192212000, 3.88f, colour_blue);

	//Define moons
	m_earth->hasMoon = true;
	m_venus->hasMoon = true;

	//Set up planet select controls
	for (int i = 0; i < 9; i++)
	{
		m_planetSelect[i] = false;
	}

	//Create classes.
	m_camera = new CameraClass;
	m_gfx = new GFXClass;

	//Enable openGL stuff
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColorMaterial(GL_FRONT, GL_AMBIENT);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_POLYGON_SMOOTH);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	return true;
}

void SystemClass::Run()
{
	while (!needToQuit)											//Whilst the user doesn't exit the window
	{
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			if (m_msg.message == WM_QUIT)
			{
				needToQuit = true;
			}
			else
			{
				TranslateMessage(&m_msg);
				DispatchMessage(&m_msg);
			}
		}
		
		m_gfx->StartScene(WIDTH, HEIGHT);

			CheckControls();
			m_camera->Update(upPressed, downPressed, leftPressed, rightPressed, spacePressed, m_cameraPos);
		
			//Planet updates
			m_sun->Update(m_gravToggle);
			m_mercury->Update(m_gravToggle);
			m_venus->Update(m_gravToggle);
			m_earth->Update(m_gravToggle);
			m_mars->Update(m_gravToggle);
			m_jupiter->Update(m_gravToggle);
			m_saturn->Update(m_gravToggle);
			m_uranus->Update(m_gravToggle);
			m_neptune->Update(m_gravToggle);
		
			m_gfx->SetLight();
		
		m_gfx->EndScene(m_DeviceContext);

	}
}

WPARAM SystemClass::Stop()
{
	//Clean up
	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(m_RenderContext);

	ReleaseDC(m_window, m_DeviceContext);

	return m_msg.wParam;
}

void SystemClass::CheckControls()
{
	if (wPressed)
	{
		if (!m_wireframeToggle) { m_wireframeToggle = true; }
		else { m_wireframeToggle = false; }
		wPressed = false;
	}

	if (gPressed)
	{
		if (!m_gravToggle) { m_gravToggle = true; }
		else { m_gravToggle = false; }
		wPressed = false;
	}


	if (m_wireframeToggle) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); } //Toggle wireframe on/off
	else { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }

	if (onePressed){
		if (!m_planetSelect[0]) 
		{
			m_planetSelect[0] = true; 
		}
		else { m_planetSelect[0] = false; }
		onePressed = false;
	}
	if (twoPressed){
		if (!m_planetSelect[1]) { m_planetSelect[1] = true; }
		else { m_planetSelect[1] = false; }
		twoPressed = false;
	}

	if (threePressed){
		if (!m_planetSelect[2]) { m_planetSelect[2] = true; }
		else { m_planetSelect[2] = false; }
		threePressed = false;
	}

	if (fourPressed){
		if (!m_planetSelect[3]) { m_planetSelect[3] = true; }
		else { m_planetSelect[3] = false; }
		fourPressed = false;
	}

	if (fivePressed){
		if (!m_planetSelect[4]) { m_planetSelect[4] = true; }
		else { m_planetSelect[4] = false; }
		fivePressed = false;
	}

	if (sixPressed){
		if (!m_planetSelect[5]) { m_planetSelect[5] = true; }
		else { m_planetSelect[5] = false; }
		sixPressed = false;
	}

	if (sevenPressed){
		if (!m_planetSelect[6]) { m_planetSelect[6] = true; }
		else { m_planetSelect[6] = false; }
		sevenPressed = false;
	}

	if (eightPressed){
		if (!m_planetSelect[7]) { m_planetSelect[7] = true; }
		else { m_planetSelect[7] = false; }
		eightPressed = false;
	}

	if (m_planetSelect[0]) { m_mercury->GetPosition(m_cameraPos); }
	else if (m_planetSelect[1]) { m_venus->GetPosition(m_cameraPos); }
	else if (m_planetSelect[2]) { m_earth->GetPosition(m_cameraPos); }
	else if (m_planetSelect[3]) { m_mars->GetPosition(m_cameraPos); }
	else if (m_planetSelect[4]) { m_jupiter->GetPosition(m_cameraPos); }
	else if (m_planetSelect[5]) { m_saturn->GetPosition(m_cameraPos); }
	else if (m_planetSelect[6]) { m_uranus->GetPosition(m_cameraPos); }
	else if (m_planetSelect[7]) { m_neptune->GetPosition(m_cameraPos); }
}

HRESULT SystemClass::InitWindow(HINSTANCE hInstance, HWND hWnd, int iCmdShow)
{
									// this will be used to store messages from the operating system
	bool needToQuit = false;				// whether or not the player has quit the app



	// this bit creates a window class, basically a template for the window we will make later, so we can do more windows the same.
	WNDCLASS myWindowClass;
	myWindowClass.cbClsExtra = 0;											// no idea
	myWindowClass.cbWndExtra = 0;											// no idea
	myWindowClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	// background fill black
	myWindowClass.hCursor = LoadCursor(NULL, IDC_ARROW);					// arrow cursor       
	myWindowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				// type of icon to use (default app icon)
	myWindowClass.hInstance = hInstance;									// window instance name (given by the OS when the window is created)   
	myWindowClass.lpfnWndProc = WndProc;									// window callback function - this is our function below that is called whenever something happens
	myWindowClass.lpszClassName = TEXT("Window Class");				// our new window class name
	myWindowClass.lpszMenuName = 0;											// window menu name (0 = default menu?) 
	myWindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;				// redraw if the window is resized horizontally or vertically, allow different context for each window instance

	// Register that class with the Windows OS..
	RegisterClass(&myWindowClass);


	// create a rect structure to hold the dimensions of our window
	RECT rect;
	SetRect(&rect, TOPLEFTX,				// the top-left corner x-coordinate
		TOPLEFTY,				// the top-left corner y-coordinate
		TOPLEFTX + WIDTH,		// far right
		TOPLEFTY + HEIGHT);	// far left



	// adjust the window, no idea why.
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);



	// call CreateWindow to create the window
	m_window = CreateWindow(TEXT("Window Class"),		// window class to use - in this case the one we created a minute ago
		TEXT("Orrery"),					// window title
		WS_OVERLAPPEDWINDOW,						// ??
		TOPLEFTX, TOPLEFTY,						// x, y
		TOPLEFTX + WIDTH, TOPLEFTY + HEIGHT,		// width and height
		NULL, NULL,								// ??
		hInstance, NULL);							// ??


	// check to see that the window created okay
	if (m_window == NULL)
	{
		FatalAppExit(NULL, TEXT("CreateWindow() failed!"));
	}

	// if so, show it
	ShowWindow(m_window, iCmdShow);


	// get a device context from the window
	m_DeviceContext = GetDC(m_window);


	// we create a pixel format descriptor, to describe our desired pixel format. 
	// we set all of the fields to 0 before we do anything else
	// this is because PIXELFORMATDESCRIPTOR has loads of fields that we won't use
	PIXELFORMATDESCRIPTOR myPfd = { 0 };


	// now set only the fields of the pfd we care about:
	myPfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);		// size of the pfd in memory
	myPfd.nVersion = 1;									// always 1

	myPfd.dwFlags = PFD_SUPPORT_OPENGL |				// OpenGL support - not DirectDraw
		PFD_DOUBLEBUFFER |				// double buffering support
		PFD_DRAW_TO_WINDOW;					// draw to the app window, not to a bitmap image

	myPfd.iPixelType = PFD_TYPE_RGBA;					// red, green, blue, alpha for each pixel
	myPfd.cColorBits = 24;								// 24 bit == 8 bits for red, 8 for green, 8 for blue.
	// This count of color bits EXCLUDES alpha.

	myPfd.cDepthBits = 32;								// 32 bits to measure pixel depth.



	// now we need to choose the closest pixel format to the one we wanted...	
	int chosenPixelFormat = ChoosePixelFormat(m_DeviceContext, &myPfd);

	// if windows didnt have a suitable format, 0 would have been returned...
	if (chosenPixelFormat == 0)
	{
		FatalAppExit(NULL, TEXT("ChoosePixelFormat() failed!"));
	}

	// if we get this far it means we've got a valid pixel format
	// so now we need to set the device context up with that format...
	int result = SetPixelFormat(m_DeviceContext, chosenPixelFormat, &myPfd);

	// if it failed...
	if (result == NULL)
	{
		FatalAppExit(NULL, TEXT("SetPixelFormat() failed!"));
	}


	// we now need to set up a render context (for opengl) that is compatible with the device context (from windows)...
	m_RenderContext = wglCreateContext(m_DeviceContext);

	// then we connect the two together
	wglMakeCurrent(m_DeviceContext, m_RenderContext);

	return S_OK;
}

// this function is called when any events happen to our window
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{

	switch (message)
	{
	case WM_KEYDOWN:
		switch (wparam)
		{
		case VK_UP:
			// Process the UP ARROW key. 
			upPressed = true;
			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			downPressed = true;
			return 0;

		case VK_LEFT:
			// Process the LEFT ARROW key. 
			leftPressed = true;
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key. 
			rightPressed = true;
			return 0;

		case VK_SPACE:
			// Process the SPACEBAR. 
			spacePressed = true;
			return 0;

		case 0x57:
			//Process the 'w' key.
			wPressed = true;
			return 0;

		case 0x47:
			//Process the 'g' key
			gPressed = true;
			return 0;

		case 0x31:
			//Process the '1' key.
			onePressed = true;
			return 0;

		case 0x32:
			//Process the '2' key.
			twoPressed = true;
			return 0;

		case 0x33:
			//Process the '3' key.
			threePressed = true;
			return 0;

		case 0x34:
			//Process the '4' key.
			fourPressed = true;
			return 0;

		case 0x35:
			//Process the '5' key.
			fivePressed = true;
			return 0;

		case 0x36:
			//Process the '6' key.
			sixPressed = true;
			return 0;

		case 0x37:
			//Process the '7' key.
			sevenPressed = true;
			return 0;

		case 0x38:
			//Process the '8' key.
			eightPressed = true;
			return 0;


		}
		return 0;
	case WM_KEYUP:
		switch (wparam)
		{
		case VK_UP:

			// Process the UP ARROW key. 
			upPressed = false;
			return 0;

		case VK_DOWN:
			// Process the DOWN ARROW key. 
			downPressed = false;
			return 0;

		case VK_LEFT:
			// Process the LEFT ARROW key. 
			leftPressed = false;
			return 0;

		case VK_RIGHT:
			// Process the RIGHT ARROW key.  
			rightPressed = false;
			return 0;

		case VK_SPACE:
			// Process the SPACEBAR.  
			spacePressed = false;
			return 0;

		case 0x57:
			//Process the 'w' key.
			wPressed = false;
			return 0;

		case 0x47:
			//Process the 'g' key
			gPressed = false;
			return 0;

		case 0x31:
			//Process the '1' key.
			onePressed = false;
			return 0;

		case 0x32:
			//Process the '2' key.
			twoPressed = false;
			return 0;

		case 0x33:
			//Process the '3' key.
			threePressed = false;
			return 0;

		case 0x34:
			//Process the '4' key.
			fourPressed = false;
			return 0;

		case 0x35:
			//Process the '5' key.
			fivePressed = false;
			return 0;

		case 0x36:
			//Process the '6' key.
			sixPressed = false;
			return 0;

		case 0x37:
			//Process the '7' key.
			sevenPressed = false;
			return 0;

		case 0x38:
			//Process the '8' key.
			eightPressed = false;
			return 0;
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
		break;
	}
	return DefWindowProc(hwnd, message, wparam, lparam);

}

