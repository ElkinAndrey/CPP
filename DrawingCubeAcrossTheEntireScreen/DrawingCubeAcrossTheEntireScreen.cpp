#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const wchar_t CLASS_NAME[] = L"GDIAnimationWindowClass";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST, // Set the extended window style for transparency and layered topmost window
        CLASS_NAME,
        L"GDI Animation",
        WS_POPUP, // Use a borderless window so it doesn't appear as a separate application
        0,
        0,
        GetSystemMetrics(SM_CXSCREEN),
        GetSystemMetrics(SM_CYSCREEN),
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    // Set the window as a transparent layered window
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static int xPos, yPos;
    static int xDir, yDir;
    static RECT desktopRect;

    switch (msg)
    {
    case WM_CREATE:
    {
        GetClientRect(GetDesktopWindow(), &desktopRect);

        // Animation initial position and direction
        xPos = desktopRect.right / 2; // Start in the center of the screen
        yPos = desktopRect.bottom / 2;
        xDir = 2; // Move 2 pixels at a time horizontally
        yDir = 2; // Move 2 pixels at a time vertically

        SetTimer(hwnd, 1, 10, NULL); // Timer for animation refresh
    }
    break;

    case WM_TIMER:
    {
        if (wParam == 1)
        {
            // Animation update
            xPos += xDir;
            yPos += yDir;

            // Check if animation hits the screen boundaries
            if (xPos <= 0 || xPos >= desktopRect.right - 100) // Assuming the width of animated object is 100
            {
                xDir = -xDir; // Reverse direction
            }
            if (yPos <= 0 || yPos >= desktopRect.bottom - 100) // Assuming the height of animated object is 100
            {
                yDir = -yDir; // Reverse direction
            }

            // Redraw window
            InvalidateRect(hwnd, NULL, TRUE);
        }
    }
    break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Draw animated object (a simple rectangle)
        Rectangle(hdc, xPos, yPos, xPos + 100, yPos + 100); // Size of animated object is set as 100x100

        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}