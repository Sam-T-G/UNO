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
    friend void disPrvSts(const Player &); // friend function
public:
    Player(); // Constructor
    // ~Player();              // Destructor
    Player(const Player &); // Copy constructor
    string name;
    list<Card> hand;
    int trns = 0;
    // virtual void disPrvSts() const = 0; // Pure virtual function
    int hndSze() const { return hand.size(); } // inline method
    // Public wrappers for private logic
    void resetCombo();
    void updateCombo();
    void drawCard(std::queue<Card> &deck);
    Scores getScores() const;
    void setScores(const Scores &);
    int getMaxCombo() const;
    virtual void takeTurn(Player &opponent, std::stack<Card> &discard, std::queue<Card> &deck, bool &turn);
    virtual ~Player() {} // Best practice for base class
private:
    int cmb = 0;
    int cmbMx = 0;
    void rstCmb();
    void updCmb();
    void drwCrd(std::queue<Card> &deck);
    Scores scr;

protected:
    string role = "HUMAN"; // Protected member that indicates a human player, not NPC
};

#endif