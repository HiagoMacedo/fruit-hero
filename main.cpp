#include <iostream>
#include "include/Game.h"

using namespace std;


int main( int argc, const char** argv )
{
    Game game;
    bool quit = false;
    char option;
    
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
                break;
            default:
                cout << "Invalid option!" << endl;
                break;
        }
    }
    cout << "Game was sucessfully exited" << endl;
    return 0;
}
