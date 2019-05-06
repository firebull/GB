/**
 * @file    task2.cpp
 * @brief   Создание простейшего класса с наследованием
 *
 * @note    1. Создать класс Person (человек) с полями: имя, возраст, пол и вес.
 *          2. Определить методы переназначения имени, изменения возраста и веса.
 *          3. Создать производный класс Student (студент), имеющий поле года обучения.
 *             Определить методы переназначения и увеличения этого значения.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>

/** Пол */
enum Sex {
    SEX_UNDEFINED = 0,
    SEX_MALE,
    SEX_FEMALE
};

/** Просто символьные именования пола */
static char sexNames[3] = {'-', 'm', 'f'};

class Person {
  protected:
    std::string name;   /*!< Имя человека */
    unsigned    age;    /*!< Возраст человека */
    Sex         sex;    /*!< Пол человека */
    float       weight; /*!< Вес человека */
  public:
    /** Конструктор */
    Person(std::string n = "", int a = 0, Sex s = SEX_UNDEFINED, float w = 0) : name(n), age(a), sex(s), weight(w) {}

    /** Изменить имя */
    Person &SetName(std::string n) {
        name = n;

        return *this;
    }

    /** Изменить возраст */
    Person &SetAge(unsigned age) {
        this->age = age;

        return *this;
    }

    /** Изменить пол */
    Person &SetSex(Sex s) {
        sex = s;

        return *this;
    }

    /** Изменить вес */
    Person &SetWeight(float w) {
        weight = w;

        return *this;
    }
};

class Student: public Person {
  private:
    unsigned sYear; /*!< Год обучения */
  public:
    Student(std::string n = "-", int a = 0, Sex s = SEX_UNDEFINED, float w = 0, unsigned y = 2019) : Person(n, a, s, w), sYear(y) {}

    void PrintData() const {
        std::cout << name << ", " << age << " years old, of " << weight << "kg, " << sexNames[sex] << ", started at " << sYear << std::endl;
    }

    /** Изменить год обучения */
    Student &SetStudYear(unsigned y) {
        sYear = y;

        return *this;
    }

    /** Увеличить год обучения на 1 */
    Student &IncStudYear() {
        sYear++;

        return *this;
    }
};

int main (int argc, char ** args) {

    Student student;

    student.PrintData();

    student.SetName("Comrade Bulkin").SetAge(40).SetSex(SEX_MALE).SetWeight(86.3);

    // @todo Хотелось бы понять, можно ли SetStudYear сделать одной строкой к прошлой?
    student.SetStudYear(2018);

    student.PrintData();

    student.IncStudYear().IncStudYear().IncStudYear();

    student.PrintData();

    return 0;
}
