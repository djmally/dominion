/* DOMINION
 * David Mally, Richard Roberts
 * VictoryCard.cpp
 * Defines VictoryCard class, which is used to represent
 * victory cards (estate, duchy, province, gardens) in Dominion.
 */
#ifndef __VICTORYCARD_H__
#define __VICTORYCARD_H__

#include <string>
#include "Card.h"

class VictoryCard : public Card {
    public:
        VictoryCard(int cost, int points, std::string name,
                    CardType type = VICTORY, std::string info = "");
        int GetPoints(void);
        std::string ToString(void);
};

#endif

