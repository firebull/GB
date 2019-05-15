#ifndef DECK_H
#define DECK_H
#include "generic_player.h"
#include "hand.h"

class Deck : public Hand {
  public:
    Deck();

    virtual ~Deck();

    // создает стандартную колоду из 52 карт
    void Populate();

    // тасует карты
    void Shuffle();

    // раздает одну карту в руку
    void Deal(Hand &aHand);

    // дает дополнительные карты игроку
    void AdditionalCards(GenericPlayer &aGenericPlayer);
};

#endif  // DECK_H
