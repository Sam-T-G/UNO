/*
Name: Samuel Gerungan
Date: 4/29/25
Purpose: UNO! Game Version 3.3
*/

// System Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Player.h"
#include "Card.h"
#include "Scores.h"

using namespace std;

// User Libraries

// Global Constants

// Only use scientific values like pi, speed of light, etc

// Conversion between units

// Function Protypes
// Most structures on external files
// Save Data structure
struct SaveData
{
    char name[20]; // Fixed-length(20) C-string name
    Scores scr;    // Score data (turns, combo)
};

void menu(Player &);                              // Function to display modular main menu screen
void draw(Player &);                              // Modular Function to Draw a Card
void deal(Player &, Player &);                    // Function to deal initial hand to a given player
void actvCrd(Card &);                             // Function to place current active card
void crdDisp(Player &);                           // Function to display current card in play
void usrInt(Player &, Player &, Card &);          // Function to show user interface and prompt
void play(Card &, Player &);                      // Funcition to put a card in play and to check if the play is valid
void plyrTrn(Player &, Player &, Card &, bool &); // Function to prompt and process playr turn
void npcTrn(Player &, Player &, Card &, bool &);  // Function to process npc logic
void calcScrs(Player &, Player &npc);
void readScrs();
void updtScr(const string &, const Scores &);

void Player::resetCombo() { rstCmb(); }
void Player::updateCombo() { updCmb(); }
void Player::drawCard() { drwCrd(); }

Scores Player::getScores() const { return scr; }
void Player::setScores(const Scores &s) { scr = s; }
int Player::getMaxCombo() const
{
    return cmbMx;
}

Card draw();

string crdInfo(const Card &);

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables

    // Initialize Variables

    // Map the inputs and outputs - Process
    Player *p1 = new Player;  // Create a player 1 structure to hold player's information - later can be modularized
    Player *npc = new Player; // Create an NPC opponent
    Card actvCrd = draw();
    menu(*p1); // pass player 1 structure into function
    deal(*p1, *npc);

    bool turn = true; // Player starts first

    // Display and output the results
    while (!p1->hand.empty() && !npc->hand.empty())
    {
        if (turn == true) // Player's turn
        {
            plyrTrn(*p1, *npc, actvCrd, turn);
        }
        else if (turn == false) // NPC's turn
        {
            npcTrn(*p1, *npc, actvCrd, turn);
        }
    }

    if (p1->hand.empty())
    {
        cout << "========================================================" << endl
             << endl;
        cout << setw(22) << " " << "You win!" << endl
             << endl;
        cout << "========================================================" << endl;
        char upd; // temporary update variable
        cout << setw(9) << " " << "Update your saved score? (y/n): ";
        cin >> upd;
        if (tolower(upd) == 'y')
        {
            cout << "========================================================" << endl
                 << endl;
            calcScrs(*p1, *npc);
            char upd;
            cout << "Update existing saved score? (y/n): ";
            cin >> upd;
            if (tolower(upd) == 'y')
            {
                updtScr(p1->name, p1->getScores()); // update score function
            }
        }
    }
    else if (npc->hand.empty()) // NPC wins and score not saved
    {
        cout << "NPC wins!" << endl;
    }

    readScrs(); // View history of past game scores

    // Clean up!
    delete p1;
    delete npc;

    // Exit the program
    return 0;
};

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
    newCrd.color = static_cast<CardClr>(rand() % 5);
    newCrd.suit = static_cast<CardSuit>(rand() % 13);
    return newCrd;
}

// Wild Card Function
void wildCrd(Card &card)
{
    if (card.color == WILD)
    {
        char newClr;
        bool valid = false;

        while (!valid)
        {
            cout << "--------------------------------------------------------" << endl
                 << setw(18) << " " << "Choose a new color!" << endl
                 << setw(6) << " " << "R = Red, B = Blue, Y = Yellow, G = Green" << endl
                 << "--------------------------------------------------------" << endl
                 << "New Color: ";
            cin >>
                newClr;
            newClr = toupper(newClr); // Handle lowercase input
            cout << "--------------------------------------------------------" << endl;

            switch (newClr)
            {
            case 'R':
                card.color = RED;
                cout << "You selected: Red" << endl;
                valid = true;
                break;
            case 'B':
                card.color = BLUE;
                cout << "You selected: Blue" << endl;
                valid = true;
                break;
            case 'Y':
                card.color = YELLOW;
                cout << "You selected: Yellow" << endl;
                valid = true;
                break;
            case 'G':
                card.color = GREEN;
                cout << "You selected: Green" << endl;
                valid = true;
                break;
            default:
                cout << "Invalid color selection. Please try again." << endl;
            }
            cout << "========================================================" << endl;
        }
    }
}

// Active Card Display Function
void dispCrd(Card &actvCrd)
{
    // String arrays for descriptive output
    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2", "DRAW 4"};

    if (actvCrd.color == WILD)
    {
        cout << "Wild" << endl;
    }
    else if (actvCrd.color >= 0 && actvCrd.color < 5 && actvCrd.suit >= 0 && actvCrd.suit < 13)
    {
        cout << values[actvCrd.suit] << " " << colors[actvCrd.color] << endl;
    }
    else
    {
        cout << "Invalid Card" << endl;
    }
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

// Sort Hand Function
void srtHnd(Player &p1)
{
    sort(p1.hand.begin(), p1.hand.end(), [](const Card &a, const Card &b)
         {
        if (a.color == b.color) {
            return a.suit < b.suit;
        }
        return a.color < b.color; });
}

// User Interface Function
void usrInt(Player &p1, Player &npc, Card &actvCrd)
{
    srtHnd(p1); // Sort the player's hand before displaying

    string colors[] = {"Red", "Blue", "Yellow", "Green", "Wild"};
    string values[] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "SKIP", "DRAW 2", "DRAW 4"};

    cout << "========================================================" << endl;
    cout << fixed << setw(16) << " " << "It's your turn, " << p1.name << "!" << endl;
    cout << "--------------------------------------------------------" << endl;

    // Display player's hand
    cout
        << "Your hand: " << endl;
    for (int i = 0; i < p1.hand.size(); i++)
    {
        cout << " [" << i << "] ";
        if (p1.hand[i].color == WILD)
            cout << "Wild";
        else
            cout << values[p1.hand[i].suit] << " " << colors[p1.hand[i].color];
        cout << endl;
    }

    // Display Active Card
    cout << "--------------------------------------------------------" << endl;
    cout << setw(17) << " " << "Active Card: " << crdInfo(actvCrd) << endl;
    cout << "| Cards in your hand: " << p1.hand.size()
         << "  | Opponent number of cards: " << npc.hand.size() << " |" << endl;

    // Prompt for how player wants to proceed
    cout << "--------------------------------------------------------" << endl;
    cout << setw(16) << " " << "What would you like to do?" << endl;
    cout << "| Choose a card to play [0-" << p1.hand.size() << "] | Type -1 to draw a card | " << endl;
}

// Card Info to Decipher card information
string crdInfo(const Card &card)
{
    // Map CardClr to string
    string clrStr;
    switch (card.color)
    {
    case RED:
        clrStr = "Red";
        break;
    case BLUE:
        clrStr = "Blue";
        break;
    case YELLOW:
        clrStr = "Yellow";
        break;
    case GREEN:
        clrStr = "Green";
        break;
    case WILD:
        clrStr = "Wild";
        break;
    }

    // Map CardSuit to string
    string suitStr;
    switch (card.suit)
    {
    case ZERO:
        suitStr = "0";
        break;
    case ONE:
        suitStr = "1";
        break;
    case TWO:
        suitStr = "2";
        break;
    case THREE:
        suitStr = "3";
        break;
    case FOUR:
        suitStr = "4";
        break;
    case FIVE:
        suitStr = "5";
        break;
    case SIX:
        suitStr = "6";
        break;
    case SEVEN:
        suitStr = "7";
        break;
    case EIGHT:
        suitStr = "8";
        break;
    case NINE:
        suitStr = "9";
        break;
    case SKIP:
        suitStr = "Skip";
        break;
    case DRAW_TWO:
        suitStr = "Draw Two";
        break;
    case DRAW_FOUR:
        suitStr = "Draw Four";
        break;
    }

    // Combine color and suit into a readable string
    return clrStr + " " + suitStr;
}

// Play card function
void play(Player &p1, Player &npc, int choice, Card &actvCrd, bool &turn)
{
    // store selected card
    Card slctd = p1.hand[choice];

    // Error check for card range chosen
    if (choice < 0 || choice >= p1.hand.size())
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Validate play: same color, same suit (number/action), or wild
    if (slctd.color == actvCrd.color || slctd.suit == actvCrd.suit || slctd.color == WILD)
    {
        actvCrd = slctd;                         // Update active card
        p1.hand.erase(p1.hand.begin() + choice); // Remove played card
        cout << setw(16) << " " << "You've played a ";
        dispCrd(actvCrd); // Display active card in human-readable format

        if (p1.hand.empty())
        {
            cout << setw(13) << " " << "You've played your last card!" << endl;
            return; // Exit early — game ends after this play
        }

        // Handle special cards
        if (slctd.suit == 10) // SKIP
        {
            cout << "SKIP played! It's your turn again!" << endl;
            turn = true; // Player goes again
        }
        else if (slctd.suit == 11) // DRAW 2
        {
            cout << "DRAW 2 played! Opponent draws 2 cards!" << endl;
            npc.hand.push_back(draw()); // draw two cards
            npc.hand.push_back(draw());
            cout << "Opponent now has " << npc.hand.size() << " cards!" << endl;
            turn = true; // Player goes again
        }
        else if (slctd.suit == 12) // DRAW 4 (if added)
        {
            cout << "DRAW 4 played! Opponent draws 4 cards!" << endl;
            for (int i = 0; i < 4; i++) // loop to process 4 card draw
            {
                npc.hand.push_back(draw());
            }
            cout << "Opponent now has " << npc.hand.size() << " cards!" << endl;
            turn = true; // Player goes again
        }

        // Handle color choice if Wild
        if (slctd.color == WILD)
        {
            wildCrd(actvCrd); // call wild card function
        }

        // Keep Track of Player combo
        p1.updateCombo();
        npc.resetCombo();

        // increment turn count
        p1.trns++;
    }
    else
    {
        cout << "Invalid play: Card does not match active card by color or number!" << endl;
        turn = true; // Let the player try again
    }
}

// Player turn funciton sequence
void plyrTrn(Player &p1, Player &npc, Card &actvCrd, bool &turn)
{
    int choice;

    while (turn == true)
    {
        turn = false;             // Default set turn to false at the start of the loop
        usrInt(p1, npc, actvCrd); // Display the current game state
        cout << "--------------------------------------------------------" << endl;
        cout << "Which card would you like to play?: "; // Prompt for visual Clarity
        cin >> choice;                                  // Input player choice
        cout << "========================================================" << endl;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again." << endl;
            turn = true;
        }
        else if (choice == -1)
        {
            cout << "You chose to draw a card." << endl;
            p1.drawCard();
            p1.resetCombo(); // Reset combo streak
            turn = true;     // Player goes again after drawing a card
        }
        else if (choice < 0 || choice >= static_cast<int>(p1.hand.size()))
        {
            cout << "Invalid choice. Pick a valid card index or -1 to draw." << endl;
            turn = true; // Allow another turn if the choice is invalid
        }
        else
        {
            play(p1, npc, choice, actvCrd, turn);
        }
    }
}

// NPC turn function sequence
void npcTrn(Player &p1, Player &npc, Card &actvCrd, bool &turn)
{
    bool valid = false;
    int i = 0;

    while (!valid) // Check if valid play has been made
    {
        if (i < npc.hand.size())
        {
            Card c = npc.hand[i]; // Make a copy of card at given index

            if (c.color == actvCrd.color || c.suit == actvCrd.suit || c.color == WILD)
            {
                actvCrd = c;
                npc.hand.erase(npc.hand.begin() + i);
                p1.resetCombo(); // Reset player's combo

                cout << "NPC played: " << crdInfo(actvCrd) << "!" << endl;

                // Check if NPC hand is empty
                if (npc.hand.empty())
                {
                    cout << "NPC has played their last card!" << endl;
                    p1.resetCombo();
                    return;
                }

                // Default: player's turn next
                turn = true;

                if (c.color == WILD)
                {
                    CardClr newClr = static_cast<CardClr>(rand() % 4);
                    actvCrd.color = newClr;
                    string colors[] = {"Red", "Blue", "Yellow", "Green"};
                    cout << "NPC plays a WILD and chooses " << colors[newClr] << "!" << endl;
                }

                // Handle special cards
                if (c.suit == SKIP)
                {
                    cout << "NPC played SKIP! You lose a turn." << endl;
                    turn = false;
                }
                else if (c.suit == DRAW_TWO)
                {
                    cout << "NPC played DRAW 2! You draw 2 cards." << endl;
                    for (int i = 0; i < 2; ++i)
                        p1.hand.push_back(draw());
                    turn = false;
                }
                else if (c.suit == DRAW_FOUR)
                {
                    cout << "NPC played DRAW 4! You draw 4 cards." << endl;
                    for (int i = 0; i < 4; ++i)
                        p1.hand.push_back(draw());
                    turn = false;
                }

                valid = true; // Set Valid to true if valid play has been made
            }
            else
            {
                ++i;
            }
        }
        else
        {
            Card drawn = draw();
            npc.hand.push_back(drawn);
            cout << "NPC draws a card!" << endl;
            npc.resetCombo(); // Reset combo on failed turn

            if (drawn.color == actvCrd.color || drawn.suit == actvCrd.suit || drawn.color == WILD)
            {
                actvCrd = drawn;
                npc.hand.pop_back(); // play the drawn card
                cout << "NPC plays the drawn card: " << crdInfo(actvCrd) << "!" << endl;

                // Edge case for when NPC wins with last drawn card
                if (npc.hand.empty())
                {
                    cout << "NPC plays the final drawn card and wins!" << endl;
                    return;
                }

                if (drawn.color == WILD)
                {
                    CardClr newClr = static_cast<CardClr>(rand() % 4);
                    actvCrd.color = newClr;
                    string colors[] = {"Red", "Blue", "Yellow", "Green"};
                    cout << "NPC chooses " << colors[newClr] << "!" << endl;
                }

                // If it's a special card, handle turn
                if (drawn.suit == SKIP || drawn.suit == DRAW_TWO || drawn.suit == DRAW_FOUR)
                {
                    if (drawn.suit == SKIP)
                        cout << "NPC played SKIP! You lose a turn." << endl;
                    else if (drawn.suit == DRAW_TWO)
                    {
                        cout << "NPC played DRAW 2! You draw 2 cards." << endl;
                        for (int i = 0; i < 2; ++i)
                            p1.hand.push_back(draw());
                    }
                    else if (drawn.suit == DRAW_FOUR)
                    {
                        cout << "NPC played DRAW 4! You draw 4 cards." << endl;
                        for (int i = 0; i < 4; ++i)
                            p1.hand.push_back(draw());
                    }

                    turn = false; // NPC goes again
                }
                else
                {
                    turn = true; // Player's turn
                }

                valid = true;
            }
        }
    }
}

// Save Scores Function
void calcScrs(Player &p1, Player &npc)
{
    Scores updatedScore;
    updatedScore.trns = p1.trns;
    updatedScore.cmbHi = p1.getMaxCombo();

    // Save the updated score back to the player
    p1.setScores(updatedScore);

    int diff = npc.hand.size(); // card difference

    cout << "\n--- SCORES ---\n";
    cout << p1.name << " wins in " << updatedScore.trns << " turns\n";
    cout << "Highest combo: " << updatedScore.cmbHi << '\n';
    cout << "Card diff: " << diff << "\n";

    // Prepare SaveData object
    SaveData data;
    strncpy(data.name, p1.name.c_str(), sizeof(data.name));
    data.name[sizeof(data.name) - 1] = '\0'; // ensure null-terminated
    data.scr = updatedScore;                 // Write updated score into SaveData

    ofstream out("scores.dat", ios::binary | ios::app);
    if (out)
    {
        out.write(reinterpret_cast<char *>(&data), sizeof(SaveData));
        out.close();
    }
    else
    {
        cerr << "Failed to write to scores.dat\n";
    }
}

void readScrs()
{
    ifstream in("scores.dat", ios::binary);
    if (!in)
    {
        cerr << "Error opening scores.dat\n";
        return;
    }

    SaveData data;
    int count = 1;

    cout << "\n"
         << setw(12) << " " << "=== SCORE HISTORY ===\n";

    while (in.read(reinterpret_cast<char *>(&data), sizeof(SaveData)))
    {
        cout << setw(15) << " " << "Record " << count++ << ":\n";
        cout << setw(15) << " " << "  Player  : " << data.name << '\n';
        cout << setw(15) << " " << "  Turns   : " << data.scr.trns << '\n';
        cout << setw(15) << " " << "  HiCombo : " << data.scr.cmbHi << "\n\n";
    }

    in.close();
}

void updtScr(const string &player, const Scores &newScr)
{
    fstream file("scores.dat", ios::in | ios::out | ios::binary);
    if (!file)
    {
        cerr << "Failed to open scores.dat\n";
        return;
    }

    SaveData temp;
    while (file.read(reinterpret_cast<char *>(&temp), sizeof(SaveData)))
    {
        if (player == temp.name)
        {
            // Move file pointer back to start of this record
            file.seekp(-static_cast<int>(sizeof(SaveData)), ios::cur);
            temp.scr = newScr;
            file.write(reinterpret_cast<char *>(&temp), sizeof(SaveData));
            cout << "Score for " << player << " updated.\n";
            file.close();
            return;
        }
    }

    file.close();
    cout << "Player not found in save file.\n";
}
