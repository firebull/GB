#ifndef PLAYER_H
#define PLAYER_H
#include "generic_player.h"

class Player : public GenericPlayer {
  public:
    Player(const std::string &name = "");

    virtual ~Player();

    // показывает, хочет ли игрок продолжать брать карты
    virtual bool IsHitting() const;

    // объявляет, что игрок победил
    void Win() const;

    // объявляет, что игрок проиграл
    void Lose() const;

    // объявляет ничью
    void Push() const;
};

#endif  // PLAYER_H
