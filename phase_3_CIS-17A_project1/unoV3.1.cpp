/*
Name: Samuel Gerungan
Date: 4/29/25
Purpose: UNO! Game Version 3.1
*/

// System Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
using namespace std;

// User Libraries

// Global Constants

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
// Structure to hold card information

enum CardColor
{
    RED,
    BLUE,
    YELLOW,
    GREEN,
    WILD
};

enum CardSuit
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    SKIP,
    DRAW_TWO,
    DRAW_FOUR
};
struct Card
{
    // color of card
    CardColor color; // red = 0 | blue = 1 | 2 = yellow | 3  = green | wild = 4
    CardSuit suit;   // numbers =  0-9 | skip = 10 | draw 2 = 11 | draw 4 = 12 | * if wild, numbers/skip interpreted as normal cards
};

struct Scores
{
    int numTrns; // Number of turns
    int hiCombo; // integer value to store highest number of combo
};

struct Player
{
    string name;           // Player name
    vector<Card> hand;     // Nested Card Vector to house hand contents
    struct Scores plyrScr; // nested structure to store scores
};

void menu(Player &);           // Function to display modular main menu screen
void draw(Player &);           // Modular Function to Draw a Card
void deal(Player &, Player &); // Function to deal initial hand to a given player
void actvCrd(Player &);        // Function to place current active card
void crdDisp(Player &);        // Function to display current card in play
void play(Card &, Player &);   // Funcition to put a card in play and to check if the play is valid

Card draw();

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables

    // Initialize Variables

    // Map the inputs and outputs - Process
    Player *p1 = new Player;  // Create a player 1 structure to hold player's information - later can be modularized
    Player *npc = new Player; // Create an NPC opponent
    menu(*p1);                // pass player 1 structure into function
    deal(*p1, *npc);
    crdDisp(*p1); // Display cards in hand

    // Display and output the results

    // Exit the program
    return 0;
}

// Main menu function
void menu(Player &p1)
{
    for (int i = 0; i < 56; i++)
    {
        cout << "~";
    }
    cout << endl
         << "UNO! The game where friendships and loyalties go to die" << endl;
    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl;
    cout << "|" << setw(30) << "Main Menu" << setw(25) << "|" << endl
         << endl;
    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl
         << "|" << setw(3) << " " << "Input caracters corresponding to your selections" << setw(4) << "|" << endl
         << endl;
    cout << "|" << setw(10) << " " << "Enter your name to Start the Game" << setw(11) << " " << "|" << endl
         << endl;
    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl;
    cin >> p1.name;
    cout << endl;
};

// Draw function
Card draw()
{
    Card newCrd;
    newCrd.color = static_cast<CardColor>(rand() % 5);
    newCrd.suit = static_cast<CardSuit>(rand() % 13);
    return newCrd;
}

// Deal function
void deal(Player &p1, Player &npc)
{ // Deal 7 Starting cards for player and npc
    for (int i = 0; i < 7; i++)
    {
        p1.hand.push_back(draw());
        npc.hand.push_back(draw());
    }
};

// Play function
void play(Card &, Player &) {

};

// Sort Hand Function
void srtHnd() {
};

// Active Card Display Function

// User Interface Function

// Display Hand Function
void crdDisp(Player &p1)
{
    for (int i = 0; i < p1.hand.size(); i++)
    {
        cout << endl
             << "Card " << i << " Color : " << p1.hand[i].color
             << endl;
        cout << endl
             << "Card " << i << " Suit: " << p1.hand[i].suit
             << endl;
    }
};

// Card Info to Decipher card information

// Wild Card Function

// Player turn funciton sequence

// NPC turn function sequence

// Save Scores Function

// Display results