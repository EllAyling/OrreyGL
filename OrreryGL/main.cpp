#include "system.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int iCmdShow)
{
	SystemClass* System;
	System = new SystemClass;

	bool result;

	result = System->Init(iCmdShow);
	if (result)							//If initialised correctly, run the program.
	{
		System->Run();
	}
	System->Stop();
	return 0;
}