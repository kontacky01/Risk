#include <iostream>
#include <memory>
#include "Cards.h"

using namespace std;

void testCards() {
    cout << "\n*************************************\n"
         << "Hello, World! Let's test some Cards. \n"
         << "*************************************\n\n";

    /**
    * Declare some variables for later use
    */
    //string cardToPlay = "Bomb";
    string checkCardType;
    Card *drawnCard;
    //Card *card1 = new Card();
    Card *card1 = new Card();
    Card *card2 = new Card();
    Card *card3 = new Card();
    Card *card4 = new Card();
    Card *card5 = new Card();

    cout << "---------> Testing Phase 1: Creating/Setting/Validating Cards <---------\n\n";

    /**
    * Create some cards for testing
     * Card 5 is set to invalid type to trigger error message
     * Card 5 is set to a valid type
     * We test the getter method by retrieving Card 5's new type
     * Validates type of Card 2
    */
    card1->setType("bomb");
    card2->setType("reinforcement");
    card3->setType("blockade");
    card4->setType("airlift");
    cout << "...Setting Card5 to \"Breakfast\"...\n";
    card5->setType("breakfast");
    cout << "\n";

    cout << "Card 1 type: " << card1->getType() << "\n";
    cout << "Card 2 type: " << card2->getType() << "\n";
    cout << "Card 3 type: " << card3->getType() << "\n";
    cout << "Card 4 type: " << card4->getType() << "\n";
    cout << "Card 5 type: " << card5->getType() << "\n\n";
    cout << "...Setting Card5 to a valid type...\n";
    card5->setType("diplomacy");
    cout << "Card5 is now a \"" << card5->getType() << "\" card.\n\n";

    cout << "...Validating Card2 type...\n";
    checkCardType = card2->getType();
    if (Card::isValidCardType(checkCardType)) {
        cout << "Card type \"" << checkCardType << "\" is valid.\n\n";
    } else {
        cout << "Card type \"" << checkCardType << "\" is not valid.\n\n";
    }

    cout << "---------> Testing Phase 2: Copy Constructors <---------\n\n";

    /**
    * Validating deep copy constructors by
     * Creating a copy of Card 4
     * Setting original Card 4 to a new type and comparing the two
     * Create a deck and do the same
    */
    cout << "...Making a deep copy of Card4...\n";
    Card *copiedCard(card4);
    cout << "Card4 type: \"" << card4->getType() << "\"\n";
    cout << "...Setting Card4 type to \"Blockade\"...\n";
    card4->setType("Blockade");
    cout << "Card4 original is now: \"" << card4->getType() << "\"\n";
    cout << "Card4 copy is now: \"" << copiedCard->getType() << "\"\n" << "Deep copy is a success!\n\n";

    cout << "...Creating a new deck of cards...\n\n";
    Deck newDeck;
    newDeck.fillDeck(3);
    newDeck.printDeck();
    newDeck.getDeckSize();
    cout << "\n";
    cout << "...Creating a deep copy of The Deck...\n\n";
    Deck NewDeckCopy(newDeck);
    cout << "...Shuffling original Deck...\n\n";
    cout << "(Shuffled Original) \n";
    newDeck.shuffleDeck();
    newDeck.printDeck();
    cout << "\n...Printing deep copy of The Deck...\n\n";
    cout << "(Copy) ";
    NewDeckCopy.printDeck();
    cout << "\nDeep copy is a success!\n";

    cout << "\n---------> Testing Phase 3: Draw/Play Cards <---------\n\n";

    /**
    * Creates a hand for our player and fills it with cards
     * Checks deck size after each action to validate change
     * Validates ability to draw and play a card
     * Validates ability to return a card back to deck
    */
    cout << "...Creating a player's hand of cards...\n\n";
    Hand hand;
    for (int i = 0; i < 5; ++i) {
        newDeck.draw(hand);
    }
    hand.printHand();
    hand.getHandSize();
    cout << "\n...Checking The Deck for remaining cards...\n\n";
    newDeck.printDeck();
    newDeck.getDeckSize();

    // testing play function
    cout << "\n...Player is choosing a card to play...\n\n";
    cout << "...Checking Orders List for created order...\n\n";
    //hand.play(card1, &newDeck);
    //hand.play(card3, &newDeck);
    cout << "\n";
    cout << "...Checking Your Hand for remaining cards...\n\n";
    hand.printHand();
    hand.getHandSize();

    cout << "\n...Checking The Deck to see if played card has returned...\n\n";
    newDeck.printDeck();
    newDeck.getDeckSize();

    cout << "\n...You drew a card from The Deck...\n\n";

    drawnCard = newDeck.draw(hand);
    cout << "You drew a \"" << drawnCard->getType() << "\" card.\n";
    cout << "\n...Checking remaining cards in The Deck...\n\n";
    newDeck.printDeck();
    newDeck.getDeckSize();

    cout << "\n...Checking the cards in Your Hand...\n\n";
    hand.printHand();
    hand.getHandSize();
    cout << "\n";

    delete drawnCard;
}