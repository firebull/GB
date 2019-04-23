/**
 * @file    task1.cpp
 * @brief   Тестируем вирутальные функции
 *
 * @note    1. Создать абстрактный класс Figure (фигура).
 *             Его наследниками являются классы Parallelogram (параллелограмм)
 *             и Circle (круг).
 *          2. Класс Parallelogram — базовый для классов Rectangle (прямоугольник),
 *             Square (квадрат), Rhombus (ромб). Для всех классов создать конструкторы.
 *          3. Для класса Figure добавить чисто виртуальную функцию area() (площадь).
 *          4. Во всех остальных классах переопределить эту функцию, исходя из
 *             геометрических формул нахождения площади.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cmath>

/**
 * @brief Абстрактный класс Фигура
 *
 * @note Включает виртуальную функцию вычисления площади фигуры
 */
class Figure {
  public:
    virtual double area() = 0;

};

/**
 * @brief Базовый класс Параллелограмм
 */
class Parallelogram : public Figure {
  protected:
    double size_a; /*!< Сторона А */
    double size_b; /*!< Сторона Б */
  public:
    Parallelogram() {
        size_a = 0;
        size_b = 0;
    }

    Parallelogram(double a = 0, double b = 0): size_a(a), size_b(b) {};
};

/** Описание круга */
class Circle : public Figure {
  protected:
    double radius;  /*!< Радиус круга */
  public:
    Circle() {
        radius = 0;
    }

    Circle(double r): radius(r) {};

    /** Вычисление площади круга */
    double area() {
        return M_PIl * radius * radius;
    }

};

/** Описание прямоугольника */
class Rectangle : public Parallelogram {
  public:
    Rectangle() : Parallelogram(0, 0) {};
    Rectangle(double a, double b): Parallelogram(a, b) {};

    /** Вычисление площади прямоугольника */
    double area() {
        return (size_a * size_b);
    }

};

/** Описание квадрата */
class Square : public Parallelogram {
  public:
    Square() : Parallelogram(0, 0) {};
    Square(double a): Parallelogram(a, a) {};

    /** Вычисление площади квадрата */
    double area() {
        return size_a * size_a;
    }
};

/** Описание ромба */
class Rhombus : public Parallelogram {
  private:
    float angle; /*!< Угол между сторонами ромба */
  public:
    Rhombus() : Parallelogram(0, 0) {};
    Rhombus(double a, float an): Parallelogram(a, a), angle(an) {};

    /** Вычисление площади ромба */
    double area() {
        double h = size_a * sin(angle * M_PIl / 180.0f);

        return h * size_a;
    }
};

int main (int argc, char ** args) {

    Rectangle rectangle(5, 6);

    std::cout << "Rectangle area is: " << rectangle.area() << std::endl;

    Square square(5);

    std::cout << "Square area is: " << square.area() << std::endl;

    Rhombus rhombus(5, 60);

    std::cout << "Rhombus area is: " << rhombus.area() << std::endl;

    Circle circle(5);

    std::cout << "Circle area is: " << circle.area() << std::endl;

    return 0;
}
