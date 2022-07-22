#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <list>



using namespace std;

struct Cord {
    int x;
    int y;
    Cord() {}
    Cord(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

Cord Apple;
const int WindowWidth = 150 * 10; // Ширина окна приложения
const int WindowHeight = 70 * 10; // Высота окна приложения

int Red = 0;
int Blue = 0;
int Green = 255;
char direction = 'l';
int mas[WindowHeight / 10][WindowWidth / 10];

list<Cord> cords;




// Функция для фиксации изменений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

bool Check(int x, int y) {
    return ((x + WindowWidth * int(y) > 0) and (x + WindowWidth * int(y) <= WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) <= WindowWidth - 1));
}

void VertLine(RGBQUAD* arr, int x, int y, int Red, int Blue, int Green) {
    for (int i = -1; i < 2; i++) {
        if (Check(x, y + i)) {
            arr[x + WindowWidth * int(y + i)].rgbRed = Red;
            arr[x + WindowWidth * int(y + i)].rgbBlue = Blue;
            arr[x + WindowWidth * int(y + i)].rgbGreen = Green;
        }
    }
}

void HorLine(RGBQUAD* arr, int x, int y, int Red, int Blue, int Green) {
    for (int i = -1; i < 2; i++) {
        if (Check(x + i, y)) {
            arr[x + i + WindowWidth * int(y)].rgbRed = Red;
            arr[x + i + WindowWidth * int(y)].rgbBlue = Blue;
            arr[x + i + WindowWidth * int(y)].rgbGreen = Green;
        }
    }
}

void Pixel(RGBQUAD* arr, int x, int y, int Red, int Green, int Blue) {
    for (int i = x; i < x + 10; i++)
        for (int j = y; j < y + 10; j++)
            if (Check(x, y)) {
                arr[i + WindowWidth * int(j)].rgbRed = Red;
                arr[i + WindowWidth * int(j)].rgbBlue = Blue;
                arr[i + WindowWidth * int(j)].rgbGreen = Green;
            }

}

Cord RandApple() {
    while (true) {
        bool flag = false;
        Cord a(rand() % (WindowWidth / 10), rand() % (WindowHeight / 10));
        for (auto iter = cords.begin(); iter != cords.end(); iter++)
            if (iter->x == a.x and iter->y == a.y) {
                flag = true;
                break;
            }
        if (!flag)
            return a;
    }
}

void Snake() {

    if (cords.front().x == Apple.x and cords.front().y == Apple.y) {
        cords.push_front(cords.back());
    }
    else {
        // Поставить голову
        if (direction == 'u') {
            if (cords.front().x == Apple.x and cords.front().y - 1 == Apple.y) {
                cords.push_front(Apple);
                Apple = RandApple();
            }
            else {
                cords.back().x = cords.front().x;
                cords.back().y = cords.front().y - 1;
                cords.push_front(cords.back());
                cords.pop_back();
            }
        }
        if (direction == 'd')
        {
            if (cords.front().x == Apple.x and cords.front().y + 1 == Apple.y) {
                cords.push_front(Apple);
                Apple = RandApple();
            }
            else {
                cords.back().x = cords.front().x;
                cords.back().y = cords.front().y + 1;
                cords.push_front(cords.back());
                cords.pop_back();
            }
        }
        if (direction == 'l')
        {
            if (cords.front().x - 1 == Apple.x and cords.front().y == Apple.y) {
                cords.push_front(Apple);
                Apple = RandApple();
            }
            else {
                cords.back().x = cords.front().x - 1;
                cords.back().y = cords.front().y;
                cords.push_front(cords.back());
                cords.pop_back();
            }

        }
        if (direction == 'r')
        {
            if (cords.front().x + 1 == Apple.x and cords.front().y == Apple.y) {
                cords.push_front(Apple);
                Apple = RandApple();
            }
            else {
                cords.back().x = cords.front().x + 1;
                cords.back().y = cords.front().y;
                cords.push_front(cords.back());
                cords.pop_back();
            }
        }
    }

}

void Paint(RGBQUAD* arr) {
    for (auto iter = cords.begin(); iter != cords.end(); iter++) {
        // При выходе за границы
        if (iter->x >= WindowWidth / 10)
            iter->x = 0;
        if (iter->x < 0)
            iter->x = WindowWidth / 10 - 1;
        if (iter->y >= WindowHeight / 10)
            iter->y = 0;
        if (iter->y < 0)
            iter->y = WindowHeight / 10 - 1;


        // Если врезалась в себя
        Pixel(arr, 10 * iter->x, 10 * iter->y, 0, 255, 0);
    }
    Pixel(arr, 10 * Apple.x, 10 * Apple.y, 255, 0, 0);
}




// Функция, выводящая изображение на экран
void func(HDC hdc) {

    BITMAPINFO bif;
    ZeroMemory(&bif, sizeof(BITMAPINFO));
    bif.bmiHeader.biSize = sizeof(bif);

    RGBQUAD* arr = new RGBQUAD[WindowWidth * WindowHeight]();

    // Код

    Snake();

    Paint(arr);

    // Код

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

    cords.push_back(Cord(WindowWidth / 20, WindowHeight / 20));
    Apple = RandApple();

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
        WindowWidth + 16, // начальный размер x
        WindowHeight + 39, // начальный размер y
        NULL, // дескриптор родительского окна
        NULL, // дескриптор меню окна
        hInstance, // дескриптор экземпляра программы
        NULL); // параметры создания

    SetTimer(hwnd, 1, 10, nullptr); // Установление таймера
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
    int mas[2];
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
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_GETMINMAXINFO: // Сделать окно неизменияемым
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = WindowWidth + 16;
        lpMMI->ptMinTrackSize.y = WindowHeight + 39;

        lpMMI->ptMaxTrackSize.x = WindowWidth + 16;
        lpMMI->ptMaxTrackSize.y = WindowHeight + 39;
        return 0;
    }
    case WM_MOUSEWHEEL:
        break;
    case WM_KEYDOWN://нажата клавиша
        switch (wParam)
        {
        case 0x57://w
            if (direction != 'd') {
                direction = 'u';
            }
            break;
        case 0x44://d
            if (direction != 'l') {
                direction = 'r';
            }
            break;
        case 0x41://a
            if (direction != 'r') {
                direction = 'l';
            }
            break;
        case 0x53://s
            if (direction != 'u') {
                direction = 'd';
            }
            break;
        }


        return 0;
    case WM_KEYUP://нажата клавиша

        return 0;
    case WM_DESTROY: // При закрытии
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}