#pragma once

#include <string>
#include <vector>
#include "../OrdersList/Orders.h"

using namespace std;

/************************************************************ Card ************************************************************/
class Card {
public:

    Card(); // default constructor

    virtual ~Card(); // destructor, virtual to prevent deletion

    explicit Card(const string &cardType); // initializes card types

    Card(const Card &other); // copy constructor

    Card &operator=(const Card &other); // assignment operator definition

    string getType() const; // prints card type

    void setType(const string &newType); // sets new card type

    static bool isValidCardType(const string &value); // validates authenticity of card type

protected:
    string *type;

    static const vector<string> cardTypes; // stores valid card types
};

/************************************************************ Deck ************************************************************/
class Deck : public Card { // inherits Card class
public:
    Deck(); // default constructor

    ~Deck() override; // destructor

    Deck(const Deck &other); // deep copy constructor

    Deck &operator=(const Deck &other); // assignment operator definition

    void fillDeck(); // creates finite collection of cards

    void printDeck(); // prints contents of deck

    virtual void getSize(); //prints size of deck

    void shuffleDeck(); // randomizes the deck

    Card *draw(Deck &transfer); // draws and removes a card from the deck

    virtual void addCard(Card *transferCard); // adds card back to deck

    void returnCard(Card *returningCard); // return card back to deck

protected:
    vector<Card *> deck; // stores collection of cards created by fillDeck
    vector<Card *> transfer; // placeholder vector used to transfer cards from deck to hand
};

/************************************************************ Hand ************************************************************/
class Hand : public Deck {
public:
    Hand(); // parametrized constructor

    ~Hand() override; // destructor

    Hand(const Hand &other); // copy constructor

    Hand &operator=(const Hand &other); // assignment operator definition

    void printHand(); // prints contents of hand

    void getSize() override; // prints size of hand

    void addCard(Card *newHandCard) override; // adds a new card to hand

    void play(string &playedCardType, Deck *returningDeck); // removes card from hand, pushes orders, and returns card to original deck

protected:
    vector<Card *> hand; // stores collection of cards created by fillHand
    OrdersList OL;
};

/************************************************************ Cards Driver ************************************************************/
void testCards(); // testing function