
#define T int
#define STACK_MAX_SIZE 10

class Stack {
  private:
    unsigned int size = 0;       /*!< Текущий размер стэка */
    unsigned int current = 0;
    T data[STACK_MAX_SIZE];

  public:
    /** Коды ошибок  */
    enum ErrorsList_t {
        ERROR_BAD_VALUE          = -5, /*!< Некорректное значение переменной */
        ERROR_STACK_MEMORY_ALLOC = -4, /*!< Невозможно выделить память */
        ERROR_STACK_IS_FULL      = -3, /*!< Переполнение стэка */
        ERROR_STACK_IS_EMPTY     = -2, /*!< Стэк пуст */
        NO_ERROR = -1,                 /*!< Нет ошибок */
    };

    bool push(T value);
    T pop();
    unsigned int getSize();
    void print();
    void reset();
};
