#include <windows.h>
#include <iostream>
#include <cmath>

struct pixel {
	union {
		struct {
			/* 'a' не используется, используется для 32-битного выравнивания,
			* также может использоваться для хранения альфа-пикселя
			*/
			unsigned char b, g, r, a;
		};
		int val;
	};

	pixel() {
		val = 0;
	}
};

// Размер клиента окна
const int width = 375;
const int height = 375;

/* Целевой fps, хотя достичь этого fps сложно
* без дополнительных функций таймера, если у вас нет
* мощный процессор. Увеличение этого значения приведет
* увеличьте скорость, хотя это будет использовать больше процессора.
*/
const int fps = 1000;

// Глобальные переменные Windows/Рисования
HBITMAP hbmp;
HANDLE hTickThread;
HWND hwnd;
HDC hdcMem;

// Указатель на пиксели (с помощью CreateDIBSection автоматически будет выделено пространство
pixel* pixels;


void onFrame(pixel* pixels) {
	// Здесь происходит все рисование

	pixel* p;

	// +0,005 каждый кадр
	static float frameOffset = 0;

	float px; // % пути по растровому изображению
	float py; // % пути вниз по растровому изображению

	for (int x = 0; x < width; ++x) {
		for (int y = 0; y < height; ++y) {
			p = &pixels[y * width + x];

			px = float(x) / float(width);
			py = float(y) / float(height);

			p->r = unsigned char(((cos(px + frameOffset * 10) / sin(py + frameOffset)) * cos(frameOffset * 3) * 10) * 127 + 127);
			p->g = ~p->r;
			p->b = 255;
		}
	}

	frameOffset += 0.005f;
}



DWORD WINAPI tickThreadProc(HANDLE handle) {
	// Даем достаточно времени основному потоку, чтобы завершить настройку
	Sleep(50);
	ShowWindow(hwnd, SW_SHOW);

	// Получаем DC окна
	HDC hdc = GetDC(hwnd);

	// Создаем DC с общими пикселями для переменной 'pixels'
	hdcMem = CreateCompatibleDC(hdc);
	HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, hbmp);

	// Миллисекунды ожидания каждого кадра
	int delay = 1000 / fps;

	for (;; ) {
		// Делаем что-то с пикселями
		onFrame(pixels);

		// Рисуем пиксели в окне
		BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

		// Ждать
		Sleep(delay);
	}

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdc);
}

void MakeSurface(HWND hwnd) {
	/* Используйте CreateDIBSection, чтобы создать HBITMAP, который можно быстро
	* переносится на поверхность, обеспечивая 100% быстрый доступ к пикселям
	* перед блит.
	*/

	// Желаемые свойства растрового изображения
	BITMAPINFO bmi;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmi.bmiHeader.biWidth = width;
	bmi.bmiHeader.biHeight = -height; // Order pixels from top to bottom
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32; // last byte not used, 32 bit for alignment
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiColors[0].rgbBlue = 0;
	bmi.bmiColors[0].rgbGreen = 0;
	bmi.bmiColors[0].rgbRed = 0;
	bmi.bmiColors[0].rgbReserved = 0;

	HDC hdc = GetDC(hwnd);

	// Создаем раздел DIB, чтобы всегда предоставлять прямой доступ к пикселям
	hbmp = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, (void**)&pixels, NULL, 0);
	DeleteDC(hdc);

	// Создаем новый поток для использования в качестве таймера
	hTickThread = CreateThread(NULL, NULL, &tickThreadProc, NULL, NULL, NULL);
}

LRESULT CALLBACK WndProc(
	HWND hwnd,
	UINT msg,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (msg) {
	case WM_CREATE:
	{
		MakeSurface(hwnd);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// Рисуем пиксели в окне, когда окно нужно перерисовать
		BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

		EndPaint(hwnd, &ps);
	}
	break;
	case WM_CLOSE:
	{
		DestroyWindow(hwnd);
	}
	break;
	case WM_DESTROY:
	{
		TerminateThread(hTickThread, 0);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}

	return 0;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nShowCmd)
{
	WNDCLASSEX wc;
	MSG msg;

	// Инициализируем туалет
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hbrBackground = CreateSolidBrush(0);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = TEXT("animation_class");
	wc.lpszMenuName = NULL;
	wc.style = 0;

	// Регистрируем туалет
	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, TEXT("Failed to register window class."), TEXT("Error"), MB_OK);
		return 0;
	}

	// Создать окно
	hwnd = CreateWindowEx(
		WS_EX_APPWINDOW,
		TEXT("animation_class"),
		TEXT("Animation"),
		WS_MINIMIZEBOX | WS_SYSMENU | WS_POPUP | WS_CAPTION,
		300, 200, width, height,
		NULL, NULL, hInstance, NULL);


	RECT rcClient, rcWindow;
	POINT ptDiff;

	// Получаем размеры окна и клиента
	GetClientRect(hwnd, &rcClient);
	GetWindowRect(hwnd, &rcWindow);

	// Находим смещение между размером окна и размером клиента
	ptDiff.x = (rcWindow.right - rcWindow.left) - rcClient.right;
	ptDiff.y = (rcWindow.bottom - rcWindow.top) - rcClient.bottom;

	// Изменяем размер клиента
	MoveWindow(hwnd, rcWindow.left, rcWindow.top, width + ptDiff.x, height + ptDiff.y, false);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, NULL) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}