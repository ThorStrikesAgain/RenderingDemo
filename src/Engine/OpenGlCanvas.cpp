#include <Windows.h>
#include <assert.h>
#include <GL/GL.h>

HMODULE sModule;
HGLRC sOpenGlContext;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    sModule = hModule;

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR),
            1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
            PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
            32,                        //Colordepth of the framebuffer.
            0, 0, 0, 0, 0, 0,
            0,
            0,
            0,
            0, 0, 0, 0,
            24,                        //Number of bits for the depthbuffer
            8,                        //Number of bits for the stencilbuffer
            0,                        //Number of Aux buffers in the framebuffer.
            PFD_MAIN_PLANE,
            0,
            0, 0, 0
        };

        HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

        int  letWindowsChooseThisPixelFormat;
        letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
        SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

        sOpenGlContext = wglCreateContext(ourWindowHandleToDeviceContext);
        wglMakeCurrent(ourWindowHandleToDeviceContext, sOpenGlContext);
    }
    case WM_PAINT:
    {
        HDC ourWindowHandleToDeviceContext = GetDC(hWnd);
        wglMakeCurrent(ourWindowHandleToDeviceContext, sOpenGlContext);
        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;

}

extern "C" __declspec(dllexport) HWND DoBuildWindowCore(HWND hwndParent, int width, int height)
{
    // Create the window class.
    WNDCLASSEX mainWindowClass;
    SecureZeroMemory(&mainWindowClass, sizeof(WNDCLASSEX));
    mainWindowClass.cbSize = sizeof(WNDCLASSEX);
    mainWindowClass.style = CS_OWNDC; // Allocate a unique device context for each window
    mainWindowClass.lpfnWndProc = WndProc;
    mainWindowClass.cbClsExtra = 0;
    mainWindowClass.cbWndExtra = 0;
    mainWindowClass.hInstance = sModule;
    mainWindowClass.hIcon = NULL;
    mainWindowClass.hCursor = NULL;
    mainWindowClass.hbrBackground = NULL;
    mainWindowClass.lpszMenuName = NULL;
    mainWindowClass.lpszClassName = "MainWindow";
    mainWindowClass.hIconSm = NULL;
    ATOM mainWindowClassAtom = RegisterClassEx(&mainWindowClass);
    assert(mainWindowClassAtom != 0);

    // Create the window.
    HWND mainWindowHwnd = CreateWindowEx(
        0,
        "MainWindow", // Window Class
        "", // Title
        WS_CHILD | WS_VISIBLE,
        0,
        0,
        width,
        height,
        hwndParent,
        NULL, // No menu
        sModule, // hInstance
        NULL); // No additional data
    assert(mainWindowHwnd != NULL);

    return mainWindowHwnd;
}

extern "C" __declspec(dllexport) void DoDestroyWindowCore(HWND hwnd)
{
    wglDeleteContext(sOpenGlContext);
    DestroyWindow(hwnd);
}
