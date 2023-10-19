#include <algorithm>
#include <iostream>
#include <random>
#include "Cards.h"

/************************************************************ Card ************************************************************/
/// <summary>
/// vector holding all card types
/// </summary>
const vector<string> Card::cardTypes = {"Bomb", "Reinforcement", "Blockade", "Airlift", "Diplomacy"};

/// <summary>
/// default constructor
/// </summary>
Card::Card() {
    type = nullptr;
}

/// <summary>
/// destructor
/// </summary>
Card::~Card() {
    delete type;
    type = nullptr;
}

/// <summary>
/// parametrized constructor
/// </summary>
Card::Card(const string &cardType) {
    type = nullptr;
    if (isValidCardType(cardType)) {
        type = new string(cardType);
    } else {
        cout << "Invalid card type: " << cardType << "\n";
    }
}

/// <summary>
/// deep copy constructor
/// </summary>
Card::Card(const Card &other) {
    type = nullptr;
    if (other.type != nullptr) {
        type = new string(*(other.type));
    }
}

/// <summary>
/// assignment operator
/// </summary>
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

/// <summary>
/// returns true if card is valid type
/// </summary>
bool Card::isValidCardType(const string &value) {
    for (size_t i = 0; i < cardTypes.size(); i++) {
        if (value == cardTypes[i]) {
            return true;
        }
    }
    return false;
}

/// <summary>
/// prints card type
/// </summary>
string Card::getType() const {
    if (type != nullptr) {
        return *type;
    } else {
        return " ";
    }
}

/// <summary>
/// sets new type for card
/// </summary>
void Card::setType(const string &newType) {
    if (isValidCardType(newType)) {
        if (type == nullptr) {
            type = new string(newType);
        } else {
            *type = newType;
        }
    } else {
        cout << "Invalid card type!" << "\n";
    }
}

/************************************************************ Deck ************************************************************/
/// <summary>
/// default constructor
/// </summary>
Deck::Deck() {

}

/// <summary>
/// destructor
/// </summary>
Deck::~Deck() {

}

/// <summary>
/// deep copy constructor
/// </summary>
Deck::Deck(const Deck &other) {
    for (size_t i = 0; i < other.deck.size(); ++i) {
        deck.push_back(new Card(*(other.deck[i])));
    }
}

/// <summary>
/// assignment operator
/// </summary>
Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        for (size_t i = 0; i < other.deck.size(); ++i) {
            deck.push_back(new Card(*(other.deck[i])));
        }
    }
    return *this;
}

/// <summary>
/// fills deck with 3 cards of each type
/// </summary>
void Deck::fillDeck() {
    for (int i = 0; i < 3; i++) {
        for (size_t j = 0; j < cardTypes.size(); j++) {
            Card *newCard = new Card(cardTypes[j]);
            deck.push_back(newCard);
        }
    }
}

/// <summary>
/// prints card number and type
/// </summary>
void Deck::printDeck() {
    cout << "The Deck contains: " << "\n" << "-------------------" << "\n";
    for (size_t i = 0; i < deck.size(); i++) {
        const Card *pointer = deck[i];
        cout << "Card #" << i << " : " << pointer->getType() << "\n";
    }
}

/// <summary>
/// prints size of deck
/// </summary>
void Deck::getSize() {
    cout << "The Deck contains " << deck.size() << " cards." << "\n";
}

/// <summary>
/// randomize cards in the deck
/// </summary>
void Deck::shuffleDeck() {
    random_device random;
    default_random_engine seed(random());
    shuffle(deck.begin(), deck.end(), seed);
}

/// <summary>
/// draw function: randomizes deck, draws a card, adds it to hand through an temporary vector, and removes it from deck
/// </summary>
Card *Deck::draw(Deck &transfer) {
    shuffleDeck();

    if (deck.empty()) {
        cout << "Cannot draw card; The Deck is empty!" << "\n";
        return nullptr;
    }

    Card *drawnCard = deck.back();

    deck.pop_back();

    transfer.addCard(drawnCard);

    return drawnCard;
}

/// <summary>
/// adds card to temporary vector
/// </summary>
void Deck::addCard(Card *transferCard) {

    transfer.push_back(transferCard);
}

/// <summary>
/// returns card back to deck
/// </summary>
void Deck::returnCard(Card *returningCard) {

    deck.push_back(returningCard);
}

/************************************************************ Hand ************************************************************/
/// <summary>
/// default constructor
/// </summary>
Hand::Hand() {

}

/// <summary>
/// destructor
/// </summary>
Hand::~Hand() {

}

/// <summary>
/// deep copy constructor
/// </summary>
Hand::Hand(const Hand &other) {
    for (size_t i = 0; i < other.hand.size(); ++i) {
        hand.push_back(new Card(*(other.hand[i])));
    }
}

/// <summary>
/// assignment operator
/// </summary>
Hand &Hand::operator=(const Hand &other) {
    if (this != &other) {
        for (size_t i = 0; i < other.hand.size(); ++i) {
            hand.push_back(new Card(*(other.hand[i])));
        }
    }
    return *this;
}

/// <summary>
/// prints types of hand cards
/// </summary>
void Hand::printHand() {
    cout << "Your Hand contains: " << "\n" << "-------------------" << "\n";
    for (size_t i = 0; i < hand.size(); i++) {
        const Card *pointer = hand[i];
        cout << "Card #" << i << " : " << pointer->getType() << "\n";
    }
}

/// <summary>
/// prints amount of hand cards
/// </summary>
void Hand::getSize() {
    cout << "Your Hand contains " << hand.size() << " cards." << "\n";
}

/// <summary>
/// adds a new card to hand
/// </summary>
void Hand::addCard(Card *newHandCard) {
    hand.push_back(newHandCard);
}

/// <summary>
/// play function: takes card type and original deck as arguments
/// </summary>
void Hand::play(string &playedCardType, Deck *returningDeck) {
    OrdersList *OL = new OrdersList(); /// <summary> declare a list of orders
    auto it = find_if(hand.begin(), hand.end(), [&playedCardType](const Card *card) {
        return card->getType() == playedCardType;
    });

    cout << "You played the " << "\"" << playedCardType << "\" card." << "\n";

    if (it != hand.end()) {
        /// <summary> orders: deploy, advance, bomb, blockade, airlift, and negotiate
        if (playedCardType == "Bomb") {
            auto *order = new Bomb();
            OL->addOrder(order);
            cout << "\n" << OL;
        } else if (playedCardType == "Reinforcement") {
            auto *order = new Deploy();
            OL->addOrder(order);
            cout << "\n" << OL;
        } else if (playedCardType == "Blockade") {
            auto *order = new Blockade();
            OL->addOrder(order);
            cout << "\n" << OL;
        } else if (playedCardType == "Airlift") {
            auto *order = new Airlift();
            OL->addOrder(order);
            cout << "\n" << OL;
        } else if (playedCardType == "Diplomacy") {
            auto *order = new Negotiate();
            OL->addOrder(order);
            cout << "\n" << OL;
        } else {
            cout << "Invalid card type: " << playedCardType << "\n";
        }
        returningDeck->returnCard(*it);
        hand.erase(it);
    } else {
        cout << "Error: Card of type " << "\"" << playedCardType << "\"" << " not found in hand!" << "\n";
    }
}