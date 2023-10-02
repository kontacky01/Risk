#include <iostream>
#include "Cards.h"

void CardsDriver::testCards() {
    cout << endl << "*************************************" << endl
         << "Hello, World! Let's test some Cards. \n"
         << "*************************************" << endl << endl;

    // some variables for later
    string cardToPlay = "Bomb";
    string CheckCardType;

    cout << "---------> Testing Phase 1 <---------" << endl << endl;

    // we start by creating some cards
    Card card1("Bomb");
    Card card2("Reinforcement");
    Card card3("Blockade");
    Card card4("Airlift");
    cout << "...Setting Card5 to \"Breakfast\"..." << endl;
    Card card5("Breakfast"); // invalid type, will produce error message
    cout << endl;

    cout << "Card 1 type: " << card1.getType() << endl;
    cout << "Card 2 type: " << card2.getType() << endl;
    cout << "Card 3 type: " << card3.getType() << endl;
    cout << "Card 4 type: " << card4.getType() << endl;
    cout << "Card 5 type: " << card5.getType() << endl << endl;
    cout << "...Setting Card5 to a valid type..." << endl;
    card1.setType("Diplomacy"); // testing setter; changes invalid type to something valid
    cout << "Card5 is now a \"" << card1.getType() << "\" card." << endl << endl; // testing getter

    cout << "...Validating Card2 type..." << endl;
    CheckCardType = card2.getType(); // validate a card type using isValidCardType function
    if (Card::isValidCardType(CheckCardType)) {
        cout << "Card type " << "\"" << CheckCardType << "\" is valid." << endl << endl;
    } else {
        cout << "Card type " << "\"" << CheckCardType << "\" is not valid." << endl << endl;
    }

    cout << "---------> Testing Phase 2 <---------" << endl << endl;

    // let's copy some cards
    cout << "...Making a deep copy of Card4..." << endl;
    Card copiedCard(card4);
    cout << "Card4 type: " << "\"" << card4.getType() << "\"" << endl;
    cout << "...Setting Card4 type to \"Blockade\"..." << endl;
    card4.setType("Blockade");
    cout << "Card4 original is now: \"" << card4.getType() << "\"" << endl;
    cout << "Card4 copy is now: \"" << copiedCard.getType() << "\"" << endl << "Deep copy is a success!" << endl << endl;

    cout << "...Creating a new deck of cards..." << endl << endl;
    Deck NewDeck;
    NewDeck.fillDeck();
    NewDeck.printDeck();
    NewDeck.getSize();
    cout << endl;
    cout << "...Creating a deep copy of The Deck..." << endl << endl;
    Deck NewDeckCopy (NewDeck);
    cout << "...Shuffling original Deck..." << endl << endl;
    cout << "(Shuffled Original) \n"; NewDeck.shuffleDeck();
    NewDeck.printDeck();
    cout << endl << "...Printing deep copy of The Deck..." << endl << endl;
    cout << "(Copy) "; NewDeckCopy.printDeck();
    cout << endl << "Deep copy is a success!" << endl;

    cout << endl << "---------> Testing Phase 3 <---------" << endl << endl;

    cout << "...Creating a player's hand of cards..." << endl << endl;
    Hand Hand;
    Hand.fillHand(NewDeck);
    Hand.printHand();
    Hand.getSize();
    cout << endl << "...Checking The Deck for remaining cards..." << endl << endl;
    NewDeck.printDeck();
    NewDeck.getSize();

    // testing play function
    cout << endl << "...Player is choosing a card to play..." << endl << endl;
    cout << "...Checking Orders List for created order..." << endl << endl;
    Hand.play(cardToPlay, &NewDeck);
    cout << endl;
    cout << "...Checking Your Hand for remaining cards..." << endl << endl;
    Hand.printHand();
    Hand.getSize();

    cout << endl << "...Checking The Deck to see if played card has returned..." << endl << endl;
    NewDeck.printDeck();
    NewDeck.getSize();

    cout << endl << "...You drew a card from The Deck..." << endl << endl;
    Card* drawnCard = NewDeck.draw();
    Hand.addCard(drawnCard);
    cout << "You drew a \"" << drawnCard->getType() << "\" card." << endl;
    cout << endl << "...Checking remaining cards in The Deck..." << endl << endl;
    NewDeck.printDeck();
    NewDeck.getSize();

    cout << endl << "...Checking the cards in Your Hand..." << endl << endl;
    Hand.printHand();
    Hand.getSize();
    cout << endl;
}