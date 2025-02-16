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
const int COL = 5;        // column value to set up 2D array
const char PERCENT = 100; // percent conversion

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
void draw(int[][COL], int);                                                                                   // function to draw a card and place into hand
void actvCrd(int[][COL], string &, int);                                                                      // function to iterpret active card
void deal(int[][COL], int[][COL], int[][COL], string &, char, int, int &, int &, int, bool &);                // initial deal at the start of a new game
void crdCnv(int[][COL], int);                                                                                 // card conversion to readable string
void usrInt(int[][COL], int[][COL], int[][COL], int[][COL], string &, int &, int &, int, bool &);             // handle player turn
void npcTrn(int[][COL], int[][COL], int[][COL], string &, int &, int &, int, bool &);                         // handle npc turn
void dispHnd(int[][COL], int[][COL], string &, int);                                                          // player hand display
void plyrTrn(int[][COL], int[][COL], int[][COL], int[][COL], string &, char, int, int &, int &, int, bool &); // handle player menu plyrTrn
void wild(int[][COL], int, int &);
void play(int[][COL], int[][COL], int[][COL], string &, int &, int &, int, int, int, bool &);
int getCol(char);
void wldPlay(int[][COL], int[][COL], string &, int, int, int, bool &);
void loadScr(vector<int> &scores, fstream &file);
void saveScr(vector<int> &scores, fstream &file);
void clcSts(vector<int> &scores, unsigned int score, float &average, float &variance, float &stdDev, float &pctChng, string &btrWrse);
void dispRes(int plyCnt, int npcCnt, vector<int> &scores, fstream &file, unsigned int score, float average, float variance, float stdDev, float pctChng, string &btrWrse);
void bubSrt(int plyrHnd[][COL], int ROW, string &, int srtdHnd[][COL]);
void selSrt(int plyrHnd[][COL], int ROW, string &, int srtdHnd[][COL]);

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables
    const int ROW = 12; // variation of colors to set up 2D array
    char
        menuSel, // menu selection
        numSel;
    int
        actvArr[ROW][COL], // active card 2D array
        plyrHnd[ROW][COL], // player hand table 2D Array
        npcHnd[ROW][COL],  // npc hand table 2D Array
        srtdHnd[ROW][COL], // sorted hand 2D array
        plyrCnt = 0,       // player card count
        npcCnt = 0,        // npc card count
        colSel = 0;

    string
        name,    // player name
        btrWrse, // better or worse string
        actvDsp; // active card display

    fstream file("hiScore.dat", ios::in); // initialization of high scores storage
    vector<int> scores;

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

    deal(plyrHnd, npcHnd, actvArr, actvDsp, colSel, numSel, plyrCnt, npcCnt, ROW, turn); // deal the initial card arrays

    // Map the inputs and outputs - Process

    // INITIAL DRAW of 5 CARDS

    // TURN HADNLING
    do
    {
        if (turn == true)
        {
            plyrTrn(plyrHnd, npcHnd, srtdHnd, actvArr, actvDsp, colSel, numSel, plyrCnt, npcCnt, ROW, turn);
        }
        if (turn == false && plyrCnt != 0)
        {
            npcTrn(plyrHnd, npcHnd, actvArr, actvDsp, plyrCnt, npcCnt, ROW, turn);
        }
    } while (plyrCnt != 0 && npcCnt != 0);

    // finsih prompt if one hand count reaches zero
    if (plyrCnt == 0 || npcCnt == 0)
    {
        cout << "Game Over!" << endl
             << endl;
        dispRes(plyrCnt, npcCnt, scores, file, score, average, varince, stdDev, pctChng, btrWrse);
    }

    // Exit the program
    return 0;
}

// draw function - pass in copy of pyrTrn, pass by reference hand count of player and npc
void draw(int drwHnd[][COL], int ROW)
{
    int drwCol = 0;        // initialize a color of card - i index
    int drwVal = 0;        // initialize a value of card - j index
    drwCol = rand() % COL; // randomize a color drawn - j index
    if (drwCol == 4)
    {
        drwVal = rand() % 3; // if wild card, choose from only three options - standard, draw two, draw four
    }
    else
    {
        drwVal = rand() % ROW; // if not wild card, choose from 11 options
    }

    drwHnd[drwVal][drwCol]++; // increment the value found at given coordinate

    // VISUAL MATRIX DEBUG
    // for (int i = 0; i < ROW; i++) // loop i for max length of  = 5
    // {
    //     for (int j = 0; j < COL; j++) // loop j for max height of color types = 12
    //     {
    //         cout << drwHnd[i][j]; // display value at given matrix coordinate
    //     }
    //     cout << endl; // move to next line when row is filled
    // }
    // cout << "Drawn Card: " << (drwCol == 4 ? "Wild" : to_string(drwCol)) << " of " << drwVal << endl;
    cout << endl;
}
void deal(int plyrHnd[][COL], int npcHnd[][COL], int actvArr[][COL], string &actvDsp, char colSel, int numSel, int &plyrCnt, int &npcCnt, int ROW, bool &turn)
{
    int nCrdSt = 7; // create a modifiable variable to dictate the number of cards we want to start with
    // Initialize both hands before dealing the cards to clear random memory
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            plyrHnd[i][j] = 0; // Initialize player's hand
            npcHnd[i][j] = 0;  // Initialize NPC's hand
        }
        cout << endl
             << "Initialized both hands." << endl
             << endl;
    }
    for (int i = 0; i < nCrdSt; i++) // loop until we deal amount of cards desired
    {
        draw(plyrHnd, ROW); // deal a card for player
        plyrCnt++;
        cout << endl
             << "Player hand" << endl
             << plyrCnt << endl
             << endl;
        draw(npcHnd, ROW); // deal a card for npc
        npcCnt++;
        cout << endl
             << "Opponent hand" << endl
             << npcCnt << endl
             << endl;
    }
    cout << endl
         << "both hands have been dealt" << endl
         << endl;

    bool wldFrst = false; // initialize a boolean to signify if the first active card is a wild
    do
    {
        wldFrst = false; // initialize a boolean to signify if the first active card is a wild
        // reset active card value
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
            {
                actvArr[i][j] = 0;
                // cout << endl
                //      << actvArr[i][j] << endl // debug line
                //      << endl;
            }
        }
        draw(actvArr, ROW); // draw a card and set it to the active card
        // check to see if the active card is a wild card
        for (int i = 0; i < ROW; i++)
        {
            if (actvArr[i][4] != 0)
            { // Only check the wild row
                cout << endl
                     << "First draw was a wild card! Redrawing..." << endl
                     << endl;
                wldFrst = true;
            }
        }
    } while (wldFrst == true);

    // call active card function to interpret the active card
    actvCrd(actvArr, actvDsp, ROW);

    cout << "You and the opponent have recieved your starting hands." << endl
         << "The first active card is " << actvDsp << endl;
    turn = true;
}

void usrInt(int plyrHnd[][COL], int npcHnd[][COL], int srtdHnd[][COL], int actvArr[][COL], string &actvDsp, int &plyrCnt, int &npcCnt, int ROW, bool &turn)
{
    cout << "It's your turn!" << endl
         << endl;
    cout << "The active card is ";
    crdCnv(actvArr, ROW);
    cout << endl
         << endl;
    bubSrt(plyrHnd, ROW, actvDsp, srtdHnd);
    cout << endl
         << "| Total number of cards in hand: " << plyrCnt << " | Opponent number of cards: " << npcCnt << " |" << endl
         << endl;

    // Prompt for how player wants to proceed
    cout << "What would you like to do?" << endl;
    cout << "| R: Play Red | B: Play Blue | Y: Play Yellow | G: Play Green | W: Play Wild | D: Draw Card | " << endl;
    cout << "| 0-9: Card Number | 10: SKIP | 11: DRAW 2 | " << endl;
}

void dispHnd(int plyrHnd[][COL], int srtdHnd[][COL], string &actvDsp, int ROW)
{
    // Create an array of strings for the card colors
    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    // Create an array of strings for the card values
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2"};

    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl
         << fixed << "|";
    for (int j = 0; j < COL; j++)
    {
        cout << setw(10) << colors[j] << "|"; // Print color columns
    }
    cout << endl;
    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < ROW; i++)
    {
        cout << "|"; // Start a new row

        for (int j = 0; j < COL; j++)
        {
            // if (srtdHnd[i][j] != 0) // If there are cards in this slot
            // {
            //     cout << setw(7) << values[i] << "(" << srtdHnd[i][j] << ")|"; // Print the value and how many of that card exist
            // }
            // else
            // {
            //     cout << setw(10) << " " << "|"; // No card in this slot, leave it blank
            // }

            if (plyrHnd[i][j] != 0) // If there are cards in this slot
            {
                cout << setw(7) << values[i] << "(" << plyrHnd[i][j] << ")|"; // Print the value and how many of that card exist
            }
            else
            {
                cout << setw(10) << " " << "|"; // No card in this slot, leave it blank
            }
        }
        cout << endl; // New line after each row of cards
    }
    for (int i = 0; i < 56; i++)
    {
        cout << "-";
    }
    cout << endl;
}

// Bubble Sort Function (returns sorted array in srtdHnd)
void bubSrt(int plyrHnd[][COL], int ROW, string &actvDsp, int srtdHnd[][COL])
{
    // Initialize srtdHnd with zeroes
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            srtdHnd[i][j] = 0;
        }
    }

    for (int j = 0; j < COL; j++)
    {
        vector<int> colVal; // Store nonzero values for sorting

        // Collect nonzero values from the column
        for (int i = 0; i < ROW; i++)
        {
            if (plyrHnd[i][j] != 0)
                colVal.push_back(plyrHnd[i][j]);
        }

        // Bubble Sort
        for (size_t x = 0; x < colVal.size(); x++)
        {
            for (size_t y = 0; y < colVal.size() - x - 1; y++)
            {
                if (colVal[y] > colVal[y + 1])
                    swap(colVal[y], colVal[y + 1]);
            }
        }

        // Populate srtdHnd top-down
        for (size_t i = 0; i < colVal.size(); i++)
        {
            srtdHnd[i][j] = colVal[i];
        }
    }

    // Print the sorted hand
    // cout << "Bubble Sort Hand:" << endl;
    dispHnd(plyrHnd, srtdHnd, actvDsp, ROW);
}

// Selection Sort Function (returns sorted array in srtdHnd)
void selSrt(int plyrHnd[][COL], int ROW, string &actvDsp, int srtdHnd[][COL])
{
    // Initialize srtdHnd with zeroes
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            srtdHnd[i][j] = 0;
        }
    }

    for (int j = 0; j < COL; j++)
    {
        vector<int> colVal; // Store nonzero values for sorting

        // Collect nonzero values from the column
        for (int i = 0; i < ROW; i++)
        {
            if (plyrHnd[i][j] != 0)
                colVal.push_back(plyrHnd[i][j]);
        }

        // Selection Sort
        for (size_t x = 0; x < colVal.size(); x++)
        {
            size_t minIndex = x;
            for (size_t y = x + 1; y < colVal.size(); y++)
            {
                if (colVal[y] < colVal[minIndex])
                    minIndex = y;
            }
            swap(colVal[x], colVal[minIndex]);
        }

        // Populate srtdHnd top-down
        for (size_t i = 0; i < colVal.size(); i++)
        {
            srtdHnd[i][j] = colVal[i];
        }
    }

    // Print the sorted hand
    cout << "Selection Sort Hand:" << endl;
    dispHnd(plyrHnd, srtdHnd, actvDsp, ROW);
}

void plyrTrn(int plyrHnd[][COL], int npcHnd[][COL], int srtdHnd[][COL], int actvArr[][COL], string &actvDsp, char colSel, int numSel, int &plyrCnt, int &npcCnt, int ROW, bool &turn)
{
    bool vldPly = false;

    while (!vldPly) // Loop until a valid play is made
    {
        usrInt(plyrHnd, npcHnd, srtdHnd, actvArr, actvDsp, plyrCnt, npcCnt, ROW, turn);
        cout << "Choose a card color!" << endl;
        cin >> colSel;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }
        cout << "Choose a Value" << endl;
        cin >> numSel;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }
        // Handle drawing a card
        if (colSel == 'D' || colSel == 'd')
        {
            cout << "You've drawn a card!" << endl;
            draw(plyrHnd, ROW); // draw randomized card value
            plyrCnt++;          // increment player hand count
            colSel = 0;         // empty value
            numSel = 0;         // empty value
        }
        else
        {
            int colIdx = getCol(colSel); // create a colindex int variable to retrieve if color selected is viable
            while (colIdx == -1)         // if not viable
            {
                bubSrt(plyrHnd, ROW, actvDsp, srtdHnd);            // bubble sort display
                selSrt(plyrHnd, ROW, actvDsp, srtdHnd);            // selection Srt display
                cout << "Invalid color selection! Choose again: "; // prompt user selection is invalid
                cin >> colSel;                                     // input a new color selection
                colIdx = getCol(colSel);                           // re-index and check loop again
            }

            // Handle wild card logic
            if (colSel == 'W' || colSel == 'w')
            {
                if (plyrHnd[numSel][colIdx] > 0)
                {
                    wldPlay(plyrHnd, actvArr, actvDsp, colIdx, numSel, ROW, turn);
                    plyrCnt--;                 // decrement hand count
                    plyrHnd[numSel][colIdx]--; // Remove the wild card from player's hand
                    vldPly = true;             // confirm as valud play and continue
                }
                else
                {
                    cout << "You don't have any Wild cards!";
                }
            }

            // Regular card play logic
            if (turn)
            {
                if (numSel >= 0 && numSel <= 11) // Check if number is within range
                {
                    if (plyrHnd[numSel][colIdx] > 0)
                    {
                        play(plyrHnd, npcHnd, actvArr, actvDsp, plyrCnt, npcCnt, colIdx, numSel, ROW, turn);
                        vldPly = true; // Exit loop after a successful play
                        cout << "The active card is now ";
                        crdCnv(actvArr, ROW);
                        cout << endl
                             << endl;
                    }
                    else
                    {
                        cout << "You don't have that card! Choose again: ";
                        cin >> colSel >> numSel; // Re-prompt
                    }
                }
                else
                {
                    cout << "Invalid card number! Choose again: ";
                    cin >> colSel >> numSel; // Re-prompt
                }
            }
        }
    }
}

void actvCrd(int actvArr[][COL], string &actvDsp, int ROW)
{
    // create string array to describe the columns - displaying card colors
    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    // create string array to describe the row values
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2"};
    actvDsp = ""; // clear the active display
    // determine active card
    for (int i = 0; i < ROW; i++)     // Iterate through Card Types
        for (int j = 0; j < COL; j++) // iterate through card colors
        {
            if (actvArr[i][j] != 0) // If this slot has a card
            {
                // Handle wild cards separately
                if (j == 4)
                    actvDsp = "Wild";

                else
                    actvDsp = values[i] + " " + colors[j];

                return; // Stop searching after finding the first card
            }
        }
}

void crdCnv(int array[][COL], int ROW)
{
    // Create an array of strings for the card colors
    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    // Create an array of strings for the card values
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2"};

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (array[i][j] != 0) // If there are cards in this slot
            {
                cout << values[i] << " of " << colors[j];
            }
        }
    }
}

void play(int plyrHnd[][COL], int npcHnd[][COL], int actvArr[][COL], string &actvDsp, int &plyrCnt, int &npcCnt, int colIdx, int numSel, int ROW, bool &turn)
{
    int color = 0, number = 0;

    // Find the currently active card
    for (int i = 0; i < ROW; i++) // Iterate over columns (card numbers)
    {
        for (int j = 0; j < COL; j++) // Iterate over rows (colors)
        {
            if (actvArr[i][j] > 0) // Active card found
            {
                color = j;  // Store the active card's color
                number = i; // Store the active card's number
            }
        }
    }

    // Verify if the card can be played
    if (colIdx == color || numSel == number) // Matches either color or number
    {
        if (plyrHnd[numSel][colIdx] > 0) // Check if player has the card
        {
            plyrHnd[numSel][colIdx]--; // Remove card from player's hand
            cout << "Card played!" << endl;

            // Clear the active array
            for (int i = 0; i < ROW; i++)
                for (int j = 0; j < COL; j++)
                    actvArr[i][j] = 0;

            // Set the active card
            actvArr[numSel][colIdx] = 1;
            actvCrd(actvArr, actvDsp, ROW); // Update the active card display

            cout << "You've played a " << actvDsp << endl;
            turn = false; // Switch to NPC turn
            plyrCnt--;
            if (numSel == 10)
            {
                turn = true; // override the turn to have a second turn if played a skip
                cout << "It's your turn again!" << endl
                     << endl;
            }
            if (numSel == 11)
            {
                turn = true; // override turn as well if played a DRAW 2
                cout << "The opponent has to Draw Two Cards!" << endl
                     << endl;
                draw(npcHnd, ROW);
                draw(npcHnd, ROW);
                npcCnt++;
                npcCnt++;
            }
        }
        else
        {
            cout << "You don't have that card!" << endl;
        }
    }
    else
    {
        cout << "Neither the color nor the number matches!" << endl;
    }
}

int getCol(char colSel)
{
    switch (colSel)
    {
    case 'R':
    case 'r':
        return 0; // Red
    case 'B':
    case 'b':
        return 1; // Blue
    case 'Y':
    case 'y':
        return 2; // Yellow
    case 'G':
    case 'g':
        return 3; // Green
    case 'W':
    case 'w':
        return 4; // Wild
    default:
        cout << "Invalid color!" << endl;
        return -1;
    }
}

void wldPlay(int plyrHnd[][COL], int actvArr[][COL], string &actvDsp, int colIdx, int numSel, int ROW, bool &turn)
{
    char colSel; // initialize user input of color char
    cout << "You played a Wild Card! Choose a color to swap to (R = Red, B = Blue, Y = Yellow, G = Green): " << endl;
    cin >> colSel; // choose color
    colIdx = 0;
    colIdx = getCol(colSel); // fetch color index

    // cout << "Choose which wild card slot!" << endl; // validate correct wild index slot
    // cin >> numSel;                                  // choose wildcard index slot
    // while (plyrHnd[numSel][colIdx] == 0)            // Check if player has the card
    // {
    //     cout << "Invalid input! Make sure you choose the right WILD index from your hand 0-2" << endl;
    //     cout << "Input Wild Card" << endl;
    //     cin >> colSel;
    //     colIdx = getCol(colSel);
    //     cout << "Input Wild index 0-2" << endl;
    //     cin >> numSel;
    // }

    while (colIdx < 0 || colIdx > 3)
    {
        colIdx = 0;
        cout << "Invalid input! Choose a valid color (R = Red, B = Blue, Y = Yellow, G = Green): " << endl;
        cin >> colSel;
        colIdx = getCol(colSel); // fetch color index
    }

    // Clear the active array2
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            actvArr[i][j] = 0; // Reset active card display

    // Set the chosen color as active
    actvArr[0][colIdx] = 1; // Assign the wild card to the new color
    actvDsp = (colIdx == 0) ? "Red" : (colIdx == 1) ? "Blue"
                                  : (colIdx == 2)   ? "Yellow"
                                                    : "Green";

    cout << "Wild card has been played! The new color is " << actvDsp << "!" << endl;
    turn = false; // End player's turn
}

// function to process WILD card color change
void wild(int actvArr[][COL], int ROW, int &j)
{
    actvArr[0][j] = 1; // Set wild card action to the active card
    string newCol;
    if (j == 0)
    {
        newCol = "RED";
    }
    else if (j == 1)
    {
        newCol = "BLUE";
    }
    else if (j == 2)
    {
        newCol = "YELLOW";
    }
    else if (j == 3)
    {
        newCol = "GREEN";
    }
    cout << "Wild card has been played! The new color is " << newCol << "!" << endl;
}

// npc AI logic
void npcTrn(int plyrHnd[][COL], int npcHnd[][COL], int actvArr[][COL], string &actvDsp, int &plyrCnt, int &npcCnt, int ROW, bool &turn)
{
    int color = 0, number = 0; // initialize color and number to 0

    // Find the currently active card
    for (int i = 0; i < ROW; i++) // Iterate over columns (card numbers)
    {
        for (int j = 0; j < COL; j++) // Iterate over rows (colors)
        {
            if (actvArr[i][j] > 0) // Active card found
            {
                color = j;  // Store the active card's color
                number = i; // Store the active card's number
            }
        }
    }
    // int binarySearch(int arr[], int low, int high, int x)
    // {
    // while (low <= high) {
    //     int mid = low + (high - low) / 2;

    //     // Check if x is present at mid
    //     if (arr[mid] == x)
    //         return mid;

    //     // If x greater, ignore left half
    //     if (arr[mid] < x)
    //         low = mid + 1;

    //     // If x is smaller, ignore right half
    //     else
    //         high = mid - 1;
    // }

    // If we reach here, then element was not present
    // return -1;
    // }
    // Search the NPC hand to see if there are any values at either coordinate of the NPC hand.
    bool found = false; // create a boolean to initialize a search for the next possible card
    while (!found)
    {
        int i = 0; // manually set indexes at 0 since we are not using for loops
        while (i < ROW && !found)
        {
            int j = 0;
            while (j < COL && !found)
            {
                if ((npcHnd[i][j] > 0) && (i == number || j == color))
                {
                    // Clear the active array
                    for (int i = 0; i < ROW; i++)
                        for (int j = 0; j < COL; j++)
                        {
                            actvArr[i][j] = 0; // set every value to zero
                        }
                    actvArr[i][j] = 1; // if found, set card found value to the active card in play.
                    npcHnd[i][j]--;    // decrement npc card from hand

                    cout << "The opponent has played a ";
                    crdCnv(actvArr, ROW); // convert card into readable value for UI
                    cout << "!" << endl;

                    npcCnt--; // reduce total npc hand count

                    cout << "The opponent now has " << npcCnt << " cards in their hand!" << endl;
                    found = true; // set found to true so we can break out of loops
                    turn = true;

                    color = j;
                    number = i;
                    if (color == 4)
                    {
                        for (int i = 0; i < ROW; i++)
                            for (int j = 0; j < COL; j++)
                            {
                                actvArr[i][j] = 0; // set every value to zero to reset active card
                            }
                        j = rand() % 3;
                        actvArr[i][j] = 1;
                    }
                }
                j++; // increment when still not found
            }
            i++; // increment when still not found
        }

        // while STILL not found any matches, prompt the enemy to draw cards
        if (!found)
        {
            draw(npcHnd, ROW); // draw a card if no values found
            npcCnt++;          // increment npc hand count
            cout << "The opponent draws a card!" << endl
                 << endl;
        }
    }
}

// Function to load scores from file
void loadScr(vector<int> &scores, fstream &file)
{
    int score;
    while (file >> score)
    {
        scores.push_back(score);
    }
    file.close();
}

// Function to save updated scores to file
void saveScr(vector<int> &scores, fstream &file)
{
    file.open("hiScore.dat", ios::out);
    for (int i = 0; i < scores.size(); i++)
    {
        file << scores[i] << endl;
    }
    file.close();
}

// Function to calculate the stats (average, variance, stdDev, pctChng)
void clcSts(vector<int> &scores, unsigned int score, float &average, float &variance, float &stdDev, float &pctChng, string &btrWrse)
{
    unsigned int sum = 0;

    for (int i = 0; i < scores.size(); i++)
    {
        sum += scores[i];
    }

    // Calculate average
    if (scores.size() == 1)
    {
        average = static_cast<float>(scores[0]);
    }
    else
    {
        average = static_cast<float>(sum) / scores.size();
    }

    // Calculate variance
    variance = 0;
    for (int i = 0; i < scores.size(); i++)
    {
        variance += pow(scores[i] - average, 2);
    }
    variance /= scores.size();

    // Calculate standard deviation
    stdDev = sqrt(variance);

    // Check if the score is better or worse
    if (average < score)
    {
        btrWrse = "better";
    }
    else
    {
        btrWrse = "worse";
    }

    // Calculate percent change
    pctChng = (score - average) / static_cast<float>(average) * PERCENT;
    if (pctChng < 0)
    {
        pctChng *= -1;
    }
}

// Function to display results
// Original function
void dispRes(int plyCnt, int npcCnt, vector<int> &scores, fstream &file, unsigned int score,
             float average, float variance, float stdDev, float pctChng, string &btrWrse)
{
    if (!file)
    {
        cout << "Error: High score file not found!" << endl;
        exit(1);
    }

    if (plyCnt == 0)
    {
        loadScr(scores, file); // call load scores file

        cout << "Congratulations, you've won!" << endl
             << endl;
        score = npcCnt - plyCnt;
        cout << "You've scored " << score << " points!" << endl;

        scores.push_back(score);

        if (scores.size() > 10)
        {
            scores.erase(scores.begin()); // Remove the oldest score (front of the vector)
        }

        saveScr(scores, file);

        clcSts(scores, score, average, variance, stdDev, pctChng, btrWrse);

        cout << fixed << setprecision(2) << showpoint;
        cout << "Which is " << pctChng << "% " << btrWrse << " than the average of the last ten victories." << endl
             << endl;
        cout << "Average of last " << scores.size() << " scores: " << average << endl;
        cout << "Standard Deviation of the scores: " << stdDev << endl;
    }
    else if (npcCnt == 0)
    {
        cout << "You've Lost!" << endl
             << endl;
    }
}

// Overloaded version without file and statistical details
void dispRes(int plyCnt, int npcCnt, vector<int> &scores, unsigned int score)
{
    if (plyCnt == 0)
    {
        cout << "Congratulations, you've won!" << endl
             << endl;
        score = npcCnt - plyCnt;
        cout << "You've scored " << score << " points!" << endl;

        scores.push_back(score);

        if (scores.size() > 10)
        {
            scores.erase(scores.begin()); // Remove the oldest score (front of the vector)
        }
    }
    else if (npcCnt == 0)
    {
        cout << "You've Lost!" << endl
             << endl;
    }
}