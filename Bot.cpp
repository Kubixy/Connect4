#include "Bot.h"

int beginnerBot(Board &t, int &column)
{
    int output = -1;

    while (output < 0)
    {
        column = rand() % t.columns;
        output = insertCard('X', column, t);
    }

    return output;
}

int nextMovementBot(Board &t, bool axis, int row, int column)
{
    int output = -1;

    if (axis && (column + 1 < t.columns && t.info[row][column + 1] == ' '))
        output = column + 1;
    else if (axis && (column - 4 > 0 && t.info[row][column - 4] == ' '))
        output = column - 4;
    else if (!axis && (((row - 4) > 0) && t.info[row - 4][column] == ' '))
        output = column;

    return output;
}

int advancedBot(Board &t, int &column)
{
    int output, tmp = 0, col = 0,
            player_target = -1, bot_target = 0,
            player_count = 0, bot_count = -1,
            j, i;

    for (i = 0; i < t.rows && player_target == -1; i++)
    {
        for (j = 0; j < t.columns && player_count != 3; j++)
        {
            if (t.info[i][j] == 'O')
                player_count++;
            else
                player_count = 0;

            if (t.info[i][j] == 'X')
                bot_count++;
            else if (t.info[i][j] == ' ' && bot_count >= tmp)
            {
                bot_target = j - 1 < t.columns - 1 ? j - 1 : 0;
                tmp = bot_target;
                bot_count = 0;
            }
            else
                bot_count = 0;
        }

        if (player_count == 3)
            player_target = nextMovementBot(t, true, i, j - 1);

        player_count = 0;
    }

    player_count = 0;
    bot_count = 0;
    tmp = 0;

    while (col < t.columns && player_target == -1)
    {
        for (i = 0; i < t.rows && player_count != 3; i++)
        {
            if (t.info[i][col] == 'O')
                player_count++;
            else
                player_count = 0;

            if (t.info[i][col] == 'X')
                bot_count++;
            else if (t.info[i][col] == ' ' && bot_count >= tmp)
            {
                bot_target = col < t.columns - 1 ? col : 0;
                tmp = bot_target;
                bot_count = 0;
            }
            else
                bot_count = 0;
        }

        if (player_count == 3)
            player_target = nextMovementBot(t, false, i - 1, col);

        player_count = 0;
        col++;
    }

    cout << player_target << endl;

    if (player_target != -1)
    {
        output = insertCard('X', player_target, t);
        column = player_target;
    }
    else
    {
        output = insertCard('X', bot_target, t);
        column = bot_target;
    }

    return output;
}