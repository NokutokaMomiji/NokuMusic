#ifndef NOKU_MUSIC_RESOURCE_MANAGER_H
#define NOKU_MUSIC_RESOURCE_MANAGER_H

#include <map>

#include "SDL2/SDL.h"
#include "SDL2/SDL_FontCache.h"

#include "Window.h"
#include "Sprite.h"
#include "Song.h"

namespace NokuMusic {
    class ResourceManager {
        public:
            ResourceManager();

            void LoadTexture(Window* window, const char* path, const char* name);
            void LoadFont(Window* window, const char* path, const char* name, int size, int style);
            void LoadSprite(Window* window, const char* path, const char* name);
            void LoadSong(const char* path, const char* name);

            SDL_Texture* GetTexture(const char* name);
            FC_Font* GetFont(const char* name);
            Sprite* GetSprite(const char* name);
            Song* GetSong(const char* name);

            void Print();

            static ResourceManager* GetGeneralManager();
        private:
            std::map<const char*, SDL_Texture*> Textures;
            std::map<const char*, FC_Font*>     Fonts;
            std::map<const char*, Sprite*>      Sprites;
            std::map<const char*, Song*>        Songs;
            static ResourceManager* generalManager;
    };
}

#endif