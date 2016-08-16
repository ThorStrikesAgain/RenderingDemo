#include <Windows.h>
#include <gl/GL.h>
#include <Wingdi.h>

#include <assert.h>
#include <iostream>

#include "Application.h"

using namespace std;

LRESULT CALLBACK Application::StaticMainWindowProc(
	HWND   hwnd,
	UINT   uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	return Application::Instance().InstanceMainWindowProc(hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK Application::InstanceMainWindowProc(
		HWND   hwnd,
		UINT   uMsg,
		WPARAM wParam,
		LPARAM lParam)
	{
	switch (uMsg)
	{
		case WM_CREATE:
		{
			assert(mOpenGLContext == NULL);
			mDeviceContext = GetWindowDC(hwnd);

			PIXELFORMATDESCRIPTOR pfd = {
				sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd
				1,                                // version number
				PFD_DRAW_TO_WINDOW |              // support window
				PFD_SUPPORT_OPENGL |              // support OpenGL
				PFD_DOUBLEBUFFER,                 // double buffered
				PFD_TYPE_RGBA,                    // RGBA type
				24,                               // 24-bit color depth
				0, 0, 0, 0, 0, 0,                 // color bits ignored
				0,                                // no alpha buffer
				0,                                // shift bit ignored
				0,                                // no accumulation buffer
				0, 0, 0, 0,                       // accum bits ignored
				32,                               // 32-bit z-buffer
				0,                                // no stencil buffer
				0,                                // no auxiliary buffer
				PFD_MAIN_PLANE,                   // main layer
				0,                                // reserved
				0, 0, 0                           // layer masks ignored
			};

			// get the device context's best, available pixel format match
			int iPixelFormat = ChoosePixelFormat(mDeviceContext, &pfd);

			// make that match the device context's current pixel format
			SetPixelFormat(mDeviceContext, iPixelFormat, &pfd);

			mOpenGLContext = wglCreateContext(mDeviceContext);
			assert(mOpenGLContext != NULL);

			BOOL success = wglMakeCurrent(mDeviceContext, mOpenGLContext);
			assert(success);

			return 0; // Continue the creation of the window.
		}
		case WM_PAINT:
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			glFlush();
			SwapBuffers(mDeviceContext);
			return 0; // Message processed.
		}
		case WM_CLOSE:
		{
			// TODO: We could confirm here.
			DestroyWindow(hwnd);
			return 0; // Message processed.
		}
		case WM_DESTROY:
		{
			// TODO: Destroy the OpenGL Context.
			BOOL success = wglDeleteContext(mOpenGLContext);
			assert(success);
			return 0; // Message processed.
		}
	}

	return DefWindowProc(hwnd, uMsg, wParam, lParam); // TODO.
}

void Application::Execute(HINSTANCE hInstance, int nCmdShow)
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
		CS_OWNDC;        // Allocate a unique device context for each window
	mainWindowClass.lpfnWndProc = StaticMainWindowProc;
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

	// Display the window.
	// TODO: Do this after drawing for the first time...
	ShowWindow(mainWindowHwnd, nCmdShow);

	// Main Loop.
	while (true)
	{
		//int ret = GetMessage;
		MSG msg;
		int ret = GetMessage(
			&msg,
			mainWindowHwnd,
			0, // Get all messages.
			0);
		if (ret == 0)
		{
			// WM_QUIT
			break;
		}
		if (ret == -1)
		{
			// TODO: Retrieve the error with GetLastError and handle it properly.
			break;
		}

		TranslateMessage(&msg); // Interpret key combinations.
		DispatchMessage(&msg); // Dispatch to the proper window proc.
	}
}
