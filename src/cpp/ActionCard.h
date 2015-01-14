/* DOMINION
 * David Mally, Richard Roberts
 * ActionCard.h
 * Header for ActionCard class.
 * Also defines a state block struct,
 * which is defined here for ease of inclusion.
 * (We were getting weird multiple-inclusion
 * errors before, even with header guards, due
 * to this struct definition)
 */

#ifndef __ACTIONCARD_H__
#define __ACTIONCARD_H__

#include <string>
#include "Card.h"
#include "Player.h"
#include "Pile.h"

struct stateBlock{
    Player *p1;
    Player *p2;
    Pile *trash;
    std::vector<Pile> *kingdom;
};


class ActionCard : public Card {
    public:
        ActionCard(int cost, int actions, int buys, int cards, int coins,
                   std::string name,
                   bool (*effect)(struct stateBlock *, bool) = NULL,
                   CardType type = ACTION, std::string info = "");
        std::string ToString(void);
};

#endif

