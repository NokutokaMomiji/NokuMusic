#include <exception>
#include "Utilities/Sprite.h"
#include "taglib/tbytevector.h"
#include "Utilities/FileManager.h"

using namespace NokuMusic;

SDL_Texture* Sprite::defaultTexture = NULL;

static SDL_Surface* IMG_Load_Safe(const char* file) {
    if (!FileManager::Exists(file)) {
        printf("> [Sprite]: File \"%s\" doesn't exist.\n", file);
        throw std::runtime_error("File doesn't exist.");
    }

    return IMG_Load(file);
}

void Sprite::SetDefaultTexture(Window* window) {
    if (defaultTexture != NULL)
        return;

    SDL_Surface* temp = IMG_Load_Safe("Textures/DefaultAlbumArt.png");
    defaultTexture = SDL_CreateTextureFromSurface(window->GetSDLRenderer(), temp);
    if (defaultTexture == NULL)
        printf("> [Sprite]: Failed to load default texture.\n");
    SDL_FreeSurface(temp);
}

Sprite::Sprite(Window* window, const char* path) {
    Sprite::SetDefaultTexture(window);
    innerWindow = window;

    SDL_Surface* Image = IMG_Load(path);
    if (Image == NULL) {
        printf("> [Sprite]: Failed to load image \"%s\".\n", path);
        printf("> [Sprite]: Error: %s\n", IMG_GetError());
        return;
    }

    texture = SDL_CreateTextureFromSurface(window->GetSDLRenderer(), Image);
    
    SetDimensions();

    SDL_FreeSurface(Image);
}

Sprite::Sprite(Window* window, SDL_Texture* texture) {
    Sprite::SetDefaultTexture(window);
    innerWindow = window;
    
    this->texture = texture;
    SetDimensions();
}

Sprite::Sprite(Window* window, TagLib::ByteVector byteVector) {
    Sprite::SetDefaultTexture(window);
    innerWindow = window;

    if (byteVector.isEmpty()) {
        printf("> [Sprite]: Byte Vector is empty.\n");
        texture = defaultTexture;
        SetDimensions();
        return;
    }
    printf("> size: %d\n", byteVector.size());
    
    SDL_RWops* rw = SDL_RWFromMem(byteVector.data(), byteVector.size());
    SDL_Surface* Image = IMG_Load_RW(rw, 1);

    if (Image == NULL) {
        SDL_RWclose(rw);
        printf("> [Sprite]: Failed to load image from byte vector.\n");
        printf("> [Sprite]: Error: %s\n", SDL_GetError());
        texture = defaultTexture;
        SetDimensions();
        return;
    }

    printf("> format: %s\n", SDL_GetPixelFormatName(Image->format->format));

    SDL_RWclose(rw);

    texture = SDL_CreateTextureFromSurface(window->GetSDLRenderer(), Image);

    if (texture == NULL) {
        printf("> [Sprite]: Failed to create texture from image raw data surface.\n");
        printf("> [Sprite]: Error: %s\n", SDL_GetError());
        texture = defaultTexture;
    }

    SetDimensions();

    SDL_FreeSurface(Image);
}

void Sprite::Draw(int x, int y, int width, int height) {
    Sprite::SetDefaultTexture(innerWindow);

    if (texture == NULL) {
        texture = defaultTexture;
        SetDimensions();
    }
    if (texture == NULL) {
        printf("Fuck me.\n");
        return;
    }

    if (innerWindow == nullptr)
        printf("null window why?\n");

    width = (width < 0) ? (Dimensions.X - width) : ((width == 0) ? Dimensions.X : width);
    height = (height < 0) ? (Dimensions.Y - height) : ((height == 0) ? Dimensions.Y : height);
    SDL_Rect srcRect = { 0, 0, Dimensions.X, Dimensions.Y };
    int ratio = Dimensions.X / Dimensions.Y;

    if (ratio > 1) {
        srcRect.w = Dimensions.Y;
        srcRect.x = (Dimensions.X / 2) - (srcRect.w / 2);
    }
    else if (ratio < 1) {
        srcRect.h = Dimensions.X;
        srcRect.y = (Dimensions.Y / 2) - (srcRect.h / 2);
    }

    SDL_Rect destRect = { x, y, width, height };
    SDL_RenderCopy(innerWindow->GetSDLRenderer(), texture, &srcRect, &destRect);
}

Vector2D<int> Sprite::GetDimensions() {
    return Dimensions;
}

void Sprite::SetDimensions() {
    if (texture == NULL)
        texture = defaultTexture;

    int width, height;
    SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    Dimensions.X = width;
    Dimensions.Y = height;
}