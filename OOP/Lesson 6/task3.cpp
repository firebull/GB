/**
 * @file    task3.cpp
 * @brief   Считывает целое число типа int.
 *
 * @note    Поставить «защиту от дурака»: если пользователь
 *          вводит что-то кроме одного целочисленного значения,
 *          нужно вывести сообщение об ошибке и предложить ввести число еще раз.
 *
 * @note    Т.к. строки типа 1n, 556hdf тоже по заданию являются некорректными,
 *          придётся писать свой парсинг до того, как загонять строку в stoi
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <iomanip>
#include <limits>
#include <cstdlib>
#include <cctype>
#include <string>

int main (int argc, char ** args) {

    int num = 0;            /*!< Итоговое число */
    bool correctNum = true; /*!< Корректное ли чесло было введено */

    for (;;) {
        // char inStr[6] = {'\0'}; // Строка для парсинга в C-стиле

        std::string inStr; /*!< Строка, куда пишем отпарсиный текст */
        int len = 0;       /*!< Количество символов в строке. .size даёт кол-во байт, не подходит нам */

        std::cout << "Enter integer num: ";

        /*
        // Парсим в C-стиле
        std::cin.get(inStr, 6);

        for (short i = 0; i < 6; ++i) {
            if (inStr[i] < '0' || inStr[i] > '9') {
                if (inStr[i] == '\0') {
                    break;
                }

                if (inStr[i] == '-' || inStr[i] == '+') {
                    if (len == 0) {
                        continue;
                    }

                    correctNum = false;
                    break;
                }

                std::cerr << "Incorrect num!" << std::endl;
                correctNum = false;
                break;
            }

            len++;
        }*/

        std::cin >> std::ws;  // Обрежем пробелы и прочее

        char c;

        while (std::cin.get(c)) {
            if (c == '\n') {
                break;
            }

            if (std::isdigit(c)) {
                len++;
                inStr.push_back(c);
                continue;
            } else {
                if (c == '-' || c == '+') {
                    if (len == 0) {
                        inStr.push_back(c);
                        len++;
                        continue;
                    }
                }

                correctNum = false;
                break;
            }
        }

        // Если число некорретное, сбросить буфер и идти на новй круг
        if (len == 0 || !correctNum) {
            std::cout << "Incorrect num!" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            correctNum = true;
            continue;
        }

        //num = std::atoi(inStr); // Преобразование в C-стиле

        // Преобразуем число из строки в int
        num = std::stoi(inStr);
        std::cout << "Entered num is: " << num << std::endl;

        break;
    }

    return 0;
}
