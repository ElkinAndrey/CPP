#include <windows.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>


int WindowWidth = 700; // Ширина окна приложения
int WindowHeight = 600; // Высота окна приложения
// Цвет
int Red = 0;
int Blue = 0;
int Green = 0;
int length = 60; // Размер клетки
// Размер массива (картинки
const int sizeX = 100;
const int sizeY = 100;
int mas[sizeY][sizeX];

// Нужно рисовать или стирать
int click = 1;

// Положение мыши
int mouseX;
int mouseY;

// Координаты верхнего левого угла массива. В начале центр массива будет в центре координат
int StartX = WindowWidth / 2 - sizeX * (length) / 2;
int StartY = WindowHeight / 2 - sizeY * (length) / 2;




// Функция для фиксации изменений
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);




void CaptureScreen(HWND window)
{
    //Получаем прямоугольную область экрана
    RECT windowRect;
    //GetWindowRect(window, &windowRect);
    GetClientRect(window, &windowRect); // Это изменяет только коордианаты правого угла =(


    //Размеры битмэпа
    int bitmap_dx = windowRect.right - windowRect.left;
    int bitmap_dy = windowRect.bottom - windowRect.top;

    BITMAPINFOHEADER bmpInfoHeader;
    BITMAPFILEHEADER bmpFileHeader;
    BITMAP* pBitmap;

    bmpFileHeader.bfType = 0x4d42;
    bmpFileHeader.bfSize = 0;
    bmpFileHeader.bfReserved1 = 0;
    bmpFileHeader.bfReserved2 = 0;
    bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    bmpInfoHeader.biSize = sizeof(bmpInfoHeader);
    bmpInfoHeader.biWidth = bitmap_dx;
    bmpInfoHeader.biHeight = bitmap_dy;
    bmpInfoHeader.biPlanes = 1;
    bmpInfoHeader.biBitCount = 24;
    bmpInfoHeader.biCompression = BI_RGB;
    bmpInfoHeader.biSizeImage = bitmap_dx * bitmap_dy * (24 / 8);
    bmpInfoHeader.biXPelsPerMeter = 0;
    bmpInfoHeader.biYPelsPerMeter = 0;
    bmpInfoHeader.biClrUsed = 0;
    bmpInfoHeader.biClrImportant = 0;

    BITMAPINFO info;
    info.bmiHeader = bmpInfoHeader;

    BYTE* memory;
    HDC winDC = GetWindowDC(window);
    HDC bmpDC = CreateCompatibleDC(winDC);
    //Создаем битмэп
    HBITMAP bitmap = CreateDIBSection(winDC, &info, DIB_RGB_COLORS, (void**)&memory, NULL, 0);
    SelectObject(bmpDC, bitmap);//Выбираем в контекст битмэп
    BitBlt(bmpDC, 0, 0, bitmap_dx, bitmap_dy, winDC, 0, 0, SRCCOPY);
    ReleaseDC(window, winDC);

    OPENFILENAME ofn;//Указатель на структуру с данными инициализации диалогового окна
    char strFilter[] = "Файлы данных *.bmp\0";
    char strFileName[MAX_PATH] = "";
    memset(&ofn, 0, sizeof(OPENFILENAME));//Обнуление ofn
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = window;
    ofn.nMaxFile = MAX_PATH;//Размер файла
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
    GetSaveFileName(&ofn); //MessageBox(hwnd,"Невозможно сохранить файл", "О программе...",MB_ICONINFORMATION);

    HANDLE hFile = CreateFile(
        ofn.lpstrFile, GENERIC_WRITE,
        0, NULL, OPEN_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
        return;

    DWORD dwWritten = 0;
    WriteFile(hFile, &bmpFileHeader, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
    WriteFile(hFile, &bmpInfoHeader, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
    WriteFile(hFile, memory, bmpInfoHeader.biSizeImage, &dwWritten, NULL);
    CloseHandle(hFile);
}






// Нарисовать пустой квадрат 
void EmptySquare(RGBQUAD* arr, int StartX, int StartY) {
    // Не рисовать квадрат, если он выходит за рамки приложения
    if (StartX + length < 0 or StartX - length > WindowWidth or StartY + length < 0 or StartY - length > WindowHeight)
        return;
    for (int x = StartX; x < StartX + length + 1; x++) {
        if ((int(x) + WindowWidth * StartY > 1) and (int(x) + WindowWidth * StartY < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
            arr[x + WindowWidth * StartY].rgbRed = Red;
            arr[x + WindowWidth * StartY].rgbBlue = Blue;
            arr[x + WindowWidth * StartY].rgbGreen = Green;
        }
        if ((int(x) + WindowWidth * (StartY + length) > 1) and (int(x) + WindowWidth * (StartY + length) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
            arr[x + WindowWidth * (StartY + length)].rgbRed = Red;
            arr[x + WindowWidth * (StartY + length)].rgbBlue = Blue;
            arr[x + WindowWidth * (StartY + length)].rgbGreen = Green;
        }
    }
    for (int y = StartY; y < StartY + length + 1; y++) {
        if ((StartX + WindowWidth * int(y) > 1) and (StartX + WindowWidth * int(y) < WindowHeight * WindowWidth) and (StartX >= 0) and (StartX < WindowWidth)) {
            arr[StartX + WindowWidth * y].rgbRed = Red;
            arr[StartX + WindowWidth * y].rgbBlue = Blue;
            arr[StartX + WindowWidth * y].rgbGreen = Green;
        }
        if ((StartX + length + WindowWidth * int(y) > 1) and (StartX + length + WindowWidth * int(y) < WindowHeight * WindowWidth) and (StartX + length >= 0) and (StartX + length - 1 < WindowWidth)) {
            arr[StartX + length + WindowWidth * y].rgbRed = 0;
            arr[StartX + length + WindowWidth * y].rgbBlue = Blue;
            arr[StartX + length + WindowWidth * y].rgbGreen = Green;
        }
    }
}

// Нарисовать закрашеный квадрат
void FilledSquare(RGBQUAD* arr, int StartX, int StartY) {
    // Не рисовать квадрат, если он выходит за рамки приложения
    if (StartX + length < 0 or StartX - length > WindowWidth or StartY + length < 0 or StartY - length > WindowHeight)
        return;
    for (int y = StartY; y < StartY + length + 1; y++) {
        for (int x = StartX; x < StartX + length + 1; x++) {
            if ((int(x) + WindowWidth * int(y) > 1) and (int(x) + WindowWidth * int(y) < WindowHeight * WindowWidth) and (int(x) >= 0) and (int(x) < WindowWidth)) {
                arr[x + WindowWidth * y].rgbRed = Red;
                arr[x + WindowWidth * y].rgbBlue = Blue;
                arr[x + WindowWidth * y].rgbGreen = Green;
            }
        }
    }
}

// Функция, выводящая изображение на экран
void func(HDC hdc) {
    // Создание массива
    BITMAPINFO bif;
    ZeroMemory(&bif, sizeof(BITMAPINFO));
    bif.bmiHeader.biSize = sizeof(bif);
    RGBQUAD* arr = new RGBQUAD[WindowWidth * WindowHeight];


    // Заполнение массива
    for (int y = StartY; y < StartY + (length)*sizeY; y += length) {
        for (int x = StartX; x < StartX + (length)*sizeX; x += length) {
            if (mas[(y - StartY) / (length)][(x - StartX) / (length)] == 0) // Если в массиве 0, то не закрашивать, если 1, то закрасить
                EmptySquare(arr, x, y);
            else
                FilledSquare(arr, x, y);
        }
    }

    // Точка в центре экрана
    arr[WindowWidth / 2 + WindowWidth * int(WindowHeight / 2)].rgbRed = 255;
    arr[WindowWidth / 2 + WindowWidth * int(WindowHeight / 2)].rgbBlue = Blue;
    arr[WindowWidth / 2 + WindowWidth * int(WindowHeight / 2)].rgbGreen = Green;

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



    SetTimer(hwnd, 1, 100000, nullptr); // Установление таймера
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
    static HWND hwndButton, hwndButton2;
    switch (message)
    {
    case WM_CREATE:
        hwndButton = CreateWindow( // Создание кнопки
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Окрасить в белый",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            710,         // x position 
            10,         // y position 
            200,        // Button width
            40,        // Button height
            hwnd,     // Parent window
            NULL,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        ShowWindow(hwndButton, SW_SHOWNORMAL); // Запуск окна

        hwndButton2 = CreateWindow( // Создание кнопки
            L"BUTTON",  // Predefined class; Unicode assumed 
            L"Окрасить в черный",      // Button text 
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
            710,         // x position 
            60,         // y position 
            200,        // Button width
            40,        // Button height
            hwnd,     // Parent window
            NULL,       // No menu.
            (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE),
            NULL);      // Pointer not needed.
        ShowWindow(hwndButton, SW_SHOWNORMAL); // Запуск окна
        break;
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
    case WM_MOUSEWHEEL: // Уркчение колесика
        if ((short)HIWORD(wParam) > 0 and length + WindowWidth / 200 < 200) {
            StartX = mouseX - int(float((mouseX - StartX) * (length + WindowWidth / 200)) / float(length));
            StartY = mouseY - int(float((mouseY - StartY) * (length + WindowWidth / 200)) / float(length));
            length += WindowWidth / 200;
        }
        if ((short)HIWORD(wParam) < 0 and length - WindowWidth / 200 > 6) {
            StartX = mouseX - int(float((mouseX - StartX) * (length - WindowWidth / 200)) / float(length));
            StartY = mouseY - int(float((mouseY - StartY) * (length - WindowWidth / 200)) / float(length));
            length -= WindowWidth / 200;
        }
        else if ((short)HIWORD(wParam) < 0 and length - WindowWidth / 200 > 0) {
            length -= WindowWidth / 200;
            StartX = WindowWidth / 2 - sizeX * (length) / 2;
            StartY = WindowHeight / 2 - sizeY * (length) / 2;
        }

        InvalidateRect(hwnd, nullptr, FALSE);
        break;
    case WM_MOUSEMOVE: // Перемещение мыщи
        mouseX = LOWORD(lParam);
        mouseY = HIWORD(lParam);
        if (UINT(wParam) & MK_LBUTTON) {
            if (mouseX > StartX and mouseX < StartX + (length)*sizeX and mouseY > StartY and mouseY < StartY + (length)*sizeY) {
                if (click == 1)
                    mas[(mouseY - StartY) / (length)][(mouseX - StartX) / (length)] = 1;
                else
                    mas[(mouseY - StartY) / (length)][(mouseX - StartX) / (length)] = 0;
            }
        }
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_LBUTTONDOWN: // При нажатии ЛКМ
        if (mouseX > StartX and mouseX < StartX + (length)*sizeX and mouseY > StartY and mouseY < StartY + (length)*sizeY) {
            if (mas[(mouseY - StartY) / (length)][(mouseX - StartX) / (length)] == 0) {
                click = 1;
                mas[(mouseY - StartY) / (length)][(mouseX - StartX) / (length)] = 1;
            }
            else {
                click = 0;
                mas[(mouseY - StartY) / (length)][(mouseX - StartX) / (length)] = 0;
            }
        }

        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;

    case WM_LBUTTONUP: // При отпускании ЛКМ
        InvalidateRect(hwnd, nullptr, FALSE);
        return 0;
    case WM_GETMINMAXINFO: // Сделать окно неизменияемым
    {
        LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
        lpMMI->ptMinTrackSize.x = 1000;
        lpMMI->ptMinTrackSize.y = WindowHeight;

        lpMMI->ptMaxTrackSize.x = 1000;
        lpMMI->ptMaxTrackSize.y = WindowHeight;
        return 0;
    }
    case WM_COMMAND: // Обработка нажатия кнопки
        if (lParam == (LPARAM)hwndButton) {
            for (int y = 0; y < sizeY; y++) {
                for (int x = 0; x < sizeX; x++) {
                    mas[y][x] = 0;
                }
            }
        }
        if (lParam == (LPARAM)hwndButton2) {
            for (int y = 0; y < sizeY; y++) {
                for (int x = 0; x < sizeX; x++) {
                    mas[y][x] = 1;
                }
            }
        }

        InvalidateRect(hwnd, nullptr, FALSE);
        break;
    case WM_DESTROY: // При закрытии
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}