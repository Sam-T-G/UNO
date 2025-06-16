#include "Player.h"
#include "Card.h"
#include <iostream>
using namespace std;

extern Card draw();

void Player::rstCmb()
{
    cmb = 0;
}

void Player::updCmb()
{
    cmb++;
    if (cmb > cmbMx)
        cmbMx = cmb;
}

void Player::drwCrd()
{
    hand.push_back(draw());
    Card::totalDrawn++;
}

int Player::hndSze() const
{
    return hand.size();
}

void disPrvSts(const Player &p)
{
    cout << "Accessing private stats for " << p.name << ":\n";
    cout << "Current Combo: " << p.cmb << "\n";
    cout << "Max Combo:     " << p.cmbMx << "\n";
}

Player::Player(const Player &src)
{
    name = src.name;
    hand = src.hand; // vector has deep copy
    trns = src.trns;
    cmb = src.cmb;
    cmbMx = src.cmbMx;
    scr = src.scr; // assuming Scores has a working copy constructor or defaulted
}