/**
 * @file    task1.cpp
 * @brief   Реализация контйнерного списка
 *
 * @note    1. Добавить в контейнерный класс, который был написан
 *             в этом уроке, функцию для удаления последнего элемента
 *             массива (аналог функции pop_back() в векторах).
 *             Подсказка: сначала напишите функцию удаления любого
 *             элемента в массиве.
 *          2. Также напишите функцию для добавления другого массива
 *             в любое место исходного.
 *          3. Реализуйте функцию сортировки элементов массива.
 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <cassert>

#define SWAP(A, B) { int t = A; A = B; B = t; }

class ArrayInt {
  private:
    int m_length;
    int * m_data;

    /**
    * @brief Быстрая сортировка через рекурсию
    *
    * @param first Номер стартового элемента
    * @param last  Номер конечного элемента
    */
    void sortArray(int first, int last) {

        if (first < last) {
            int left   = first,
                right  = last,
                medium = m_data[(left + right) / 2];

            do {
                while (m_data[left] < medium) {
                    left++;
                };

                while (m_data[right] > medium) {
                    right--;
                };

                if (left <= right) {
                    SWAP(m_data[left], m_data[right]);
                    left++;
                    right--;
                }
            } while (left <= right);

            sortArray(first, right);
            sortArray(left, last);
        }
    }

  public:
    ArrayInt(): m_length(0), m_data(nullptr) {};

    ArrayInt(int length): m_length(length) {
        assert(length >= 0);

        if (length > 0) {
            m_data = new int[length];
        } else {
            m_data = nullptr;
        }
    }

    ~ArrayInt() {
        delete[] m_data;
    }

    /** Очистка массива */
    void erase() {
        delete[] m_data;

        m_data = nullptr;
        m_length = 0;
    }

    /**
     * @brief Возвращает текущую длину массива
     *
     * @return Длина массива
     */
    int getLength() {
        return m_length;
    }

    /**
     * @brief меняет размер массива.
     *
     * @note Все существующие элементы сохраняются. Процесс медленный
     * @param newLength Новый размер массива
     */
    void resize(int newLength) {
        // Если массив уже нужной длины — return
        if (newLength == m_length) {
            return;
        }

        // Если нужно сделать массив пустым — делаем это и затем return
        if (newLength <= 0) {
            erase();
            return;
        }

        // Теперь знаем, что newLength >0
        // Выделяем новый массив
        int *data = new int[newLength];

        // Затем нужно разобраться с количеством копируемых элементов в новый массив
        // Нужно скопировать столько элементов, сколько их есть в меньшем из массивов
        if (m_length > 0) {
            int elementsToCopy = (newLength > m_length) ? m_length : newLength;

            // Поочередно копируем элементы
            for (int index = 0; index < elementsToCopy ; ++index) {
                data[index] = m_data[index];
            }
        }

        // Удаляем старый массив, так как он нам уже не нужен
        delete[] m_data;

        // И используем вместо старого массива новый! Обратите внимание, m_data указывает
        // на тот же адрес, на который указывает наш новый динамически выделенный массив. Поскольку
        // данные были динамически выделенные — они не будут уничтожены, когда выйдут из области видимости
        m_data = data;
        m_length = newLength;
    }

    /**
     * @brief Вставляет элемент в массив
     *
     * @param value Что вставить
     * @param index Куда вставить
     */
    void insertBefore(int value, int index) {
        // Проверка корректности передаваемого индекса
        assert(index >= 0 && index <= m_length);

        // Создаем новый массив на один элемент больше старого массива
        int *data = new int[m_length + 1];

        // Копируем все элементы до index-а
        for (int before = 0; before < index; ++before) {
            data[before] = m_data[before];
        }

        // Вставляем новый элемент в новый массив
        data [index] = value;

        // Копируем все значения после вставляемого элемента
        for (int after = index; after < m_length; ++after) {
            data[after + 1] = m_data[after];
        }

        // Удаляем старый массив и используем вместо него новый
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    ArrayInt & push_back(int value) {
        insertBefore(value, m_length);

        return *this;
    }

    /**
     * @brief Удаляет элемент массива
     *
     * @param index Индекс элемента для удаления
     */
    void del_element(int index) {
        // Проверка корректности передаваемого индекса
        assert(m_length > 0 && index >= 0 && index <= m_length);

        if (m_length == 1) {
            erase();
        }

        // Создаем новый массив на один элемент больше старого массива
        int *data = new int[m_length - 1];

        // Копируем все значения кроме удаляемого
        for (int i = 0, j = 0; i < m_length; ++i) {
            if (i == index) {
                continue;
            }

            data[j++] = m_data[i];
        }

        // Удаляем старый массив и используем вместо него новый
        delete[] m_data;
        m_data = data;
        --m_length;
    }

    /** Удаляет последний элемент массива */
    ArrayInt & pop_back() {
        del_element(m_length - 1);

        return *this;
    }

    /**
     * @brief Вставляет другой массив в текущий
     *
     * @param newArr  Другой массив
     * @param arrSize Размер другого массива
     * @param index   Куда вставить
     */
    void insert_array(int newArr[], int arrSize, int index) {
        assert(newArr != nullptr && index >= 0 && index <= m_length);

        if (arrSize == 0) {
            return;
        }

        int *data = new int[m_length + arrSize];

        int i = 0,
            n = 0;

        for (; i <= index; ++i, ++n) {
            data[i] = m_data[i];
        }

        for (int j = 0; i <= index + arrSize; ++i, ++j) {
            data[i] = newArr[j];
        }

        for (; i < m_length + arrSize; ++n, ++i) {
            data[i] = m_data[n];
        }

        // Удаляем старый массив и используем вместо него новый
        delete[] m_data;
        m_data = data;
        m_length += arrSize;
    }

    /** Сортировка текущего массива */
    ArrayInt & sort() {
        sortArray(0, m_length - 1);

        return *this;
    }

    /** Вывод текущего массива в консоль */
    void print() {
        std::cout << "[ ";

        for (int i = 0; i < m_length; ++i) {
            std::cout << m_data[i];

            if (i < m_length - 1) {
                std::cout << ", ";
            }
        }

        std::cout << " ]" << std::endl;
    }

    /** Возвращаем элемент массива */
    int &operator[](int index) {
        assert(index >= 0 && index < m_length);
        return m_data[index];
    }
};

int main (int argc, char ** args) {

    ArrayInt arr1;

    arr1.push_back(1);
    arr1.push_back(2);
    arr1.push_back(3);
    arr1.push_back(4);
    arr1.push_back(5);

    int *arr2 = new int[3];
    arr2[0] = 10;
    arr2[1] = 11;
    arr2[2] = 12;

    arr1.insert_array(arr2, 3, 2);

    arr1.print();

    arr1.sort().print();

    arr1.del_element(0);
    arr1.pop_back().print();

    return 0;
}
