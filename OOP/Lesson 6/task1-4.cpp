/**
 * @file    task1-4.cpp
 * @brief   Тестируем вирутальные функции и перегрузку операций
 *
 * @note    Задание №1: Добавить перегрузку операторов ввода-вывода для класса Fraction
 *          Задание №4: Создать собственный манипулятор endll для стандартного потока
 *                      вывода, который выводит два перевода строки и сбрасывает буфер.
 *
 * @note    1. Создать абстрактный класс Fraction (дробь).
 *          2. От него наследуют два класса: SimpleFraction (обыкновенная дробь)
 *             и MixedFraction (смешанная дробь).
 *          3. Обыкновенная дробь имеет только числитель и знаменатель (например, 3/7 или 9/2),
 *             а смешанная — еще и целую часть (например, 3 1/2 ). Предусмотреть, чтобы
 *             знаменатель не был равен 0.
 *          4. Перегрузить математические бинарные операторы (+, -, *, /) для выполнения
 *             действий с дробями, а также унарный оператор (-).
 *          5. Перегрузить логические операторы сравнения двух дробей (==, !=, <, >, <=, >=).
 *             Поскольку операторы < и >=, > и <= — это логические противоположности,
 *             попробуйте перегрузить один через другой.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cstdio>
#include <iomanip>
#include <string>

class Fraction {
  protected:
    bool     isCorrect;      /*!< Корректная ли дробь */
    int      sign;           /*!< Знак дроби (+1 или -1) */
    unsigned intPart;        /*!< Целая часть дроби */
    long     numerator;      /*!< Числитель дроби */
    unsigned denominator;    /*!< Знаменатель дроби */
    double   resFraction;    /*!< Итоговое число с плавающей точкой */

    virtual void GetIntPart()    = 0;

  public:
    virtual void printFraction() = 0;

    /** Операция преобразования дроби в тип double */
    operator double() {
        resFraction = static_cast<double>(sign) *
                      (intPart * denominator + numerator) /
                      static_cast<double>(denominator);

        return resFraction;
    }

    friend std::ostream& endll(std::ostream &out);
};

class SimpleFraction : public Fraction {
  protected:
    /** Выделение целой части дроби, заглушка функции */
    void GetIntPart() {};
  public:
    SimpleFraction() {
        isCorrect = false;
        denominator = 1;
    };

    SimpleFraction(int s, long n, unsigned d) {
        set(s, n, d);
    }

    void set(int s, long n, unsigned d) {
        if (d == 0) {
            isCorrect = false;
            return;
        }

        isCorrect   = true;

        if (s >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }

        intPart     = 0;
        numerator   = n;
        denominator = d;
    }

    /** Вывод дроби в консоль */
    void printFraction() {
        std::cout << *this << std::endl;
    }

    /** Сложение двух дробей */
    SimpleFraction operator + (SimpleFraction a) {
        SimpleFraction res;

        res.numerator = sign * numerator * a.denominator +
                        a.sign * a.numerator * denominator;

        res.denominator = denominator * a.denominator;

        res.intPart     = 0;
        res.isCorrect   = true;

        return res;
    }

    /** Вычитание двух дробей */
    SimpleFraction operator - (SimpleFraction a) {
        SimpleFraction res(1, 0, 1);

        res.numerator = sign * numerator * a.denominator -
                        a.sign * a.numerator * denominator;

        res.denominator = denominator * a.denominator;

        if (res.numerator < 0) {
            res.sign = -1;
            res.numerator *= -1;
        }

        return res;
    }

    /** Умножение двух дробей */
    SimpleFraction operator * (SimpleFraction a) {
        SimpleFraction res(1, 0, 1);

        res.sign        = sign * a.sign;
        res.numerator   = numerator * a.numerator;
        res.denominator = denominator * a.denominator;

        return res;
    }

    /** Деление двух дробей */
    SimpleFraction operator / (SimpleFraction a) {
        SimpleFraction res(1, 0, 1);

        res.sign        = sign * a.sign;
        res.numerator   = numerator * a.denominator;
        res.denominator = denominator * a.numerator;

        return res;
    }

    /** Логическая операция сравнения двух дробей "меньше чем" */
    bool operator < (SimpleFraction b) {
        return double(*this) < double(b);
    }

    /** Логическая операция сравнения двух дробей "больше чем" */
    bool operator > (SimpleFraction b) {
        return double(*this) > double(b);
    }

    /** Логическая операция сравнения двух дробей "больше или равно чем" */
    bool operator >= (SimpleFraction b) {
        return !(*this < b);
    }

    /** Логическая операция сравнения двух дробей "меньше или равно чем" */
    bool operator <= (SimpleFraction b) {
        return !(*this > b);
    }

    /** Логическая операция сравнения двух дробей */
    bool operator == (SimpleFraction b) {
        return double(*this) == double(b);
    }

    /** Унарная операция изменения знака дроби */
    SimpleFraction operator - () {
        SimpleFraction res(sign * -1, numerator, denominator);
        return res;
    }

    friend std::ostream& operator<< (std::ostream &out, const SimpleFraction &fraction);
    friend std::istream& operator>> (std::ostream &in, const SimpleFraction &fraction);
};

/** Перегрузка оператора вывода для печати дроби */
std::ostream& operator<< (std::ostream &out, const SimpleFraction &fraction) {

    if (fraction.sign < 0) {
        out << "-";
    }

    out << fraction.numerator << "/" << fraction.denominator;

    return out;
}

/** Перегрузка оператора ввода для парсинга дроби */
std::istream& operator>> (std::istream &in, SimpleFraction &fraction) {

    int sign = 1, n = 0, d = 1;
    char s[21];

    in >> std::setw(21) >> s;

    std::sscanf(s, "%d/%d", &n, &d);

    if (n < 0){
        sign = -1;
        n *= -1;
    }

    fraction.set(sign, n, d);

    return in;
}

/** Собственный оператор endll, выводит дополнительную строку и очищает буфер */
std::ostream& endll(std::ostream &out){

    out << "\n\n";

    out.clear();

    return out;
}

class MixedFraction : public Fraction {
  protected:
    /** Выделение целой части дроби */
    void GetIntPart() {
        if (numerator >= denominator) {
            intPart += (numerator / denominator);
            numerator %= denominator;
        }
    }

  public:
    MixedFraction() {
        isCorrect = false;
        denominator = 1;
    };

    MixedFraction(int s, unsigned i, unsigned n, unsigned d) {
        if (d == 0) {
            isCorrect = false;
            return;
        }

        if (s >= 0) {
            sign = 1;
        } else {
            sign = -1;
        }

        isCorrect   = true;
        intPart     = i;
        numerator   = n;
        denominator = d;

        GetIntPart();
    }

    /** Вывод дроби в консоль */
    void printFraction() {
        if (sign < 0) {
            std::cout << "-";
        }

        std::cout << intPart << " " << numerator << "/" << denominator << std::endl;
    }

    /** Сложение двух дробей */
    MixedFraction operator + (MixedFraction a) {
        MixedFraction res(1, 0, 0, 1);

        res.numerator = sign * (intPart * denominator + numerator) * a.denominator +
                        a.sign * (a.intPart * a.denominator + a.numerator) * denominator;
        res.denominator = denominator * a.denominator;

        res.GetIntPart();

        return res;
    }

    /** Вычитание двух дробей */
    MixedFraction operator - (MixedFraction a) {
        MixedFraction res(1, 0, 0, 1);

        res.numerator = sign * (intPart * denominator + numerator) * a.denominator -
                        a.sign * (a.intPart * a.denominator + a.numerator) * denominator;
        res.denominator = denominator * a.denominator;

        if (res.numerator < 0) {
            res.sign = -1;
            res.numerator *= -1;
        }

        res.GetIntPart();
        return res;
    }

    /** Умножение двух дробей */
    MixedFraction operator * (MixedFraction a) {
        MixedFraction res(1, 0, 0, 1);

        res.sign        = sign * a.sign;
        res.numerator   = (intPart * denominator + numerator) * (a.intPart * a.denominator + a.numerator);
        res.denominator = denominator * a.denominator;

        res.GetIntPart();
        return res;
    }

    /** Деление двух дробей */
    MixedFraction operator / (MixedFraction a) {
        MixedFraction res(1, 0, 0, 1);

        res.sign        = sign * a.sign;
        res.numerator   = (intPart * denominator + numerator) * a.denominator;
        res.denominator = denominator * (a.intPart * a.denominator + a.numerator);

        res.GetIntPart();
        return res;
    }

    /** Логическая операция сравнения двух дробей "меньше чем" */
    bool operator < (MixedFraction b) {
        return double(*this) < double(b);
    }

    /** Логическая операция сравнения двух дробей "больше чем" */
    bool operator > (MixedFraction b) {
        return double(*this) > double(b);
    }

    /** Логическая операция сравнения двух дробей "больше или равно чем" */
    bool operator >= (MixedFraction b) {
        return !(*this < b);
    }

    /** Логическая операция сравнения двух дробей "меньше или равно чем" */
    bool operator <= (MixedFraction b) {
        return !(*this > b);
    }

    /** Логическая операция сравнения двух дробей */
    bool operator == (MixedFraction b) {
        return double(*this) == double(b);
    }

    /** Унарная операция изменения знака дроби */
    MixedFraction operator - () {
        MixedFraction res(sign * -1, intPart, numerator, denominator);
        return res;
    }
};


int main (int argc, char ** args) {

    /*
    // Кусок кода из прошлого ДЗ, на основе которого делаю текущее

    SimpleFraction n1(1, 3, 4);
    SimpleFraction n2(1, 2, 4);

    std::cout << "Logic n1 <= n2 is: " << (n1 <= n2) << endll;

    SimpleFraction sn = n1 / n2;

    std::cout << "(Overloaded) New fraction is: " << sn << std::endl;
    std::cout << "(Method) New fraction is: ";
    sn.printFraction();

    MixedFraction n3(1, 1, 1, 4);
    MixedFraction n4(1, 1, 2, 5);

    std::cout << "Logic n3 >= n4 is: " << (n3 >= n4) << endll;

    MixedFraction mn = n3 / n4;

    mn.printFraction();

    MixedFraction mm = -n3;

    mm.printFraction();
    */

    SimpleFraction f1;
    std::cout << "Enter fraction 1: ";
    std::cin >> f1;

    SimpleFraction f2;
    std::cout << "Enter fraction 2: ";
    std::cin >> f2;

    std::cout << f1 << " * " << f2 << " is " << f1 * f2 << endll;

    return 0;
}
