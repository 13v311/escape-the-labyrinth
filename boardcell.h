// boardcell.h
//
// BoardCell class starter code for course project
// University of Illinois at Chicago
// CS 211 - Programming Practicum
// Original Author: Professor Scott Reckinger
//

#ifndef _BOARDCELL_H
#define _BOARDCELL_H

using namespace std;

// First, the BoardCell abstract base class 

class BoardCell {
	
    public:  
		BoardCell() {} // default contstructor (do nothing)
        virtual ~BoardCell() {} // destructor (do nothing)
        
        virtual char display( ) = 0; // pure virtual function; this is an abstract base class

    	virtual void attemptSpreadTo(size_t& newR, size_t& newC) {
            
            //------------------------------------------------------------
            //uses the default action which is to stay put 
            //------------------------------------------------------------
            
            newR = myRow; 
            newC = myCol; 
            
        }
        
        virtual void setWind(char inChar ) {}

        void setRow(size_t r) {myRow = r;}
        size_t getRow() {return myRow;}
        void setCol(size_t c) {myCol = c;}
        size_t getCol() {return myCol;}
        void setPos(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        void setNewSpread(bool u) {newSpread = u;}
        bool getNewSpread() {return newSpread;}

    private:
        size_t myRow; // current row for this board cell in a 2D grid
        size_t myCol; // current column for this board cell in a 2D grid
        
        // newSpread: should be defaulted to false; only true IF this board cell was
        //            updated as a result of a previous spread in the current round;
        bool newSpread; 
}; // BoardCell (abstract base class)


// Then, all the derived classes

class Fire: public BoardCell {
	public:
    	Fire(size_t r, size_t c) {
            setRow(r);
            setCol(c);
            windDir = 's';
        }
        
        virtual char display( ) {
            return '*';
        }
        
        virtual void setWind(char inChar ) {
            windDir = inChar;
        }
    	
        //this function uses the windDir to determine what newR and newC will be, which represent the
        //new row and column value. this function only attempts a spread, but it does not check for 
        //collisions, so if one of the parameters are out-of-bounds, that would need to be verified
        //by a function outside of this class (gameboard!)
        virtual void attemptSpreadTo(size_t& newR, size_t& newC) {
            
            if(windDir == 'q') {
                newR = getRow() - 1;
                newC = getCol() - 1;
            } else if (windDir == 'a') {
                newR = getRow();
                newC = getCol() - 1;
            } else if (windDir == 'z') {
                newR = getRow() + 1;
                newC = getCol() - 1;
            } else if (windDir == 'w') {
                newR = getRow() - 1;
                newC = getCol();
            } else if (windDir == 'x') {
                newR = getRow() + 1;
                newC = getCol();
            } else if (windDir == 'c') {
                newR = getRow() + 1;
                newC = getCol() + 1;
            } else if (windDir == 'd') {
                newR = getRow();
                newC = getCol() + 1;
            } else if (windDir == 'e') {
                newR = getRow() - 1;
                newC = getCol() + 1;
            } else {
                newR = getRow();
                newC = getCol();
            }
        }

    private:
        char windDir;

}; // Fire cell

class Water: public BoardCell {
    public:
		Water(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display( ) {
            return '~';
        }
        
        //similar to attemptSpreadTo for the Fire class, this function will only attempt a spread
        //in contrast, it does not use the windDir, but instead uses rand() to spread using one of
        //three options: -1, 0, +1 from its original spot
    	virtual void attemptSpreadTo(size_t& newR,size_t& newC) {
            
            newR = getRow() + (rand() % 3 - 1);
            newC = getCol() + (rand() % 3 - 1); // modify/remove this line
        }    	

}; // Water cell

class Grass: public BoardCell {
	public:
    	Grass(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display( ) {
            return ',';
        }

}; // Grass cell

class Wall: public BoardCell {
	public:
    	Wall(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display( ) {
            return 'x';
        }

}; // Wall cell

class Empty: public BoardCell {
	public:
    	Empty(size_t r, size_t c) {
            setRow(r);
            setCol(c);
        }

        virtual char display( ) {
            return ' ';
        }

}; // Empty cell

#endif //_BOARDCELL_H
