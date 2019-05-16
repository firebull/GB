#ifndef PLAYER_H
#define PLAYER_H
#include "generic_player.h"

class Player : public GenericPlayer {
  public:
    Player(const std::string &name = "");

    virtual ~Player();

    /**
     * @brief Показывает, хочет ли игрок продолжать брать карты
     * @return TRUE, если хочет
     * @return FALSE, если не хочет
     */
    virtual bool IsHitting() const;

    /** Объявляет, что игрок победил */
    void Win() const;

    /** Объявляет, что игрок проиграл */
    void Lose() const;

    /** Объявляет ничью */
    void Push() const;
};

#endif  // PLAYER_H
