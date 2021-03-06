#ifndef CARD_H
#define CARD_H

#include <iostream>

class Card {
  public:
    enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    /**
     * Перегружаем оператор<<, чтобы можно было отправить объект
     * типа Card в стандартный поток вывода
     */
    friend std::ostream &operator<<(std::ostream &os, const Card &aCard);

    Card(rank r = ACE, suit s = SPADES, bool ifu = true);

    /** Возвращает значение карты от 1 до 11 */
    int GetValue() const;

    /**
     * @brief Переворачивает карту
     *
     * @note Карта, лежащая лицом вверх, переворачивается
     *       лицом вниз и наоборот
     */
    void Flip();

  private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

/** Перегружает оператор<<, чтобы получить возможность отправить
    объект типа Card в поток cout */
std::ostream &operator<<(std::ostream &os, const Card &aCard);

#endif  // CARD_H
