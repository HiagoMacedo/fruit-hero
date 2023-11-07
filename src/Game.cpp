#include "Game.h"
#include <iostream>
#include <string>
// #include <filesystem>
// #include "Gerenciador.h"
#include "../error/FileNotOpenedException.h"
#include "../error/MusicNotLoadedException.h"

#ifdef WIN32
#define CLEAR_TERMINAL "cls"
#else
#define CLEAR_TERMINAL "clear"
#endif

const int VOLUME = 100;

using namespace cv;
using namespace std;

Game::Game() {
    // filesystem::path path = filesystem::current_path() / "high_score.txt";  
    // gerenciador = new Gerenciador(path.string());
    // gerenciador.setPath(path.string());
    draw = nullptr;
    points = new Points();
}



int Game::start() {
    VideoCapture capture;
    Mat frame;
    bool tryflip;
    CascadeClassifier cascade;
    double scale;
    std::string cascadeName("haarcascade_frontalface_default.xml");
    
    draw = new Draw(sequenceFile);
    points->setPoints(0);
    // points = new Points();
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
            
            draw->detectAndDraw( frame, cascade, scale, tryflip, audio, *points );

            char c = (char)waitKey(10);
            if( c == 27 || c == 'q' || c == 'Q' ) {
                break;
            }
        }
        audio.quit();
        // cout << "Final Points: " << draw->getPoints() << endl;
        cout << "Final Points: " << points->getPoints() << endl;
        cout << "Press enter to continue\n" ;
        // getchar();
        // getchar();
        cin.ignore();
        cin.get();
        // updateHighScore(draw);
        // updateHighScore();
        points->updateHighScore(chosenMusic);
    }
    if (draw != nullptr) {
        delete(draw);
        draw = nullptr;
    }
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
        // chosenMusic = "titanium.mp3";
        chosenMusic = "Titanium";
        sequenceFile = "titanium_sequence.txt";
    }
    else if (option == '2') {
        chosenMusic = "Drive Breakbeat"; 
        sequenceFile = "drive_breakbeat_sequence.txt";
    }
    else {
        option = '3';
    }
    system(CLEAR_TERMINAL);
    return option;
}

void Game::showHighScore() {
    vector<string> highScore;
    cout << "----------------------------------------\n";
    cout << "\t\tFRUIT HERO\n";
    cout << "________________________________________\n";
    cout << " High Score\n";
    cout << "________________________________________\n";
    highScore = points->getHighScore();
    for (int i = 0; i < highScore.size(); i+=3) {
        cout << "Music: " << highScore[i] << endl;
        cout << highScore[i+1] << " - " << highScore[i+2] << endl;
        cout << "\n";
    }
    cout << "----------------------------------------\n";
    cout << "Press enter to continue";
    // getchar();
    // getchar();
    cin.ignore();
    cin.get();
    system(CLEAR_TERMINAL);
}
