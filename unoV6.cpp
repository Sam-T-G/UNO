/*
Name: Samuel Gerungan
Date: 1/28/25
Purpose: Use various methods to create a functioning UNO game in c++

//PROJECT OUTLINE PSESUDOCODE
FIRST ITERATION CAN NOT USE FUNCTIONS AND ARRAYS

Upon program execution, user will be prompted into a menu (will be modular for future iteration which will include option to add more NPC opponents)
START - EXIT

//GENERAL CONSIDERATIONS
**DECK CONTENT**
There are a limited amount of cards that can be present in the deck totaling 108
25 Cards of each in four colors RED - YELLOW - GREEN - BLUE
TWO of each number in each color EXCEPT only ONE zero in each color
TWO of each action cards in each color which consist of SKIP - DRAW TWO (and skip) - REVERSE
FOUR Color change wild cards
FOUR DRAW FOUR and Color change wild cards

//LOGIC CONSIDERATIONS
Program needs to be able to reverse order of play (can be future implementation if base program only has one NPC)

*/

// System Libraries
#include <iostream> //io library
#include <iomanip>  //format library
#include <cmath>    //math library
#include <cstdlib>  //random library
#include <cstring>  //string library
#include <ctime>    //time library
#include <deque>    //que library
#include <fstream>  //file input output library
using namespace std;

// User Libraries

// Global Constants
const int MAXCARDS = 100; // most amount of cards a player can have in their hand
const char PERCENT = 100; // percent conversion

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
void draw(int[][MAXCARDS]);    // function to draw a card and place into hand
void addHand(int[][MAXCARDS]); // add given card draw to a hand
void actvCrd();                // function to handle active card logic
void menuSel();                // handles menu selection

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables
    const int ROW = 100; // max number of rows = 100
    char
        menuSel; // menu selection
    int
        plyrHnd[ROW][MAXCARDS], // player hand table 2D Array
        npcHnd[ROW][MAXCARDS];  // npc hand table 2D Array

    string
        name,    // player name
        btrWrse, // better or worse string
        actCol;  // active color

    fstream file("hiScore.dat", ios::in); // initialization of high scores storage
    deque<int> scores;                    // Using deque to store scores instead of using arrays

    const int maxScrs = 10; // Create an unedtiable ceiling of 10 scores

    unsigned int
        sum,     // sum of last 10 scores
        score,   // player score
        plyCnt,  // player card count
        npcCnt,  // npc card count
        actCrd,  // active card
        card,    // card placeholder
        wildCrd, // player wild card
        npcTmp,  // temp storage for npc logic
        npcWld;  // npc wild card

    float
        pctChng, // percent change from average
        varince, // statistical variance from mean
        stdDev,  // standard deviation
        average; // average score of last 10 runs

    bool plyrTrn; // boolean that dictates if it's the player's turn

    // Initialize Variables
    // CREATE MENU
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "UNO! The game where friendships and loyalties go to die" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl;
    cout << "Main Menu" << endl
         << endl;
    cout << "Type the character that corresponds to your selections within this game" << endl
         << endl;
    cout << "| Enter your name to Start the Game |" << endl
         << endl;
    cin >> name;
    cout << endl;

    draw(plyrHnd);

    // Map the inputs and outputs - Process

    // INITIAL DRAW of 5 CARDS

    // PLAYER CARDS

    // Exit the program
    return 0;
}

// draw function - pass in copy of pyrTrn, pass by reference hand count of player and npc
void draw(int drwHnd[][MAXCARDS])
{
    int drwVal;              // initialize a value of card - i index
    int drwCol = rand() % 5; // randomize a color drawn - j index
    if (drwCol == 4)
    {
        drwVal = rand() % 3; // if wild card, choose from only three options - standard, draw two, draw four
    }
    else
    {
        drwVal = rand() % 12; // if not wild card, choose from 11 options
    }

    drwHnd[drwVal][drwCol]++; // increment the value found at given coordinate

    // VISUAL MATRIX DEBUG
    for (int i = 0; i < 11; i++) // loop i for max length of card values = 11
    {
        for (int j = 0; j < 5; j++) // loop j for max height of color types = 5
        {
            cout << drwHnd[i][j]; // display value at given matrix coordinate
        }
        cout << endl; // move to next line when row is filled
    }
}

void addHand()
{
}

void actvCrd()
{
}
void menuSel()
{
}