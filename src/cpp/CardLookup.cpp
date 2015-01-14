/* DOMINION
 * David Mally, Richard Roberts
 * CardLookup.cpp
 * Contains definitions for card effects,
 * utilities for handling i/o errors in card
 * effects, and a function to generate a vector
 * of all action cards.
 */

#include <vector>
#include <iostream>
#include <limits>
#include "CardLookup.h"

/* Clears cin of error flags and flushes the stdin buffer */
void lookup::ClearCinError(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<int>::max(),'\n');
}

/* Checks invalid input when choosing cards by index from a pile or vector
 * of piles. */
void lookup::CheckInvalidChoice(size_t pileSize, int *choicePtr) {
    if(std::cin.fail() || *choicePtr < DEF_CHOICE ||
      *choicePtr > (int)pileSize - 1) {
        lookup::ClearCinError();
        std::cout << "Invalid choice." << std::endl;
        *choicePtr = BAD_CHOICE;
    }
}

bool lookup::CellarEffect(struct stateBlock *state, bool p1) {
    Pile *hand = p1 ? state->p1->HandPtr() : state->p2->HandPtr();
    Pile *discard = p1 ? state->p1->DiscardPtr() : state->p2->DiscardPtr();
    Pile *deck = p1 ? state->p1->DeckPtr() : state->p2->DeckPtr();
    int numDiscarded = 0;
    size_t handSize = hand->Size();
    for(size_t i = 0; i < handSize; i++) {
        hand->PrintPileAsHand();
        int choice = BAD_CHOICE;
        while(choice < DEF_CHOICE) {
            std::cout << "Choose a card to discard (0 - "
                      << hand->GetCards().size() - 1
                      << ") or -1 to discard none: ";
            std::cin >> choice;
            CheckInvalidChoice(hand->GetCards().size(), &choice);
        }
        if(choice >= 0) {
            hand->Move(choice, discard);
            numDiscarded++;
        }
    }
    for(int i = 0; i < numDiscarded; i++) {
        if(deck->Size() > 0) {
            hand->TopDeck(deck->DrawTopCard());
        }
    }
    return false;
}

bool lookup::ChapelEffect(struct stateBlock *state, bool p1) {
    Pile *hand = p1 ? state->p1->HandPtr() : state->p2->HandPtr();
    int choice = BAD_CHOICE;
    for(size_t i = 0; i < LIM_CHAPEL; i++) {
        hand->PrintPileAsHand();
        choice = BAD_CHOICE;
        while(choice == BAD_CHOICE) {
            std::cout << "Choose a card to trash (0 - "
                      << hand->GetCards().size() - 1
                      << ") or -1 to trash none: ";
            std::cin >> choice;
            CheckInvalidChoice(hand->GetCards().size(), &choice);
        }
        if(choice >= 0) {
            hand->Move(choice, state->trash);
        }
        if(choice == DEF_CHOICE) {
            break;
        }
    }
    return false;
}

bool lookup::ChancellorEffect(struct stateBlock *state, bool p1) {
    Pile *discard = p1 ? state->p1->DiscardPtr() : state->p2->DiscardPtr();
    Pile *deck = p1 ? state->p1->DeckPtr() : state->p2->DeckPtr();
    std::string cmd;
    std::cout << "Put deck -> discard? (y/n) ";
    std::cin >> cmd;
    if(cmd == YES) {
        discard->TakeAllFrom(deck);
        std::cout << std::endl
                  << "Discarded deck." << std::endl;
    } else {
        std::cout << std::endl
                  << "Keeping deck." << std::endl;
    }
    return false;
}

bool lookup::WorkshopEffect(struct stateBlock *state, bool p1) {
    Pile *discard = p1 ? state->p1->DiscardPtr() : state->p2->DiscardPtr();
    std::string cmd;
    std::cout << "Choose a card with cost <= $4:" << std::endl;
    for(size_t i = 0; i < state->kingdom->size(); i++) {
        if(state->kingdom->at(i).GetTopCard()->GetCost() <= LIM_WORKSHOP) {
            std::cout << state->kingdom->at(i).GetTopCard()->GetName()
                      << std::endl;
        }
    }
    bool validResponse = false;
    while(!validResponse) {
        std::cout << "Name a card: ";
        std::cin >> cmd;
        for(size_t i = 0; i < state->kingdom->size(); i++) {
            if(state->kingdom->at(i).GetTopCard()->GetName() == cmd &&
               state->kingdom->at(i).GetTopCard()->GetCost() <= LIM_WORKSHOP) {
                state->kingdom->at(i).Move(0, discard);
                validResponse = true;
            }
        }
    }
    return false;
}

bool lookup::BureaucratEffect(struct stateBlock *state, bool p1) {
    Pile *deck = p1 ? state->p1->DeckPtr() : state->p2->DeckPtr();
    Pile *otherHand = p1 ? state->p2->HandPtr() : state->p1->HandPtr();
    Pile *otherDeck = p1 ? state->p2->DeckPtr() : state->p1->DeckPtr();

    // Topdeck a silver
    for(size_t i = 0; i < state->kingdom->size(); i++) {
        if(state->kingdom->at(i).GetName() == "silver") {
            state->kingdom->at(i).Move(0, deck);
        }
    }

    // Opponent reveals a victory card and topdecks it
    for(size_t i = 0; i < otherHand->Size(); i++) {
        if(otherHand->At(i)->GetPoints() > 0) {
            otherHand->Move(i, otherDeck);
            return false;
        }
    }
    return false;
}

bool lookup::FeastEffect(struct stateBlock *state, bool p1) {
    //Trash self
    //Gain card costing up to 5
    Player *currPlayer = p1 ? state->p1 : state->p2;
    std::cout << "Gain a card costing up to $5:" << std::endl;
    std::vector<Pile> *kingdom = state->kingdom;
    for(size_t i = 0; i < kingdom->size(); i++) {
        std::cout << i << ": "
                  << kingdom->at(i).GetTopCard()->ToString() << std::endl;
    }
    int idx = DEF_CHOICE;
    while(idx < 0) {
        std::cin >> idx;
        CheckInvalidChoice(kingdom->size(), &idx);
        if(kingdom->at(idx).GetTopCard()->GetCost() > LIM_FEAST) {
            std::cout << "Invalid choice. Card must cost <= $5."
                      << std::endl;
            idx = DEF_CHOICE;
        } else {
            currPlayer->AddToDiscard(kingdom->at(idx).DrawTopCard());
        }
    }
    return true;
}

bool lookup::MilitiaEffect(struct stateBlock *state, bool p1) {
    // Opponent discards down to 3 cards
    Player *otherPlayer = p1 ? state->p2 : state->p1;
    char otherPlayerNum = p1 ? '2' : '1';
    std::cout << "Player " << otherPlayerNum
              << ", discard down to 3 cards."
              << std::endl;
    while(otherPlayer->HandPtr()->Size() > LIM_MILITIA) {
        int idx = DEF_CHOICE;
        std::cout << "Choose card(s) to discard:" << std::endl;
        otherPlayer->HandPtr()->PrintPileAsHand();
        while(idx < 0 || idx > (int)otherPlayer->GetHand().Size() - 1) {
            std::cin >> idx;
            CheckInvalidChoice(otherPlayer->HandPtr()->Size(), &idx);
        }
        otherPlayer->DiscardCard(idx);
    }
    return false;
}
bool lookup::MoneylenderEffect(struct stateBlock *state, bool p1) {
    // Trash a copper and gain + $3
    Player *currPlayer = p1 ? state->p1 : state->p2;
    std::string cmd;
    std::cout << "Trash a copper and gain $3? (y/n)" << std::endl;
    std::cin >> cmd;
    if(cmd == YES) {
        int idx = currPlayer->GetHand().LookThrough(new Card(lookup::copper));
        if(idx > DEF_CHOICE) {
            currPlayer->TrashCard(idx, state->trash);
            currPlayer->AddCoins(COINS_MONEYLENDER);
        }
    }
    return false;
}

bool lookup::RemodelEffect(struct stateBlock *state, bool p1) {
    // Trash a card and gain a card costing up to $2 more than it
    Player *currPlayer = p1 ? state->p1 : state->p2;
    Pile *trash = state->trash;
    std::vector<Pile> *kingdom = state->kingdom;
    int idx = DEF_CHOICE;
    currPlayer->GetHand().PrintPileAsHand();
    while(idx < 0) {
        std::cin >> idx;
        CheckInvalidChoice(currPlayer->GetHand().Size(), &idx);
    }
    int cardCost = currPlayer->GetHand().At(idx)->GetCost();
    currPlayer->HandPtr()->Move(idx, trash);
    for(size_t i = 0; i < kingdom->size(); i++) {
        std::cout << i << ": " << kingdom->at(i).GetTopCard()->ToString()
                  << std::endl;
    }
    idx = DEF_CHOICE;
    while(idx < 0) {
        std::cout << "Choose a card from the kingdom costing up to $"
                  << cardCost + LIM_REMODEL << ":" << std::endl;
        std::cin >> idx;
        CheckInvalidChoice(kingdom->size(), &idx);
        if(kingdom->at(idx).GetTopCard()->GetCost() >
           cardCost + LIM_REMODEL) {
            idx = DEF_CHOICE;
        }
    }
    currPlayer->AddToDiscard(kingdom->at(idx).DrawTopCard());
    return false;
}

bool lookup::SpyEffect(struct stateBlock *state, bool p1) {
    // all players reveal top card of deck and either discard
    // or put back, your choice
    Player *currPlayer = p1 ? state->p1 : state->p2;
    Player *otherPlayer = p1 ? state->p2 : state->p1;
    std::string cmd;
    Card *currCard = currPlayer->GetDeck().GetTopCard();
    Card *otherCard = otherPlayer->GetDeck().GetTopCard();
    std::cout << "Your top card: " << currCard->GetName() << std::endl;
    std::cout << "Opponent's top card: " << otherCard->GetName() << std::endl;
    std::cout << std::endl << "Discard your card? (y/n)" << std::endl;
    std::cin >> cmd;
    if(cmd == YES) {
        currPlayer->DeckPtr()->Move(currPlayer->DeckPtr()->Size() - 1,
                                    currPlayer->DiscardPtr());
    }
    std::cout << std::endl << "Discard your opponent's card? (y/n)" << std::endl;
    std::cin >> cmd;
    if(cmd == YES) {
        otherPlayer->DeckPtr()->Move(otherPlayer->DeckPtr()->Size() - 1,
                                     otherPlayer->DiscardPtr());
    }
    return false;
}

bool lookup::ThiefEffect(struct stateBlock *state, bool p1) {
    // Other player reveals top 2 cards of deck, trashes one
    // of your choice if a treasure, and then discards the other.
    // You may gain the trashed card if you wish.
    Player *currPlayer = p1 ? state->p1 : state->p2;
    Player *otherPlayer = p1 ? state->p2 : state->p1;
    Pile *trash = state->trash;
    std::string cmd;
    Card *otherCard1 = otherPlayer->DeckPtr()->DrawTopCard();
    Card *otherCard2 = otherPlayer->DeckPtr()->DrawTopCard();
    std::cout << "Opponent's top 2 cards: " << std::endl
              << otherCard1->GetName() << std::endl
              << otherCard2->GetName() << std::endl;
    bool trashed = false;
    if(otherCard1->GetType() == TREASURE_C) {
        std::cout << "Trash " << otherCard1->GetName() << "? (y/n)"
                  << std::endl;
        std::cin >> cmd;
        if(cmd == YES) {
            // Trash and optionally gain the first card?
            trashed = true;
            std::cout << "Do you wish to gain the trashed card? (y/n)"
                      << std::endl;
            std::cin >> cmd;
            if(cmd == YES) {
                currPlayer->AddToDiscard(otherCard1);
            } else {
                trash->TopDeck(otherCard1);
            }
            // Discard the 2nd card, since we already trashed one
            otherPlayer->AddToDiscard(otherCard2);
            return false;
        } else {
            // If we choose not to trash, discard the card
            otherPlayer->AddToDiscard(otherCard1);
        }
    } else {
        // If the first card is not a treasure, we must discard it
        otherPlayer->AddToDiscard(otherCard1);
    }

    // If the 2nd card is a treasure and we didn't trash the first one,
    // we may choose to trash it
    if(otherCard2->GetType() == TREASURE_C && !trashed) {
        std::cout << "Trash " << otherCard2->GetName() << "? (y/n)"
                  << std::endl;
        std::cin >> cmd;
        if(cmd == YES) {
            // Trash and optionally gain the first card?
            trashed = true;
            std::cout << "Do you wish to gain the trashed card? (y/n)"
                      << std::endl;
            std::cin >> cmd;
            if(cmd == YES) {
                currPlayer->AddToDiscard(otherCard2);
            } else {
                trash->TopDeck(otherCard2);
            }
        } else {
            otherPlayer->AddToDiscard(otherCard2);
        }
    } else {
        // If the second card is not a treasure, we must discard it
        otherPlayer->AddToDiscard(otherCard2);
    }
    return false;
}

bool lookup::ThroneroomEffect(struct stateBlock *state, bool p1) {
    // Plays any action card from your hand twice
    Player *currPlayer = p1 ? state->p1 : state->p2;
    int idx = DEF_CHOICE;
    currPlayer->GetHand().PrintPileAsHand();
    while(idx < 0) {
        std::cin >> idx;
        CheckInvalidChoice(currPlayer->HandPtr()->Size(), &idx);
        if(currPlayer->HandPtr()->At(idx)->GetType() != ACTION &&
           currPlayer->HandPtr()->At(idx)->GetType() != ATTACK &&
           currPlayer->HandPtr()->At(idx)->GetType() != REACTION) {
            idx = DEF_CHOICE;
            std:: cout << "Selection was not an action card." << std::endl;
        }
    }
    bool trashed = false;
    // Apply all +action, +buy, +coin, +card and effects twice
    for(int i = 0; i < LIM_THRONEROOM; i++) {
        if(currPlayer->HandPtr()->At(idx)->GetEffect() != NULL) {
            trashed = currPlayer->HandPtr()->At(idx)->PlayEffect(state, p1);
        }
        currPlayer->AddActions(currPlayer->HandPtr()->At(idx)->GetActions());
        currPlayer->AddBuys(currPlayer->HandPtr()->At(idx)->GetBuys());
        int plusCards = currPlayer->HandPtr()->At(idx)->GetCards();
        for(int i = 0; i < plusCards; i++) {
            currPlayer->DrawCard();
        }
        currPlayer->AddCoins(currPlayer->HandPtr()->At(idx)->GetCoins());
    }
    if(trashed) {
        currPlayer->TrashCard(idx, state->trash);
    } else {
        currPlayer->DiscardCard(idx);
    }
    return false;
}

bool lookup::CouncilroomEffect(struct stateBlock *state, bool p1) {
    // Other player draws a card
    Player *otherPlayer = p1 ? state->p2 : state->p1;
    otherPlayer->DrawCard();
    return false;
}

bool lookup::LibraryEffect(struct stateBlock *state, bool p1) {
    // Draw until you have 7 cards in hand. If you draw actions,
    // you may discard them if you wish.
    Player *currPlayer = p1 ? state->p1 : state->p2;
    while(currPlayer->GetHand().Size() < LIM_LIBRARY) {
        Card *tmpCard = currPlayer->DeckPtr()->DrawTopCard();
        if(tmpCard->GetType() == ACTION ||
           tmpCard->GetType() == ATTACK ||
           tmpCard->GetType() == REACTION) {
            std::string cmd;
            std::cout << tmpCard->ToString() << std::endl;
            std::cout << "Do you wish to set this card aside? (y/n)"
                      << std::endl;
            std::cin >> cmd;
            if(cmd == "y" || cmd == "yes") {
                currPlayer->AddToDiscard(tmpCard);
            } else {
                currPlayer->AddToHand(tmpCard);
            }
        } else {
            currPlayer->AddToHand(tmpCard);
        }
    }
    return false;
}

bool lookup::MineEffect(struct stateBlock *state, bool p1) {
    // Trash a treasure card and gain a treasure card costing
    // up to 3 more than it in-hand.
    Player *currPlayer = p1 ? state->p1 : state->p2;
    std::vector<Pile> *kingdom = state->kingdom;
    int idx = DEF_CHOICE;
    while(idx < 0) {;
        currPlayer->GetHand().PrintPileAsHand();
        std::cin >> idx;
        CheckInvalidChoice(currPlayer->HandPtr()->Size(), &idx);
        if(currPlayer->HandPtr()->At(idx)->GetType() == TREASURE_C) {
            std::cout << "Card choices:" << std::endl;
            int cardCost = currPlayer->HandPtr()->At(idx)->GetCost();
            currPlayer->TrashCard(idx, state->trash);
            // Treasure cards are the last 3 cards in the kingdom vector
            // Silver
            std::cout << "0: " << kingdom->at(IDX_SILVER(kingdom->size()))
                                  .At(0)->ToString()
                      << std::endl;
            // Gold
            if(cardCost + LIM_MINE >= COST_GOLD) {
                std::cout << "1: "
                          << kingdom->at(IDX_GOLD(kingdom->size())).At(0)
                             ->ToString()
                          << std::endl;
            }
            idx = DEF_CHOICE;
            while(idx < 0) {
                std::cin >> idx;
                CheckInvalidChoice(currPlayer->HandPtr()->Size(), &idx);
                if(idx >= 0 && idx < LIM_MINE_IDX){
                    // Add card to hand
                    currPlayer->AddToHand(kingdom->at(
                                kingdom->size() - 1 - (1 -idx)).DrawTopCard());
                } else {
                    idx = DEF_CHOICE;
                }
            }
        } else {
            idx = DEF_CHOICE;
        }
    }
    return false;
}

bool lookup::WitchEffect(struct stateBlock *state, bool p1) {
    // Opponent gains 1 curse
    Pile *otherDiscard = p1 ? state->p2->DiscardPtr()
                            : state->p1->DiscardPtr();
    for(size_t i = 0; i < state->kingdom->size(); i++) {
        if(state->kingdom->at(i).GetName() == "curse") {
            state->kingdom->at(i).Move(0, otherDiscard);
        }
    }
    return false;
}

bool lookup::AdventurerEffect(struct stateBlock *state, bool p1) {
    // Reveal cards from your deck until you find 2 treasures.
    // Put the treasures in-hand and discard the other cards.
    Player *currPlayer = p1 ? state->p1 : state->p2;
    int treasureCount = 0;
    while(treasureCount < LIM_ADVENTURER) {
        Card *tmpCard = currPlayer->DeckPtr()->DrawTopCard();
        if(tmpCard->GetType() == TREASURE_C) {
            treasureCount++;
            currPlayer->AddToHand(tmpCard);
        } else {
            currPlayer->AddToDiscard(tmpCard);
        }
    }
    return false;
}

std::vector<Card> lookup::GenAllCards(void) {
    std::vector<Card> allCards;

    allCards.push_back((lookup::cellar));
    allCards.push_back((lookup::chapel));
    allCards.push_back((lookup::moat));

    allCards.push_back((lookup::chancellor));
    allCards.push_back((lookup::village));
    allCards.push_back((lookup::woodcutter));
    allCards.push_back((lookup::workshop));

    allCards.push_back((lookup::bureaucrat));
    allCards.push_back((lookup::feast));
    allCards.push_back((lookup::gardens));
    allCards.push_back((lookup::militia));
    allCards.push_back((lookup::moneylender));
    allCards.push_back((lookup::remodel));
    allCards.push_back((lookup::smithy));
    allCards.push_back((lookup::spy));
    allCards.push_back((lookup::thief));
    allCards.push_back((lookup::throneroom));

    allCards.push_back((lookup::councilroom));
    allCards.push_back((lookup::festival));
    allCards.push_back((lookup::laboratory));
    allCards.push_back((lookup::library));
    allCards.push_back((lookup::market));
    allCards.push_back((lookup::mine));
    allCards.push_back((lookup::witch));

    allCards.push_back((lookup::adventurer));

    return allCards;
}
