#ifndef NOKU_MUSIC_ALBUM_PAGE_H
#define NOKU_MUSIC_ALBUM_PAGE_H

#include "InterfacePage.h"
#include "SDL2/SDL_FontCache.h"


namespace NokuMusic {
    class AlbumPage : public InterfacePage {
        public:
            void Init(Window* window, FC_Font* font);
            void Update() override;
            void Draw() override;
    };
}

#endif