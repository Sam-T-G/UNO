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
struct Card
{
    // color of card
    char color; // red = r | blue = b | y = yellow | g  = green | wild = w
    char suit;  // numbers =  0-9 | skip = > | draw 2 = + | draw 4 | * if wild, numbers/skip interpreted as normal cards
};

struct Player
{
    string name;      // Player name
    struct Card hand; // Nested Card Structure to house hand information
    int score;        // Player score
};

void menu(Player &); // Function to display modular main menu screen

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables

    // Initialize Variables

    // Map the inputs and outputs - Process
    Player player1; // Create a player 1 structure to hold player's information - later can be modularized
    menu(player1);  // pass player 1 structure into function
    cout << player1.name;

    // Display and output the results

    // Exit the program
    return 0;
}

// Main menu function
void menu(Player &player1)
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
    cin >> player1.name;
    cout << endl;
};

// Draw function

// Deal function

// Play function

// Sort Hand Function

// Active Card Function

// User Interface Function

// Display Hand Function

// Card Info to Decipher card information

// Wild Card Function

// Player turn funciton sequence

// NPC turn function sequence

// Save Scores Function

// Display results