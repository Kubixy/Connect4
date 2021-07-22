#ifndef UNTITLED_DATA_H
#define UNTITLED_DATA_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int MAX = 10;
const int MAX_GAMES = 100;
const string FILE_NAME = "Connect4.game";

typedef char Matrix[MAX][MAX];

struct Score
{
    string name;
    string score;
};

typedef Score MatrixScore[MAX_GAMES];

struct Board
{
    int rows, columns, moves, dificulty;
    Matrix info;
    MatrixScore scores;
    int total_score;
};


int insertCard(char, int, Board &);

#endif
