#ifndef AUDIO_H
#define AUDIO_H

#ifdef _WIN32
#include <mmsystem.h> // Include the necessary header file for Windows
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#endif

#include <iostream>

bool startGame = false;
bool gameOverAudio = false;
bool gameWinAudio = false;
bool gameMenuAudio = true;
bool explosion = false;
bool atiraAudio = false;
bool audioLife = false;
bool audioApareceBonus = false;
bool audioPegaBonus = false;
bool audioHitMetal = false;

#ifdef _WIN32
void playAudio() {
    if (startGame == false) {
        mciSendString("play sounds/gamestart.wav", NULL, 0, NULL);
        startGame = true;
    }

    if (audioLife) {
        mciSendString("play sounds/life.wav", NULL, 0, NULL);
        audioLife = false;
        audioPegaBonus = false;
    }
}
#else
SDL_AudioDeviceID audioDevice;
Uint8* wavBuffer;
Uint32 wavLength;
SDL_AudioSpec wavSpec;
bool audioInitialized = false;

bool loadWAV(const char* file) {
    if (SDL_LoadWAV(file, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        std::cerr << "Erro ao carregar o som: " << SDL_GetError() << std::endl;
        return false;
    }
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
    if (audioDevice == 0) {
        std::cerr << "Erro ao abrir o dispositivo de áudio: " << SDL_GetError() << std::endl;
        SDL_FreeWAV(wavBuffer);
        return false;
    }
    return true;
}

void playAudio() {
    if (!audioInitialized) {
        std::cerr << "Erro: Subsistema de áudio não inicializado." << std::endl;
        return;
    }

    if (startGame == false) {
        if (loadWAV("sounds/gamestart.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, SDL_FALSE);
            startGame = true;
        }
    }

    if (audioLife) {
        if (loadWAV("sounds/life.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            audioLife = false;
            audioPegaBonus = false;
        }
    }

    if (audioHitMetal) {
        if (loadWAV("sounds/hitMetal.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            audioHitMetal = false;
        }
    }

    if (audioPegaBonus) {
        if (loadWAV("sounds/pegaBonus.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            audioPegaBonus = false;
        }
    }
}

bool initAudio() {
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        std::cerr << "Erro ao inicializar SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "Erro ao inicializar SDL_mixer: " << Mix_GetError() << std::endl;
        return false;
    }
    audioInitialized = true;
    return true;
}

void closeAudio() {
    if (audioInitialized) {
        SDL_CloseAudioDevice(audioDevice);
        SDL_FreeWAV(wavBuffer);
        Mix_CloseAudio();
        SDL_Quit();
        audioInitialized = false;
    }
}

void playMenuAudio() {
    if (gameMenuAudio) {
        if (loadWAV("sounds/menu.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            gameMenuAudio = false;
        }
    }
}

void playGameWinAudio() {
    if (gameWinAudio) {
        if (loadWAV("sounds/gamewin.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            gameWinAudio = false;
        }
    }
}

void playGameOverAudio() {
    if (gameOverAudio) {
        if (loadWAV("sounds/gameover.wav")) {
            SDL_QueueAudio(audioDevice, wavBuffer, wavLength);
            SDL_PauseAudioDevice(audioDevice, 0);
            gameOverAudio = false;
        }
    }
}
#endif

#endif // AUDIO_H