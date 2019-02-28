/**
 * @copyright Nikita Bulaev 2019
 *
 * @file  task05.c
 * @brief С клавиатуры вводится номер месяца. Требуется определить,
 *        к какому времени года он относится.
 *
 */

#include <stdio.h>

/**
 * @brief Список месяцев
 *
 * @note на всякий случай жёстко пропишу их номера
 */
typedef enum {
    MONTH_JANUARY   = 1,
    MONTH_FEBRUARY  = 2,
    MONTH_MARCH     = 3,
    MONTH_APRIL     = 4,
    MONTH_MAY       = 5,
    MONTH_JUNE      = 6,
    MONTH_JULY      = 7,
    MONTH_AUGUST    = 8,
    MONTH_SEPTEMBER = 9,
    MONTH_OCTOBER   = 10,
    MONTH_NOVEMBER  = 11,
    MONTH_DECEMBER  = 12
} Month_l;

int main (int argc, const char * argv[]) {

    short month = 0;

    printf("Enter month number: ");

    // Проверяю входное значение. Если это не число,
    // вываливаюсь с системной ошибкой.
    if (scanf("%hd", &month) == 0) {
        printf("Invalid value, exitting.\n\n");
        return 1;  // Выходим с системной ошибкой
    }

    switch (month) {
        case MONTH_DECEMBER:
        case MONTH_JANUARY:
        case MONTH_FEBRUARY:
            printf("Month %hd is a WINTER month.\n", month);
            break;

        case MONTH_MARCH:
        case MONTH_APRIL:
        case MONTH_MAY:
            printf("Month %hd is a SPRING month.\n", month);
            break;

        case MONTH_JUNE:
        case MONTH_JULY:
        case MONTH_AUGUST:
            printf("Month %hd is a SUMMER month.\n", month);
            break;

        case MONTH_SEPTEMBER:
        case MONTH_OCTOBER:
        case MONTH_NOVEMBER:
            printf("Month %hd is an AUTUMN month.\n", month);
            break;

        default:
            printf("Must be between 1 and 12, exitting.\n\n");
            return 1;  // Выходим с системной ошибкой
            break;
    }

    return 0;
}
