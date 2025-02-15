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
const int ROW = 13;       // column value to set up 2D array
const char PERCENT = 100; // percent conversion

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
void draw(int[][ROW]);                                                       // function to draw a card and place into hand
void actvCrd(int[][ROW], string &);                                          // function to iterpret active card
void deal(int[][ROW], int[][ROW], int[][ROW], string &, int &, int &, bool); // initial deal at the start of a new game
void plyrTrn(int[][ROW], int[][ROW], int &, bool);
void npcTrn(int[][ROW], int[][ROW], int &, bool);

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables
    const int COL = 5; // variation of colors to set up 2D array
    char
        menuSel; // menu selection
    int
        actvArr[COL][ROW] = {0}, // active card 2D array
        plyrHnd[COL][ROW] = {0}, // player hand table 2D Array
        npcHnd[COL][ROW] = {0},  // npc hand table 2D Array
        plyrCnt = 0,             // player card count
        npcCnt = 0;              // npc card count

    string
        name,    // player name
        btrWrse, // better or worse string
        actvDsp; // active card display

    fstream file("hiScore.dat", ios::in); // initialization of high scores storage
    deque<int> scores;                    // Using deque to store scores instead of using arrays

    const int maxScrs = 10; // Create an unedtiable ceiling of 10 scores

    unsigned int
        sum,     // sum of last 10 scores
        score,   // player score
        card,    // card placeholder
        wildCrd, // player wild card
        npcTmp,  // temp storage for npc logic
        npcWld;  // npc wild card

    float
        pctChng, // percent change from average
        varince, // statistical variance from mean
        stdDev,  // standard deviation
        average; // average score of last 10 runs

    bool turn; // boolean that dictates if it's the player's turn

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

    deal(plyrHnd, npcHnd, actvArr, actvDsp, plyrCnt, npcCnt, turn); // deal the initial card arrays

    // Map the inputs and outputs - Process

    // INITIAL DRAW of 5 CARDS

    // TURN HADNLING
    // do
    // {
    //     if (turn == true)
    //     {
    //         plyrTrn(plyrHnd, actvArr, plyrCnt);
    //     }
    //     if (turn == false && plyrCnt != 0)
    //     {
    //         npcTrn(npcHnd, actvArr, npcCnt);
    //     }
    // } while (plyrCnt != 0 || npcCnt != 0);

    // Exit the program
    return 0;
}

// draw function - pass in copy of pyrTrn, pass by reference hand count of player and npc
void draw(int drwHnd[][ROW])
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
    for (int i = 0; i < 12; i++) // loop i for max length of  = 5
    {
        for (int j = 0; j < 5; j++) // loop j for max height of color types = 12
        {
            cout << drwHnd[i][j]; // display value at given matrix coordinate
        }
        cout << endl; // move to next line when row is filled
    }
    cout << endl;
}
void deal(int plyrHnd[][ROW], int npcHnd[][ROW], int actvArr[][ROW], string &actvDsp, int &plyrCnt, int &npcCnt, bool turn)
{
    int nCrdSt = 7; // create a modifiable variable to dictate the number of cards we want to start with
    // Initialize both hands before dealing the cards
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            plyrHnd[i][j] = 0; // Initialize player's hand
            npcHnd[i][j] = 0;  // Initialize NPC's hand
        }
    }
    // if (turn == true)
    // {
    //     plyrHnd[drwVal][drwCol]++; // increment the value found at given coordinate
    //     plyrCnt++;
    // }
    // else
    // {
    //     plyrHnd[drwVal][drwCol]++; // increment the value found at given coordinate
    //     plyrCnt++;
    // }
    for (int i = 0; i < nCrdSt; i++) // loop until we deal amount of cards desired
    {
        draw(plyrHnd); // deal a card for player
        plyrCnt++;
        cout << endl
             << "Player hand" << endl
             << plyrCnt << endl
             << endl;
        draw(npcHnd); // deal a card for npc
        npcCnt++;
        cout << endl
             << "Opponent hand" << endl
             << plyrCnt << endl
             << endl;
    }
    cout << endl
         << "both hands have been dealt" << endl
         << endl;

    bool wldFrst = false; // initialize a boolean to signify if the first active card is a wild
    do
    {
        // reset active card value
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < 5; j++)
                actvArr[i][j] = 0;
        }
        draw(actvArr); // draw a card and set it to the active card
        // check to see if the active card is a wild card
        for (int i = 0; i < 5; i++)
        {
            if (actvArr[i][4] != 0)
            { // Only check the wild row
                wldFrst = true;
                cout << endl
                     << "First draw was a wild card! Redrawing..." << endl
                     << endl;
            }
        }
    } while (wldFrst);

    // call active card function to interpret the active card
    actvCrd(actvArr, actvDsp);

    cout << "You and the opponent have recieved your starting hands." << endl
         << "The first active card is " << actvDsp << endl;
}

void plyrTrn(int plyrHnd[][ROW], int actCrd[][ROW], int &plyrCnt, bool turn)
{
    char menuSel; // Menu selection variable
}

void npcTrn(int plyrHnd[][ROW], int actCrd[][ROW], int &npcCnt, bool turn)
{
}

void actvCrd(int actvArr[][ROW], string &actvDsp)
{
    // create string array to describe the columns - displaying card colors
    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    // create string array to describe the row values
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2"};
    actvDsp = ""; // clear the active display
    // determine active card
    for (int i = 0; i < ROW; i++) // Iterate through colors
    {
        for (int j = 0; j < 5; j++) // Iterate through numbers
        {
            if (actvArr[i][j] != 0) // iff this slot has a card
            {
                if (actvArr[i][j] != 0) // If this slot has a card
                {
                    // Handle wild cards separately
                    if (i == 4)
                        actvDsp = "Wild";
                    else
                        actvDsp = values[i] + " " + colors[j];

                    return; // Stop searching after finding the first card
                }
            }
        }
    }
}