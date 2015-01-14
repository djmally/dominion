/* DOMINION
 * David Mally, Richard Roberts
 * Card.cpp
 * Contains class definition for basic Card class,
 * which is the superclass of all card types.
 */

#include <iostream>
#include <string>
#include "Card.h"
#include "Defs.h"

Card::Card(int cost, std::string name, CardType type, std::string info,
           bool (*effect)(struct stateBlock *, bool)) {
    m_cost = cost;
    m_name = name;
    m_type = type;
    m_info = info;
    m_effect = effect;
    m_actions = DEF_ACTIONS;
    m_buys = DEF_BUYS;
    m_cards = DEF_CARDS;
    m_coins = DEF_COINS;
    m_points = DEF_POINTS;
}

int Card::GetCost(void) {
    return m_cost;
}

std::string Card::GetName(void) {
    return m_name;
}

CardType Card::GetType(void) {
    return m_type;
}

bool Card::operator==(Card other) {
    return m_name == other.GetName();
}

int Card::GetPoints(void) { return m_points; }

std::string Card::ToString(void) {
    return m_name + ": Cost: " + std::to_string(m_cost);
}

int Card::GetActions(void) { return m_actions; }
int Card::GetBuys(void)    { return m_buys; }
int Card::GetCards(void)   { return m_cards; }
int Card::GetCoins(void)   { return m_coins; }

void Card::SetActions(int actions)  { m_actions = actions; }
void Card::SetBuys(int buys)        { m_buys = buys; }
void Card::SetCards(int cards)      { m_cards = cards; }
void Card::SetCoins(int coins)      { m_coins = coins; }
void Card::SetPoints(int points)    { m_points = points; }

std::string Card::GetInfo(void) {
    return "\n" + m_info;
}

void Card::SetEffect(bool (*effect)(struct stateBlock *state, bool p1)) {
    m_effect = effect;
}

void *Card::GetEffect(void) {
    // Return types on function pointers are nasty
    return (void *)m_effect;
}


bool Card::PlayEffect(struct stateBlock *state, bool p1) {
    std::cout << ToString() << std::endl
              << GetInfo()  << std::endl;
    return m_effect(state, p1);
}
