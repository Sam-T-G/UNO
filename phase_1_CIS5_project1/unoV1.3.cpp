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
        menuSel; // menu selection

    string
        actCol; // active color

    unsigned int
        plyCnt,  // player card count
        npcCnt,  // npc card count
        actCrd,  // active card
        card,    // card placeholder
        redCard, // user number of red cards
        bluCard, // user number of blue cards
        yelCard, // user number of yellow cards
        grnCard, // user number of green cards
        npcRed,  // npc number of red cards
        npcBlu,  // npc number of blue cards
        npcYel,  // npc number of yellow cards
        npcGrn;  // npc number of green cards

    bool plyrTrn; // boolean that dictates if it's the player's turn

    // Initialize Variables
    redCard = bluCard = yelCard = grnCard = npcRed = npcBlu = npcYel = npcGrn = plyCnt = npcCnt = 0; // mass initialization of base card value to 0
    // CREATE MENU
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "UNO! The game where friendships and loyalties go to die" << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl
         << endl;
    cout << "Main Menu" << endl
         << endl;
    cout << "Type the character that corresponds to your selections within this game" << endl
         << endl;
    cout << "| Enter any Key to Start the Game |" << endl
         << endl;
    cin >> menuSel;
    cout << endl
         << endl;

    // Map the inputs and outputs - Process

    // INITIAL DRAW of 5 CARDS

    // PLAYER CARDS
    for (int i = 0; i < 7; i++) // first hand initialized to seven cards
    {
        card = rand() % 4;                            // random 0-3 representing four colors - red blue yellow green
        card == 0 ? redCard++ : card == 1 ? bluCard++ // ternary operator to translate random card draw
                            : card == 2   ? yelCard++
                                          : grnCard++;
        plyCnt++;
    }

    // NPC Cards
    for (int i = 0; i < 7; i++) // first hand initialized to seven cards
    {
        card = rand() % 4; // random 0-3 representing four colors - red blue yellow green
        switch (card)      // this time we utilize a switch case to determine NPC draws
        {
        case 0:
            npcRed++;
            break;
        case 1:
            npcBlu++;
            break;
        case 2:
            npcYel++;
            break;
        case 3:
            npcGrn++;
            break;
        }
        npcCnt++;
    }

    // generate an active card in play
    actCrd = rand() % 4;

    // set first turn to be on the player - can introduce randomized turns later using this boolean
    plyrTrn = true;

    do
    { // debug check for NPC HAND
        // cout << "Red Cards: " << npcRed << " Blue Cards : " << npcBlu << " Yellow Cards: " << npcYel << " Green Cards: " << npcGrn << endl;

        // if - else if statements to translate rng number into colors
        if (actCrd == 0)
        {
            actCol = "Red";
        }
        else if (actCrd == 1)
        {
            actCol = "Blue";
        }
        else if (actCrd == 2)
        {
            actCol = "Yellow";
        }
        else if (actCrd == 3)
        {
            actCol = "Green";
        }
        cout << "CARD IN PLAY: " << actCol; // display card in play

        // Check to see if it's the player's turn
        if (plyrTrn == true)
        { // player hand display
            cout << endl
                 << "| Red Cards: " << redCard << " | Blue Cards : " << bluCard << " | Yellow Cards: " << yelCard << " | Green Cards: "
                 << grnCard << " | Total number of cards in hand: " << plyCnt << " | Opponent number of cards: " << npcCnt << " |" << endl
                 << endl;

            // Prompt for how player wants to proceed
            cout << "What would you like to do?" << endl;
            cout << "| R: Play Red | B: Play Blue | Y: Play Yellow | G: Play Green | D: Draw Card | " << endl;
            cin >> menuSel;
            cout << endl;

            if (menuSel == 'R' || menuSel == 'r') // if user selects either uppercase or lowercase r
            {
                if (plyrTrn == true)
                {
                    if (redCard > 0 && actCrd == 0) // logic to verify user input and return appropriate responses
                    {
                        redCard--;
                        plyCnt--;
                        cout << "You play a red card!" << endl
                             << endl;
                        plyrTrn = false;
                    }
                    else if (actCrd != 0) // if the card selected from menu option does not equal card in play
                    {
                        cout << "The colors don't match!" << endl
                             << endl;
                    }
                    else // else user does not own any of the cards selected for play
                    {
                        cout << "You don't have any RED cards!" << endl
                             << endl;
                    }
                }
            }

            if (menuSel == 'B' || menuSel == 'b') // if user selects either uppercase or lowercase b
            {
                if (plyrTrn == true)
                {
                    if (bluCard > 0 && actCrd == 1) // logic to verify user input and return appropriate responses
                    {
                        bluCard--;
                        plyCnt--;
                        cout << "You play a blue card!" << endl
                             << endl;
                        plyrTrn = false;
                    }
                    else if (actCrd != 1) // if the card selected from menu option does not equal card in play
                    {
                        cout << "The colors don't match!" << endl
                             << endl;
                    }
                    else // else user does not own any of the cards selected for play
                    {
                        cout << "You don't have any BLUE cards!" << endl
                             << endl;
                    }
                }
            }

            if (menuSel == 'Y' || menuSel == 'y') // if user selects either uppercase or lowercase y
            {
                if (plyrTrn == true)
                {
                    if (yelCard > 0 && actCrd == 2) // logic to verify user input and return appropriate responses
                    {
                        yelCard--;
                        plyCnt--;
                        cout << "You play a yellow card!" << endl
                             << endl;
                        plyrTrn = false;
                    }
                    else if (actCrd != 2) // if the card selected from menu option does not equal card in play
                    {
                        cout << "The colors don't match!" << endl
                             << endl;
                    }
                    else // else user does not own any of the cards selected for play
                    {
                        cout << "You don't have any YELLOW cards!" << endl
                             << endl;
                    }
                }
            }

            if (menuSel == 'G' || menuSel == 'g') // if user selects either uppercase or lowercase g
            {
                if (plyrTrn == true)
                {
                    if (grnCard > 0 && actCrd == 3) // logic to verify user input and return appropriate responses
                    {
                        grnCard--; // decrement card color count
                        plyCnt--;  // decrement overall hand card count
                        cout << "You play a green card!" << endl
                             << endl;
                        plyrTrn = false;
                    }
                    else if (actCrd != 3) // if the card selected from menu option does not equal card in play
                    {
                        cout << "The colors don't match!" << endl
                             << endl;
                    }
                    else // else user does not own any of the cards selected for play
                    {
                        cout << "You don't have any GREEN cards!" << endl
                             << endl;
                    }
                }
            }

            if (menuSel == 'D' || menuSel == 'd') // if user selects either uppercase or lowercase d
            {
                card = rand() % 4;                            // draw a random card value
                card == 0 ? redCard++ : card == 1 ? bluCard++ // ternary operator to translate random card draw
                                    : card == 2   ? yelCard++
                                                  : grnCard++;
                plyCnt++; // increment player hand count
                cout << endl
                     << endl;
            }
        }

        // if it's not the player's turn AND if the player has not won yet
        if (plyrTrn == false && plyCnt != 0)
        {
            // program displaying opponents turn and game status
            cout << "It's the opponent's turn!" << endl
                 << endl;
            cout << "The opponent has " << npcCnt << " cards in their hand." << endl
                 << endl;
            cout << "The active card is " << actCol << "." << endl // call the active color string to display active color
                 << endl;

            // have npc check active card
            if (actCrd == 0) // if active card is red
            {
                if (plyrTrn == false) // if it's still the opponent's turn
                {
                    if (npcRed > 0) // nested case if npc also has red cards
                    {
                        cout << "Opponent plays a red card!" << endl
                             << endl;
                        npcRed--;
                        npcCnt--;
                        plyrTrn = true; // npc has a red card and has played one
                    }
                    else // if it's red and npc does not have a red card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                                         : npcGrn++;
                        npcCnt++; // increment opponent hand count
                        cout << endl
                             << endl;
                    }
                }
            }

            if (actCrd == 1) // if active card is blue
            {
                if (plyrTrn == false) // if it's still the opponent's turn
                {
                    if (npcBlu > 0) // nested case if npc also has blue cards
                    {
                        cout << "Opponent plays a blue card!" << endl
                             << endl;
                        npcBlu--;
                        npcCnt--;
                        plyrTrn = true; // npc has a blue card and has played one
                    }
                    else // if it's blue and npc does not have a blue card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                                         : npcGrn++;
                        npcCnt++; // increment opponent hand count
                        cout << endl
                             << endl;
                    }
                }
            }

            if (actCrd == 2) // if active card is yellow
            {
                if (plyrTrn == false) // if it's still the opponent's turn
                {
                    if (npcYel > 0) // nested case if npc also has yellow cards
                    {
                        cout << "Opponent plays a yellow card!" << endl
                             << endl;
                        npcYel--;
                        npcCnt--;
                        plyrTrn = true; // npc has a yellow card and has played one
                    }
                    else // if it's yellow and npc does not have a yellow card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                                         : npcGrn++;
                        npcCnt++; // increment opponent hand count
                        cout << endl
                             << endl;
                    }
                }
            }

            if (actCrd == 3) // if active card is green
            {
                if (plyrTrn == false) // if it's still the opponent's turn
                {
                    if (npcGrn > 0) // nested case if npc also has green cards
                    {
                        cout << "Opponent plays a green card!" << endl
                             << endl;
                        npcGrn--;
                        npcCnt--;
                        plyrTrn = true; // npc has a green card and has played one
                    }
                    else // if it's green and npc does not have a green card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                                         : npcGrn++;
                        npcCnt++; // increment opponent hand count
                        cout << endl
                             << endl;
                    }
                }
            }
        }
    } while (plyCnt != 0 || npcCnt != 0); // while neither the player or opponent has won

    // Display and output the results

    // Exit the program
    return 0;
}