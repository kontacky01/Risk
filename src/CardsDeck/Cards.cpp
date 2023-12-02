#include <algorithm>
#include <iostream>
#include <random>
#include "Cards.h"

/************************************************************ Card ************************************************************/
/**
* 'cardTypes' vector holds all possible card types
*/
const vector<string> Card::cardTypes = {"bomb", "reinforcement", "blockade", "airlift", "diplomacy"};

/**
* Default constructor
*/
Card::Card() {
    type = nullptr;
}

/**
* Destructor
*/
Card::~Card() {
    delete type;
    type = nullptr;
}

/**
* Parameterized constructor
*/
Card::Card(const string &cardType) {
    type = nullptr;
    if (isValidCardType(cardType)) {
        type = new string(cardType);
    } else {
        cout << "Invalid card type: " << cardType << "\n";
    }
}

/**
* Deep copy constructor
*/
Card::Card(const Card &other) {
    type = nullptr;
    if (other.type != nullptr) {
        type = new string(*(other.type));
    }
}

/**
* Assignment operator
*/
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

/**
* Method returns true if card type is valid and false if type is not present in cardTypes vector
*/
bool Card::isValidCardType(const string &value) {
    for (size_t i = 0; i < cardTypes.size(); i++) {
        if (value == cardTypes[i]) {
            return true;
        }
    }
    return false;
}

/**
* Method outputs card type
*/
string Card::getType() const {
    if (type != nullptr) {
        return *type;
    } else {
        return " ";
    }
}

/**
* Method sets new card type
*/
void Card::setType(const string &newType) {
    if (isValidCardType(newType)) {
        if (type == nullptr) {
            type = new string(newType);
        } else {
            *type = newType;
        }
    } else {
        cout << "Invalid card type!\n";
    }
}

/************************************************************ Deck ************************************************************/
/**
* Default constructor
*/
Deck::Deck() {

}

/**
* Destructor
*/
Deck::~Deck() {
    for (Card *card: deck) {
        delete card;
    }
}

/**
* Deep copy constructor
*/
Deck::Deck(const Deck &other) {
    for (size_t i = 0; i < other.deck.size(); ++i) {
        deck.push_back(new Card(*(other.deck[i])));
    }
}

/**
* Assignment operator
*/
Deck &Deck::operator=(const Deck &other) {
    if (this != &other) {
        for (Card *card: deck) {
            delete card;
        }
        deck.clear();

        deck.reserve(other.deck.size());
        for (Card *card: other.deck) {
            deck.push_back(new Card(*card));
        }
    }
    return *this;
}

/**
* Method fills a deck with three cards of each type
*/
/*void Deck::fillDeck() {
    for (int i = 0; i < 3; i++) {
        for (size_t j = 0; j < cardTypes.size(); j++) {
            Card *newCard = new Card(cardTypes[j]);
            deck.push_back(newCard);
        }
    }
}*/

void Deck::fillDeck(int cPerType) {
    deck.reserve(cPerType * cardTypes.size());
    for (int i = 0; i < cPerType; i++) {
        for (const auto &type: cardTypes) {
            deck.push_back(new Card(type));
        }
    }
}

/**
* Method outputs a list of deck cards with their respective number and type
 *
*/
void Deck::printDeck() {
    cout << "The Deck contains: \n-------------------\n";
    for (size_t i = 0; i < deck.size(); i++) {
        const Card *pointer = deck[i];
        cout << "Card #" << i << " : " << pointer->getType() << "\n";
    }
}

/**
* Method outputs size of deck
*/
void Deck::getDeckSize() {
    cout << "The Deck contains " << deck.size() << " cards.\n";
}

/**
* Method randomizes card order in deck
*/
void Deck::shuffleDeck() {
    random_device random;
    default_random_engine seed(random());
    shuffle(deck.begin(), deck.end(), seed);
}

/**
* Method randomizes deck, draws a card from it, adds said card to hand through a temporary vector,
 * and removes card from deck of origin
*/
Card *Deck::draw(Deck &transfer) {
    shuffleDeck();

    if (deck.empty()) {
        cout << "Cannot draw card; The Deck is empty!\n";
        return nullptr;
    }

    Card *drawnCard = deck.back();

    deck.pop_back();

    transfer.addCard(drawnCard);

    return drawnCard;
}

Card *Deck::drawACard() {
    if (deck.empty()) {
        cout << "Cannot draw card; The Deck is empty!\n";
        return nullptr;
    }

    Card *drawnCard = deck.back();
    deck.pop_back();
    return drawnCard;
}

/**
* Method adds card from deck to temporary vector
*/
void Deck::addCard(Card *transferCard) {

    transfer.push_back(transferCard);
}

/**
* Method returns a card to the deck of origin
*/
/*void Hand::returnCard(Card *card, Deck *originalDeck) {
    auto it = find(hand.begin(), hand.end(), card);
    if (it != hand.end()) {
        originalDeck->addCard(*it);
        hand.erase(it);
    }
}*/

void Deck::returnCard(Card *returningCard) {
    if (returningCard != nullptr) {
        deck.push_back(returningCard);
    } else {
        // Handle the null pointer scenario, e.g., log an error
    }
}

/************************************************************ Hand ************************************************************/
/**
* Default constructor
*/
Hand::Hand() {

}

/**
* Destructor
*/
Hand::~Hand() {
    cout << "...Hand destructor was called..." << endl;
    hand.clear();
}

/**
* Deep copy constructor
*/
Hand::Hand(
        const Hand &other) {
    for (size_t i = 0; i < other.hand.size(); ++i) {
        hand.push_back(new Card(*(other.hand[i])));
    }
}

/**
* Assignment operator
*/
Hand &Hand::operator=(const Hand &other) {
    if (this != &other) {
        for (Card* card : hand) {
            delete card;
        }
        hand.clear();

        // Copy new cards
        for (size_t i = 0; i < other.hand.size(); ++i) {
            hand.push_back(new Card(*(other.hand[i])));
        }
    }
    return *this;
}

/**
* Method outputs a list of cards in a player's hand
*/
void Hand::printHand() {
    cout << "Your Hand contains: \n-------------------\n";
    for (size_t i = 0; i < hand.size(); i++) {
        const Card *pointer = hand[i];
        cout << "Card #" << i << " : " << pointer->getType() << "\n";
    }
}

/**
* Method outputs size of player's hand
*/
void Hand::getHandSize() {
    cout << "Your Hand contains " << hand.size() << " cards.\n";
}

/**
* Method adds a card to player's hand
*/
void Hand::addCard(Card *newHandCard) {
    hand.push_back(newHandCard);
}

/**
* Play method takes card type and deck of origin as arguments
 * Declares a list of orders
 * Valid orders include: deploy, advance, bomb, blockade, airlift, and negotiate
 * Once a card is player, we create the order, remove the card from hand and return it back to the deck
*/
void Hand::play(Card *card, Deck *returningDeck, OrdersList *OL) {
    // Check that the card is actually in the hand before proceeding
    auto it = find_if(hand.begin(), hand.end(), [card](const Card *c) {
        return c->getType() == card->getType();
    });

    if (it != hand.end()) {
        // Determine the card type
        if (card->getType() == "bomb" || card->getType() == "reinforcement" ||
             card->getType() == "blockade" || card->getType() == "airlift" ||
              card->getType() == "diplomacy") {
            // Return the card to the deck and remove it from the player's hand
            returningDeck->returnCard(*it);

            swap(*it, hand.back());
            hand.pop_back();

            cout << "You played the " << "\"" << card->getType() << "\" card.\n";
        } else {
            cout << "Invalid card type: " << card->getType() << "\n";
            return;
        }
        // Add the order to the player's OrdersList
        //OL->addOrder(order); i commented this out because we can't just add an order that was not initialized with parameters
        //the valid initialization and adding to the player's orderlist will be done in issueorder()
    } else {
        cout << "Error: Card not found in hand!\n";
    }
}


/**
 * Override the stream operator for Card
 */
ostream &operator<<(ostream &out, Hand *h) {
    out << "The Hand contains \n------------------------\n";
    int handSize = h->hand.size();
    if (handSize == 0) {
        out << "Hand is empty\n";
    } else {
        for (int i = 0; i < h->hand.size(); i++) {
            out << "Card type:" << h->hand.at(i)->getType() << "\n";
        }
    }
    return out;
}