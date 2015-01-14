/* DOMINION
 * David Mally, Richard Roberts
 * Player.cpp
 * Defines Player class, which represents the player and
 * tracks several piles (hand, deck, discard), as well as
 * functions on said piles.
 */
#include <cstdlib>
#include <string>
#include "Player.h"
#include "CardLookup.h"
#include "Pile.h"

Player::Player(int num, std::string name) {
    m_name = name;
    m_hand = num == 1 ? Pile(PLAYER1) : Pile(PLAYER2);
    m_deck = num == 1 ? Pile(PLAYER1) : Pile(PLAYER2);
    m_discard = num == 1 ? Pile(PLAYER1) : Pile(PLAYER2);

    /* Initialize actions/buys/coins */
    m_actions = BASE_ACTIONS;
    m_buys    = BASE_BUYS;
    m_coins   = BASE_COINS;

    /* Initialize deck to 3 estates & 7 coppers */
    for(int i = 0; i < NUM_ESTATES; i++) {
        VictoryCard *tmp = new VictoryCard(lookup::estate);
        m_deck.TopDeck(tmp);
    }
    for(int i = 0; i < NUM_COPPERS; i++) {
        TreasureCard *tmp = new TreasureCard(lookup::copper);
        m_deck.TopDeck(tmp);
    }

    /* Shuffle the deck */
    m_deck.TrueShuffle();

    /* Draw 5 cards */
    for(int i = 0; i < BASE_HAND_SIZE; i++) {
        m_deck.Move(0, &m_hand);
    }
}

void Player::SetNewTurn(void) {
    m_actions = BASE_ACTIONS;
    m_buys = BASE_BUYS;
    m_coins = BASE_COINS;
    for(int i = 0; i < BASE_HAND_SIZE; i++) {
        DrawCard();
    }
}

Pile Player::GetHand(void) {
    return m_hand;
}

Pile Player::GetDeck(void) {
    return m_deck;
}

Pile Player::GetDiscard(void) {
    return m_discard;
}

Pile *Player::HandPtr(void) {
    return &m_hand;
}

Pile *Player::DeckPtr(void) {
    return &m_deck;
}

Pile *Player::DiscardPtr(void) {
    return &m_discard;
}

std::string Player::GetName(void) {
    return m_name;
}

int Player::GetActions(void) {
    return m_actions;
}

int Player::GetBuys(void) {
    return m_buys;
}

int Player::GetCoins(void) {
    return m_coins;
}

void Player::AddActions(int actions) {
    m_actions += actions;
}

void Player::AddBuys(int buys) {
    m_buys += buys;
}

void Player::AddCoins(int coins) {
    m_coins += coins;
}

void Player::AddToHand(Card *card) {
    m_hand.TopDeck(card);
}

void Player::AddToDeck(Card *card) {
    m_deck.TopDeck(card);
}

void Player::AddToDiscard(Card *card) {
    m_discard.TopDeck(card);
}

void Player::DrawCard(void) {
    // If the deck runs out, put the discard pile into the deck
    // and reshuffle
    if(m_deck.Size() == 0) {
        m_deck.TakeAllFrom(&m_discard);
        m_deck.TrueShuffle();
    }
    // If the deck isn't completely drawn out, draw a card
    if(m_deck.Size() > 0) {
        m_deck.Move(0, &m_hand);
    }
}

void Player::DiscardCard(int handIdx) {
    m_hand.Move(handIdx, &m_discard);
}

void Player::TrashCard(int handIdx, Pile *trash) {
    m_hand.Move(handIdx, trash);
}

void Player::PlayCard(int handIdx) {
    if((size_t)handIdx < m_hand.Size()) {
    }
}

bool Player::operator==(Player other) {
    return m_name == other.GetName();
}

