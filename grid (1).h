/*-------------------------------------------
    Program 5: Follow the Links, Escape the Labyrinth Part 1
    This project allows the user to simulate a maze that they have to
    escape from utilizing gdb and pointers. Specifically the maze
    is unique to the user based on their netID, and there are two 
    types of mazes. The first is a regular maze which features pointers 
    to north, east, south, and west in a normal grid shape. The maze 
    itself retains this shape through the use of a Grid class. The 
    second is a twisty maze, where directions don't lead to normal 
    boxes, i.e., north could go west, so the user must pay attention
    to the memory addresses. To escape this maze, the user needs to
    pick up three items: a potion, a spellbook, and a wand.

Course: CS 211, Spring 2025, UIC
Author: Levell Kensey
------------------------------------------- */
#pragma once

#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class Grid {
private:
    struct CELL {
        CELL* Next;
        T Val;
        size_t NumCols;  // total # of columns (0..NumCols-1)
        CELL(CELL* _Next = nullptr, T _Val = T(), size_t _NumCols = 0) {
            Next = _Next;
            Val = _Val;
            NumCols = _NumCols;
        }
    };
    
    size_t NumRows;  // total # of rows (0..NumRows-1)
    CELL** Rows;     // C array of linked lists
public:
    //
    // default constructor:
    //
    // Called automatically by C++ to construct a 4x4 Grid.  All
    // elements are initialized to the default value of T.
    //
    Grid() {
        // initialize 4 rows
        Rows = new CELL*[4];
        NumRows = 4;
        
        // allocate the first cell of the linked list with default value:
        for (size_t r = 0; r < NumRows; ++r) {
            Rows[r] = new CELL(nullptr, T(), 4);
            CELL* cur = Rows[r];
            
            // create the linked list for this row.
            for(size_t c = 1; c < Rows[r]->NumCols; ++c) {
                cur->Next = new CELL(nullptr, T());
                cur = cur->Next;
            }
        }
        
    }
    
    //
    // parameterized constructor:
    //
    // Called automatically by C++ to construct a Grid with R rows,
    // where each row has C columns. All elements are initialized to
    // the default value of T.
    //
    Grid(size_t R, size_t C) {

        //avoid invalid parameters
            if (R == 0 || C == 0 || R > static_cast<size_t>(10000) || C > static_cast<size_t>(10000)) {
        throw invalid_argument("Grid must have positive dimensions."); 
    }
    

        Rows = new CELL*[R];
        NumRows = R;

        for(size_t i = 0; i < NumRows; i++) {
            Rows[i] = new CELL(nullptr, T(), C);
            CELL* curr = Rows[i];

            for(size_t j = 1; j < Rows[i]->NumCols; j++) {
                curr->Next = new CELL(nullptr, T());
                curr = curr->Next; 
            }
        }
    }
    
    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the vector.
    //
    virtual ~Grid() {
        
        for(size_t i = 0; i < NumRows; i++) {
            CELL* temp = Rows[i];
            while(temp != nullptr) {
                CELL* nextNode = temp->Next; //save the pointer to next
                delete temp;  
                temp = nextNode; //temp now points to its next before deletion
            }
        }
        delete[] Rows;
    }
    
    
    //
    // copy constructor:
    //
    // Called automatically by C++ to construct a Grid that contains a
    // copy of an existing Grid.  Example: this occurs when passing
    // Grid as a parameter by value
    //
    //   void somefunction(Grid<int> G2)  <--- G2 is a copy:
    //   { ... }
    //
    Grid(const Grid<T>& other) {
      
      if(other.NumRows == 0) { //just make an empty grid if other is empty
        this->NumRows = other.NumRows;
        this->Rows = new CELL*[NumRows];
        for(size_t i = 0; i < NumRows; i++) {
            Rows[i] = nullptr;
        }
        return;
      }

        //otherwise, make a grid with same size and data as other's
      this->NumRows = other.NumRows;
      this->Rows = new CELL*[NumRows];

      for(size_t i = 0; i < NumRows; i++) {
        Rows[i] = new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
        CELL* curr = Rows[i];
        CELL* othercurr = other.Rows[i]->Next;
        while(othercurr != nullptr) {
            //make sure to allocated new memory so that we avoid double-free
            curr->Next = new CELL(nullptr, othercurr->Val);
            curr = curr->Next;
            othercurr = othercurr->Next;
        } 
      }
    }
    
    //
    // copy operator=
    //
    // Called when you assign one vector into another, i.e. this = other;
    //
    Grid& operator=(const Grid& other) {

        if (this == &other) {return *this;} //protect against self-assignment

        //clear the current data
        for(size_t i = 0; i < NumRows; i++) {
            CELL* temp = Rows[i];
            while(temp != nullptr) {
                CELL* nextNode = temp->Next;
                delete temp;
                temp = nextNode;
            }
        }
        delete[] Rows;

        //initialize Rows
        this->NumRows = other.NumRows;
        Rows = new CELL*[NumRows];
        for(size_t i = 0; i < NumRows; i++) {
            Rows[i] = nullptr;
        }

        for(size_t i = 0; i < NumRows; i++) {

            if(other.Rows[i] == nullptr) {continue;}
            Rows[i] = new CELL(nullptr, other.Rows[i]->Val, other.Rows[i]->NumCols);
            CELL* curr = Rows[i];
            CELL* othercurr = other.Rows[i]->Next;

            while(othercurr != nullptr) {
                //make sure to allocate new memory to avoid double-free
                curr->Next = new CELL(nullptr, othercurr->Val);
                othercurr = othercurr->Next;
                curr = curr->Next;
            }
        }
        return *this; 
    }
    

    // returns the # of rows in the Grid. 

    size_t numrows() const {
       return NumRows;
    }
    
    

    // returns the # of columns in row r.  columns are only listed in the 
    //beginning of the row 
    size_t numcols(size_t r) const {
        if(Rows == nullptr || r >= NumRows) {
            throw invalid_argument("Invalid number of rows.");
        }
        return Rows[r]->NumCols;
        
    }
    
    

    // returns the total # of elements in the grid.
    size_t size() const {
        size_t total = 0;
        if(Rows == nullptr) {return 0;}
        for(int i = 0; i < NumRows; i++) {
            for(int j = 0; j < Rows[i]->NumCols; j++) {
                total++;
            }
        }
        return total; 
    }
    
    
    
    // returns a reference to the element at location (r, c); this
    // allows you to access the element by returning or change it using '=':

T& operator()(size_t r, size_t c) {
    if (Rows == nullptr || r >= NumRows) {
        throw invalid_argument("Invalid row index.");
    }

    CELL* result = Rows[r];

    for (size_t j = 0; j < c; j++) {
        if (result == nullptr) {
            throw invalid_argument("Invalid column index.");
        }
        result = result->Next;
    }

    if (result == nullptr) {
        throw invalid_argument("Invalid column index.");
    }

    return result->Val;
}

    
    //
    // _output
    //
    // Outputs the contents of the grid; for debugging purposes.  This is not
    // tested.
    //
    void _output() {
        
        //-------------------------------------------------
        // TODO:  Write this function.
        //-------------------------------------------------
        
    }
    
};
