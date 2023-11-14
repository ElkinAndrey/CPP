#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;

/// <summary>
/// Получить dpi (масштаб экрана) у windows
/// </summary>
/// <returns>dpi (масштаб экрана)</returns>
double GetDpi() {
	HDC screen = GetDC(NULL);
	double dpi = GetDpiForWindow(GetForegroundWindow()) / 96.0;
	ReleaseDC(NULL, screen);
	return dpi;
}

/// <summary>
/// Узнать ширину и высоту экрана в пикселях
/// </summary>
/// <param name="pixelsWidth">Ширина экрана в пикселях</param>
/// <param name="pixelsHeight">Высота экрана в пикселях</param>
void GetMonitorSize(int* pixelsWidth, int* pixelsHeight)
{
	HDC screen = GetDC(NULL);
	double dpi = GetDpiForWindow(GetForegroundWindow()) / 96.0;
	*pixelsWidth = GetDeviceCaps(screen, HORZRES) * dpi;
	*pixelsHeight = GetDeviceCaps(screen, VERTRES) * dpi;
	ReleaseDC(NULL, screen);
}

int main() {
	int x;
	int y;
	GetMonitorSize(&x, &y);
	cout << x << " " << y;
}