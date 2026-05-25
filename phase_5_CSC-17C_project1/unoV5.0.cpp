/*
Name: Samuel Gerungan
Date: 5/24/26
Purpose: UNO! Game Version 5.0
*/

// System Libraries
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <list>
#include <iterator>
#include <stack>
#include <queue>
#include <map>
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
void initDeck(queue<Card> &);                     // Function to build and shuffle the 100-card draw deck
void deal(Player &, Player &, queue<Card> &);     // Function to deal initial hand to a given player
void actvCrd(Card &);                             // Function to place current active card
void crdDisp(Player &);                           // Function to display current card in play
void usrInt(Player &, Player &, Card &);                  // Function to show user interface and prompt
void play(Player &, Player &, int, stack<Card> &, queue<Card> &, bool &); // Function to put a card in play and to check if the play is valid
void plyrTrn(Player &, Player &, stack<Card> &, queue<Card> &, bool &);   // Function to prompt and process playr turn
void npcTrn(Player &, Player &, stack<Card> &, queue<Card> &, bool &);    // Function to process npc logic
CardClr pickClr(const list<Card> &);                                      // Step 5: tally NPC hand by color via map and pick the dominant one
void calcScrs(Player &, Player &npc);
void readScrs();
void updtScr(const string &, const Scores &);
bool loadScoreMap(map<string, Scores> &); // Step 4: read scores.dat into an associative container
void chkIdx(int, int);                    // exception

// Constructor
Player::Player()
{
    name = "";
    trns = 0;
    cmb = 0;
    cmbMx = 0;
    hand.clear(); // Optional, list default is already empty
}

// Destructor
// Player::~Player()
// {
//     hand.clear(); // Optional, list handles memory automatically
// }

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

void Player::drwCrd(queue<Card> &deck)
{
    if (deck.empty())
    {
        cout << "Deck exhausted! No card drawn." << endl;
        return;
    }
    hand.push_back(deck.front());
    deck.pop();
    Card::totalDrawn++;
}
void Player::takeTurn(Player &opponent, stack<Card> &discard, queue<Card> &deck, bool &turn)
{
    plyrTrn(*this, opponent, discard, deck, turn); // assumes this is the player version
}

// Wrappers
void Player::resetCombo() { rstCmb(); }
void Player::updateCombo() { updCmb(); }
void Player::drawCard(queue<Card> &deck) { drwCrd(deck); }
Scores Player::getScores() const { return scr; }
void Player::setScores(const Scores &s) { scr = s; }
int Player::getMaxCombo() const { return cmbMx; }
int Card::totalDrawn = 0; // static member

Card draw(queue<Card> &);

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
    queue<Card> deck;         // Draw deck as STL container adaptor; front() is the next card up
    initDeck(deck);           // Fill and shuffle the 100-card UNO deck
    stack<Card> discard;      // Discard pile as STL container adaptor; top() is the active card
    discard.push(draw(deck)); // Seed the pile with the first active card
    menu(*p1); // pass player 1 structure into function
    deal(*p1, *npc, deck);

    bool turn = true; // Player starts first

    // Display and output the results
    while (!p1->hand.empty() && !npc->hand.empty())
    {
        if (turn == true) // Player's turn
        {
            plyrTrn(*p1, *npc, discard, deck, turn);
        }
        else if (turn == false) // NPC's turn
        {
            npcTrn(*p1, *npc, discard, deck, turn);
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

// Deck initialization function
// Builds a 100-card UNO distribution into a fixed array, Fisher-Yates shuffles
// it with rand(), and pushes the shuffled order into the queue. Step 7 will
// later swap the in-place shuffle for std::shuffle to claim the mutating
// algorithm rubric line.
void initDeck(queue<Card> &deck)
{
    const int DECK_SIZE = 100;
    Card pool[DECK_SIZE];
    int idx = 0;

    // 4 non-wild colors: 1x ZERO + 2x each of ONE..NINE + 2x SKIP + 2x DRAW_TWO
    CardClr colors[] = {RED, BLUE, YELLOW, GREEN};
    for (CardClr c : colors)
    {
        pool[idx++] = {c, ZERO};
        for (int s = ONE; s <= NINE; s++)
        {
            pool[idx++] = {c, static_cast<CardSuit>(s)};
            pool[idx++] = {c, static_cast<CardSuit>(s)};
        }
        pool[idx++] = {c, SKIP};
        pool[idx++] = {c, SKIP};
        pool[idx++] = {c, DRAW_TWO};
        pool[idx++] = {c, DRAW_TWO};
    }
    // 4 plain wilds + 4 wild draw-four
    for (int i = 0; i < 4; i++)
        pool[idx++] = {WILD, ZERO};
    for (int i = 0; i < 4; i++)
        pool[idx++] = {WILD, DRAW_FOUR};

    // Fisher-Yates shuffle using rand(); Step 7 will replace this with std::shuffle.
    for (int i = DECK_SIZE - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        Card tmp = pool[i];
        pool[i] = pool[j];
        pool[j] = tmp;
    }

    for (int i = 0; i < DECK_SIZE; i++)
        deck.push(pool[i]);
}

// Draw function: pops the front of the deck queue and returns it.
Card draw(queue<Card> &deck)
{
    if (deck.empty())
    {
        cout << "Deck exhausted! Returning placeholder card." << endl;
        return Card{WILD, ZERO};
    }
    Card top = deck.front();
    deck.pop();
    Card::totalDrawn++;
    return top;
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
void deal(Player &p1, Player &npc, queue<Card> &deck)
{ // Deal 7 Starting cards for player and npc
    for (int i = 0; i < 7; i++)
    {
        p1.hand.push_back(draw(deck));
        npc.hand.push_back(draw(deck));
    }
};

// Sort Hand Function
void srtHnd(Player &p1)
{
    // list<Card> does not support std::sort (no random-access iterators),
    // so we call the list's own member sort. Step 9 claims this as the
    // organizational-algorithm rubric line.
    p1.hand.sort([](const Card &a, const Card &b)
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

    // Display player's hand. list<Card> is bidirectional, so we drop the
    // index-based loop and walk an iterator while keeping a parallel int
    // for the user-facing "[i]" label.
    cout
        << "Your hand: " << endl;
    int i = 0;
    for (list<Card>::iterator it = p1.hand.begin(); it != p1.hand.end(); ++it, ++i)
    {
        cout << " [" << i << "] ";
        if (it->color == WILD)
            cout << "Wild";
        else
            cout << values[it->suit] << " " << colors[it->color];
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
void play(Player &p1, Player &npc, int choice, stack<Card> &discard, queue<Card> &deck, bool &turn)
{
    // Error check for card range chosen. Bounds check has to run before the
    // iterator walk, since std::next past the end is undefined.
    if (choice < 0 || choice >= static_cast<int>(p1.hand.size()))
    {
        cout << "Invalid choice!" << endl;
        return;
    }

    // Walk the list once and reuse the iterator for both read and erase.
    list<Card>::iterator it = next(p1.hand.begin(), choice);
    Card slctd = *it;

    // Validate play: same color, same suit (number/action), or wild
    if (slctd.color == discard.top().color || slctd.suit == discard.top().suit || slctd.color == WILD)
    {
        discard.push(slctd); // Push onto the discard pile; new top is the active card
        p1.hand.erase(it);   // Remove played card via the cached iterator
        cout << setw(16) << " " << "You've played a ";
        dispCrd(discard.top()); // Display active card in human-readable format

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
            npc.hand.push_back(draw(deck)); // draw two cards
            npc.hand.push_back(draw(deck));
            cout << "Opponent now has " << npc.hand.size() << " cards!" << endl;
            turn = true; // Player goes again
        }
        else if (slctd.suit == 12) // DRAW 4 (if added)
        {
            cout << "DRAW 4 played! Opponent draws 4 cards!" << endl;
            for (int i = 0; i < 4; i++) // loop to process 4 card draw
            {
                npc.hand.push_back(draw(deck));
            }
            cout << "Opponent now has " << npc.hand.size() << " cards!" << endl;
            turn = true; // Player goes again
        }

        // Handle color choice if Wild
        if (slctd.color == WILD)
        {
            wildCrd(discard.top()); // mutate the top of the discard pile in place
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
void plyrTrn(Player &p1, Player &npc, stack<Card> &discard, queue<Card> &deck, bool &turn)
{
    int choice;

    while (turn == true)
    {
        turn = false;                     // Default set turn to false at the start of the loop
        usrInt(p1, npc, discard.top());   // Display the current game state; top of pile is the active card
        cout << "--------------------------------------------------------" << endl;
        cout << "Which card would you like to play?: "; // Prompt for visual Clarity
        cin >> choice;                                  // Input player choice
        cout << "========================================================" << endl;

        // disPrvSts(*p1); //Future implementation to add option to display private stats of player

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
            p1.drawCard(deck);
            p1.resetCombo(); // Reset combo streak
            turn = true;     // Player goes again after drawing a card
        }
        else
        {
            try
            {
                chkIdx(choice, p1.hand.size());
                play(p1, npc, choice, discard, deck, turn);
            }
            catch (const out_of_range &e)
            {
                cout << "Error: " << e.what() << endl;
                turn = true;
            }
        }
    }
}

// Tally the NPC hand by color and return the most-held non-wild color.
// map<CardClr,int> is the second associative container required by the rubric.
CardClr pickClr(const list<Card> &hand)
{
    map<CardClr, int> tally;
    for (list<Card>::const_iterator it = hand.begin(); it != hand.end(); ++it)
        if (it->color != WILD)
            tally[it->color]++;

    if (tally.empty()) // hand was all wilds; fall back to a random color
        return static_cast<CardClr>(rand() % 4);

    CardClr best = tally.begin()->first;
    int bestN = tally.begin()->second;
    for (map<CardClr, int>::const_iterator it = tally.begin(); it != tally.end(); ++it)
        if (it->second > bestN)
        {
            best = it->first;
            bestN = it->second;
        }
    return best;
}

// NPC turn function sequence
void npcTrn(Player &p1, Player &npc, stack<Card> &discard, queue<Card> &deck, bool &turn)
{
    bool valid = false;
    list<Card>::iterator it = npc.hand.begin(); // list<Card> is bidirectional; we advance manually instead of indexing.

    while (!valid) // Check if valid play has been made
    {
        if (it != npc.hand.end())
        {
            Card c = *it; // Make a copy of card at the current iterator

            if (c.color == discard.top().color || c.suit == discard.top().suit || c.color == WILD)
            {
                discard.push(c);
                npc.hand.erase(it);
                p1.resetCombo(); // Reset player's combo

                cout << "NPC played: " << crdInfo(discard.top()) << "!" << endl;

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
                    CardClr newClr = pickClr(npc.hand); // most-held color via map tally
                    discard.top().color = newClr;       // mutate the active card on top of the pile
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
                        p1.hand.push_back(draw(deck));
                    turn = false;
                }
                else if (c.suit == DRAW_FOUR)
                {
                    cout << "NPC played DRAW 4! You draw 4 cards." << endl;
                    for (int i = 0; i < 4; ++i)
                        p1.hand.push_back(draw(deck));
                    turn = false;
                }

                valid = true; // Set Valid to true if valid play has been made
            }
            else
            {
                ++it;
            }
        }
        else
        {
            Card drawn = draw(deck);
            npc.hand.push_back(drawn);
            cout << "NPC draws a card!" << endl;
            npc.resetCombo(); // Reset combo on failed turn

            if (drawn.color == discard.top().color || drawn.suit == discard.top().suit || drawn.color == WILD)
            {
                discard.push(drawn);
                npc.hand.pop_back(); // play the drawn card
                cout << "NPC plays the drawn card: " << crdInfo(discard.top()) << "!" << endl;

                // Edge case for when NPC wins with last drawn card
                if (npc.hand.empty())
                {
                    cout << "NPC plays the final drawn card and wins!" << endl;
                    return;
                }

                if (drawn.color == WILD)
                {
                    CardClr newClr = pickClr(npc.hand); // most-held color via map tally
                    discard.top().color = newClr;       // mutate the active card on top of the pile
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
                            p1.hand.push_back(draw(deck));
                    }
                    else if (drawn.suit == DRAW_FOUR)
                    {
                        cout << "NPC played DRAW 4! You draw 4 cards." << endl;
                        for (int i = 0; i < 4; ++i)
                            p1.hand.push_back(draw(deck));
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
    int trnsWon = maxValue(p1.trns, npc.trns);

    cout << "\n--- SCORES ---\n";
    cout << p1.name << " wins in " << updatedScore.trns << " turns\n";
    cout << "Highest combo: " << updatedScore.cmbHi << '\n';
    cout << "Card diff: " << diff << "\n";
    cout << "Total cards drawn this game: " << Card::totalDrawn << endl;
    cout << "Most turns taken in game: " << trnsWon << endl;

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

// Step 4: slurp scores.dat into a map<string, Scores>. Returns false when the
// file cannot be opened so the caller can keep its original error message.
// The on-disk SaveData format stays untouched; the map is purely in-memory.
bool loadScoreMap(map<string, Scores> &out)
{
    ifstream in("scores.dat", ios::binary);
    if (!in)
        return false;
    SaveData data;
    while (in.read(reinterpret_cast<char *>(&data), sizeof(SaveData)))
    {
        out[data.name] = data.scr;
    }
    return true;
}

void readScrs()
{
    map<string, Scores> scores;
    if (!loadScoreMap(scores))
    {
        cerr << "Error opening scores.dat\n";
        return;
    }

    cout << "\n"
         << setw(12) << " " << "=== SCORE HISTORY ===\n";

    // Bidirectional iterator walk over the map. Records print in name order
    // since map keeps its keys sorted, which is a small UX improvement over
    // the prior insertion-order display.
    int count = 1;
    for (map<string, Scores>::iterator it = scores.begin(); it != scores.end(); ++it)
    {
        cout << setw(15) << " " << "Record " << count++ << ":\n";
        cout << setw(15) << " " << "  Player  : " << it->first << '\n';
        cout << setw(15) << " " << "  Turns   : " << it->second.trns << '\n';
        cout << setw(15) << " " << "  HiCombo : " << it->second.cmbHi << "\n\n";
    }
}

void updtScr(const string &player, const Scores &newScr)
{
    map<string, Scores> scores;
    if (!loadScoreMap(scores))
    {
        cerr << "Failed to open scores.dat\n";
        return;
    }

    // O(log n) associative lookup replaces the Phase 4 linear name-scan.
    map<string, Scores>::iterator it = scores.find(player);
    if (it == scores.end())
    {
        cout << "Player not found in save file.\n";
        return;
    }
    it->second = newScr;

    // Flush the whole map back to disk. Truncate+rewrite preserves the
    // fixed-size SaveData record format on scores.dat so existing history
    // stays readable by readScrs.
    ofstream out("scores.dat", ios::binary | ios::trunc);
    if (!out)
    {
        cerr << "Failed to open scores.dat for writing\n";
        return;
    }
    for (map<string, Scores>::iterator it = scores.begin(); it != scores.end(); ++it)
    {
        SaveData temp;
        strncpy(temp.name, it->first.c_str(), sizeof(temp.name));
        temp.name[sizeof(temp.name) - 1] = '\0';
        temp.scr = it->second;
        out.write(reinterpret_cast<char *>(&temp), sizeof(SaveData));
    }
    cout << "Score for " << player << " updated.\n";
}

void chkIdx(int idx, int max)
{
    if (idx < 0 || idx >= max)
    {
        throw out_of_range("Invalid card index selected.");
    }
}

// FUTURE IMPLEMENTATION AND FIXES

// Player original;
// original.name = "Samuel";
// original.trns = 5;
// original.drawCard(); // etc.

// Player copy = original; // invokes copy constructor
// disPrvSts(copy);        // Show copy's private state

// cout << "Copied player name: " << copy.name << endl;
// cout << "Cards in hand: " << copy.hndSze() << endl;

// NPCPlayer npc;
// npc.name = "CPU_X";
// npc.drawCard();  // inherited from Player
// npc.printRole(); // NPC-only method
// npc.cheat();     // NPC-only method

// disPrvSts(npc); // friend function still works