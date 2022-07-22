#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>



double angle1 = 0; // Угол вверх/вниз 
double angle2 = 0; // Угол вправо/влево
double startangle1 = 0; // Чтобы после отпускания мышки угол вверх/вниз не менялся
double startangle2 = 0; // Чтобы после отпускания мышки угол вправо/влево не менялся
float lenth = 60.0; // Длина единичного отрезка в 3D
int CenterX = 750; // Центр координат по X
int CenterY = 400; // Центр координат по Y
int WindowWidth = 1500; // Ширина окна приложения
int WindowHeight = 800; // Высота окна приложения
int Red = 255;
int Blue = 255;
int Green = 255;

// Функция для фиксации изменений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// Рисует точку 3 на 3
void DoPoint(RGBQUAD* arr, int x, int y) {
    for (int i1 = -2; i1 < 3; i1++) {
        for (int i2 = -2; i2 < 3; i2++) {
            if ((x + i1 + WindowWidth * int(y + i2) > 0) and (x + i1 + WindowWidth * int(y + i2) <= WindowHeight * WindowWidth) and (int(x + i1) >= 0) and (int(x + i1) <= WindowWidth - 1)) {
                arr[x + i1 + WindowWidth * int(y + i2)].rgbRed = Red;
                arr[x + i1 + WindowWidth * int(y + i2)].rgbBlue = Blue;
                arr[x + i1 + WindowWidth * int(y + i2)].rgbGreen = Green;
            }
        }
    }
}

// Рисует линию 
void DoLine(RGBQUAD* arr, int x1, int y1, int x2, int y2) {
    int x, y;
    // Поменять местами точки, если линия идет назад 
    float k = float((y2 - y1)) / float((x2 - x1));
    if ((abs(k) >= 1 and x2 - x1 > 0 and y2 - y1 < 0) or (y2 - y1 <= 0 and x2 - x1 <= 0) or (abs(k) < 1 and x2 - x1 < 0 and y2 - y1 > 0)) {
        x = x2;
        x2 = x1;
        x1 = x;
        y = y2;
        y2 = y1;
        y1 = y;
    }
    // При k пренадлежащем {-1;1}
    if (abs(y2 - y1) < abs(x2 - x1)) {
        float k = float(y2 - y1) / float(x2 - x1);
        for (x = x1; x < x2; x++) {
            y = k * float(x - x1) + y1;
            if ((int(x) + WindowWidth * int(y) > 1) and (int(x) + WindowWidth * int(y) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
                arr[x + WindowWidth * int(y)].rgbRed = Red;
                arr[x + WindowWidth * int(y)].rgbBlue = Blue;
                arr[x + WindowWidth * int(y)].rgbGreen = Green;
            }
        }
    }
    // При остальных k
    else {
        float k;
        k = float(x2 - x1) / float(y2 - y1);
        int x, y;
        for (y = y1; y < y2; y++) {
            x = k * float(y - y1) + x1;
            if ((int(x) + WindowWidth * int(y) > 1) and (int(x) + WindowWidth * int(y) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
                arr[x + WindowWidth * int(y)].rgbRed = Red;
                arr[x + WindowWidth * int(y)].rgbBlue = Blue;
                arr[x + WindowWidth * int(y)].rgbGreen = Green;
            }
        }
    }
}

// Помогает рисовать многоугольник
void DoFigureHelp(bool* arra, int x1, int y1, int x2, int y2) {
    int x, y;
    float k = float(x2 - x1) / float(y2 - y1);
    // Поменять местами точки, если линия идет назад 
    if (y2 - y1 < 0) {
        x = x2;
        x2 = x1;
        x1 = x;
        y = y2;
        y2 = y1;
        y1 = y;
    }
    for (y = y1; y < y2; y++) {
        x = k * float(y - y1) + x1;
        if ((int(x) + WindowWidth * int(y) > 1) and (int(x) + WindowWidth * int(y) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
            arra[x + WindowWidth * int(y)] = true;
        }
    }
}

// Рисует многоугольник
void DoFigure(RGBQUAD* arr, int mas1[], int mas2[], int mas3[], int mas4[]) {
    int masX[] = { mas1[0], mas2[0], mas3[0], mas4[0], mas1[0] };
    int masY[] = { mas1[1], mas2[1], mas3[1], mas4[1], mas1[1] };
    int MaxX = masX[0];
    int MaxY = masY[0];
    int MinX = masX[0];
    int MinY = masY[0];
    for (int i = 1; i < 4; i++) {
        if (MaxX < masX[i])
            MaxX = masX[i];
        if (MaxY < masY[i])
            MaxY = masY[i];
        if (MinX > masX[i])
            MinX = masX[i];
        if (MinY > masY[i])
            MinY = masY[i];
    }

    bool* arra = new bool[WindowHeight * WindowWidth];
    for (int i = 0; i < WindowHeight * WindowWidth; i++)
        arra[i] = false;
    for (int i = 0; i < 4; i++) {
        DoFigureHelp(arra, masX[i], masY[i], masX[i + 1], masY[i + 1]);
    }

    int f;
    for (int y = MinY; y <= MaxY; y++) {

        f = 0;
        for (int x = MinX; x <= MaxX; x++) {
            if (x + y * WindowWidth < WindowHeight * WindowWidth) {
                if (arra[x + y * WindowWidth])
                    f++;
                if (f > 1)
                    break;
            }
        }
        if (f == 1)
            continue;

        f = 0;
        for (int x = MinX; x <= MaxX; x++) {
            if ((f == 1 or arra[x + y * WindowWidth]) and (int(x) + WindowWidth * int(y) > 1) and (int(x) + WindowWidth * int(y) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
                arr[x + WindowWidth * int(y)].rgbRed = Red;
                arr[x + WindowWidth * int(y)].rgbBlue = Blue;
                arr[x + WindowWidth * int(y)].rgbGreen = Green;
            }
            if (arra[x + y * WindowWidth]) {
                if (f == 1) {
                    f = 0;
                    break;
                }
                else if (f == 0)
                    f = 1;
            }
        }
    }
    delete[] arra;

}

// Рисует точку в 2Д плоскости из 3Д пространства
void DoPoint3D(RGBQUAD* arr, float mas[3]) {
    float x1 = sin(angle2 / 57.0) * lenth;
    float y1 = sin(angle1 / 57.0) * cos(angle2 / 57.0) * lenth;
    float x2 = sin((angle2 - 90.0) / 57.0) * lenth;
    float y2 = sin(angle1 / 57.0) * sin(angle2 / 57.0) * lenth;
    float x3 = 0;
    float y3 = -cos(angle1 / 57.0) * lenth;

    DoPoint(arr,
        int(CenterX + x1 * mas[0] + x2 * mas[1] + x3 * mas[2]),
        int(CenterY + y1 * mas[0] + y2 * mas[1] + y3 * mas[2])
    );

}

// Рисует линию в 2Д плоскости из 3Д пространства
void DoLine3D(RGBQUAD* arr, float mas1[3], float mas2[3]) {
    // Проекция единичного отрезка Ox на плоскость экрана
    float x1 = sin(angle2 / 57.0) * lenth;
    float y1 = sin(angle1 / 57.0) * cos(angle2 / 57.0) * lenth;
    // Проекция единичного отрезка Oy на плоскость экрана
    float x2 = sin((angle2 - 90.0) / 57.0) * lenth;
    float y2 = sin(angle1 / 57.0) * sin(angle2 / 57.0) * lenth;
    // Проекция единичного отрезка Oz на плоскость экрана
    float x3 = 0;
    float y3 = -cos(angle1 / 57.0) * lenth;

    DoLine(arr,
        int(CenterX + x1 * mas1[0] + x2 * mas1[1] + x3 * mas1[2]),
        int(CenterY + y1 * mas1[0] + y2 * mas1[1] + y3 * mas1[2]),
        int(CenterX + x1 * mas2[0] + x2 * mas2[1] + x3 * mas2[2]),
        int(CenterY + y1 * mas2[0] + y2 * mas2[1] + y3 * mas2[2])
    );
}

// Рисует 3D плоскость в 2D плоскости экрана
void DoFigure3D(RGBQUAD* arr, float mas1[3], float mas2[3], float mas3[3], float mas4[3]) {
    float x1 = sin(angle2 / 57.0) * lenth;
    float y1 = sin(angle1 / 57.0) * cos(angle2 / 57.0) * lenth;
    // Проекция единичного отрезка Oy на плоскость экрана
    float x2 = sin((angle2 - 90.0) / 57.0) * lenth;
    float y2 = sin(angle1 / 57.0) * sin(angle2 / 57.0) * lenth;
    // Проекция единичного отрезка Oz на плоскость экрана
    float x3 = 0;
    float y3 = -cos(angle1 / 57.0) * lenth;

    int one[] = { CenterX + x1 * mas1[0] + x2 * mas1[1] + x3 * mas1[2], CenterY + y1 * mas1[0] + y2 * mas1[1] + y3 * mas1[2] };
    int two[] = { CenterX + x1 * mas2[0] + x2 * mas2[1] + x3 * mas2[2], CenterY + y1 * mas2[0] + y2 * mas2[1] + y3 * mas2[2] };
    int three[] = { CenterX + x1 * mas3[0] + x2 * mas3[1] + x3 * mas3[2], CenterY + y1 * mas3[0] + y2 * mas3[1] + y3 * mas3[2] };
    int four[] = { CenterX + x1 * mas4[0] + x2 * mas4[1] + x3 * mas4[2], CenterY + y1 * mas4[0] + y2 * mas4[1] + y3 * mas4[2] };
    DoFigure(arr, one, two, three, four);
}

// Функция, выводящая изображение на экран
void func(HDC hdc) {

    BITMAPINFO bif;
    ZeroMemory(&bif, sizeof(BITMAPINFO));
    bif.bmiHeader.biSize = sizeof(bif);
    RGBQUAD* arr = new RGBQUAD[WindowWidth * WindowHeight]();



    float Center[] = { 0, 0, 0 };
    float ForX[] = { 0.5, 0, 0 };
    float ForY[] = { 0, 0.5, 0 };
    float ForZ[] = { 0, 0, 0.5 };
    // Линии осей координат
    DoLine3D(arr, Center, ForX); // ось Ox
    DoLine3D(arr, Center, ForY); // ось Oy
    DoLine3D(arr, Center, ForZ); // ось Oz
    // Центр координат
    DoPoint(arr, CenterX, CenterY);

    float P01[] = { 1, -1, 2 };
    float P02[] = { -1, -1, 2 };
    float P03[] = { -1, 1, 2 };
    float P04[] = { 1, 1, 2 };
    float P05[] = { 2, -1, 1 };
    float P06[] = { 1, -2, 1 };
    float P07[] = { -1, -2, 1 };
    float P08[] = { -2, -1, 1 };
    float P09[] = { -2, 1, 1 };
    float P10[] = { -1, 2, 1 };
    float P11[] = { 1, 2, 1 };
    float P12[] = { 2, 1, 1 };

    float P13[] = { 2, -1, -1 };
    float P14[] = { 1, -2, -1 };
    float P15[] = { -1, -2, -1 };
    float P16[] = { -2, -1, -1 };
    float P17[] = { -2, 1, -1 };
    float P18[] = { -1, 2, -1 };
    float P19[] = { 1, 2, -1 };
    float P20[] = { 2, 1, -1 };
    float P21[] = { 1, -1, -2 };
    float P22[] = { -1, -1, -2 };
    float P23[] = { -1, 1, -2 };
    float P24[] = { 1, 1, -2 };


    DoLine3D(arr, P01, P02);
    DoLine3D(arr, P02, P03);
    DoLine3D(arr, P03, P04);
    DoLine3D(arr, P04, P01);

    DoLine3D(arr, P05, P06);
    DoLine3D(arr, P06, P07);
    DoLine3D(arr, P07, P08);
    DoLine3D(arr, P08, P09);
    DoLine3D(arr, P09, P10);
    DoLine3D(arr, P10, P11);
    DoLine3D(arr, P11, P12);
    DoLine3D(arr, P12, P05);

    DoLine3D(arr, P05, P01);
    DoLine3D(arr, P06, P01);
    DoLine3D(arr, P07, P02);
    DoLine3D(arr, P08, P02);
    DoLine3D(arr, P09, P03);
    DoLine3D(arr, P10, P03);
    DoLine3D(arr, P11, P04);
    DoLine3D(arr, P12, P04);


    DoLine3D(arr, P05, P13);
    DoLine3D(arr, P06, P14);
    DoLine3D(arr, P07, P15);
    DoLine3D(arr, P08, P16);
    DoLine3D(arr, P09, P17);
    DoLine3D(arr, P10, P18);
    DoLine3D(arr, P11, P19);
    DoLine3D(arr, P12, P20);


    DoLine3D(arr, P13, P14);
    DoLine3D(arr, P14, P15);
    DoLine3D(arr, P15, P16);
    DoLine3D(arr, P16, P17);
    DoLine3D(arr, P17, P18);
    DoLine3D(arr, P18, P19);
    DoLine3D(arr, P19, P20);
    DoLine3D(arr, P20, P13);

    DoLine3D(arr, P13, P21);
    DoLine3D(arr, P14, P21);
    DoLine3D(arr, P15, P22);
    DoLine3D(arr, P16, P22);
    DoLine3D(arr, P17, P23);
    DoLine3D(arr, P18, P23);
    DoLine3D(arr, P19, P24);
    DoLine3D(arr, P20, P24);

    DoLine3D(arr, P21, P22);
    DoLine3D(arr, P22, P23);
    DoLine3D(arr, P23, P24);
    DoLine3D(arr, P24, P21);



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

    SetTimer(hwnd, 1, 1, nullptr); // Установление таймера
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

        return 0;
    }
    case WM_TIMER: {
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    }
    case WM_GETMINMAXINFO: // Сделать окно неизменияемым
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = WindowWidth;
        lpMMI->ptMinTrackSize.y = WindowHeight;

        lpMMI->ptMaxTrackSize.x = WindowWidth;
        lpMMI->ptMaxTrackSize.y = WindowHeight;
        return 0;
    }
    case WM_MOUSEWHEEL:
        if ((short)HIWORD(wParam) > 0)
            lenth += WindowWidth / 100;
        if ((short)HIWORD(wParam) < 0 and lenth > 0)
            lenth -= WindowWidth / 100;

        InvalidateRect(hwnd, nullptr, FALSE);
        break;
    case WM_MOUSEMOVE:
        if (UINT(wParam) & MK_LBUTTON) {
            angle2 = LOWORD(lParam) - startangle2; // Координаты в системе окна
            angle1 = HIWORD(lParam) - startangle1;
        }
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_LBUTTONDOWN:
        startangle2 = LOWORD(lParam) - angle2; //Сохраним координаты курсора мыши в системе окна
        startangle1 = HIWORD(lParam) - angle1;
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_DESTROY: // При закрытии
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}