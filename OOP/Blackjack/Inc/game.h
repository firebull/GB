#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>

#include "deck.h"
#include "house.h"
#include "player.h"

class Game {
  public:
    Game(const std::vector<std::string> &names);

    ~Game();

    // проводит игру в Blackjack
    void Play();

  private:
    Deck                m_Deck;
    House               m_House;
    std::vector<Player> m_Players;
};

#endif  // GAME_H
