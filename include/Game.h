#pragma once
#include <vector>
#include <string>
#include "Draw.h"
#include "Fruit.h"
#include "Gerenciador.h"
#include "Audio.h"
// #include "UniformRandomInt.h"

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

    void updateHighScore();

    // void updateHighScore(Draw *draw);

    void showHighScore();

private:
    vector<string> highScore;
    Draw* draw;
    Audio audio;
    Gerenciador* gerenciador;
    string chosenMusic;
    string sequenceFile;
};