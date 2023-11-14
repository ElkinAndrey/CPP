#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

VOID OnPaint(HDC hdc)
{
    Graphics graphics(hdc);
    graphics.Clear(Color(0, 0, 0, 0));
    Pen      pen(Color(255, 255, 255, 255));

    // Линия
    graphics.DrawLine(&pen, 10, 10, 100, 50);

    // Многоугольник линиями
    PointF point1(100.0f, 100.0f);
    PointF point2(200.0f, 130.0f);
    PointF point3(150.0f, 200.0f);
    PointF point4(50.0f, 200.0f);
    PointF point5(0.0f, 130.0f);
    PointF points[5] = { point1, point2, point3, point4, point5 };
    PointF* pPoints = points;
    graphics.DrawPolygon(&pen, pPoints, 5);

    // Нарисовать закрашенный многоугольник
    PointF point12(200, 400);
    PointF point22(500, 330);
    PointF point32(100, 630);
    PointF points2[3] = { point12, point22, point32 };
    PointF* pPoints2= points2;
    SolidBrush solidBrush2(Color(255, 255, 255, 255));
    graphics.FillPolygon(&solidBrush2, pPoints2, 3);
}

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, PSTR, INT iCmdShow)
{
    HWND                hWnd;
    MSG                 msg;
    WNDCLASS            wndClass;
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR           gdiplusToken;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    wndClass.style = CS_HREDRAW | CS_VREDRAW;
    wndClass.lpfnWndProc = WndProc;
    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hInstance = hInstance;
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.lpszMenuName = NULL;
    wndClass.lpszClassName = TEXT("GettingStarted");

    RegisterClass(&wndClass);

    hWnd = CreateWindow(
        TEXT("GettingStarted"),   // window class name
        TEXT("Getting Started"),  // window caption
        WS_OVERLAPPEDWINDOW,      // window style
        CW_USEDEFAULT,            // initial x position
        CW_USEDEFAULT,            // initial y position
        CW_USEDEFAULT,            // initial x size
        CW_USEDEFAULT,            // initial y size
        NULL,                     // parent window handle
        NULL,                     // window menu handle
        hInstance,                // program instance handle
        NULL);                    // creation parameters

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GdiplusShutdown(gdiplusToken);
    return msg.wParam;
}  // WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
    WPARAM wParam, LPARAM lParam)
{
    HDC          hdc;
    PAINTSTRUCT  ps;

    switch (message)
    {
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        OnPaint(hdc);
        EndPaint(hWnd, &ps);
        return 0;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
} // WndProc