/**
 * @file    task2.cpp
 * @brief   Тестируем Ввод/Вывод строк
 *
 * @note  Программа заточена под однобайтовые символы. Юникод тоже
 *        работает, но форматирование, конечно, съезжает, т.к.
 *        Юникод таки минимум 2-х байтовый.
 *
 * @note    - Запрашивать у пользователя строки до тех пор, пока он
 *            не введет пустую строку.
 *          - После этого программа должна вывести список введенных
 *            строк в два столбца, первый из которых выровнен по
 *            левому краю, а второй — по правому краю.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

// Вместо #define лучше определять константы так
constexpr int MAX_ROW_WIDTH = 50;  /*!< Максимальная ширина столбца*/

int main (int argc, char ** args) {
    std::vector<std::string> input; /*!< Вектор, где храним полученные строки */
    std::string inStr;              /*!< Переменная, куда считываем строку */

    std::cout << "Print strings. Print empty string to stop:" << std::endl;

    for (;;) {
        std::getline(std::cin, inStr);

        // Можно определять пустую строку и по gcount(),
        // но я предпочитаю смотреть на уже считанную строку.
        if (inStr.empty()) {
            break;
        }

        // Закинуть строку в вектор
        input.push_back(inStr);

        // Очистить временную переменную-хранилище строки
        inStr.clear();
    }


    std::vector<std::string>::const_iterator iStr; /*!< Итератор для хранилища считанных строк */

    iStr = input.begin();

    std::cout << std::setw(MAX_ROW_WIDTH * 2 + 7) << std::setfill('-') << "-" << std::endl;

    std::cout << "| " << std::left << std::setw(MAX_ROW_WIDTH) << std::setfill(' ') << "Left align" << " | ";
    std::cout << std::right << std::setw(MAX_ROW_WIDTH) << "Right align" << " |" << std::endl;

    std::cout << std::setw(MAX_ROW_WIDTH * 2 + 7) << std::setfill('-') << "-" << std::endl;

    while (iStr != input.end()) {
        std::cout << "| " << std::left << std::setw(MAX_ROW_WIDTH) << std::setfill(' ') << *iStr << " | ";
        std::cout << std::right << std::setw(MAX_ROW_WIDTH) << *iStr << " |" << std::endl;

        ++iStr;
    }

    return 0;
}
