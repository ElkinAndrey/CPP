#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


#define ID_TIMER 1
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
COLORREF* arr = (COLORREF*)calloc(400 * 300, sizeof(COLORREF));

int WindowWidth = 2200;
int WindowHeight = 1100;
int Red = 252;
int Green = 0;
int Blue = 0;



void ArrayFormation() {
    for (int x = 0; x < 400 * 300; x++) {
        arr[x] = RGB(Blue, Green, Red);
    }

}


void func(HDC hdc) {

    BITMAPINFO bif;
    ZeroMemory(&bif, sizeof(BITMAPINFO));
    bif.bmiHeader.biSize = sizeof(bif);
    RGBQUAD* arr = new RGBQUAD[2200 * 1100];
    // Заполнение массива черным цветом
    for (int i = 0; i < 2200 * 1100; i++) {
        arr[i].rgbRed = Red;
        arr[i].rgbBlue = Green;
        arr[i].rgbGreen = Blue;
    }
    getchar();

    // Вывод массива
    bif.bmiHeader.biHeight = -WindowHeight;
    bif.bmiHeader.biWidth = WindowWidth;
    bif.bmiHeader.biSizeImage = WindowWidth * WindowHeight;
    bif.bmiHeader.biPlanes = 1;
    bif.bmiHeader.biBitCount = sizeof(RGBQUAD) * 8;
    SetDIBitsToDevice(hdc, 0, 0, WindowWidth, WindowHeight, 0, 0, 0, WindowHeight, arr, &bif, DIB_PAL_COLORS);
    delete arr;

}


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
        TEXT("Comparing Circle Drawings"), // window caption
        WS_OVERLAPPEDWINDOW, // стиль окна
        10, // начальная позиция x
        50, // начальная позиция y
        400, // начальный размер x
        300, // начальный размер y
        NULL, // дескриптор родительского окна
        NULL, // дескриптор меню окна
        hInstance, // дескриптор экземпляра программы
        NULL); // параметры создания

    SetTimer(hwnd, ID_TIMER, 100, nullptr); // Установление таймера
    ShowWindow(hwnd, iCmdShow); // Запуск окна
    UpdateWindow(hwnd); // Не надо

    HDC dc = GetDC(hwnd);
    while (true)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break; // Закрытике окна
            TranslateMessage(&msg); // Сообщение о поступлении символа
            DispatchMessage(&msg);
        }
    }

    return msg.wParam;
}


// Тут выполняются разные состояния приложения
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    int timing = 3;
    switch (message)
    {
    case WM_PAINT:
    {
        hdc = BeginPaint(hwnd, &ps);
        func(hdc);
        EndPaint(hwnd, &ps);

        return 0;
    }
    case WM_TIMER: {
        if (Red == 252 and Blue == 0 and Green == 0) {
            Blue += timing;
        }
        else if (Red == 252 and Green == 0 and Blue > 0 and Blue < 252) {
            Blue += timing;
        }
        else if (Red == 252 and Blue == 252 and Green == 0) {
            Red -= timing;
        }
        else if (Red > 0 and Red < 252 and Blue == 252 and Green == 0) {
            Red -= timing;
        }
        else if (Red == 0 and Blue == 252 and Green == 0) {
            Green += timing;
        }
        else if (Red == 0 and Blue == 252 and Green > 0 and Green < 252) {
            Green += timing;
        }
        else if (Red == 0 and Blue == 252 and Green == 252) {
            Blue -= timing;
        }
        else if (Red == 0 and Blue < 252 and Blue >0 and Green == 252) {
            Blue -= timing;
        }
        else if (Blue == 0 and Red == 0 and Green == 252) {
            Red += timing;
        }
        else if (Blue == 0 and Green == 252 and Red > 0 and Red < 252) {
            Red += timing;
        }
        else if (Blue == 0 and Red == 252 and Green == 252) {
            Green -= timing;
        }
        else if (Blue == 0 and Red == 252 and Green > 0 and Green < 252) {
            Green -= timing;
        }
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_DESTROY: // При закрытии
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, message, wParam, lParam);
}