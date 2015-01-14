/* DOMINION
 * David Mally, Richard Roberts
 * TreasureCard.cpp
 * Defines TreasureCard class, which is used to represent
 * treasures (copper, silver, gold) in Dominion.
 */
#include <string>
#include "TreasureCard.h"
#include "Card.h"

TreasureCard::TreasureCard(int cost, int coins, std::string name,
                           CardType type, std::string info)
                           : Card(cost, name, type, info) {
    SetCoins(coins);
}

int TreasureCard::GetCoins(void) {
    return m_coins;
}

std::string TreasureCard::ToString(void) {
    std::string cardPrint = Card::ToString();
    return cardPrint + "\nCoins: " + std::to_string(m_coins);
}

