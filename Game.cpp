#include "Game.h"

bool fourInLine(Board &t, char card, int column, int row)
{
    int rowSuccess = 0, columnSuccess = 0;
    bool output = false;

    for (int i = 0; i < t.columns && !output; i++)
    {
        if (t.info[row][i] == card)
        {
            if (++columnSuccess == 4)
                output = true;
        }
        else
            columnSuccess = 0;
    }

    for (int i = 0; i < t.rows && !output; i++)
    {
        if (t.info[i][column] == card)
        {
            if (++rowSuccess == 4)
                output = true;
        }
        else
            rowSuccess = 0;
    }

    if (firstDiagonal(t, card, column, row))
        output = true;

    if (secondDiagonal(t, card, column, row))
        output = true;

    return output;
}

bool firstDiagonal(Board &t, char card, int column, int row)
{
    int success = 1, index = column - 1;
    bool output = false;

    for (int i = row + 1; i < t.rows + 1 && 0 <= index && !output; i++)
    {
        if (t.info[i][index] == card)
        {
            if (++success == 4)
                output = true;
        }
        else
        {
            break;
        }
        index--;
    }

    index = column + 1;

    for (int i = row - 1; i >= 0 && index < t.columns && !output; i--)
    {
        if (t.info[i][index] == card)
        {
            if (++success == 4)
                output = true;
        }
        else
        {
            break;
        }
        index++;
    }

    return output;
}

bool secondDiagonal(Board &t, char card, int column, int row)
{
    int success = 1, index = column - 1;
    bool output = false;

    for (int i = row - 1; i >= 0 && index >= 0; i--)
    {
        if (t.info[i][index] == card)
        {
            if (++success == 4)
                output = true;
        }
        else
        {
            break;
        }
        index--;
    }

    index = column + 1;

    for (int i = row + 1; i < t.rows && index < t.columns; i++)
    {
        if (t.info[i][index] == card)
        {
            if (++success == 4)
                output = true;
        }
        else
        {
            break;
        }
        index++;
    }

    return output;
}

bool tieResult(Board &t)
{
    bool output = false;

    for (int i = 0; i < t.columns && !output; i++)
        output = t.info[0][i] == ' ';

    return output;
}