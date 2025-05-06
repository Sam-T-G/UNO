/*
Name: Samuel Gerungan
Date: 4/29/25
Purpose: UNO! Game Version 3.1
*/

// System Libraries
#include <iostream>
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
struct card
{
    // color of card
    char color; // red = r | blue = b | y = yellow | g  = green | wild = w
    char suit;  // numbers =  0-9 | skip = > | draw 2 = + | draw 4 | * if wild, numbers/skip interpreted as normal cards
};

struct player
{
    string name;      // Player name
    struct card hand; // Nested Card Structure to house hand information
    int score;        // Player score
};

int main(int argv, char **argc)
{
    // Random seeds are set for random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Declare Variables

    // Initialize Variables

    // Map the inputs and outputs - Process

    // Display and output the results

    // Exit the program
    return 0;
}

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