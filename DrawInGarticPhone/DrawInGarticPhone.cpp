#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>

// Подключение файла с функциями
extern "C" {
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
}

// Вспомогательная функция ( картинка (вектор), расположение картинки, ширина (запишется в эту переменную), высота (запишется в эту переменную), компонент (3 - получить RGB, 4 - получить RGBA) )
bool load_image(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y, const int& component)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, component);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y * 3);
    }
    stbi_image_free(data);
    return (data != nullptr);
}

// Вспомогательная функция
byte MP(int newNum)
{
    if (newNum > 255) { newNum = 255; }
    else if (newNum < 0) { newNum = 0; }
    return (byte)newNum;
}

// Картинка в формате массива преобразуется в однобитовую
void ConvertToOneBitImage(byte*& grayImage, int cont, int width, int height)
{

    // Преобразование картинки
    byte oldPixel;
    byte newPixel;
    int error;
    int newNumber;
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            oldPixel = grayImage[x * width + y];
            if (oldPixel > 128) { newPixel = 255; }
            else { newPixel = 0; }
            grayImage[x * width + y] = newPixel;
            error = oldPixel - newPixel + cont + 2;

            if (y < width - 1)
            {
                newNumber = grayImage[x * width + y + 1] + error * 7 / 16;
                grayImage[x * width + y + 1] = MP(newNumber);
            }

            if (y > 0 && x < height - 1)
            {
                newNumber = grayImage[(x + 1) * width + y - 1] + error * 3 / 16;
                grayImage[(x + 1) * width + y - 1] = MP(newNumber);
            }

            if (x < height - 1)
            {
                newNumber = grayImage[(x + 1) * width + y] + error * 5 / 16;
                grayImage[(x + 1) * width + y] = MP(newNumber);
            }

            if (x < height - 1 && y < width - 1)
            {
                newNumber = grayImage[(x + 1) * width + y + 1] + error * 1 / 16;
                grayImage[(x + 1) * width + y + 1] = MP(newNumber);
            }
        }
    }
}

int main()
{
    std::string filename = "D:\\Projects\\ImageMaker2\\ExamplesImage\\focused_199751338-stock-photo-close-cat-face-white-background.jpg"; // Путь к картинке
    int width, height; // Ширина и высота
    std::vector<unsigned char> image; // Картинка
    int component = 3; // 3 - получить RGB, 4 - получить RGBA
    bool success = load_image(image, filename, width, height, component); // Запуск
    if (!success)
    {
        std::cout << "Error loading image\n";
        return 1;
    }

    byte* mas = new byte[width * height];


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            byte a = (static_cast<int>(image[component * (i * width + j) + 0]) + static_cast<int>(image[component * (i * width + j) + 1]) + static_cast<int>(image[component * (i * width + j) + 0])) / 3;
            mas[i * width + j] = a;
        }
    }

    ConvertToOneBitImage(mas, 0, width, height);

    int x1 = 510;
    int y1 = 320;
    int x2 = x1 + width;
    int y2 = y1 + height;

    Sleep(2000);


    for (int i = x1; i < x2; i += 1) {
        for (int j = y1; j < y2; j += 1) {
            if (static_cast<int>(mas[i - x1 + width * (j - y1)]) == 0) {
                SetCursorPos(i, j);
                mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, i, j, 0, 0);
                for (int s = 0; s < 10000000 / 4; s++) {};
            }
        }
    }

    return 0;
}