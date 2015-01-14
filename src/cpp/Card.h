/* DOMINION
 * David Mally, Richard Roberts
 * Card.h
 * Header file for Card class. Also
 * defines a card type enum
 */

#ifndef __CARD_H__
#define __CARD_H__

#include <string>
#include "Defs.h"

#define DEF_POINTS  0
#define DEF_COST   -1
#define DEF_ACTIONS 0
#define DEF_BUYS    0
#define DEF_CARDS   0
#define DEF_COINS   0
#define DEF_NAME ""

struct stateBlock;

enum CardType {
    ACTION,
    ATTACK,
    REACTION,
    TREASURE_C, // To avoid duplicate enum names
    VICTORY,
    BASE
};


class Card {
    private:
        int m_cost;
        std::string m_name;
        CardType m_type;
        std::string m_info;
        bool (*m_effect)(struct stateBlock *state, bool p1);
    protected:
        int m_actions;
        int m_buys;
        int m_cards;
        int m_coins;
        int m_points;
        void SetActions(int actions);
        void SetBuys(int buys);
        void SetCards(int cards);
        void SetCoins(int coins);
        void SetPoints(int points);
    public:
        Card(int cost = DEF_COST, std::string name = DEF_NAME,
             CardType type = BASE, std::string info = "",
             bool (*effect)(struct stateBlock *, bool) = NULL);
        int GetCost(void);
        std::string GetName(void);
        CardType GetType(void);
        bool operator==(Card other);
        virtual int GetPoints(void);
        virtual std::string ToString(void);
        int GetActions(void);
        int GetBuys(void);
        int GetCards(void);
        int GetCoins(void);
        std::string GetInfo(void);
        void SetEffect(bool (*effect)(struct stateBlock *state, bool p1));
        void *GetEffect(void);
        bool PlayEffect(struct stateBlock *state, bool p1);
};

#endif

