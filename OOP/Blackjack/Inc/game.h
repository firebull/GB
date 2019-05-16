#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "deck.h"
#include "house.h"
#include "player.h"

class Game {
  public:
    /**
     * @brief Конструктор этого класса принимает ссылку на вектор
     *        строк, представляющих имена игроков - людей.
     *
     * @note  Конструктор создает объект класса Player для каждого имени
    */
    Game(const std::vector<std::string> &names);

    ~Game();

    /** Проводит игру в Blackjack */
    void Play();

  private:
    Deck                m_Deck;
    House               m_House;
    std::vector<Player> m_Players;
};

#endif  // GAME_H
