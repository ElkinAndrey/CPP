#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <math.h>
#include <complex>
#include <stdio.h>

using namespace std;

double x, y;
int WindowWidth = 1200; // Ширина окна приложения
int WindowHeight = 800; // Высота окна приложения
int CenterX = WindowWidth / 2 + 100;
int CenterY = WindowHeight / 2 - 30;
int d = 1;
int maxIter = 30;
double zoom = 2.5 / WindowHeight;



void DoSet(RGBQUAD* arr) {
    for (int y = 0; y < WindowHeight; y++)
        for (int x = 0; x < WindowWidth; x++)
        {
            complex< double > c((x - CenterX) * zoom, (y - CenterY) * zoom);
            complex< double > z = 0;
            int numIter = 0;
            for (int f = 0; f < maxIter; f++) {
                z = z * z + c;
                if (abs(z) > 2)
                    break;
                numIter++;
            }
            numIter *= 10;
            arr[x + WindowWidth * y].rgbRed = numIter;
            arr[x + WindowWidth * y].rgbBlue = numIter;
            arr[x + WindowWidth * y].rgbGreen = numIter;
        }
}


// Функция для фиксации изменений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Функция, выводящая изображение на экран
void func(HDC hdc) {
    BITMAPINFO bif;
    ZeroMemory(&bif, sizeof(BITMAPINFO));
    bif.bmiHeader.biSize = sizeof(bif);
    RGBQUAD* arr = new RGBQUAD[WindowWidth * WindowHeight];

    DoSet(arr);


    // Вывод массива
    bif.bmiHeader.biHeight = -WindowHeight;
    bif.bmiHeader.biWidth = WindowWidth;
    bif.bmiHeader.biSizeImage = WindowWidth * WindowHeight;
    bif.bmiHeader.biPlanes = 1;
    bif.bmiHeader.biBitCount = sizeof(RGBQUAD) * 8;
    SetDIBitsToDevice(hdc, 0, 0, WindowWidth, WindowHeight, 0, 0, 0, WindowHeight, arr, &bif, DIB_PAL_COLORS);
    delete[] arr;

}

// Главная функция
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int iCmdShow) {
    static  TCHAR szAppName[] = TEXT("CircleDemoApp");
    HWND        hwnd;
    MSG         msg;
    WNDCLASS    wndclass;

    wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION); // Указать иконку
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW); // Указать курсор
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // Указать задний фон
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program requires Windows NT!"),
            szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName,                         // window class name
        TEXT(" "), // window caption
        WS_OVERLAPPEDWINDOW, // стиль окна
        10, // начальная позиция x
        40, // начальная позиция y
        WindowWidth, // начальный размер x
        WindowHeight, // начальный размер y
        NULL, // дескриптор родительского окна
        NULL, // дескриптор меню окна
        hInstance, // дескриптор экземпляра программы
        NULL); // параметры создания

    SetTimer(hwnd, 1, 100, nullptr); // Установление таймера
    ShowWindow(hwnd, iCmdShow); // Запуск окна
    UpdateWindow(hwnd); // Не надо

    HDC dc = GetDC(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (msg.message == WM_QUIT) break; // Закрытике окна
        TranslateMessage(&msg); // Сообщение о поступлении символа
        DispatchMessage(&msg);

    }

    return msg.wParam;
}

// Тут выполняются разные состояния приложения
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    switch (message)
    {
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        func(hdc);
        EndPaint(hwnd, &ps);

        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_TIMER: {
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_DESTROY: // При закрытии
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}