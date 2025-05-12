#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "Card.h"
#include "Scores.h"
using namespace std;

struct Player
{
    string name;
    vector<Card> hand;
    int trns = 0;
    int cmb = 0;
    int cmbMx = 0;
    Scores scr;

    void rstCmb();
    void updCmb();
    void drwCrd();
    int hndSze() const;
};

#endif
