#define _WIN32_WINNT 0x500
#include <windows.h>
#include <gdiplus.h>

using namespace Gdiplus;

#pragma comment (lib,"Gdiplus.lib")

BOOL CALLBACK MonitorEnumProc(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData)
{
    MONITORINFOEXW info;
    info.cbSize = sizeof(info);
    ::GetMonitorInfoW(hMonitor, &info);

    HWND hDesktopWindow = GetDesktopWindow();


    //Calling GetDC with argument NULL retrieves the desktop's DC
    HDC hdc = GetDCEx(hDesktopWindow, NULL, DCX_CACHE | DCX_LOCKWINDOWUPDATE);

    {
        Gdiplus::Graphics graphics(hdc);

        FontFamily  fontFamily(L"Times New Roman");
        Font        font(&fontFamily, 24, FontStyleRegular, UnitPixel);
        SolidBrush  brush(Color(255, 0, 0, 255));
        graphics.Clear(Color(0, 0, 0, 0));
    }

    ::DeleteDC(hdc);

    return TRUE;
}

int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    ULONG_PTR m_gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&m_gdiplusToken, &gdiplusStartupInput, NULL);

    while (true)
    {
        ::EnumDisplayMonitors(NULL, NULL, MonitorEnumProc, NULL);
    }

    Gdiplus::GdiplusShutdown(m_gdiplusToken);

    return 0;
}