#include <iostream>
#include <filesystem>

#include "Points.h"
#include "../error/FileNotOpenedException.h"

Points::Points() {
    std::filesystem::path path = std::filesystem::current_path() / "high_score.txt";  
    gerenciador.setPath(path.string());
    points = 0;
}

void Points::incrementPoints(int val) {
    points += val;
}

int Points::getPoints() {
    return points;
}

void Points::setPoints(int p) {
    points = p;
}

std::vector<std::string> Points::getHighScore() {
    try {
        highScore = gerenciador.read();
    } 
    catch (FileNotOpenedException e) {
        cout << e.what() << endl;
    }
    
    return highScore;
}

void Points::updateHighScore(std::string chosenMusic) {
    std::vector<std::string> newScore;
    std::string name;
    std::string music;

    try {
        newScore = getHighScore();
        for (int i = 0; i < newScore.size(); i+=3) {
            if (newScore[i] == chosenMusic && points > stoi(newScore[i+2]) ) {
                std::cout << "Congratulations you have the new high score!" << std::endl;
                std::cout << "Type your name:" << std::endl;
                getline(cin, name);
                newScore[i+1] = name;
                newScore[i+2] = to_string(points);
                
            }
        }
        gerenciador.create(newScore);
    }
    catch (FileNotOpenedException e) {
        std::cout << e.what() << std::endl;
    }
}
