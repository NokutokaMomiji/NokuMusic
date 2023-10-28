// Adapted from Cataclysm Engine's Window implementation.

#ifndef NOKU_MUSIC_WINDOW_H
#define NOKU_MUSIC_WINDOW_H

#include <string>
#include <vector>

#include "SDL2/SDL.h"

#include "Vector.h"

namespace NokuMusic {
    class Window {
        public:
            Window(const char* title, int width, int height, bool fullscreen);

            static void Initialize();
            void Clear();
            void Display();
            void CleanUp();
            static void CleanUpAll();
            
            SDL_Window* GetSDLWindow();
            SDL_Renderer* GetSDLRenderer();

            void SetBorderless(bool borderless);
            void GetBorderless(bool borderless);
            void ToggleBorderless(bool borderless);

            void SetFullscreen(bool fullscreen);
            bool GetFullscreen();
            void ToggleFullscreen();

            void SetResizable(bool resizable);
            void GetResizable();
            void ToggleResizable();

            void SetToMaxSize();

            void SetTitle(const char* title);
            void SetTitle(std::string title);
            const char* GetTitle();

            Vector2D<int> GetWindowDimensions();
            void SetWindowDimensions(Vector2D<int> dimensions);

            void ResizeViewport();
            SDL_Color clearColor = { 0, 0, 0 };
        private:
            bool isFullscreen = false;
            bool isBorderless = false;
            bool isResizable = false;
            struct Vector2D<int> drawableArea = { 0, 0 };
            SDL_Window* mainWindow = nullptr;
            SDL_Renderer* mainRenderer = nullptr;
            static std::vector<Window*> listOfWindows;
    };
}

#endif
