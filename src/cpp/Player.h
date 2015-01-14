/* DOMINION
 * David Mally, Richard Roberts
 * Player.h
 * Defines Player class, which represents the player and
 * tracks several piles (hand, deck, discard), as well as
 * functions on said piles.
 */
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <string>
#include "Pile.h"

#define BASE_HAND_SIZE  5
#define BASE_DECK_SIZE 10
#define BASE_ACTIONS    1
#define BASE_BUYS       1
#define BASE_COINS      0

#define NUM_COPPERS     7
#define NUM_ESTATES     3

class Player {
    private:
        std::string m_name;
        Pile m_hand;
        Pile m_deck;
        Pile m_discard;
        int m_actions;
        int m_buys;
        int m_coins;
    public:
        Player(int num = 1, std::string name = "p1");
        void SetNewTurn(void);
        Pile GetHand(void);
        Pile GetDeck(void);
        Pile GetDiscard(void);
        Pile *HandPtr(void);
        Pile *DeckPtr(void);
        Pile *DiscardPtr(void);
        std::string GetName(void);
        int GetActions(void);
        int GetBuys(void);
        int GetCoins(void);
        void AddActions(int actions);
        void AddBuys(int buys);
        void AddCoins(int coins);
        void AddToHand(Card *card);
        void AddToDeck(Card *card);
        void AddToDiscard(Card *card);
        void DrawCard(void);
        void DiscardCard(int handIdx);
        void TrashCard(int handIdx, Pile *trash);
        void PlayCard(int handIdx);
        bool operator==(Player other);
};

#endif

