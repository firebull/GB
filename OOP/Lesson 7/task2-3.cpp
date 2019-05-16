/**
 * @file    task2-3.cpp
 * @brief   Тестируем умные указатели
 *
 * @note  1. Создайте класс Date с полями день, месяц, год и
 *           методами доступа к этим полям.
 *        2. Перегрузите оператор вывода для данного класса.
 *        3. Создайте два "умных" указателя today и date.
 *           - Первому присвойте значение сегодняшней даты.
 *           - Для него вызовите по отдельности методы доступа
 *             к полям класса Date, а также выведите на экран
 *             данные всего объекта с помощью перегруженного
 *             оператора вывода.
 *           - Затем переместите ресурс, которым владеет
 *             укзаатель today в указатель date.
 *           - Проверьте, являются ли нулевыми указатели today
 *             и date и выведите соответствующую информацию об
 *             этом в консоль.
 *         4. Создайте два умных указателя date1 и date2
 *            - Создайте функцию, которая принимает в качестве параметра
 *              два умных указателя типа Date и сравнивает их между собой
 *              (сравнение происходит по датам). Функция должна вернуть
 *              более позднюю дату.
 *            - Создайте функцию, которая обменивает ресурсами (датами)
 *              два умных указателя, переданных в функцию в качестве параметров.
 *            - Первая функция не должна уничтожать объекты, переданные ей
 *              в качестве параметров.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <memory>

class Date {
  private:
    unsigned       year;      /*!< Год */
    unsigned short month;     /*!< Месяц */
    unsigned short day;       /*!< День */
    unsigned long  dateStamp; /*!< Слепок даты в формате 20190512 */

    /** Сохраняем слепок даты */
    void setDateStamp() {
        dateStamp = year * 10000 + month * 100 + day;
    }

    /** Проверка корректности установленной даты */
    bool checkDate() const {
        if (month == 0 || month > 12 || day == 0 || day > 31) {
            return false;
        }

        return true;
    }

    /** Проверка корректности устанавливаемой даты */
    bool checkDate(unsigned short m, unsigned short d) const {
        if (m == 0 || m > 12 || d == 0 || d > 31) {
            return false;
        }

        return true;
    }

  public:
    Date() : year(2019), month(5), day(16), dateStamp(20190516) {};

    /**
     * @brief Конструктор даты
     *
     * @note Если установленная дата некорректна, выход с ошибкой
     */
    Date(unsigned y, unsigned short m, unsigned short d) {
        year  = y;
        month = m;
        day   = d;

        if (!checkDate()) {
            exit(1);
        }

        setDateStamp();
    }

    /** Конструктор копирования */
    Date(Date &date) {
        year      = date.year;
        month     = date.month;
        day       = date.day;
        dateStamp = date.dateStamp;
    }

    ~Date() {};

    bool setNewDate(unsigned y, unsigned short m, unsigned short d) {
        if (!checkDate(m, d)) {
            return false;
        }

        year  = y;
        month = m;
        day   = d;

        setDateStamp();

        return true;
    }

    void setYear(unsigned y) {
        year = y;
        setDateStamp();
    }

    bool setMonth (unsigned short m) {
        if (!checkDate(m, day)) {
            return false;
        }

        month = m;
        setDateStamp();

        return true;
    }

    bool setDay (unsigned short d) {
        if (!checkDate(month, d)) {
            return false;
        }

        day = d;
        setDateStamp();

        return true;
    }

    unsigned long getDateStamp() const {
        return dateStamp;
    }

    unsigned getYear() const {
        return year;
    }

    unsigned short getMonth() const {
        return month;
    }

    unsigned short getDay() const {
        return day;
    }

    friend std::ostream &operator<<(std::ostream &os, const Date &date);
};

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << date.day << "." << date.month  << "." << date.year;
    return os;
}

/**
 * @brief Сравнение дат из умных указателей
 *
 * @param  d1 Умный указатель на первую дату
 * @param  d2 Умный указатель на вторую дату
 * @return    Наибольшую дату или дату с конструктором по-умолчанию
 */
Date CompareDates(const std::unique_ptr<Date> &d1, const std::unique_ptr<Date>&d2) {
    if (!d1 && !d2) { // Если пустые указатели вернуть дату по-умолчанию
        Date tmp;
        return tmp;
    } else if (!d1) { // Если указатель 1 нулевой, вернуть вторую дату
        Date tmp(*d2);
        return tmp;
    } else if (!d2) { // Если указатель 2 нулевой, вернуть вторую дату
        Date tmp(*d1);
        return tmp;
    }

    // Сравниваем даты по слепкам и возвращаем наибольшую
    if (d1->getDateStamp() >= d2->getDateStamp()) {
        Date tmp(*d1);
        return tmp;
    } else {
        Date tmp(*d2);
        return tmp;
    }
}

/** Меняем даты местами (хотя и так уже есть такой метод) */
void SwapDates(std::unique_ptr<Date> &d1, std::unique_ptr<Date>&d2) {
    d1.swap(d2);
}

int main (int argc, char ** args) {
    std::cout << "TASK 2:" << std::endl;

    std::unique_ptr<Date> today(new Date(1978, 10, 26));
    std::unique_ptr<Date> date;

    std::cout << "Current set date: " << *today << std::endl;

    today->setDay(16);
    today->setMonth(5);
    today->setYear(2019);

    std::cout << "New date by get methods: " << today->getDay() << "." << today->getMonth() << "." << today->getYear() << std::endl;

    std::cout << "New dateStamp: " << today->getDateStamp() << std::endl;

    std::cout << "New date by overloaded <<: " <<  *today << std::endl;

    date = std::move(today);

    std::cout << "today ptr is " << (today ? "not null" : "null") << std::endl;
    std::cout << "date ptr is " << (date ? "not null" : "null") << std::endl;

    std::cout << std::endl << "TASK 3:" << std::endl;

    std::unique_ptr<Date> date1(new Date(1978, 10, 26));
    std::unique_ptr<Date> date2(new Date(1980, 9, 20));

    std::cout << "date1 is: " << *date1 << std::endl;
    std::cout << "date2 is: " << *date2 << std::endl;

    std::cout << "The biggest date is: " << CompareDates(date1, date2) << std::endl;


    std::cout << "Lets swap them..." << std::endl;
    SwapDates(date1, date2);

    std::cout << "Now date1 is: " << *date1 << std::endl;
    std::cout << "Now date2 is: " << *date2 << std::endl;

    return 0;
}
