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
#include <ctime>    //time library
#include <cstdlib>  //random library
using namespace std;

// User Libraries

// Global Constants

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables
    char
        menuSel; // main menu selection

    unsigned int
        card,    // card placeholder
        redCard, // user number of red cards
        bluCard, // user number of blue cards
        yelCard, // user number of yellow cards
        grnCard, // user number of green cards
        npcRed,  // npc number of red cards
        npcBlu,  // npc number of blue cards
        npcYel,  // npc number of yellow cards
        npcGrn;  // npc number of green cards

    // Initialize Variables
    redCard = bluCard = yelCard = grnCard = npcRed = npcBlu = npcYel = npcGrn = 0; // mass initialization of base card value to 0
    // CREATE MENU
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "UNO! The game where friendships and loyalties go to die" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl;
    cout << "Main Menu" << endl
         << endl;
    cout << "Type the character that corresponds to your selections within this game" << endl
         << endl;
    cout << "| S : Start Game | E : Exit Game |";
    cin >> menuSel;
    cout << endl;

    // Map the inputs and outputs - Process
    // INITIAL DRAW of 5 CARDS
    for (int i = 0; i < 5; i++)
    {
        card = rand() % 4;                            // random 0-3 representing four colors - red blue yellow green
        card == 0 ? redCard++ : card == 1 ? bluCard++ // ternary operator to translate random card draw
                            : card == 2   ? yelCard++
                                          : grnCard++;
    }

    cout << "Red Cards: " << redCard << " Blue Cards : " << bluCard << " Yellow Cards: " << yelCard << " Green Cards: " << grnCard << endl;

    // Display and output the results

    // Exit the program
    return 0;
}