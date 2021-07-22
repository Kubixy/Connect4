#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "Bot.h"
#include "Score.h"

void showBoard(Board);
void fillMatrix(Board &);
void getInput(Board &);
void saveGame(Board &, string);
bool readGame(Board &, string);

int main(void)
{
    Board t;
    int column = 0, row, opt;
    bool turn = true, win = false, game_is_saved = false, tie;
    string name, file_name;

    cout << "Introduce nick: ";
    cin >> name;
    cout << endl;

    readScores(t);
    sortScores(t);
    showScores(t);

    cout << "Resume saved game or create new one? (0/1): ";
    cin >> opt;

    if (opt == 0)
    {
        cout << "Introduce file name: ";
        cin >> file_name;
        game_is_saved = readGame(t, file_name);
    }

    while (column != -1)
    {
        if (!game_is_saved)
            getInput(t);
        else
        {
            system("cls");
            showBoard(t);
            game_is_saved = false;
        }

        do
        {
            if (turn)
            {
                do
                {
                    cout << "Introduce column: ";
                    cin >> column;
                } while (column < -1 || column >= t.columns);

                row = insertCard('O', column, t);
            }
            else
                row = t.dificulty == 1 ? beginnerBot(t, column) : advancedBot(t, column);

            if (column != -1)
            {
                win = fourInLine(t, turn ? 'O' : 'X', column, row);
                tie = tieResult(t);

                system("cls");
                showBoard(t);
                turn = !turn;
            }
        } while (!win && column != -1 && tie);

        if (win && !turn && column != -1)
        {
            cout << name + " wins" << endl
                 << endl;

            if (t.total_score < MAX_GAMES)
            {
                t.scores[t.total_score].name = name;
                t.scores[t.total_score].score = to_string((10 * t.rows * t.columns - t.moves * 2) * t.dificulty);
                t.total_score += 1;
            }
            else
            {
                cout << "Limit of games reached" << endl;
            }

            writeScores(t);
        }
        else if (win && turn && column != -1)
        {
            cout << "Bot wins" << endl
                 << endl;
        }
        else if (tie && column != -1)
        {
            cout << "Tie!" << endl
                 << endl;
        }

        if (column != -1)
        {
            cout << "Enter any number to start a new game (-1 exit): ";
            cin >> column;
            turn = true;
            system("cls");
        }
    }

    if (!win)
    {
        cout << "\nPick a file name to save your game: ";
        cin >> file_name;
        saveGame(t, file_name);
    }

    return 0;
}

bool readGame(Board &t, string name)
{
    bool output = false;
    ifstream rf(name + ".game", ios::out | ios::binary);

    if (rf)
    {
        rf.read((char *)&t.info, sizeof(Matrix));
        rf.read((char *)&t.rows, sizeof(int));
        rf.read((char *)&t.columns, sizeof(int));
        rf.read((char *)&t.moves, sizeof(int));
        rf.read((char *)&t.dificulty, sizeof(int));
        rf.read((char *)&t.total_score, sizeof(int));
        output = true;
    }
    else
    {
        cout << "File not found" << endl;
    }

    return output;
}

void saveGame(Board &t, string name)
{
    ofstream wf(name + ".game", ios::out | ios::binary);

    if (wf)
    {
        wf.write((char *)&t.info, sizeof(Matrix));
        wf.write((char *)&t.rows, sizeof(int));
        wf.write((char *)&t.columns, sizeof(int));
        wf.write((char *)&t.moves, sizeof(int));
        wf.write((char *)&t.dificulty, sizeof(int));
        wf.write((char *)&t.total_score, sizeof(int));
    }
    else
    {
        cout << "Error saving the game" << endl;
    }

    wf.close();
}

void getInput(Board &t)
{
    do
    {
        cout << "Difficulty beginner/advanced (1/2): ";
        cin >> t.dificulty;
    } while (t.dificulty < 1 || t.dificulty > 2);

    do
    {
        cout << "Introduce wide (6-10): ";
        cin >> t.rows;
    } while (t.rows < 6 || t.rows > 10);

    do
    {
        cout << "Introduce height (6-10): ";
        cin >> t.columns;
    } while (t.columns < 6 || t.columns > 10);

    t.moves = 0;
    fillMatrix(t);
    srand(time(NULL));
    system("cls");
    showBoard(t);
}

void fillMatrix(Board &t)
{
    for (int i = 0; i < t.rows; i++)
        for (int j = 0; j < t.columns; j++)
            t.info[i][j] = ' ';
}

void showBoard(Board t)
{
    int i, j;

    cout << "  ";

    for (i = 0; i < t.columns; i++)
        cout << i;
    cout << endl;

    cout << " ";

    for (i = 1; i < t.columns + 3; i++)
        cout << "-";
    cout << endl;

    for (i = 0; i < t.rows; i++)
    {
        cout << i << "|";
        for (j = 0; j < t.columns; j++)
            cout << t.info[i][j];
        cout << "|" << endl;
    }

    cout << " ";
    for (i = 1; i < t.columns + 3; i++)
        cout << "-";
    cout << endl;

    cout << "  ";

    for (i = 0; i < t.columns; i++)
        cout << i;
    cout << endl
         << endl;

    return;
}