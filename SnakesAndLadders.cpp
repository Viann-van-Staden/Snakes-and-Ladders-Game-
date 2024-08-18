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

// Player definitions
enum Players {
    PLAYERONE,
    PLAYERTWO
};

int rollDice(mt19937& gen) {
    int min = 1;
    int max = 6;

    uniform_int_distribution<> distrib(min, max);

    return distrib(gen);  // Return the generated random number
}

void switchTurn(int& playerPosition, bool playerTurn, int& turnCounter) {
    mt19937 gen(time(0));
    int playerRoll = rollDice(gen);

    playerPosition += playerRoll;
    turnCounter++;  // Increment turn counter for this player

    string playerNumber = playerTurn ? "One" : "Two";

    if (playerPosition > 25) {
        playerPosition = 25;  // Cap the position at 25 (or loop around if needed)
    }

    cout << "Player " << playerNumber << " rolls: " << playerRoll << " and moves to square " << playerPosition << endl;
    Sleep(1000);
}

void Winner(string player, int turnCounter) {
    cout << "Player " << player << " wins!" << endl;
    cout << "Player " << player << " took " << turnCounter << " turns to win." << endl;

    ofstream WinnerFile("Winner.txt");

    WinnerFile << "Player " << player << " wins!" << endl;
    WinnerFile << "Player " << player << " took " << turnCounter << " turns to win." << endl;

    WinnerFile.close();
}

void playerTurn(int& playerOnePosition, int& playerTwoPosition, int& turnCounter) {
    bool isPlayerOneTurn = true;

    while (playerOnePosition < 25 && playerTwoPosition < 25) {
        if (isPlayerOneTurn) {
            switchTurn(playerOnePosition, isPlayerOneTurn, turnCounter);
            isPlayerOneTurn = false;  // Switch to Player Two
        }
        else {
            switchTurn(playerTwoPosition, isPlayerOneTurn, turnCounter);
            isPlayerOneTurn = true;  // Switch back to Player One
        }
    }

    if (playerOnePosition >= 25) {
        Winner("One", turnCounter);
    }
    else if (playerTwoPosition >= 25) {
        Winner("Two", turnCounter);
    }
}

int main() {
    int turnCounter = 0;  // Initialize turn counter
    int playerOnePosition = 0;  // Initialize player positions
    int playerTwoPosition = 0;

    playerTurn(playerOnePosition, playerTwoPosition, turnCounter);

    return 0;
}
