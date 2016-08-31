#pragma once

#include <Windows.h>
#include <gl/GL.h>

class Application
{
public:
	static Application& Instance()
	{
		static Application sApplication;
		return sApplication;
	}

	void Execute(HINSTANCE hInstance,int nCmdShow);

private:
	// Singleton
	Application() {}
	~Application() {}
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	// OpenGL
	HDC mDeviceContext = NULL;
	HGLRC mOpenGLContext = NULL;

	LRESULT CALLBACK InstanceMainWindowProc(
		HWND   hwnd,
		UINT   uMsg,
		WPARAM wParam,
		LPARAM lParam);

	static LRESULT CALLBACK StaticMainWindowProc(
		HWND   hwnd,
		UINT   uMsg,
		WPARAM wParam,
		LPARAM lParam);
};
