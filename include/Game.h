#pragma once
#include <vector>
#include <string>

#include "Draw.h"
#include "Fruit.h"
#include "Audio.h"
#include "Points.h"
// #include "UniformRandomInt.h"

using namespace std;

class Points;
class Draw;

class Game
{
public:
    Game();

    int start();

    char menu();

    char chooseMusic();

    void showHighScore();

private:
    Points* points;
    Draw* draw;
    Audio audio;
    string chosenMusic;
    string sequenceFile;
};