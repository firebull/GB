/**
 * @file    task1.cpp
 * @brief   Создание простейшего класса с копирующим конструктором
 *
 * @note    1. Создайте класс, который будет генерировать рандомные числа.
 *             У этого класса должны быть обязательно два константных метода:
 *              - один из них (Current) должен возвращать текущее сгенерированное число,
 *              - второй (Next) - следующее случайное число.
 *          2. Если самым первым методом вызвать Current, то выдать предупреждение,
 *             что число не сгенерировано еще.
 *          3. В классе должен быть конструктор по умолчанию, с параметрами, а также
 *             копирующий конструктор.
 *          4. Создать кэширование текущего случайного числа.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>

class RandCache {
  private:
    mutable int  currentNum; /*!< Текущее сгенерированное случайное число */
    mutable bool isCached;   /*!< Генерировалось ли число уже */

  public:
    /** Инициализация класса текущим временем */
    RandCache() {
        currentNum = -1;
        isCached   = false;
        srand(time(NULL));
    }

    /** Инициалировать класс своим числом */
    RandCache(int s) {
        currentNum = -1;
        isCached   = false;
        srand(s);
    }

    /** Копирующий конструктор  */
    RandCache(RandCache &r) {
        currentNum = r.currentNum;
        isCached   = r.isCached;
    }

    /** Вернуть текущее число */
    int Current() const {
        if (isCached) {
            return currentNum;
        } else {
            std::cout << "Num not generated yet." << std::endl;
            return -1;
        }
    }

    /** Сгенерировать и вернуть новое число */
    int Next() const {
        currentNum = rand();
        isCached   = true;

        return currentNum;
    }
};

int main (int argc, char ** args) {

    RandCache randNum;

    randNum.Current();
    randNum.Next();

    std::cout << "New Rand num: " << randNum.Next() << " and current: " << randNum.Current() << std::endl;

    RandCache otherRandNum(randNum);

    std::cout << "Other New Rand num: " << otherRandNum.Next() << " and current: " << otherRandNum.Current() << std::endl;

    return 0;
}
