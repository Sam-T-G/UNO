#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include "Scores.h"
using namespace std;

class Player
{
public:
    string name;
    vector<Card> hand;
    int trns = 0;

    int hndSze() const;

    // Public wrappers for private logic
    void resetCombo();
    void updateCombo();
    void drawCard();
    Scores getScores() const;
    void setScores(const Scores &);
    int getMaxCombo() const;

private:
    int cmb = 0;
    int cmbMx = 0;
    void rstCmb();
    void updCmb();
    void drwCrd();
    Scores scr;
};

#endif