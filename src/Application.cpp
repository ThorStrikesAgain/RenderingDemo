#include <Windows.h>
#include <gl/GL.h>

#include <assert.h>
#include <iostream>

#include "Application.h"

using namespace std;

LRESULT CALLBACK MainWindowProc(
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	return DefWindowProc(hwnd, uMsg, wParam, lParam); // TODO.
}

void Application::Execute(HINSTANCE hInstance)
{
	// Create the window class.
	LPCTSTR mainWindowClassName = L"MainWindow";
	WNDCLASSEX mainWindowClass;
	SecureZeroMemory(&mainWindowClass, sizeof(WNDCLASSEX));
	mainWindowClass.cbSize = sizeof(WNDCLASSEX);
	mainWindowClass.style =
		CS_GLOBALCLASS | // May be used by any module
		CS_DBLCLKS |     // Sends double-click events
		CS_HREDRAW |     // Redraws on horizontal resize
		CS_VREDRAW |     // Redraws on vertical resize
		CS_PARENTDC;     // Won't use parent device context
	mainWindowClass.lpfnWndProc = MainWindowProc;
	mainWindowClass.cbClsExtra = 0;
	mainWindowClass.cbWndExtra = 0;
	mainWindowClass.hInstance = hInstance;
	mainWindowClass.hIcon = NULL;
	mainWindowClass.hCursor = NULL;
	mainWindowClass.hbrBackground = NULL;
	mainWindowClass.lpszMenuName = NULL;
	mainWindowClass.lpszClassName = mainWindowClassName;
	mainWindowClass.hIconSm = NULL;
	ATOM mainWindowClassAtom = RegisterClassEx(&mainWindowClass);
	assert(mainWindowClassAtom != 0);

	// Create the window.
	HWND mainWindowHwnd = CreateWindowEx(
		WS_EX_LEFT,
		mainWindowClassName,
		L"Title", // TODO: Set title.
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, // TODO: Force a start location.
		CW_USEDEFAULT,
		480, // TODO: Force another resolution.
		360,
		NULL, // No Parent
		NULL, // No menu
		hInstance,
		NULL); // No additional data
	assert(mainWindowHwnd != NULL);
}
