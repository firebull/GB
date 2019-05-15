#include "house.h"

House::House(const std::string &name) : GenericPlayer(name) {}

House::~House() {}

// возвращает TRUE, если количество очков меньше или равно 16,
// и FALSE, если больше 16
bool House::IsHitting() const { return (GetTotal() <= 16); }

void House::FlipFirstCard() {
    if (!(m_Cards.empty())) {
        m_Cards[0]->Flip();
    } else {
        std::cout << "No card to flip!\n";
    }
}
