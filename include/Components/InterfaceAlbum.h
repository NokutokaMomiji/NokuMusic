#ifndef NOKU_MUSIC_INTERFACE_ALBUM_H
#define NOKU_MUSIC_INTERFACE_ALBUM_H

#include "InterfaceComponent.h"
#include "Album.h"
#include "Utilities/Sprite.h"
#include "SDL2/SDL_FontCache.h"
#include "SDL2/SDL.h"

namespace NokuMusic {
    class InterfaceAlbum : public InterfaceComponent {
        public:
            InterfaceAlbum(Window* window);
            void Init(Album* album, FC_Font* font);
            void Update(int x, int y) override;
            void Draw(int x, int y) override;
        private:
            Album* album;
            const char* albumTitle;
            const char* albumArtist;
            Sprite* albumArt;
            FC_Font* textFont;
            SDL_Renderer* renderer;
    };
}

#endif