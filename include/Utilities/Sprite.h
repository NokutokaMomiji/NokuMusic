#ifndef NOKU_MUSIC_SPRITE_H
#define NOKU_MUSIC_SPRITE_H

#define TAGLIB_STATIC

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "taglib/tbytevector.h"

#include "Vector.h"
#include "Window.h"

namespace NokuMusic {
    class Sprite {
        public:
            Sprite(Window* window, const char* path);
            Sprite(Window* window, SDL_Texture* texture);
            Sprite(Window* window, TagLib::ByteVector byteVector);

            void Draw(int x, int y, int width = 0, int height = 0);
            
            Vector2D<int> GetDimensions();
            
            void Unload();
            
        private:
            SDL_Texture* texture;
            Vector2D<int> Dimensions;
            Window* innerWindow;
            void SetDimensions();
            void SetDefaultTexture(Window* window);
            static SDL_Texture* defaultTexture;
    };
}

#endif