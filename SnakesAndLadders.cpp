#include <iostream>
#include <random>
#include <ctime>
#include <windows.h>
#include <fstream>

using namespace std;

int grid[25] = {
    21, 22, 23, 24, 25,
    16, 17, 18, 19, 20,
    11, 12, 13, 14, 15,
    6, 7, 8, 9, 10,
    1, 2, 3, 4, 5
};

// Snake definitions
enum Snake {
    SNAKE_ONE_HEAD = 13,
    SNAKE_ONE_TAIL = 2,
    SNAKE_TWO_HEAD = 19,
    SNAKE_TWO_TAIL = 6,
    SNAKE_THREE_HEAD = 24,
    SNAKE_THREE_TAIL = 3
};

// Ladder definitions
enum Ladder {
    LADDER_ONE_TOP = 17,
    LADDER_ONE_BOTTOM = 4,
    LADDER_TWO_TOP = 18,
    LADDER_TWO_BOTTOM = 7,
    LADDER_THREE_TOP = 22,
    LADDER_THREE_BOTTOM = 15
};

// Player definitions, add more players here to increase player size. and change below for loop as well.
enum Players {
    PLAYERONE,
    PLAYERTWO
};

int rollDice(mt19937& gen) { 

    int min = 1;
    int max = 6;

    // Initialize a random number generator
    uniform_int_distribution<> distrib(min, max);

    int randomValue = distrib(gen);

    return randomValue;  // Return the generated random number
}


void switchTurn(int& playerPosition, bool playerTurn) {

    mt19937 gen(time(0));
    int playerRoll = rollDice(gen);

    playerPosition += playerRoll;

    string playerNumber = playerTurn ? "One" : "Two";

    cout << "Player " << playerNumber << " rolls: " << playerRoll << " and moves to square " << playerPosition << endl;

    Sleep(1000); 
}


void Winner(string player) {

    cout << "Player " << player << " wins!" << endl; 

    ofstream WinnerFile("Winner.txt");

    WinnerFile << "Player " << player << " wins!" << endl;

    WinnerFile.close();
}

void playerTurn(int& playerOnePosition, int& playerTwoPosition) {

    bool playerTurn = true; 


    mt19937 gen(time(0)); 

    while (playerOnePosition < 25 && playerTwoPosition < 25) {
        if (playerTurn) { 
            switchTurn(playerOnePosition, playerTurn);   
            playerTurn = false;
        }
        else {
            switchTurn(playerTwoPosition, playerTurn); 
            playerTurn = true; 
        } 
    }

    if (playerOnePosition >= 25) { 
        string player = "One";
        Winner(player); 
    }
    else if (playerTwoPosition >= 25) {
        string player = "Two";
        Winner(player); 
    }
}

int main() {
    int playerOnePosition = 0;  // Initialize positions
    int playerTwoPosition = 0; 

    playerTurn(playerOnePosition, playerTwoPosition);

    return 0;
}
