#ifndef HOUSE_H
#define HOUSE_H
#include "generic_player.h"

class House : public GenericPlayer {
  public:
    House(const std::string &name = "House");

    virtual ~House();

    // показывает, хочет ли дилер продолжать брать карты
    virtual bool IsHitting() const;

    // переворачивает первую карту
    void FlipFirstCard();
};

#endif  // HOUSE_H
