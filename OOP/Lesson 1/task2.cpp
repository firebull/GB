/**
 * @file    task2.cpp
 * @brief   Создание класса иницализации RGBA
 *
 * @note    1. Написать класс с именем RGBA, который содержит
 *             4 переменные-члена типа std::uint8_t m_red, m_green,
 *             m_blue и m_alpha (#include cstdint для доступа к этому типу).
 *          2. Задать 0 в качестве значения по умолчанию для m_red, m_green,
 *             m_blue и 255 для m_alpha.
 *          3. Создать конструктор со списком инициализации членов, который
 *             позволит пользователю передавать значения для m_red, m_blue,
 *             m_green и m_alpha.
 *          4. Написать функцию print(), которая будет выводить значения
 *             переменных-членов.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cstdint>

/*!
 * @class RGBA
 * @brief Инициализация RGBA
 *
 * @note Использую this-> просто потому, что в общем случае это хороший тон
 */
class RGBA {
  private:
    std::uint8_t m_red   = 0;   /*!< Компонента RED */
    std::uint8_t m_green = 0;   /*!< Компонента GREEN */
    std::uint8_t m_blue  = 0;   /*!< Компонента BLUE */
    std::uint8_t m_alpha = 255; /*!< Компонента ALPHA */

  public:
    /** Пустой конструктор */
    RGBA() {};

    /**
     * @brief Конструктор для инициализации с параметрами
     *
     * @param r Устанавливаемое значение компоненты RED
     * @param g Устанавливаемое значение компоненты GREEN
     * @param b Устанавливаемое значение компоненты BLUE
     * @param a Устанавливаемое значение компоненты ALPHA
     */
    RGBA(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
        this->m_red   = r;
        this->m_green = g;
        this->m_blue  = b;
        this->m_alpha = a;
    }

    /** Вывод в консоль текущего значения RGBA */
    void print() {
        std::cout << "Current RGBA is: ";
        std::cout << static_cast<unsigned short>(this->m_red) << ",";
        std::cout << static_cast<unsigned short>(this->m_green) << ",";
        std::cout << static_cast<unsigned short>(this->m_blue) << ",";
        std::cout << static_cast<unsigned short>(this->m_alpha) << std::endl;
    }

};


int main (int argc, char ** args) {

    RGBA rgba; /*!< RGBA со значениями по умолчанию */

    rgba.print();

    RGBA rgba2(25, 100, 200, 128); /*!< RGBA с заданными значениями при иницализации */

    rgba2.print();

    return 0;
}
