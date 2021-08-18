/// Define unicode standard
#ifndef UNICODE
#define UNICODE
#endif

/// Includes
#include <iostream>
#include <windows.h>

/// Forward declarations
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void OnDraw(HWND);

/// Main program entry-point
/// \param hInstance the program instance
/// \param hPrevInstance legacy for 16-bit Windows that is now always 0
/// \param pCmdLine command line arguments as a Unicode string
/// \param nCmdShow a flag that says whether the main application window will be minimized, maximized, or shown normally
/// \return an integer value that can be used to convey status codes to other program. The OS does not use the return value
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"My Window Class";

    WNDCLASS wc = {};

    // These three parameters must be set
    wc.lpfnWndProc = WindowProc;    // a pointer to an application-defined function called the window procedure (the message loop function)
    wc.hInstance = hInstance;       // the handle to the application instance. This should always be the hInstance parameter of wWinMain
    wc.lpszClassName = CLASS_NAME;  // a string that identifies the window class. This must be unique

    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(
            0,                              // Optional window styles (0 is default, other values indicate other things like transparency)
            CLASS_NAME,                     // Window class
            L"Learn to Program Windows",    // Window text (By default, this is the window title. Can be used in other ways)
            WS_OVERLAPPEDWINDOW,            // Window style (WS_OVERLAPPEDWINDOW is the most commonly used flag)
            // Size and position : X, Y, nWidth, nHeight - Currently using defaults
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            NULL,       // Parent Window (null for top-level window, or the HWND instance of the parent)
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
            );

    // If creation failed, return 0
    if(hwnd == NULL) {
        return 0;
    }

    // Show the window
    ShowWindow(hwnd, nCmdShow); // nCmdShow can be used for initial window state like minimized or maximized

    // Run the message loop until no more messages are received
    MSG msg = {};
    while(GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg); // Always call before DispatchMessage
        DispatchMessage(&msg); // Calls the window procedure (WindowProc)
    }
    return 0;
}

/// The main message loop for the window
/// \param hwnd a handle to the window
/// \param uMsg the message
/// \param wParam additional message information. The contents of this parameter depend on the value of the uMsg parameter
/// \param lParam additional message information. The contents of this parameter depend on the value of the uMsg parameter
/// \return the result of the message processing
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    // Determine which type of message was received
    switch(uMsg) {
        case WM_CLOSE:
            if(MessageBox(hwnd, L"Are you sure you would like to quit?", L"Exit Application", MB_OKCANCEL) == IDOK) {
                DestroyWindow(hwnd);
            }
            return 0;
        case WM_DESTROY:
            // Terminates the message loop. Posts a WM_QUIT message that causes GetMessage to return 0
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            // Draw to the screen
            OnDraw(hwnd);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

/// Draws to the window
/// \param hwnd a handle to the window
void OnDraw(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);

    // Draw Code
    FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));
    EndPaint(hwnd, &ps);
}