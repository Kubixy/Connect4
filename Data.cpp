//
// Created by a on 22/07/2021.
//

#include "Data.h"

int insertCard(char card, int column, Board &t)
{
    int rowIndex = 1;
    t.moves++;

    if (column >= 0)
    {
        while (rowIndex <= t.rows)
        {
            if (t.info[t.rows - rowIndex][column] == ' ')
            {
                t.info[t.rows - rowIndex][column] = card;
                return t.rows - rowIndex;
            }
            rowIndex++;
        }
    }

    return -1;
}