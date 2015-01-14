/* DOMINION
 * David Mally, Richard Roberts
 * VictoryCard.cpp
 * Defines VictoryCard class, which is used to represent
 * victory cards (estate, duchy, province, gardens) in Dominion.
 */
#include <string>
#include "VictoryCard.h"
#include "Card.h"

VictoryCard::VictoryCard(int cost, int points, std::string name,
                         CardType type, std::string info)
                        : Card(cost, name, type, info) {
    m_points = points;
}

int VictoryCard::GetPoints(void) {
    return m_points;
}

std::string VictoryCard::ToString(void) {
    std::string cardPrint = Card::ToString();
    return cardPrint + "\nPoints: " + std::to_string(m_points);
}
