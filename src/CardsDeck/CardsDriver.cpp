#include <iostream>
#include "Cards.h"

void testCards() {
    cout << "\n" << "*************************************" << "\n"
         << "Hello, World! Let's test some Cards. \n"
         << "*************************************" << "\n" << "\n";

    // some variables for later
    string cardToPlay = "Bomb";
    string checkCardType;
    Card* drawnCard;

    cout << "---------> Testing Phase 1: Creating/Setting/Validating Cards <---------" << "\n" << "\n";

    // we start by creating some cards
    Card card1("Bomb");
    Card card2("Reinforcement");
    Card card3("Blockade");
    Card card4("Airlift");
    cout << "...Setting Card5 to \"Breakfast\"..." << "\n";
    Card card5("Breakfast"); // invalid type, will produce error message
    cout << "\n";

    cout << "Card 1 type: " << card1.getType() << "\n";
    cout << "Card 2 type: " << card2.getType() << "\n";
    cout << "Card 3 type: " << card3.getType() << "\n";
    cout << "Card 4 type: " << card4.getType() << "\n";
    cout << "Card 5 type: " << card5.getType() << "\n" << "\n";
    cout << "...Setting Card5 to a valid type..." << "\n";
    card1.setType("Diplomacy"); // testing setter; changes invalid type to something valid
    cout << "Card5 is now a \"" << card1.getType() << "\" card." << "\n" << "\n"; // testing getter

    cout << "...Validating Card2 type..." << "\n";
    checkCardType = card2.getType(); // validate a card type using isValidCardType function
    if (Card::isValidCardType(checkCardType)) {
        cout << "Card type " << "\"" << checkCardType << "\" is valid." << "\n" << "\n";
    } else {
        cout << "Card type " << "\"" << checkCardType << "\" is not valid." << "\n" << "\n";
    }

    cout << "---------> Testing Phase 2: Copy Constructors <---------" << "\n" << "\n";

    // let's copy some cards
    cout << "...Making a deep copy of Card4..." << "\n";
    Card copiedCard(card4);
    cout << "Card4 type: " << "\"" << card4.getType() << "\"" << "\n";
    cout << "...Setting Card4 type to \"Blockade\"..." << "\n";
    card4.setType("Blockade");
    cout << "Card4 original is now: \"" << card4.getType() << "\"" << "\n";
    cout << "Card4 copy is now: \"" << copiedCard.getType() << "\"" << "\n" << "Deep copy is a success!" << "\n" << "\n";

    cout << "...Creating a new deck of cards..." << "\n" << "\n";
    Deck newDeck;
    newDeck.fillDeck();
    newDeck.printDeck();
    newDeck.getSize();
    cout << "\n";
    cout << "...Creating a deep copy of The Deck..." << "\n" << "\n";
    Deck NewDeckCopy (newDeck);
    cout << "...Shuffling original Deck..." << "\n" << "\n";
    cout << "(Shuffled Original) \n"; newDeck.shuffleDeck();
    newDeck.printDeck();
    cout << "\n" << "...Printing deep copy of The Deck..." << "\n" << "\n";
    cout << "(Copy) "; NewDeckCopy.printDeck();
    cout << "\n" << "Deep copy is a success!" << "\n";

    cout << "\n" << "---------> Testing Phase 3: Draw/Play Cards <---------" << "\n" << "\n";

    cout << "...Creating a player's hand of cards..." << "\n" << "\n";
    Hand hand;
    for (int i = 0; i < 5; ++i) {
        newDeck.draw(hand);
    }
    hand.printHand();
    hand.getSize();
    cout << "\n" << "...Checking The Deck for remaining cards..." << "\n" << "\n";
    newDeck.printDeck();
    newDeck.getSize();

    // testing play function
    cout << "\n" << "...Player is choosing a card to play..." << "\n" << "\n";
    cout << "...Checking Orders List for created order..." << "\n" << "\n";
    hand.play(cardToPlay, &newDeck);
    cout << "\n";
    cout << "...Checking Your Hand for remaining cards..." << "\n" << "\n";
    hand.printHand();
    hand.getSize();

    cout << "\n" << "...Checking The Deck to see if played card has returned..." << "\n" << "\n";
    newDeck.printDeck();
    newDeck.getSize();

    cout << "\n" << "...You drew a card from The Deck..." << "\n" << "\n";

    drawnCard = newDeck.draw(hand);
    cout << "You drew a \"" << drawnCard->getType() << "\" card." << "\n";
    cout << "\n" << "...Checking remaining cards in The Deck..." << "\n" << "\n";
    newDeck.printDeck();
    newDeck.getSize();

    cout << "\n" << "...Checking the cards in Your Hand..." << "\n" << "\n";
    hand.printHand();
    hand.getSize();
    cout << "\n";

    delete drawnCard;
}