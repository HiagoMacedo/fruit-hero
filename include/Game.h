#pragma once
#include <vector>
#include <string>
#include "Draw.h"
#include "Fruit.h"
#include "UniformRandomInt.h"
#include "Audio.h"

using namespace std;

class Draw;

class Game
{
public:
    Game();

    int start();

    char menu();

    char chooseMusic();

    vector<string> getHighScore(); 

    void updateHighScore(Draw *draw);

    void showHighScore();

private:
    vector<string> highScore;
    Draw *draw;
    Audio audio;
    string chosenMusic;
    string sequenceFile;
};