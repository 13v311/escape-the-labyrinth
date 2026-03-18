#include <utility>
#include <random>
#include <set>
#include "grid.h"
#include "maze.h"
using namespace std;

/* Change constant kYourNetID to store your netID 
 *    - your submission will be manually inspected to ensure
 *      you have used the exact string that is your netID
 *    - thus, it is vital you understand what your netID is
 *    - ex: Professor Reckinger's email is scotreck@uic.edu, so
 *          Professor Reckinger's netID is scotreck         
 *    - ex: Student Sparky's email is sspark211@uic.edu, so
 *          Student Sparky's netID is sspark211 
 * WARNING: Once you've set set this constant and started 
 * exploring your maze, do NOT edit the value of kYourNetID. 
 * Changing kYourNetID will change which maze you get back, 
 * which might invalidate all your hard work!
 */
const string kYourNetID = "lkens";

/* Change these constants to contain the paths out of your mazes. */
const string kPathOutOfRegularMaze = "WSNEESSWWEEENN";
const string kPathOutOfTwistyMaze = "SWEWWSNNW";

bool isPathToFreedom(MazeCell *start, const string& moves) {
    

     bool potion = false;
     bool spellbook = false;
     bool wand = false;
     for(size_t i = 0; i < moves.length(); i++) {
        if(start->whatsHere == "Potion") {
            potion = true;
        }
        if(start->whatsHere == "Spellbook") {
            spellbook = true;
        }
        if(start->whatsHere == "Wand") {
            wand = true;
        }

        if(moves[i] == 'N') {
            start = start->north;
        } else if(moves[i] == 'S') {
            start = start->south;
        } else if(moves[i] == 'W') {
            start = start->west;
        } else if(moves[i] == 'E') {
            start = start->east;
        } else { //didnt go north, south, east, or west
            return false;
        }
        if(start == nullptr) {return false;}
        if(start->whatsHere == "Potion") {
            potion = true;
        }
        if(start->whatsHere == "Spellbook") {
            spellbook = true;
        }
        if(start->whatsHere == "Wand") {
            wand = true;
        }
     }

     if(spellbook && potion && wand) {return true;}
    return false;
    
    
    
}
