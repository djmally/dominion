/* DOMINION
 * David Mally, Richard Roberts
 * TreasureCard.h
 * Defines TreasureCard class, which is used to represent
 * treasures (copper, silver, gold) in Dominion.
 */
#ifndef __TREASURECARD_H__
#define __TREASURECARD_H__

#include <string>
#include "Card.h"

class TreasureCard : public Card {
    private:
    public:
        TreasureCard(int cost, int coins, std::string name,
                CardType type = TREASURE_C, std::string info = "");
        int GetCoins(void);
        std::string ToString(void);
};

#endif

