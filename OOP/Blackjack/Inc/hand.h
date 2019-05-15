#ifndef HAND_H
#define HAND_H

#include "card.h"
#include <vector>

class Hand {
  public:
    Hand();
    /** Виртуальный деструктор класса Hand */
    virtual ~Hand();

    /** Добавляет карту в руку */
    void Add(Card *pCard);

    /** Очищает руку от карт */
    void Clear();

    /**
     * @brief Получает сумму очков карт в руке, присваивая тузу
     *
     * @note Туз 1 или 11 в зависимости от ситуации
     * @return Количество очков в руке
     */
    int GetTotal() const;

  protected:
    std::vector<Card *> m_Cards;
};

#endif  // HAND_H
