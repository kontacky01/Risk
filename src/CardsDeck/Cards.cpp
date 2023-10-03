#include <algorithm>
#include <iostream>
#include <random>
#include "Cards.h"

/************************************************************ Card ************************************************************/
const vector<string> Card::cardTypes = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"}; // vector holding all card types

// default constructor
Card::Card() {
    type = nullptr;
}

// destructor
Card::~Card() {
    delete type;
}

// parametrized constructor
Card::Card(const string &cardType) {
    type = nullptr;
    if (isValidCardType(cardType)) {
        type = new string(cardType);
    } else {
        cout << "Invalid card type: " << cardType << endl;
    }
}

// deep copy constructor
Card::Card(const Card &other) {
    type = nullptr;
    if (other.type != nullptr) {
        type = new string(*(other.type));
    }
}

// assignment operator
Card &Card::operator=(const Card &other) {
    if (this != &other) {
        delete type;
        type = nullptr;
        if (other.type != nullptr) {
            type = new string(*(other.type));
        }
    }
    return *this;
}

bool Card::isValidCardType(const string &value) {
    for (size_t i = 0; i < cardTypes.size(); i++) {
        if (value == cardTypes[i]) {
            return true; // returns true if card is valid type
        }
    }
    return false;
}

string Card::getType() const {
    if (type != nullptr) {
        return *type; // prints card type
    } else {
        return " ";
    }
}

void Card::setType(const string &newType) {
    if (isValidCardType(newType)) {
        if (type == nullptr) {
            type = new string(newType); // sets new type for card
        } else {
            *type = newType;
        }
    } else {
        cout << "Invalid card type!" << endl;
    }
}

/************************************************************ Deck ************************************************************/
// default constructor
Deck::Deck() {

}

// destructor
Deck::~Deck() {

}

// deep copy constructor
Deck::Deck(const Deck &other) {
    for (size_t i = 0; i < other.deck.size(); ++i) {
        deck.push_back(new Card(*(other.deck[i])));
    }
}

// assignment operator
Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        for (size_t i = 0; i < other.deck.size(); ++i) {
            deck.push_back(new Card(*(other.deck[i])));
        }
    }
    return *this;
}

void Deck::fillDeck() {
    for (int i = 0; i < 2; i++) { // fills deck with 2 cards of each type
        for (size_t j = 0; j < cardTypes.size(); j++) {
            Card *newCard = new Card(cardTypes[j]);
            deck.push_back(newCard);
        }
    }
}

void Deck::printDeck() { // prints card number and type
    cout << "The Deck contains: " << endl << "-------------------" << endl;
    for (size_t i = 0; i < deck.size(); i++) {
        const Card *pointer = deck[i];
        cout << "Card #" << i << " : " << pointer->getType() << endl;
    }
}

void Deck::getSize() { // prints size of deck
    cout << "The Deck contains " << deck.size() << " cards." << endl;
}

void Deck::shuffleDeck() { // randomize cards in the deck
    random_device random;
    default_random_engine seed(random());
    shuffle(deck.begin(), deck.end(), seed);
}

// draw function: randomizes deck, draws a card and removes it from deck
Card *Deck::draw() {
    shuffleDeck();

    if (deck.empty()) {
        cout << "The Deck is empty!" << endl;
        return nullptr;
    }

    Card *drawnCard = deck.back();

    deck.pop_back(); // removes card from deck

    return drawnCard; // returns pointer to card drawn
}

void Deck::addCard(Card *oldCard) { // adds a card back to deck
    deck.push_back(oldCard);
}

/************************************************************ Hand ************************************************************/
// default constructor
Hand::Hand() {

}

// destructor
Hand::~Hand() {

}

// deep copy constructor
Hand::Hand(const Hand &other) {
    for (size_t i = 0; i < other.hand.size(); ++i) {
        hand.push_back(new Card(*(other.hand[i])));
    }
}

// assignment operator
Hand &Hand::operator=(const Hand &other) {
    if (this != &other) {
        for (size_t i = 0; i < other.hand.size(); ++i) {
            hand.push_back(new Card(*(other.hand[i])));
        }
    }
    return *this;
}

void Hand::fillHand(Deck &deck) {
    for (int i = 0; i < 5; i++) { // fill player's hand with 5 cards
        Card *drawnCard = deck.draw();
        if (drawnCard != nullptr) {
            hand.push_back(drawnCard);
        } else {
            cout << "Cannot draw hand; Deck is empty." << endl;
        }
    }
}

void Hand::printHand() { // prints types of hand cards
    cout << "Your Hand contains: " << endl << "-------------------" << endl;
    for (size_t i = 0; i < hand.size(); i++) {
        const Card *pointer = hand[i];
        cout << "Card #" << i << " : " << pointer->getType() << endl;
    }
}

void Hand::getSize() { // prints amount of hand cards
    cout << "Your Hand contains " << hand.size() << " cards." << endl;
}

void Hand::addCard(Card *newCard) { // adds a new card to hand
    hand.push_back(newCard);
}

// play function: takes card type and original deck as arguments
void Hand::play(string &playedCardType, Deck *returningDeck) {
    OrdersList OL; // declare a list of orders
    auto it = find_if(hand.begin(), hand.end(), [&playedCardType](const Card *card) {
        return card->getType() == playedCardType;
    });

    cout << "You played the " << "\"" << playedCardType << "\" card." << endl;

    if (it != hand.end()) {
        // orders: deploy, advance, bomb, blockade, airlift, and negotiate
        if (playedCardType == "Bomb") {
            auto *order = new Bomb();
            OL.addOrder(order);
            cout << endl << OL;
        } else if (playedCardType == "Reinforcement") {
            auto *order = new Deploy();
            OL.addOrder(order);
            cout << endl << OL;
        } else if (playedCardType == "Blockade") {
            auto *order = new Blockade();
            OL.addOrder(order);
            cout << endl << OL;
        } else if (playedCardType == "Airlift") {
            auto *order = new Airlift();
            OL.addOrder(order);
            cout << endl << OL;
        } else if (playedCardType == "Diplomacy") {
            auto *order = new Negotiate();
            OL.addOrder(order);
            cout << endl << OL;
        } else {
            cout << "Invalid card type: " << playedCardType << endl;
        }
        returningDeck->addCard(*it);
        hand.erase(it);
    } else {
        cout << "Error: Card of type " << "\"" << playedCardType << "\"" << " not found in hand!" << endl;
    }
}