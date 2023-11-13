#pragma once

#include <string>
#include <vector>
#include <memory>
#include "../OrdersList/Orders.h"

using namespace std;

/************************************************************ Card ***************************************************/
class OrdersList;//Forward declaration
class Card {
public:

    /**
    * Default constructor
    */
    Card();

    /**
    * Destructor
    */
    virtual ~Card();

    /**
    * Parameterized constructor to initialize the card types
    */
    explicit Card(const string &cardType);

    /**
    * Copy constructor
    */
    Card(const Card &other);

    /**
    * Assignment operator
    */
    Card &operator=(const Card &other);

    /**
    * The getType method outputs a card's type
    */
    string getType() const;

    /**
    * The setType method sets a new type for a given card
    */
    void setType(const string &newType);

    /**
    * The isValidCardType method validates the authenticity of card type
    */
    static bool isValidCardType(const string &value);

protected:
    string *type;
    static const vector<string> cardTypes; // The 'cardTypes' vector stores all possible card types
};

/************************************************************ Deck ***************************************************/
class Deck : public Card { // inherits Card class
public:
    /**
    * Default constructor
    */
    Deck();

    /**
    * Destructor
    */
    ~Deck() override;

    /**
    * Deep copy constructor
    */
    Deck(const Deck &other);

    /**
    * Assignment operator
    */
    Deck &operator=(const Deck &other);

    /**
    * The fillDeck method creates a finite collection of cards
    */
    void fillDeck(int cardPerType);
   // void fillDeck(); // creates finite collection of cards

    /**
    * The printDeck prints out the contents of the deck
    */
    void printDeck();

    /**
    * The getDeckSize method retrieves and outputs the size of the deck
    */
    void getDeckSize();

    /**
    * The shuffleDeck method randomizes the order of the cards in a deck
    */
    void shuffleDeck();

    /**
    * The draw method draws a card and removes it from a deck
    */
    Card *drawCards(Deck &transfer);

    Card *draw();
    /**
    * The addCard method adds card to a temporary vector
    */
    virtual void addCard(Card *transferCard);

    /**
    * The returnCard method returns a card back to its deck of origin
    */
    void returnCard(Card *returningCard);
protected:
    /**
    * 'deck' vector stores the collection of cards created by the fillDeck method
    */
    vector<Card *> deck;
    /**
    * 'transfer' is a temporary vector used to transfer cards from deck to hand and back
    */
    vector<Card *> transfer;


};

/************************************************************ Hand ****************************************************/
class Hand : public Deck {
public:
    /**
    * Default constructor
    */
    Hand();

    /**
    * Destructor
    */
    ~Hand() override;

    /**
    * Copy constructor
    */
    Hand(const Hand &other);

    /**
    * Assignment operator
    */
    Hand &operator=(const Hand &other);

    /**
    * The printHand method outputs contents of a player's hand
    */
    void printHand();

    /**
    * The getHandSize method outputs the size of a player's hand
    */
    void getHandSize();

    /**
    * The addCard method adds a new card from the deck to the player's hand
    */
    void addCard(Card *newHandCard) override;

    /**
    * The play method removes a card from hand, creates a new order, and returns card to deck of origin
    */
    void play(Card *card, Deck *returningDeck, OrdersList* OL);

    OrdersList *ordersList;

    vector<Card *> hand;

    friend ostream &operator<<(ostream &out, Hand *o); // override Stream insertion operator

    //void returnCard(Card *card, Deck *originalDeck);
};

/************************************************************ Cards Driver *******************************************/
/**
    * testCards is a testing function
    */
void testCards();