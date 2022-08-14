#include "Grid.h"
#include "Types.h"
#include "Character.h"
#include <iostream>

Grid::Grid(int Lines, int Columns)
{
    printf("The battle field has been created\n\n");
    drawBattlefield(Lines, Columns);
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
    xLength = Lines;
    yLength = Columns;

    grids.clear();

    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox();
            newBox->Index = (Columns * i + j);
            newBox->xIndex = i;
            newBox->yIndex = j;

            grids.insert(grids.end(), newBox);
        }
    }

    //updateBattlefield();
}

void Grid::updateBattlefield()
{
    system("cls");

    for (int i = 0; i < xLength; i++)
    {
        for (int j = 0; j < yLength; j++)
        {
            for (Types::GridBox* currentGrid : grids)
            {
                if (currentGrid->xIndex == i && currentGrid->yIndex == j)
                {
                    if (currentGrid->CharacterReference)
                    {
                        cout << "[" << currentGrid->CharacterReference->Icon << "]  ";
                    }
                    else
                    {
                        cout << ("[ ]  ");
                    }
                }
            }
        }
        printf("\n\n");
    }
    printf("\n\n");
}

void Grid::UpdateGridBox(Types::GridBox* gridBoxToUpdate, bool isOccupied)
{
    for (Types::GridBox* currentGrid : grids)
    {
        if (currentGrid == gridBoxToUpdate)
        {

        }
    }
}
