/**
 * @file    task3.cpp
 * @brief   Считывает целое число типа int.
 *
 * @note    Поставить «защиту от дурака»: если пользователь
 *          вводит что-то кроме одного целочисленного значения,
 *          нужно вывести сообщение об ошибке и предложить ввести число еще раз.
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

    int num = 0;
    bool correctNum = true;

    for (;;) {
        // char inStr[6] = {'\0'}; // Строка для парсинга в C-стиле
        std::string inStr;

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
                    continue;
                }

                std::cerr << "Incorrect num!" << std::endl;
                correctNum = false;
                break;
            }
        }*/

        std::cin >> std::ws;  // Обрежем пробелы и прочее

        int len = 0;

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
                        continue;
                    }
                }

                correctNum = false;
                break;
            }
        }

        if (len == 0 || !correctNum) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            correctNum = true;
            continue;
        }

        //num = std::atoi(inStr); // Преобразование в C-стиле

        num = std::stoi(inStr);
        std::cout << "Entered num is: " << num << std::endl;

        break;
    }

    return 0;
}
