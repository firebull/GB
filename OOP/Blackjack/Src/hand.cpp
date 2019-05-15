#include "hand.h"

Hand::Hand() { m_Cards.reserve(7); }

Hand::~Hand() { Clear(); }

void Hand::Add(Card *pCard) { m_Cards.push_back(pCard); }

void Hand::Clear() {
    // проходит по вектору, освобождая всю память в куче
    std::vector<Card *>::iterator iter = m_Cards.begin();

    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        delete *iter;
        *iter = nullptr;
    }

    // очищает вектор указателей
    m_Cards.clear();
}

int Hand::GetTotal() const {
    // если карт в руке нет, возвращает значение 0
    if (m_Cards.empty()) {
        return 0;
    }

    //если первая карта имеет значение 0, то она лежит рубашкой вверх:
    // вернуть значение 0
    if (m_Cards[0]->GetValue() == 0) {
        return 0;
    }

    // находит сумму очков всех карт, каждый туз дает 1 очко
    int                                 total = 0;
    std::vector<Card *>::const_iterator iter;

    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        total += (*iter)->GetValue();
    }

    // определяет, держит ли рука туз
    bool containsAce = false;

    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter) {
        if ((*iter)->GetValue() == Card::ACE) {
            containsAce = true;
        }
    }

    // если рука держит туз и сумма довольно маленькая, туз дает 11 очков
    if (containsAce && total <= 11) {
        // добавляем только 10 очков, поскольку мы уже добавили
        // за каждый туз по одному очку
        total += 10;
    }

    return total;
}
