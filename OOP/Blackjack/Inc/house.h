#ifndef HOUSE_H
#define HOUSE_H
#include "generic_player.h"

class House : public GenericPlayer {
  public:
    House(const std::string &name = "House");

    virtual ~House();

    /**
     * @brief Показывает, хочет ли дилер продолжать брать карты
     *
     * @return TRUE, если количество очков меньше или равно 16
     * @return FALSE, если больше 16
     */
    virtual bool IsHitting() const;

    /** Переворачивает первую карту */
    void FlipFirstCard();
};

#endif  // HOUSE_H
