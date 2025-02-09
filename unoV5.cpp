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
const char PERCENT = 100; // percent conversion

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
        redCard, // user number of red cards
        bluCard, // user number of blue cards
        yelCard, // user number of yellow cards
        grnCard, // user number of green cards
        npcRed,  // npc number of red cards
        npcBlu,  // npc number of blue cards
        npcYel,  // npc number of yellow cards
        npcGrn,  // npc number of green cards
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
    redCard = bluCard = yelCard = grnCard = npcRed = npcBlu = npcYel = npcGrn = plyCnt = npcCnt = wildCrd = npcWld = 0; // mass initialization of base card value to 0
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

    // Map the inputs and outputs - Process

    // INITIAL DRAW of 5 CARDS

    // PLAYER CARDS
    for (int i = 0; i < 7; i++) // first hand initialized to seven cards
    {
        card = rand() % 5;                            // random 0-4 representing four colors - red blue yellow green and wild card
        card == 0 ? redCard++ : card == 1 ? bluCard++ // ternary operator to translate random card draw
                            : card == 2   ? yelCard++
                            : card == 3   ? grnCard++
                                          : wildCrd++;
        plyCnt++;
    }

    // NPC Cards
    for (int i = 0; i < 7; i++) // first hand initialized to seven cards
    {
        card = rand() % 5; // random 0-5 representing four colors - red blue yellow green and wild card
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
        case 4:
            npcWld++;
            break;
        }
        npcCnt++;
    }

    // generate an active card in play
    actCrd = rand() % 4; // generate one of four colors

    // debug check for NPC HAND
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
    cout << "First card in play: " << actCol << endl // first card activation
         << endl;

    // set first turn to be on the player - can introduce randomized turns later using this boolean
    plyrTrn = true;

    do
    {
        // Check to see if it's the player's turn
        if (plyrTrn == true)
        { // player hand display
            cout << "It's your turn!" << endl
                 << endl;
            cout << "The active color is " << actCol;
            cout
                << endl
                << "| Red Cards: " << redCard << " | Blue Cards : " << bluCard << " | Yellow Cards: " << yelCard << " | Green Cards: "
                << grnCard << " | Wild Cards: " << wildCrd << " |" << endl
                << "| Total number of cards in hand: " << plyCnt << " | Opponent number of cards: " << npcCnt << " |" << endl
                << endl;

            // Prompt for how player wants to proceed
            cout << "What would you like to do?" << endl;
            cout << "| R: Play Red | B: Play Blue | Y: Play Yellow | G: Play Green | W: Play Wild | D: Draw Card | " << endl;
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

            if (menuSel == 'W' || menuSel == 'w') // if user selects either uppercase or lowercase w
            {
                if (plyrTrn == true)
                {
                    if (wildCrd > 0) // logic to verify user input and return appropriate responses
                    {
                        wildCrd--; // decrement wild card when used
                        plyCnt--;  // decrement player card total when used

                        cout << "You play a wild card! What color would you like to swap to?" << endl
                             << endl;
                        cout << "| R: Swap Red | B: Swap Blue | Y: Swap Yellow | G: Swap Green | " << endl
                             << endl;
                        cin >> menuSel;
                        cout << endl;

                        if (menuSel == 'R' || menuSel == 'r')
                        {
                            actCrd = 0;
                            actCol = "Red";
                        }
                        if (menuSel == 'B' || menuSel == 'b')
                        {
                            actCrd = 1;
                            actCol = "Blue";
                        }
                        if (menuSel == 'Y' || menuSel == 'y')
                        {
                            actCrd = 2;
                            actCol = "Yellow";
                        }
                        if (menuSel == 'G' || menuSel == 'g')
                        {
                            actCrd = 3;
                            actCol = "Green";
                        }

                        cout << "You have used your wild card to change the color to " << actCol << "!" << endl // display the new color
                             << endl;

                        // END TURN ONCE WILD HAS BEEN PLAYED
                        plyrTrn = false;
                    }
                    else // else user does not own any of the cards selected for play
                    {
                        cout << "You don't have any WILD cards!" << endl
                             << endl;
                    }
                }
            }

            if (menuSel == 'D' || menuSel == 'd') // if user selects either uppercase or lowercase d
            {
                card = rand() % 5;                            // random 0-4 representing four colors - red blue yellow green and wild card
                card == 0 ? redCard++ : card == 1 ? bluCard++ // ternary operator to translate random card draw
                                    : card == 2   ? yelCard++
                                    : card == 3   ? grnCard++
                                                  : wildCrd++;
                plyCnt++; // increment player hand count
                cout << "You Draw a card!" << endl
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
                    else if (npcWld > 0) // logic to verify user input and return appropriate responses
                    {
                        npcWld--; // decrement wild card when used
                        npcCnt--; // decrement player card total when used

                        if (npcRed > npcBlu && npcRed > npcYel && npcRed > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 0;
                            actCol = "Red"; // npc will then opt to choose red
                            plyrTrn = true; // end npc turn
                        }
                        if (npcBlu > npcRed && npcBlu > npcYel && npcBlu > npcGrn) // if NPC has the most amount of blue cards
                        {
                            actCrd = 1;
                            actCol = "Blue"; // npc will then opt to choose blue
                            plyrTrn = true;  // end npc turn
                        }
                        if (npcYel > npcRed && npcYel > npcBlu && npcYel > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 2;
                            actCol = "Yellow"; // npc will then opt to choose yellow
                            plyrTrn = true;    // end npc turn
                        }
                        if (npcGrn > npcRed && npcGrn > npcBlu && npcGrn > npcYel) // if NPC has the most amount of red cards
                        {
                            actCrd = 3;
                            actCol = "Green"; // npc will then opt to choose green
                            plyrTrn = true;   // end npc turn
                        }

                        cout << "The opponent plays a Wild Card! The new color is " << actCol << "!" << endl
                             << endl;
                    }
                    else // if it's red and npc does not have a red card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                           : card == 3   ? npcGrn++
                                                         : npcWld++;
                        npcCnt++; // increment opponent hand count
                        cout << "Opponent Draws a card!" << endl
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
                    else if (npcWld > 0) // logic to verify user input and return appropriate responses
                    {
                        npcWld--; // decrement wild card when used
                        npcCnt--; // decrement player card total when used

                        if (npcRed > npcBlu && npcRed > npcYel && npcRed > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 0;
                            actCol = "Red"; // npc will then opt to choose red
                            plyrTrn = true; // end npc turn
                        }
                        if (npcBlu > npcRed && npcBlu > npcYel && npcBlu > npcGrn) // if NPC has the most amount of blue cards
                        {
                            actCrd = 1;
                            actCol = "Blue"; // npc will then opt to choose blue
                            plyrTrn = true;  // end npc turn
                        }
                        if (npcYel > npcRed && npcYel > npcBlu && npcYel > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 2;
                            actCol = "Yellow"; // npc will then opt to choose yellow
                            plyrTrn = true;    // end npc turn
                        }
                        if (npcGrn > npcRed && npcGrn > npcBlu && npcGrn > npcYel) // if NPC has the most amount of red cards
                        {
                            actCrd = 3;
                            actCol = "Green"; // npc will then opt to choose green
                            plyrTrn = true;   // end npc turn
                        }

                        cout << "The opponent plays a Wild Card! The new color is " << actCol << "!" << endl
                             << endl;
                    }
                    else // if it's blue and npc does not have a blue card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                           : card == 3   ? npcGrn++
                                                         : npcWld++;
                        npcCnt++; // increment opponent hand count
                        cout << "Opponent Draws a card!" << endl
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
                    else if (npcWld > 0) // logic to verify user input and return appropriate responses
                    {
                        npcWld--; // decrement wild card when used
                        npcCnt--; // decrement player card total when used

                        if (npcRed > npcBlu && npcRed > npcYel && npcRed > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 0;
                            actCol = "Red"; // npc will then opt to choose red
                            plyrTrn = true; // end npc turn
                        }
                        if (npcBlu > npcRed && npcBlu > npcYel && npcBlu > npcGrn) // if NPC has the most amount of blue cards
                        {
                            actCrd = 1;
                            actCol = "Blue"; // npc will then opt to choose blue
                            plyrTrn = true;  // end npc turn
                        }
                        if (npcYel > npcRed && npcYel > npcBlu && npcYel > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 2;
                            actCol = "Yellow"; // npc will then opt to choose yellow
                            plyrTrn = true;    // end npc turn
                        }
                        if (npcGrn > npcRed && npcGrn > npcBlu && npcGrn > npcYel) // if NPC has the most amount of red cards
                        {
                            actCrd = 3;
                            actCol = "Green"; // npc will then opt to choose green
                            plyrTrn = true;   // end npc turn
                        }

                        cout << "The opponent plays a Wild Card! The new color is " << actCol << "!" << endl
                             << endl;
                    }
                    else // if it's yellow and npc does not have a yellow card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                           : card == 3   ? npcGrn++
                                                         : npcWld++;
                        npcCnt++; // increment opponent hand count
                        cout << "Opponent Draws a card!" << endl
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
                    else if (npcWld > 0) // logic to verify user input and return appropriate responses
                    {
                        npcWld--; // decrement wild card when used
                        npcCnt--; // decrement player card total when used

                        if (npcRed > npcBlu && npcRed > npcYel && npcRed > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 0;
                            actCol = "Red"; // npc will then opt to choose red
                            plyrTrn = true; // end npc turn
                        }
                        if (npcBlu > npcRed && npcBlu > npcYel && npcBlu > npcGrn) // if NPC has the most amount of blue cards
                        {
                            actCrd = 1;
                            actCol = "Blue"; // npc will then opt to choose blue
                            plyrTrn = true;  // end npc turn
                        }
                        if (npcYel > npcRed && npcYel > npcBlu && npcYel > npcGrn) // if NPC has the most amount of red cards
                        {
                            actCrd = 2;
                            actCol = "Yellow"; // npc will then opt to choose yellow
                            plyrTrn = true;    // end npc turn
                        }
                        if (npcGrn > npcRed && npcGrn > npcBlu && npcGrn > npcYel) // if NPC has the most amount of red cards
                        {
                            actCrd = 3;
                            actCol = "Green"; // npc will then opt to choose green
                            plyrTrn = true;   // end npc turn
                        }

                        cout << "The opponent plays a Wild Card! The new color is " << actCol << "!" << endl
                             << endl;
                    }
                    else // if it's green and npc does not have a green card
                    {
                        card = rand() % 4;                          // draw a random card value
                        card == 0 ? npcRed++ : card == 1 ? npcBlu++ // ternary operator to translate random card draw
                                           : card == 2   ? npcYel++
                                           : card == 3   ? npcGrn++
                                                         : npcWld++;
                        npcCnt++; // increment opponent hand count
                        cout << "Opponent Draws a card!" << endl
                             << endl;
                    }
                }
            }
        }
    } while (plyCnt != 0 && npcCnt != 0); // while neither the player or opponent has won

    // Display and output the results
    if (plyCnt == 0)
    {
        while (file >> score) // read in scores stored in hiScores.dat
        {
            scores.push_back(score); // use push_back function from deque library
        }
        file.close(); // close file

        cout << "Congratulations, you've won!" << endl // display player name if player wins the game.
             << endl;
        score = npcCnt - plyCnt; // if player wins calculate score by finding the difference between the opponent card count and player card count
        cout << "You've scored " << score << " points!" << endl;

        scores.push_back(score); // add score to the que

        if (scores.size() > maxScrs) // checks to see if the list of scores exceeds the constant limit of 10
        {
            scores.pop_front(); // removes the oldest score
        }

        file.open("hiScore.dat", ios::out); // clear file and write new scores

        // write updated scores back to the file
        for (int i = 0; i < scores.size(); i++) // loops for the length of size of scores
        {
            file << scores[i] << endl;
        }

        file.close();

        // Calculate the average of the stored scores
        sum = 0;                                // set the sum equal to 0
        for (int i = 0; i < scores.size(); i++) // take each score in the deque
        {
            sum += scores[i]; // set sum equal to all of the scores in the deque
        }
        // Calculate the average
        if (scores.size() == 1)
        {
            average = static_cast<float>(scores[0]); // If there is only one score, set average to that score
        }
        else
        {
            average = static_cast<float>(sum) / scores.size(); // Calculate average for more than one score
        }

        // initialize and calculate float variance
        varince = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            varince += pow(scores[i] - average, 2); // squared difference from the mean
        }
        varince /= scores.size(); // average squared difference

        // calculate the standard deviation
        stdDev = sqrt(varince); // standard deviation is calculated from taking the square root of variance

        // Display the Statistics
        if (average < score)
        {
            btrWrse = "better";
        }
        else
        {
            btrWrse = "worse";
        }

        // Calculate the percent change from the average
        pctChng = (score - average) / static_cast<float>(average) * PERCENT;
        if (pctChng < 0)
        {
            pctChng *= -1; // if percent change is negative, change to positive
        }

        cout << "Which is " << pctChng << " % " << btrWrse << " than the average of the last ten victories." << endl
             << endl;
        cout << "Average of last " << scores.size() << " scores: " << average << endl;
        cout << "Standard Deviation of the scores: " << stdDev << endl;
    }
    else if (npcCnt == 0)
    {
        cout << "You've Lost!" << endl
             << endl;
    }

    // Exit the program
    return 0;
}