#include "deck.h"
#include <algorithm>

Deck::Deck() {
    m_Cards.reserve(52);
    Populate();
}

Deck::~Deck() {}

void Deck::Populate() {
    Clear();

    // создает стандартную колоду
    for (int s = Card::CLUBS; s <= Card::SPADES; ++s) {
        for (int r = Card::ACE; r <= Card::KING; ++r) {
            Add(new Card(static_cast<Card::rank>(r), static_cast<Card::suit>(s)));
        }
    }
}

// функция переставляет указатели, расположенные в векторе m_Cards
// с помощью функции random_shuffle() стандартной библиотеки шаблонов
// Для использования данной библиотеки необходим файл <algorithm>
void Deck::Shuffle() { random_shuffle(m_Cards.begin(), m_Cards.end()); }

// функция добавляет в конец вектора m_Cards копию указателя
// с помощью функции-члена Add().
// данная функция может работать с объектами классов Player и House
void Deck::Deal(Hand &aHand) {
    if (!m_Cards.empty()) {
        aHand.Add(m_Cards.back());
        m_Cards.pop_back();
    } else {
        std::cout << "Out of cards. Unable to deal.";
    }
}

// функция может работать как с объектами типа Player, так и House
void Deck::AdditionalCards(GenericPlayer &aGenericPlayer) {
    std::cout << std::endl;

    //продолжает раздавать карты до тех пор, пока у игрока не случается
    // перебор или пока он хочет взять еще одну карту
    while (!(aGenericPlayer.IsBusted()) && aGenericPlayer.IsHitting()) {
        Deal(aGenericPlayer);
        std::cout << aGenericPlayer << std::endl;

        if (aGenericPlayer.IsBusted()) {
            aGenericPlayer.Bust();
        }
    }
}
