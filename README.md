
  # Follow the Links, Escape the Labyrinth Part 1
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

  # Part 2: Fire vs. Water
    In this part of the project, the user is able to play a different game from the one
    introduced in part one, where they will be presented with a grid that has different
    cells, each with unique attributes. There are fire, water, grass, wall, and empty cells.
    The fire and water cells can spread to nearby cells depending on their attributes. while
    the fire cell can spread to grass cells and put out water cells, the water cell can spread
    to empty cells and put out fire cells. The goal of this game is for the user to spread as many
    fire cells as possible before the fire is completely doused by water cells. This project not only
    utilizes this grid class, but the boardcell class which defines each type of cell, and the gameboard
    class which utilizes both boardcells to create the gameboard and spread cells to other cells.
