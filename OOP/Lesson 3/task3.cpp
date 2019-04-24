/**
 * @file    task3.cpp
 * @brief   Тестируем вирутальные функции и перегрузку операций
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

class Fraction {
  protected:
    bool     isCorrect;      /*!< Корректная ли дробь */
    int      sign;           /*!< Знак дроби (+1 или -1) */
    unsigned intPart;        /*!< Целая часть дроби */
    unsigned numerator;      /*!< Числитель дроби */
    unsigned denominator;    /*!< Знаменатель дроби */
    double   resFraction;    /*!< Итоговое число с плавающей точкой */
  public:
    virtual void GetIntPart() = 0;

    /** Операция преобразования дроби в тип double */
    operator double() {
        resFraction = static_cast<double>(sign) *
                      (intPart * denominator + numerator) /
                      static_cast<double>(denominator);

        return resFraction;
    }
};



class SimpleFraction : public Fraction {
  public:
    SimpleFraction() {
        isCorrect = false;
        denominator = 1;
    };

    SimpleFraction(int s, unsigned n, unsigned d) {
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

        GetIntPart();
    }

    void GetIntPart() {};

    /** Сложение двух дробей */
    SimpleFraction operator + (SimpleFraction a) {
        SimpleFraction res;
        res.numerator = sign * (denominator + numerator) * a.denominator +
                        a.sign * (a.denominator + a.numerator) * denominator;
        res.denominator = denominator * a.denominator;

        res.intPart     = 0;
        res.isCorrect   = true;

        return res;
    }

    bool operator < (SimpleFraction b) {
        if (double(*this) >= double(b)) { return false; }

        return true;
    }

    bool operator >= (SimpleFraction b) {
        return !(double(*this) < double(b));
    }
};

class MixedFraction : public Fraction {
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

    void GetIntPart() {
        if (numerator >= denominator) {
            intPart += (numerator / denominator);
            numerator %= denominator;
        }
    }
};


int main (int argc, char ** args) {

    SimpleFraction n1(1, 3, 4);
    SimpleFraction n2(1, 2, 4);

    std::cout << (n1 >= n2) << std::endl;

    return 0;
}
