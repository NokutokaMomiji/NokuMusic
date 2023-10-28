#include <stdio.h>
#include <stdexcept>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Utilities/Window.h"

using namespace NokuMusic;

std::vector<Window*> Window::listOfWindows = std::vector<Window*>();

Window::Window(const char* title, int width, int height, bool fullscreen) {
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    mainWindow = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE 
    );

    if (mainWindow == nullptr) {
        printf("> Failed to create window.\n");
        printf("> SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create window.\n");
    }

    mainRenderer = SDL_CreateRenderer(mainWindow, -1, 0);

    if (mainRenderer == nullptr) {
        printf("> Failed to create renderer for window.\n");
        printf("> SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to create renderer for window.\n");
    }

    listOfWindows.push_back(this);
}

void Window::Initialize() {
    printf("> [Window]: Initializing window stuff.\n");
    
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("> Failed to initialize SDL2 Video.\n");
        printf("> SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL2 Video.");
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_AVIF | IMG_INIT_JXL | IMG_INIT_TIF | IMG_INIT_WEBP) == 0) {
        printf("> [Window]: Failed to intialize SDL2 Image.\n");
        printf("> SDL Error: %s\n", SDL_GetError());
        throw std::runtime_error("Failed to initialize SDL2 Image.");
    }

    Window::listOfWindows = std::vector<Window*>();

    printf("> [Window]: SDL Video Initialized!\n");
}

void Window::Clear() {
    SDL_SetRenderDrawColor(mainRenderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    SDL_RenderClear(mainRenderer);
}

void Window::Display() {
    SDL_RenderPresent(mainRenderer);
}

SDL_Window* Window::GetSDLWindow() {
    return mainWindow;
}

SDL_Renderer* Window::GetSDLRenderer() {
    return mainRenderer;
}

Vector2D<int> Window::GetWindowDimensions() {
	int x, y;
	SDL_GetRendererOutputSize(mainRenderer, &x, &y);
	return { x, y };
}
