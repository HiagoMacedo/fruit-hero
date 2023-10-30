#include "Game.h"
#include <iostream>
#include <string>
#include <filesystem>
#include "Gerenciador.h"
#include "../error/FileNotOpenedException.h"
#include "../error/MusicNotLoadedException.h"

#ifdef WIN32
#define CLEAR_TERMINAL "cls"
#else
#define CLEAR_TERMINAL "clear"
#endif

const int VOLUME = 80;

using namespace cv;
using namespace std;

Game::Game() {
    filesystem::path path = filesystem::current_path() / "high_score.txt";;  
    gerenciador = new Gerenciador(path.string());
}

int Game::start() {
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;
    std::string cascadeName("haarcascade_frontalface_default.xml");
    
    draw = new Draw(sequenceFile);
    audio.init();
    try{
        audio.loadFiles(chosenMusic);
    }
    catch (MusicNotLoadedException e) {
        cout << e.what() << endl;
    }
    // audio.setVolume(VOLUME);

    scale = 1; // usar 1, 2, 4.
    if (scale < 1)
        scale = 1;
    tryflip = true;

    if (!cascade.load(cascadeName)) {
        cerr << "ERROR: Could not load classifier cascade: " << cascadeName << endl;
        return -1;
    }

    // if(!capture.open("video.mp4")) // para testar com um video
    if(!capture.open(0)) // para testar com a webcam
    {
        cout << "Capture from camera #0 didn't work" << endl;
        return 1;
    }

    if( capture.isOpened() ) {
        // cout << "Video capturing has been started ..." << endl;
        cout << "Game has been started..." << endl;

        audio.setVolume(VOLUME);
        audio.playMusic();
        while (audio.playingMusic())
        {
            capture >> frame;
            if( frame.empty() )
                break;
            
            draw->detectAndDraw( frame, cascade, scale, tryflip, audio );

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' ) {
                break;
            }
        }
        audio.quit();
        cout << "Final Points: " << draw->getPoints() << endl;
        cout << "Press enter to continue\n" ;
        getchar();
        getchar();
        updateHighScore(draw);
    }
    delete(draw);
    system(CLEAR_TERMINAL);
    return 0;
}

char Game::menu() {
    char option;
    cout << "----------------------------------------\n";
    cout << "\t\tFRUIT HERO\n";
    cout << "________________________________________\n";
    cout << " Menu\n";
    cout << "________________________________________\n";
    cout << "1. Start Game\n";
    cout << "2. High Score\n";
    cout << "3. Exit\n";
    cout << "----------------------------------------\n";
    cin >> option;
    system(CLEAR_TERMINAL);
    return option;
    
}

char Game::chooseMusic() {
    char option;
    cout << "----------------------------------------\n";
    cout << "\t\tFRUIT HERO\n";
    cout << "________________________________________\n";
    cout << " Choose Music\n";
    cout << "________________________________________\n";
    cout << "1. Titanium\n";
    cout << "2. Drive Breakbeat\n";
    cout << "3. Go back to Menu\n";
    cout << "----------------------------------------\n";
    cin >> option;
    if (option == '1') {
        chosenMusic = "titanium.mp3";
        sequenceFile = "titanium_sequence.txt";
    }
    else if (option == '2') {
        chosenMusic = "drive_breakbeat.mp3"; 
        sequenceFile = "drive_breakbeat_sequence.txt";
    }
    else {
        option = '3';
    }
    system(CLEAR_TERMINAL);
    return option;
}

vector<string> Game::getHighScore() {
    // filesystem::path cwd = filesystem::current_path() / "high_score.txt";
    // Gerenciador gerenciador(cwd.string());
    
    try {
        highScore = gerenciador->read();
    }
    catch (FileNotOpenedException e) {
        cout << e.what() << endl;
    }
    
    return highScore;
}

void Game::updateHighScore(Draw *draw) {
    // filesystem::path cwd = filesystem::current_path() / "high_score.txt";
    // Gerenciador gerenciador(cwd.string());
    vector<string> newScore;
    string name;

    try {
        highScore = gerenciador->read();
        if (draw->getPoints() > stoi(highScore[1])) {
            cout << "Congratulations you have the new high score!" << endl;
            cout << "Type your nome:" << endl;
            // cin.ignore();
            getline(cin, name);
            newScore.push_back(name);
            newScore.push_back(to_string(draw->getPoints()));
            gerenciador->create(newScore);
        }
    }
    catch (FileNotOpenedException e) {
        cout << e.what() << endl;
    }
}

void Game::showHighScore() {
    cout << "----------------------------------------\n";
    cout << "\t\tFRUIT HERO\n";
    cout << "________________________________________\n";
    cout << " High Score\n";
    cout << "________________________________________\n";
    getHighScore();
    cout << "1. " << highScore[0] << " - " << highScore[1] << endl;
    cout << "----------------------------------------\n";
    cout << "Press enter to continue";
    getchar();
    getchar();
    system(CLEAR_TERMINAL);
}

// void Game::incrementPoints(int val) {
//     points += val;
// }

// int Game::getPoints() {
//     return points;
// }

// void Game::updatePoints(Fruit& f, UniformRandomInt& ur) {
//     Draw d;
//     points++;
//     f.setY(0);
//     d.setCurrentLane(ur.get());
// }

// bool Game::updatePoints(Fruit f) {
    
//     incrementPoints(1);
//     f.setY(0);
    
//     currentLane = randomNumGen.get();
//     return true;
//     return false;
// }