#include "game.h"

// Конструктор этого класса принимает ссылку на вектор строк, представляющих
// имена игроков - людей. Конструктор создает объект класса Player для каждого имени
Game::Game(const std::vector<std::string> &names) {
    // создает вектор игроков из вектора с именами
    std::vector<std::string>::const_iterator pName;

    for (pName = names.begin(); pName != names.end(); ++pName) {
        m_Players.push_back(Player(*pName));
    }

    // запускает генератор случайных чисел
    srand(static_cast<unsigned int>(time(nullptr)));
    m_Deck.Populate();
    m_Deck.Shuffle();
}

Game::~Game() {}

void Game::Play() {
    // раздает каждому по две стартовые карты
    std::vector<Player>::iterator pPlayer;

    for (int i = 0; i < 2; ++i) {
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            m_Deck.Deal(*pPlayer);
        }

        m_Deck.Deal(m_House);
    }

    // прячет первую карту дилера
    m_House.FlipFirstCard();

    // открывает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        std::cout << *pPlayer << std::endl;
    }

    std::cout << m_House << std::endl;

    // раздает игрокам дополнительные карты
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        m_Deck.AdditionalCards(*pPlayer);
    }

    // показывает первую карту дилера
    m_House.FlipFirstCard();
    std::cout << std::endl << m_House;

    // раздает дилеру дополнительные карты
    m_Deck.AdditionalCards(m_House);

    if (m_House.IsBusted()) {
        // все, кто остался в игре, побеждают
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBusted())) {
                pPlayer->Win();
            }
        }
    } else {
        // сравнивает суммы очков всех оставшихся игроков с суммой очков дилера
        for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
            if (!(pPlayer->IsBusted())) {
                if (pPlayer->GetTotal() > m_House.GetTotal()) {
                    pPlayer->Win();
                } else if (pPlayer->GetTotal() < m_House.GetTotal()) {
                    pPlayer->Lose();
                } else {
                    pPlayer->Push();
                }
            }
        }
    }

    // очищает руки всех игроков
    for (pPlayer = m_Players.begin(); pPlayer != m_Players.end(); ++pPlayer) {
        pPlayer->Clear();
    }

    m_House.Clear();
}
