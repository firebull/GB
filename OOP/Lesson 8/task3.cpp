/**
 * @file    task2.cpp
 * @brief   Тестируем исключения
 *
 * @note    1. Написать класс «робот», моделирующий перемещения
 *             робота по сетке 10x10, у которого есть метод,
 *             означающий задание переместиться на соседнюю позицию.
 *          2. Эти методы должны запускать исключение OffTheField,
 *             если робот должен уйти с сетки, и IllegalCommand,
 *             если подана неверная команда (направление не находится
 *             в нужном диапазоне).
 *          3. Объект исключения должен содержать всю необходимую
 *             информацию — текущую позицию и направление движения.
 *          4. Написать функцию main, пользующуюся этим классом и
 *             перехватывающую все исключения от его методов, а
 *             также выводящую подробную информацию о всех возникающих
 *             ошибках.

 *
 * @copyright Nikita Bulaev 2019
 *
 */

#include <iostream>
#include <ctime>


typedef enum {
    MOVE_STOP  = 0,
    MOVE_TOP   = 1,
    MOVE_RIGHT = 2,
    MOVE_DOWN  = 3,
    MOVE_LEFT  = 4
} Move_t; /*!< Доступные ходы */


typedef struct {
    int x;
    int y;
} Coordinates_t; /*!< Стурктура для хранеия координат */

typedef enum {
    NoException = 0,
    OffTheField,
    IllegalCommand
} RobotExceptions_t; /*!< Исключения при движении робота */

constexpr int width  = 10; /*!< Ширина поля */
constexpr int height = 10; /*!< Высота поля */

/** Перегрузка оператора << для вывода названия хода */
std::ostream &operator<<(std::ostream &os, const Move_t &m) {
    switch (m) {
        case MOVE_TOP:
            os << "Top";
            break;

        case MOVE_RIGHT:
            os << "Right";
            break;

        case MOVE_DOWN:
            os << "Down";
            break;

        case MOVE_LEFT:
            os << "Left";
            break;

        case MOVE_STOP:
            os << "No move";
            break;

        default:
            os << "Unknown";
            break;
    }

    return os;
}

/** Класс для хранения исключений при движении робота */
class RobotEx {
  private:
    const RobotExceptions_t exception; /*!< Исключение */
    const int currPosX; /*!< Текущая позиция Х, на которой возникло исключение */
    const int currPosY; /*!< Текущая позиция Y, на которой возникло исключение */
    const Move_t move;  /*!< Ход, который вызвал исключение */
  public:
    RobotEx() : exception(IllegalCommand), currPosX(0), currPosY(0), move(MOVE_STOP) {}
    RobotEx(RobotExceptions_t ex, int x, int y, Move_t m): exception(ex), currPosX(x), currPosY(y), move(m) {}

    friend std::ostream &operator<<(std::ostream &os, const RobotEx &ex);
};

/** Перегрузка оператора << для вывода названия исключения и текущей позиции робота */
std::ostream &operator<<(std::ostream &os, const RobotEx &ex) {
    switch (ex.exception) {
        case OffTheField:
            os << "Off the field";
            break;

        case IllegalCommand:
            os << "Illegal command";
            break;

        case NoException:
        default:
            break;
    }

    os << ", at position [" << ex.currPosX << ", " << ex.currPosY << "], dir -> " << ex.move;

    return os;
}

/** Движение робота и обработка исключений */
class Robot {
  private:
    int x; /*!< Текущая координата X на поле */
    int y; /*!< Текущая координата Y на поле */

    /**
     * @brief Вычисление координат исходя из положения и хода
     *
     * @param  m Ход, который надо сделать
     * @return   Новые координаты
     * @throw    RobotEx() при вводе некорректного хода
     */
    Coordinates_t computeMove(Move_t m) {
        Coordinates_t tmp;

        switch (m) {
            case MOVE_TOP:
                tmp.x = x;
                tmp.y = y - 1;
                break;

            case MOVE_RIGHT:
                tmp.x = x + 1;
                tmp.y = y;
                break;

            case MOVE_DOWN:
                tmp.x = x;
                tmp.y = y + 1;
                break;

            case MOVE_LEFT:
                tmp.x = x - 1;
                tmp.y = y;
                break;

            case MOVE_STOP:
            default:
                throw RobotEx(IllegalCommand, x, y, m);
                break;
        }

        return tmp;
    }

    /**
     * @brief Проверка на корректность координат
     * @param  a Координата на оси X
     * @param  b Координата на оси Y
     * @return   true, если координаты корретные
     */
    bool isCorrectPoint(int a, int b) const {
        if (a < 0 || a >= width || b < 0 || b >= height) {
            return false;
        }

        return true;
    }

  public:
    Robot() {
        srand(time(NULL));
        x = rand() % 10;
        y = rand() % 10;
    }

    Robot(int a, int b) {
        if (!isCorrectPoint(a, b)) {
            throw  RobotEx();
        }
    }

    /**
     * @brief Совершаем ход по команде
     *
     * @param m Ход из списка Move_t
     */
    void move(Move_t m) {
        Coordinates_t newMove = computeMove(m);

        if (!isCorrectPoint(newMove.x, newMove.y)) {
            throw RobotEx(OffTheField, x, y, m);
        }

        x = newMove.x;
        y = newMove.y;
    }

    friend std::ostream &operator<<(std::ostream &os, const Robot &rb);
};

/** Перегрузка оператора << для вывода текущего положения робота на поле */
std::ostream &operator<<(std::ostream &os, const Robot &rb) {
    os << "[" << rb.x << ", " << rb.y << "]";
    return os;
}

int main (int argc, char ** args) {

    Robot robot;

    int newMove = -1;

    for (;;) {
        try {
            std::cout << "Current robot position: " << robot << std::endl;
            std::cout << "Make move (1 - top, 2 - right, 3 - down, 4 - left: ";
            std::cin >> newMove;

            robot.move(static_cast<Move_t>(newMove));
        } catch (RobotEx &ex) {
            std::cout << "Got exception: " << ex << std::endl;

        } catch (...) {
            std::cout << "Got unknown exception" << std::endl;
            exit(1);
        }
    }

    return 0;
}
