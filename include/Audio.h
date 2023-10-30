#pragma once
#include <SDL2/SDL_mixer.h>
#include <string>

class Audio
{
public:
    Audio();
    
    bool init();
    
    bool loadFiles(std::string musicChosen);
    
    void quit();

    void playMusic();

    bool playingMusic();

    void playCorrect();

    void playMiss();
    
    void setVolume(int v);

private:
    Mix_Chunk* correct;
    Mix_Chunk* miss;
    Mix_Music* music;
    int volume;
};