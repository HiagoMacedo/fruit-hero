#include <iostream>
#include "include/Game.h"

#ifdef WIN32
#define TERMINAL_CLEAR "cls"
#define TERMINAL_SLEEP "timeout 1"
#else
#define TERMINAL_CLEAR "clear"
#define TERMINAL_SLEEP "sleep 1"
#endif

using namespace std;

int main( int argc, const char** argv )
{
    Game game;
    bool quit = false;
    char option;

    system(TERMINAL_CLEAR);
    
    while(quit == false) {
        option = game.menu();
        switch (option) {
            case '1': /* game start */
                if(game.chooseMusic() != '3') {
                    game.start();
                }
                break;
            case '2': /* high score */
                game.showHighScore();
                break;
            case '3': /* exit */
                quit = true;
                cout << "Exiting game..." << endl;
                system(TERMINAL_SLEEP);
                break;
            default:
                cout << "Invalid option!" << endl;
                break;
        }
    }
    // system(TERMINAL_SLEEP);
    cout << "Game was sucessfully closed" << endl;
    return 0;
}
