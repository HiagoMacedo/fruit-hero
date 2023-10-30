#include "Audio.h"
#include <filesystem> 
#include <iostream>
#include <../error/MusicNotLoadedException.h>

Audio::Audio()
{
    music = NULL;
    correct = NULL;
    miss = NULL;
    this->volume = MIX_MAX_VOLUME;
}
    
bool Audio::init() {
    Mix_Init(MIX_INIT_MP3);
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1 ) {
        std::cout << "Mix_OpenAudio Falhou\n";
        return false;    
    }

    return true;
}
    
bool Audio::loadFiles(std::string musicChosen) {
    std::filesystem::path musicPath = std::filesystem::current_path() / "sound" / musicChosen;
    std::filesystem::path correctPath = std::filesystem::current_path() / "sound/correct.wav";
    std::filesystem::path missPath = std::filesystem::current_path() / "sound/whoosh.wav";

    music = Mix_LoadMUS( musicPath.c_str() );    
    if( music == NULL ) {
        // std::cout << "Mix_LoadMUS Falhou\n";
        throw MusicNotLoadedException("Music failed to load");
        return false;    
    }

    correct = Mix_LoadWAV( correctPath.c_str() );
    miss = Mix_LoadWAV( missPath.c_str() );
    if( (correct == NULL ) || (miss == NULL) ) {
        // std::cout << "Mix_LoadWAV Falhou\n";
        throw MusicNotLoadedException("Sound effects failed to load");
        return false;    
    }

    return true;  
}
    
void Audio::quit() {
    Mix_FreeChunk(correct);
    Mix_FreeChunk(miss);
    
    Mix_FreeMusic(music);
    
    Mix_CloseAudio();
}

void Audio::playMusic() {
    Mix_Volume(-1, volume);
    if( Mix_PlayMusic(music, 0) == -1 ) {
        // throw music error?
    }
}

bool Audio::playingMusic() {
    if(Mix_PlayingMusic() != 0)
        return true;
    
    return false;
}

void Audio::playCorrect() {
    Mix_Volume(-1, volume);
    if ( Mix_PlayChannel(-1, correct, 0) == -1 ) {
        // throw effects error?
    }
}

void Audio::playMiss() {
    Mix_Volume(-1, volume);
    if ( Mix_PlayChannel(-1, miss, 0) == -1 ) {
        // throw effects error?
        std::cout << "Mix_PlayChannel Miss Falhou\n";
    }
}

void Audio::setVolume(int v) {
    volume = (MIX_MAX_VOLUME * v) / 100;
}
