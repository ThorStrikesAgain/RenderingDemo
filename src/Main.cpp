#include <Windows.h>

#include "Application.h"

// TODO: Define wWinMain to support Unicode.
int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nCmdShow)
{
	Application app;
	app.Execute(hInstance, nCmdShow);

	// TODO: Return the exit value contained in the message's wParam, or zero if before entering the message loop.
	// See https://msdn.microsoft.com/en-us/library/windows/desktop/ms633559(v=vs.85).aspx
	return 0;
}
