#pragma once
#include <Vector>
#include "Types.h"

using namespace std;

class Grid
{

public:

    Grid(int Lines, int Columns);
    ~Grid();

    vector<Types::GridBox*> grids;

    int xLength;
    int yLength;
    
    // prints the matrix that indicates the tiles of the battlefield
    void drawBattlefield(int Lines, int Columns);
    
    // Updates the grid from the battlefield
    void updateBattlefield();

    void UpdateGridBox(Types::GridBox* gridBoxToUpdate, bool isOccupied);
};

