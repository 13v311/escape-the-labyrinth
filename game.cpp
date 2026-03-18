// game.cpp
//
// Fire vs. Water game application for course project
// University of Illinois at Chicago
// CS 211 - Programming Practicum
// Original Author: Professor Scott Reckinger
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

#include "gameboard.h"

char getWindDirection() {
    char windDir;
    cout << "Set wind direction ['s' no wind, 'd' to spread east, etc.; 'k' ends game]: " ;
    cin >> windDir;
    cout << endl;
    return windDir;
}

int main( ) {
	
    int numrows = 0; //15
    int numcols = 0; //40
    while (numrows < 10 || numrows > 30) {
        cout << "Enter the # of rows (10-30) for the board: ";
        cin >> numrows;
        cout << endl;
    }
    while (numcols < 15 || numcols > 100) {
        cout << "Enter the # of columns (15-100) for the board: ";
        cin >> numcols;
        cout << endl;
    }
    GameBoard myBoard(numrows, numcols);
    
    int numF = -1;
    while (numF < 0 || numF > 20) {
        cout << "Enter the # of Fire cells (0-20) on the board: ";
        cin >> numF;
        cout << endl;
    }
    myBoard.setNumFire(numF);
    
    int numW = -1;
    while (numW < 0 || numW > 40) {
        cout << "Enter the # of Water cells (0-40) on the board: ";
        cin >> numW;
        cout << endl;
    }
    myBoard.setNumWater(numW);

    int numM = -1;
    while (numM < 1 || numM > 9) {
        cout << "Enter the # of water moves (1-9) per single fire spread: ";
        cin >> numM;
        cout << endl;
    }
    
    int seed = -1;
    cout << "Enter a seed for the random # generator (-1 to use system time): ";
    cin >> seed;
    cout << endl;
    
    if (seed < 0) {
        myBoard.setupBoard(time(0));
    } else {
        myBoard.setupBoard(seed);
    }
    myBoard.displayBoard(true);
        
    bool gameOver = false;
    char windDir = 's';
    int turn = 0;
    windDir = getWindDirection();
    if (windDir == 'k') {gameOver = true;}
    while (!gameOver) {
        myBoard.spreadFire(windDir);
        for (int i = 0; i<numM; i++) {myBoard.spreadWater();}
        myBoard.displayBoard(true);
        turn++;
        windDir = getWindDirection();
        if (windDir == 'k') {gameOver = true;}
        if (myBoard.getNumFire() == 0 && myBoard.getNumEmpty() == 0) {gameOver = true;}
        if (myBoard.getNumGrass() == 0) {gameOver = true;}
    }  

    cout << "Game Over." << endl;
	
	return 0;
	
} // main
