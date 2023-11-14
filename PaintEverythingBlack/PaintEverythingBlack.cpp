// Базовый код
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

using namespace std;

void GetMonitorSize(int* pixelsWidth, int* pixelsHeight)
{
	HDC screen = GetDC(NULL);
	double dpi = GetDpiForWindow(GetForegroundWindow()) / 96.0;
	*pixelsWidth = GetDeviceCaps(screen, HORZRES) * dpi;
	*pixelsHeight = GetDeviceCaps(screen, VERTRES) * dpi;
	ReleaseDC(NULL, screen);
}

int main() {
	int width;
	int height;
	while (true) {
		GetMonitorSize(&width, &height);
		HWND hWnd = GetDesktopWindow();
		HDC hDCScreen = GetDC(hWnd);
		HDC hDCCompat = CreateCompatibleDC(hDCScreen);
		HBITMAP hBitmap = CreateCompatibleBitmap(hDCScreen, width, height);
		SelectObject(hDCCompat, hBitmap);
		//Rectangle(hDCCompat, 0, 0, width, height);
		BitBlt(hDCScreen, 0, 0, width, height, hDCCompat, 0, 0, SRCCOPY);
		DeleteObject(hBitmap);
		DeleteDC(hDCCompat);
		ReleaseDC(NULL, hDCScreen);
	}
}