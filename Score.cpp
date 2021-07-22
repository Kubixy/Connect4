#include "Score.h"

void writeScores(Board &t)
{
    ofstream output_file;
    output_file.open(FILE_NAME);

    for (int i = 0; i < t.total_score; i++)
    {
        output_file << t.scores[i].name << endl;
        output_file << t.scores[i].score << endl;
    }

    output_file.close();
}

void sortScores(Board &t)
{
    int i, j;
    int n = t.total_score;

    for (i = n - 2; i >= 0; i--)
    {
        t.scores[n] = t.scores[i];
        j = i + 1;

        while (stoi(t.scores[j].score) >= stoi(t.scores[n].score) && j < n)
        {
            t.scores[j - 1] = t.scores[j];
            j++;
        }
        t.scores[j - 1] = t.scores[n];
    }

    return;
}

void showScores(Board &t)
{
    cout << "Top 10 players" << endl;
    for (int i = 0; i < t.total_score; i++)
    {
        cout << i + 1 << ". " + t.scores[i].score + " / ";
        cout << t.scores[i].name << endl;
    }
    cout << endl;
}

void readScores(Board &t)
{
    ifstream file_in;
    int index = 0;
    string name = "", score = "";

    file_in.open(FILE_NAME);

    if (file_in)
    {
        while (getline(file_in, name) && index < 10)
        {
            getline(file_in, score);
            if (name != "" || score != "")
            {
                t.scores[index].name = name;
                t.scores[index].score = score;
                index++;
            }

        }
    }
    else
        cout << "There is no score file" << endl;

    t.total_score = index;
    file_in.close();
}