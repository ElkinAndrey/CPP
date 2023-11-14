#include <iostream>
#include <cmath>
#include <windows.h>
#include <gdiplus.h>
#pragma comment (lib,"Gdiplus.lib")
using namespace Gdiplus;
using namespace std;

// Global Variables
HWND hwnd;
HDC hdc;
Graphics* graphics;
HDC backHdc;
HBITMAP backBitmap;
HBITMAP oldBitmap;
ULONG_PTR gdiplusToken;
int w = 750;
int h = 500;

double angle = 0.0;

PointF* points = new PointF[12]{
	PointF(0, 1),
	PointF(0, 3),
	PointF(0, 4),
	PointF(1, 2),

	PointF(1, 5),
	PointF(2, 3),
	PointF(2, 6),
	PointF(3, 7),

	PointF(4, 5),
	PointF(4, 7),
	PointF(5, 6),
	PointF(6, 7),
};

class MyMatrix {
private:
	int matrixHeight;
	int matrixWidth;
	double* p;
public:
	MyMatrix(int height, int width) {
		this->matrixHeight = height;
		this->matrixWidth = width;
		this->p = new double[height * width]();
	}

	MyMatrix(int height, int width, double* mas) {
		this->matrixHeight = height;
		this->matrixWidth = width;
		this->p = new double[height * width]();
		for (int i = 0; i < height * width; ++i) {
			this->p[i] = mas[i];
		}
	}

	double Get(int height, int width) {
		return p[height * matrixWidth + width];
	}

	void Set(int height, int width, double value) {
		p[height * matrixWidth + width] = value;
	}

	int Height() const {
		return matrixHeight;
	}

	int Width() const {
		return matrixWidth;
	}

	MyMatrix* ReinjureMatrices(const MyMatrix* matrix) const
	{
		if (this->Width() != matrix->Height())
			return new MyMatrix(0, 0);

		MyMatrix* m = new MyMatrix(this->Height(), matrix->Width());
		for (int i = 0; i < this->Height(); i++)
			for (int j = 0; j < matrix->Width(); j++)
			{
				m->p[i * matrixWidth + j] = 0;
				for (int k = 0; k < matrix->Height(); k++) {
					m->p[i * matrixWidth + j] += this->p[i * matrixWidth + k] * matrix->p[k * matrixWidth + j];
				}

			}

		return m;
	}

	// Перегрузка оператора умножения для указателей
	MyMatrix* operator*(const MyMatrix* other) const
	{
		MyMatrix* m = this->ReinjureMatrices(other);

		return m;
	}

	~MyMatrix() {
		delete p;
	}
};

void DrawMatrix(Graphics& graphics, MyMatrix* m, PointF* points, int size) {

	Pen blackPen(Color(255, 255, 255, 255), 1);

	for (int i = 0; i < size; ++i) {
		int x1 = std::round(m->Get(points[i].X, 0));
		int y1 = std::round(m->Get(points[i].X, 1));
		int x2 = std::round(m->Get(points[i].Y, 0));
		int y2 = std::round(m->Get(points[i].Y, 1));

		graphics.DrawLine(&blackPen, x1, y1, x2, y2);
	}
}

MyMatrix* m = new MyMatrix(8, 4, new double[8 * 4]
	{
		/*a*/100 / 2, 300 / 2, 000 / 2, 1,
			/*b*/300 / 2, 200 / 2, 000 / 2, 1,
			/*c*/200 / 2, 000 / 2, 000 / 2, 1,
			/*d*/000 / 2, 100 / 2, 000 / 2, 1,
			/*e*/100 / 2, 300 / 2, 200 / 2, 1,
			/*f*/300 / 2, 200 / 2, 200 / 2, 1,
			/*g*/200 / 2, 000 / 2, 200 / 2, 1,
			/*h*/000 / 2, 100 / 2, 200 / 2, 1,
	});

MyMatrix* mAngle1 = new MyMatrix(4, 4, new double[4 * 4]
	{
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
	});

MyMatrix* mAngle2 = new MyMatrix(4, 4, new double[4 * 4]
	{
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
	});

MyMatrix* moveCenter = new MyMatrix(4, 4, new double[4 * 4]
	{
		1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1,
	});

void DrawSq(Graphics& graphics, int x, int y, double startAngle) {
	mAngle1->Set(1, 1, cos(startAngle + angle));
	mAngle1->Set(2, 1, -sin(startAngle + angle));
	mAngle1->Set(1, 2, sin(startAngle + angle));
	mAngle1->Set(2, 2, cos(startAngle + angle));

	mAngle2->Set(0, 0, cos(startAngle + angle));
	mAngle2->Set(0, 2, -sin(startAngle + angle));
	mAngle2->Set(2, 0, sin(startAngle + angle));
	mAngle2->Set(2, 2, cos(startAngle + angle));


	moveCenter->Set(3, 0, x * 1.0);
	moveCenter->Set(3, 1, y * 1.0);

	auto mat1 = *m * mAngle1;
	auto mat2 = *mat1 * mAngle2;

	auto mat3 = *mat2 * moveCenter;

	DrawMatrix(graphics, mat3, points, 12);

	delete mat1;
	delete mat2;
	delete mat3;

	//delete mAngle2;
	/*delete mAngle1;
	delete move;
	delete newM;*/

}

void Draw(Graphics& graphics) {
	for (int i = 0; i < 10; i++) {
		DrawSq(graphics, i + 200, i + 200, i * 1);
	}

	//Pen blackPen(Color(255, 255, 255, 255), 1);
	//PointF point1(100.0f, 100.0f);
	//PointF point2(200.0f, 130.0f);
	//PointF point3(150.0f, 200.0f);
	//PointF points[5] = { point1, point2, point3 };
	//PointF* pPoints = points;
	//graphics.DrawPolygon(&blackPen, pPoints, 3);
}

// Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_CREATE:
	{
		// Create a compatible HDC and Graphics object for double buffering
		hdc = GetDC(hwnd);
		graphics = new Graphics(hdc);
		backHdc = CreateCompatibleDC(hdc);
		backBitmap = CreateCompatibleBitmap(hdc, w, h);
		oldBitmap = (HBITMAP)SelectObject(backHdc, backBitmap);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);

		// Erase the previous frame
		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(backHdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

		// Draw the animated object
		Graphics graphics(backHdc);
		graphics.Clear(Color(0, 0, 0, 0));
		Pen blackPen(Color(255, 255, 255, 255), 1);
		Draw(graphics);

		// Swap the buffers
		BitBlt(hdc, 0, 0, w, h, backHdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	}
	case WM_TIMER:
	{
		// Update the animation position
		angle += 0.01;

		// Force a redraw
		InvalidateRect(hwnd, NULL, FALSE);
		break;
	}
	case WM_DESTROY:
	{
		// Clean up resources and exit the application
		SelectObject(backHdc, oldBitmap);
		DeleteObject(backBitmap);
		DeleteDC(backHdc);
		delete graphics;
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	}
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

// Entry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	// Register the window class
	const wchar_t CLASS_NAME[] = L"SimpleAnimation";
	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	RegisterClass(&wc);

	// Create the window
	hwnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Simple Animation",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, w, h,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL) {
		return 0;
	}

	// Initialize GDI+
	GdiplusStartupInput gdiplusStartupInput;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Start the animation timer
	SetTimer(hwnd, 1, 1000 / 75.0, NULL);

	// Display the window
	ShowWindow(hwnd, nCmdShow);

	// Main message loop
	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Shut down GDI+
	GdiplusShutdown(gdiplusToken);

	return 0;
}