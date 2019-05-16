#ifndef DECK_H
#define DECK_H
#include "generic_player.h"
#include "hand.h"

class Deck : public Hand {
  public:
    Deck();

    virtual ~Deck();

    /** Создает стандартную колоду из 52 карт */
    void Populate();

    /**
     * Тасует карты
     *
     * @note Функция переставляет указатели, расположенные
     *       в векторе m_Cards с помощью функции random_shuffle()
     *       стандартной библиотеки шаблонов
     */
    void Shuffle();

    /**
     * Раздает одну карту в руку
     *
     * @note Функция добавляет в конец вектора m_Cards копию
     *       указателя с помощью функции-члена Add().
     *       Данная функция может работать с объектами классов
     *       Player и House
     * @param aHand Карты игрока или дилера
     */
    void Deal(Hand &aHand);

    /** Дает дополнительные карты игроку */
    void AdditionalCards(GenericPlayer &aGenericPlayer);
};

#endif  // DECK_H
