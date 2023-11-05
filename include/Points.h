#pragma once
#include <vector>
#include <string>

#include "Fruit.h"
#include "Draw.h"
#include "Gerenciador.h"


class Points
{
public:
    Points();
    ~Points();

    void incrementPoints(int val = 1);
    
    int getPoints();

    void setPoints(int p);

    std::vector<std::string> getHighScore(); 

    void updateHighScore(std::string chosenMusic);

private:
    int points;
    std::vector<std::string> highScore;
    Gerenciador gerenciador;
};