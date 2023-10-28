#include <stdio.h>

#include "SDL2/SDL.h"

#include "Player.h"

using namespace NokuMusic;

Player* Player::player = nullptr;

void Player::LoadConfig() {
    return;
}

bool Player::Init() {
    if (player == nullptr)
        player = new Player();
    
    if (player->Initialized) {
        printf("> [Player]: Player already initialized.\n");
        return true;
    }
	
	printf("> [Player]: Initializing player...\n");
	
#ifdef _WIN32
	SDL_setenv("SDL_AUDIODRIVER", "directsound", 1);
#endif

    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("> [Player]: Failed to initialize audio.\n");
		printf("> [Player]: Error: \"%s\".", SDL_GetError());
        return false;
    }

	printf("> [Player]: Audio initialized.\n");

    player->LoadConfig();

    if (Mix_OpenAudio(player->Frequency, DEFAULT_FORMAT, player->Channels, player->chunkSize) < 0) {
        printf("> [Player]: Failed to initialize audio device.\n");
        printf("> [Player]: Error: \"%s\".\n", SDL_GetError());
		return false;
    }

	printf("> [Player]: Audio device initialized.\n");

    return true;
}

void Player::Play(Song* song) {
    bool loaded = true;
    if (!song->IsLoaded())
        loaded = song->Load();

    if (!loaded) {
        printf("> [Player]: Song wasn't loaded.\n");
        return;
    }

    Mix_PlayMusic(song->GetMusic(), 0);
}

Player::Player() {
	
}
