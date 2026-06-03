#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <list>
#include <stack>
#include <queue>
#include "Card.h"
#include "Scores.h"
using namespace std;

class Player
{
    // rubric: friend function disPrvSts (Ch.14.5)
    friend void disPrvSts(const Player &); // friend function
public:
    Player(); // Constructor
    // ~Player();              // Destructor
    // rubric: copy constructor (Ch.14.6)
    Player(const Player &); // Copy constructor
    string name;
    // rubric: list<Card> hand (aggregation, Ch.14.7)
    list<Card> hand;
    int trns = 0;
    // rubric: pure virtual disPrvSts (Ch.15.7)
    virtual void disPrvSts() const = 0; // Pure virtual; Player is abstract, concrete subclasses must override
    // rubric: inline hndSze (Ch.13.13)
    int hndSze() const { return hand.size(); } // inline method
    // Public wrappers for private logic
    void resetCombo();
    void updateCombo();
    void drawCard(queue<Card> &deck);
    Scores getScores() const;
    void setScores(const Scores &);
    int getMaxCombo() const;
    // rubric: polymorphic takeTurn (Ch.15.5)
    virtual void takeTurn(Player &opponent, stack<Card> &discard, queue<Card> &deck, bool &turn);
    virtual ~Player() {} // Best practice for base class
private:
    int cmb = 0;
    int cmbMx = 0;
    void rstCmb();
    void updCmb();
    void drwCrd(queue<Card> &deck);
    Scores scr;

protected:
    string role = "HUMAN"; // Protected member that indicates a human player, not NPC
};

#endif