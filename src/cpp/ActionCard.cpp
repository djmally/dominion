/* DOMINION
 * David Mally, Richard Roberts
 * ActionCard.cpp
 * Contains class definition and member functions for ActionCard class,
 * which represents action cards.
 */

#include <string>
#include "Card.h"
#include "ActionCard.h"

ActionCard::ActionCard(int cost, int actions, int buys, int cards,
                       int coins, std::string name,
                       bool (*effect)(struct stateBlock *, bool),
                       CardType type, std::string info)
                       : Card(cost, name, type, info, effect) {
    Card::SetActions(actions);
    Card::SetBuys(buys);
    Card::SetCards(cards);
    Card::SetCoins(coins);
}

std::string ActionCard::ToString(void) {
    std::string cardPrint = Card::ToString();
    return cardPrint
           + "\nActions: " + std::to_string(m_actions)
           + "\nBuys: "    + std::to_string(m_buys)
           + "\nCards: "   + std::to_string(m_cards)
           + "\nCoins: "   + std::to_string(m_coins);
}

