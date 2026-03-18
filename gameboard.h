// gameboard.h
//
// GameBoard class starter code for course project
// University of Illinois at Chicago
// CS 211 - Programming Practicum
// Original Author: Professor Scott Reckinger
//

#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <ctime>
#include <stdexcept>

#include "boardcell.h"
#include "grid.h"

using namespace std;

class GameBoard {
	private: 
	    Grid<BoardCell*> board;
        size_t numRows;
        size_t numCols;
        int numFire;
        int numWater;
        int numWall;
        int numGrass;
        int numEmpty;
        
	public: 
		/* default constructor */
        GameBoard() {
            numFire = 10;
            numWater = 20;
            numWall = 0;
            numGrass = 15*40-30;
            numEmpty = 0;
            
            this -> numRows = 15;
            this -> numCols = 40;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* param constructor */
        GameBoard(size_t numRows, size_t numCols) {
            numFire = 10;
            numWater = 20;
            numWall = 0;
            numGrass = numRows*numCols-30;
            numEmpty = 0;
            
            this -> numRows = numRows;
            this -> numCols = numCols;
            
            Grid<BoardCell*> boardnew(numRows, numCols);
            board = boardnew;
            
            blankBoard();
        }
        
        /* destructor */
        virtual ~GameBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    delete board(row, col);
                }
            }
        }

        void blankBoard() {
            for (size_t row = 0; row < board.numrows(); row++) {
                for (size_t col = 0; col < board.numcols(row); col++) {
                    board(row, col) = new Grass(row,col);
                }
            }
        }

        char getCellDisplay(size_t r, size_t c) {
            return board(r,c)->display();
        }

        void setCell(BoardCell* myCell, size_t r, size_t c) {
            board(r,c) = myCell;
        }
    
        void freeCell(size_t r, size_t c) {
            delete board(r,c);
        }

        // fills the board with by randomly placing...
        //  - numFire Fire (*) cells in the first three columns
        //  - 3 vertical Walls (x), each 1/2 of board height, not in the first three columns
        //  - numWater Water (~) cells to the right of the first three columns
        //  - the remaining cells are all Grass cells (,)
        void setupBoard(int seed) {
            srand(seed);
            size_t r,c;

            for (int i = 0; i < numFire; i++) {
                r = rand() % numRows;
                c = rand() % 3;
                while (board(r,c)->display() != ',') {
                    r = rand() % numRows;
                    c = rand() % 3;
                }
                delete board(r,c);
                board(r,c) = new Fire(r,c);
            }

            int sizeMid = numCols - 6;
            c = 3 + (rand() % sizeMid);
            for (r = 0; r < numRows/2; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
                numWall++;
            }
            size_t topc = c;

            while (c == topc || c == topc-1 || c == topc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows-1; r > numRows/2; --r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);  
                numWall++;
            }
            size_t botc = c;

            while (c == topc || c == topc-1 || c == topc+1 || c == botc || c == botc-1 || c == botc+1) {
                c = 3 + (rand() % sizeMid);
            }
            for (r = numRows/4; r < 3*numRows/4; ++r) {
                delete board(r,c);
                board(r,c) = new Wall(r,c);
                numWall++;
            }

            for (int i = 0; i < numWater; i++) {
                r = rand() % numRows;
                c = rand() % (numCols-3)+3;
                while (board(r,c)->display() != ',') {
                    r = rand() % numRows;
                    c = rand() % (numCols-3)+3;
                }
                delete board(r,c);
                board(r,c) = new Water(r,c);
            }

            numGrass = numRows*numCols - numFire - numWater - numWall;
            
        }

        // important setters and getters
        void setNumFire(int num) {numFire = num;}
        void setNumWater(int num) {numWater = num;}
        void setNumWall(int num) {numWall = num;}
        void setNumGrass(int num) {numGrass = num;}
        void setNumEmpty(int num) {numEmpty = num;}
        int getNumFire() {return numFire;}
        int getNumWater() {return numWater;}
        int getNumWall() {return numWall;}
        int getNumGrass() {return numGrass;}
        int getNumEmpty() {return numEmpty;}
        size_t getNumRows() {return numRows;}
        size_t getNumCols() {return numCols;}

        // neatly displaying the game board, with cell counts 
		void displayBoard(bool printCounts) {
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            for (size_t row = 0; row < board.numrows(); row++) {
                cout << '|';
                for (size_t col = 0; col < board.numcols(row); col++) {
                    cout << board(row,col)->display();
                }
                cout << '|';
                cout << endl;
            }
            cout << '-';
            for (size_t col = 0; col < board.numcols(0); col++) {
                cout << '-';
            }
            cout << '-';
            cout << endl;
            
            if (printCounts) {
                cout << "# of Fire  * cells: " << numFire << endl;
                cout << "# of Water ~ cells: " << numWater << endl;
                cout << "# of Empty   cells: " << numEmpty << endl;
                cout << "# of Grass , cells: " << numGrass << endl;
                cout << "# of Wall  x cells: " << numWall << endl;
                cout << "# of ALL gridcells: " << numRows*numCols << endl;
            }
        }

        
        //---------------------------------------------------------------------------------
        //this function spreads fire to nearby grass cells and turns nearby water cells into empty cells
        //the direction of the fire depends on the windDir parameter, which has different effects
        //that can be found in the boardcell header file
        //if the fire runs into a wall or empty cell, it will look for another nearby valid spot to spread
        //---------------------------------------------------------------------------------
        void spreadFire(char windDir) {

            for(size_t i = 0; i < numRows; i++) {
                for(size_t j = 0; j < numCols; j++) {
                    if(board(i, j)->display() == '*') {
                        board(i, j)->setNewSpread(false);
                    }
                }
            }

            for(size_t i = 0; i < numRows; i++) {
                for(size_t j = 0; j < numCols; j++) {
                    char val;
                    val = board(i, j)->display();
                    if(val == '*') {
                        if(board(i, j)->getNewSpread()) {
                            continue;
                        }

                        board(i, j)->setWind(windDir);
                        size_t row = 0;
                        size_t col = 0;
                        board(i, j)->attemptSpreadTo(row, col);

                        try { //out of bounds row
                            if(row >= numRows) {
                                throw runtime_error("Attempting to spread to out-of-bounds row.");
                            }
                        }

                        //we will stay at the current row
                        catch(runtime_error& excpt) {
                            row = i;
                        }

                        try {  //out of bounds column
                            if(col >= numCols) {
                                throw runtime_error("Attempting to spread to out-of-bounds col.");
                            }
                        }

                        //we will stay at the current column
                        catch(runtime_error& excpt) {
                            col = j;
                        }

                        try { //collision with wall or empty cell
                            if(board(row, col)->display() == 'x') {
                                throw runtime_error("Attempting to spread Fire to wall cell.");
                            }

                            if(board(row, col)->display() == ' ') {
                                throw runtime_error("Attempting to spread Fire to empty cell.");
                            }
                        }
                        catch (runtime_error& excpt) {
                            //diagonal spreads are a little different

                            //first ensure that this is a wall or empty cell
                            if(board(row, col)->display() == 'x' || board(row, col)->display() == ' ') { 
                                if(row != i && col != j) {
                                    //move vertically instead of diagonally
                                    size_t newRow = row;
                                    size_t newCol = j;

                                    //if the new spot is still a wall or empty cell... just stay where u are
                                    if(board(newRow, newCol)->display() == 'x' || board(newRow, newCol)->display() == ' ') {
                                        row = i;
                                        col = j;
                                    } else {
                                        row = newRow;
                                        col = newCol;
                                    }
                                }
                            }
                        }

                        //if spread to grass cell
                        if(board(row, col)->display() == ',') {
                            delete board(row, col); //make sure to free memory
                            board(row, col) = new Fire(row, col);
                            board(row, col)->setNewSpread(true);
                            numFire++;
                            numGrass--;
                        }

                        //if spread to water cell
                        else if(board(row, col)->display() == '~') {
                            delete board(row, col); //make sure to free memory
                            board(row, col) = new Empty(row, col);
                            numEmpty++;
                            numWater--;
                        }

                    } // end if(val == '*')
                } // end for j
            } // end for i
        }


    //-------------------------------------------------------------------------------------
        //spreadWater is similar to spreadFire, except it is slightly easier in its implementation
        //this function will spread water to nearby empty cells and extinguish nearby fire cells
        //wall and grass cells will remain unaffected, but spreadWater will attempt to look for 
        //another valid spot near those cells, in the same way that spreadFire does
        //---------------------------------------------------------------------------------
        void spreadWater() {


            //make sure to set ALL new spreads to false, not just water cells
            for(size_t i = 0; i < numRows; i++) {
                for(size_t j = 0; j < numCols; j++) {
                        board(i, j)->setNewSpread(false);
                    
                }
            }

            for(size_t i = 0; i < numRows; i++) {
                for(size_t j = 0; j < numCols; j++) {
                    char val;
                    val = board(i, j)->display();
                    if(val == '~') {
                        if(board(i, j)->getNewSpread()) {
                            continue;
                        }

                        size_t row = 0;
                        size_t col = 0;
                        board(i, j)->attemptSpreadTo(row, col);

                        try { //out of bounds row
                            if(row >= numRows) {
                                throw runtime_error("Attempting to spread to out-of-bounds row.");
                            }
                        }

                        //we will stay at the current row
                        catch(runtime_error& excpt) {
                            row = i;
                        }

                        try { //out of bounds col
                            if(col >= numCols) {
                                throw runtime_error("Attempting to spread to out-of-bounds col.");
                            }
                        }

                        //we will stay at current column
                        catch(runtime_error& excpt) {
                            col = j;
                        }

                        try { //collision with wall or grass cell
                            if(board(row, col)->display() == 'x') {
                                throw runtime_error("Attempting to spread Water to wall cell.");
                            }

                            if(board(row, col)->display() == ',') {
                                throw runtime_error("Attempting to spread Water to grass cell.");
                            }
                        }
                        catch (runtime_error& excpt) {
                            //diagonal spreads are a little different
                            //first ensure that this is a wall or grass cell
                            if(board(row, col)->display() == 'x' || board(row, col)->display() == ',') { 
                                if(row != i && col != j) {
                                    //move vertically instead of diagonally
                                    size_t newRow = row;
                                    size_t newCol = j;

                                    //if the new spot is still a wall or grass cell... just stay where u are
                                    if(board(newRow, newCol)->display() == 'x' || board(newRow, newCol)->display() == ',') {
                                        row = i;
                                        col = j;
                                    } else {
                                        row = newRow;
                                        col = newCol;
                                    }
                                }
                            }
                        }

                        //if spread to empty cell
                        if(board(row, col)->display() == ' ' && !board(row, col)->getNewSpread()) {
                            //cout << "Trying to spread Water from (" << i << "," << j << ") to (" << row << "," << col << ")" << endl;
                            delete board(row, col); //make sure to free memory
                            board(row, col) = new Water(row, col);
                            board(row, col)->setNewSpread(true);
                            numWater++;
                            numEmpty--;
                        }

                        //if spread to fire cell
                        else if(board(row, col)->display() == '*' && !board(row, col)->getNewSpread()) {
                            //cout << "Trying to spread Water from (" << i << "," << j << ") to (" << row << "," << col << ")" << endl;
                            delete board(row, col); //make sure to free memory
                            board(row, col) = new Empty(row, col);
                            board(row, col)->setNewSpread(true);
                            numFire--;
                            numEmpty++;
                        }

                    } // end if(val == '*')
                } // end for j
            } // end for i
            // Sample code to assign a specific cell a Water type
            //board(1, 2) = new Water(1,2);
            
        }
        
    
};

#endif //_GAMEBOARD_H