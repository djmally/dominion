/* DOMINION
 * David Mally, Richard Roberts
 * Pile.h
 * Defines Pile class, which is used to hold vectors of cards as well as
 * some additional state.
 */
#ifndef __PILE_H__
#define __PILE_H__

#include <vector>
#include "Card.h"

#define DEF_SIZE        0
#define DEF_NAME       ""
#define CARD_NOT_FOUND -1
#define MIN_IDX         0
#define GEN_INTS "generateIntegers"

enum Owner {
    PLAYER1,
    PLAYER2,
    KINGDOM,
    TREASURE,
    TRASH
};

class Pile {
    private:
        Owner m_owner;
        std::vector<Card *> m_cards;
        std::string m_name;
    public:
        // Creates a pile with `size` duplicates of `cardType`
        Pile(Owner owner = TRASH, Card cardType = Card(),
             int size = DEF_SIZE, std::string name = DEF_NAME);
        // Returns the size of m_cards
        size_t Size(void);
        // Returns the pile's owner
        Owner GetOwner(void);
        // Returns the pile's name
        std::string GetName(void);
        // Returns the pile's card vector
        std::vector<Card *> GetCards(void);
        // Returns m_cards.at(idx)
        Card *At(int idx);
        // Returns and removes m_cards.at(idx)
        Card *DrawAt(int idx);
        // Emptys the pile
        void EmptyDeck(void);
        // Returns the top card on the pile without removing it
        Card *GetTopCard(void);
        // Returns & removes the top card on the pile
        Card *DrawTopCard(void);
        // Puts a card on top of the pile
        void TopDeck(Card *card);
        // Looks through the pile for a specific card
        int LookThrough(Card *card);
        // Shuffles the pile
        void TrueShuffle(void);
        // Merges `other` into this pile
        void TakeAllFrom(Pile *other);
        // Puts the first instance of `card` in this pile into `other`
        void Move(Card *card, Pile *other);
        // Puts `pile.at(i)` into `other`
        void Move(int idx, Pile *other);
        // Prints out all cards in the pile, as Kingdom
        void PrintPileAsKingdom(void);
        // Prints out all cards in the pile, as Hand
        void PrintPileAsHand(void);
};

#endif

