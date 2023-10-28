#include <stdio.h>

#include "Utilities/ResourceManager.h"
#include "Album.h"

using namespace NokuMusic;

ResourceManager* ResourceManager::generalManager = new ResourceManager();

ResourceManager::ResourceManager() {
    Textures = std::map<const char*, SDL_Texture*>();
    Fonts = std::map<const char*, FC_Font*>();
    Sprites = std::map<const char*, Sprite*>();
}

void ResourceManager::LoadFont(Window* window, const char* path, const char* name, int size, int style) {
    printf("> Loading font with name \"%s\".\n", name);
    Fonts[name] = FC_CreateFont();

    FC_LoadFont(Fonts[name], window->GetSDLRenderer(), path, size, FC_MakeColor(255, 255, 255, 255), style);
}

void ResourceManager::LoadSprite(Window* window, const char* path, const char* name) {
    Sprites[name] = new Sprite(window, path);
}

void ResourceManager::LoadSong(const char* path, const char* name) {
    Song* tempSong = new Song(path);
    Songs[name] = tempSong;

    Album* temp = nullptr;
    if (!Album::Exists(tempSong->GetAlbum())) {
        temp = new Album(tempSong->GetAlbum());
    }
    else {
        temp = Album::GetAlbum(tempSong->GetAlbum());
    }

    if (temp != nullptr) {
        temp->AddSong(tempSong);
        temp->SortSongs();
    }        
}

Song* ResourceManager::GetSong(const char* name) {
    return Songs[name];
}

FC_Font* ResourceManager::GetFont(const char* name) {
    return Fonts.at(name);
}

Sprite* ResourceManager::GetSprite(const char* name) {
    return Sprites[name];
}

void ResourceManager::Print() {
    printf(">>> BEGIN!\n");
    for (const auto& font : Fonts) {
        printf("> \"%s\".\n", font.first);
    }
    printf(">>> END!\n");
}

ResourceManager* ResourceManager::GetGeneralManager() {
    return generalManager;
}