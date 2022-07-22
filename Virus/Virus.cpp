#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <thread>
#include <random>

using namespace std;

//random number gen for while loops in cursor/beep functions.
random_device rd;
mt19937 eng(rd());
uniform_int_distribution<> distr(1, 100);

// Переменные
int random, Dur, X, Y, Freq;
HANDLE hExitApp = NULL;


void Beeper()
{
    if (WaitForSingleObject(hExitApp, 0) == WAIT_TIMEOUT) // Без этого работало
    {
        do
        {
            if (distr(eng) > 75) // Без этого работает
            {
                Dur = rand() % 206;
                Freq = rand() % 2124;
                Beep(Dur, Freq);
            }
        } while (WaitForSingleObject(hExitApp, 200) == WAIT_TIMEOUT);
    }
}


void RandomCursor()
{
    if (WaitForSingleObject(hExitApp, 0) == WAIT_TIMEOUT) // Можно и без if
    {
        do
        {
            if (distr(eng) < 50) // Без этого работает
            {
                X = rand() % 3020;
                Y = rand() % 2020;
                SetCursorPos(X, Y); // Установить курсор на координаты
            }
        } while (WaitForSingleObject(hExitApp, 1) == WAIT_TIMEOUT);
    }
}

LRESULT CALLBACK MyLowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    /*
    Можно просто оставить только это
    if (reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam)->vkCode == VK_F9)
        SetEvent(hExitApp);
    return CallNextHookEx(0, nCode, wParam, lParam);
    */
    if (nCode == HC_ACTION) // Без if работает
    {
        switch (wParam) {
        case WM_KEYDOWN: // Без этого работает
        case WM_KEYUP:
            if (reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam)->vkCode == VK_F9)
                SetEvent(hExitApp);
            break;
        }
    }
    return CallNextHookEx(0, nCode, wParam, lParam);
}

void executeApp()
{
    PostThreadMessage(GetCurrentThreadId(), WM_NULL, 0, 0); // Без этого работает

    HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, &MyLowLevelKeyboardProc, NULL, 0);
    if (hook) // Без if работает
    {
        MSG msg;
        do
        {
            if (MsgWaitForMultipleObjects(1, &hExitApp, FALSE, INFINITE, QS_ALLINPUT) != (WAIT_OBJECT_0 + 1))
                break;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        } while (true);
        UnhookWindowsHookEx(hook); // Без этого работает
    }
    SetEvent(hExitApp);
}


int main()
{
    // Приложение без консоли
    ShowWindow(FindWindowA("ConsoleWindowClass", NULL), SW_HIDE);

    // Надо для паралельного выполнения
    hExitApp = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!hExitApp) return -1; // Без этого всё работает

    // Генерация рандомного числа
    srand(time(0)); // Без этого тоже работает
    random = rand() % 3;
    system("title 1337app"); // установить название консоли

    // threads позволяет выполнить несколько функций одновременно
    thread cursor(RandomCursor); // Лаганый курсор
    thread beeps(Beeper); // Звуковые сигналы
    thread appexecute(executeApp); // Закрыть приложение сочетанием F9
    cursor.join();
    beeps.join();
    appexecute.join();

    // Надо для паралельного выполнения
    CloseHandle(hExitApp);

    return 0;
}