#include <stdio.h>
#include <stdexcept>
#include <clocale>

#include "SDL2/SDL.h"
#include "SDL2/SDL_FontCache.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Utilities/IconsFontAwesome5.h"

#include "Interface.h"
#include "Song.h"
#include "Album.h"
#include "Player.h"
#include "Utilities/Vector.h"
#include "Utilities/Utilities.h"
#include "Utilities/FileManager.h"
#include "Pages/AlbumPage.h"

using namespace NokuMusic;

Uint64 timeNow = SDL_GetPerformanceCounter();
Uint64 timeLast = 0;

Interface* Interface::Instance = nullptr;

void Interface::Initialize() {
    std::setlocale(LC_ALL, ".UTF8");
    Window::Initialize();
    Player::Init();
}

void Interface::LoadResources() {
    internalManager = new ResourceManager();

    internalManager->LoadFont(mainWindow, "Fonts/Quicksand-Bold.ttf", "default", 11, TTF_STYLE_NORMAL);
    internalManager->LoadFont(mainWindow, "Fonts/Rajdhani-Medium.ttf", "title", 32, TTF_STYLE_NORMAL);
    internalManager->LoadFont(mainWindow, "Fonts/fa-regular-400.ttf", "icons", 32, TTF_STYLE_NORMAL);
    internalManager->LoadSprite(mainWindow, "Textures/DefaultAlbumArt.png", "default_album_art");
}

Interface::Interface() {
    mainWindow = new Window("Noku Player", 1280, 720, false);

    LoadResources();

    if (Instance == nullptr)
        Instance = this;
}

void Interface::Quit() {
    isRunning = false;
}

void OnWindowResized() {

}

void OnFocusGained() {

}

void OnFocusLost() {

}

void Interface::Run() {
    SDL_Event event;

    FileManager::ScanPath("D:/Archivos de Usuario/Escritorio/Music");
    FileManager::ScanPath("D:/Archivos de Usuario/Descargas/GODDESS_OF_VICTORY_NIKKE_ORIGINAL_SOUNDTRACK");

	Song* song = new Song("Temp/test.mp3", true);
	song->PrintData();
    Player::Play(song);
    
    albumPage = new AlbumPage();
    albumPage->Init(mainWindow, internalManager->GetFont("default"));

    printf("Beginning loop.\n");
    while (isRunning) {
        timeLast = timeNow;
        timeNow = SDL_GetPerformanceCounter();
        deltaTime = (double)((timeNow - timeLast) * 1000 / (double)SDL_GetPerformanceFrequency());
	
        while (SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:          Quit(); break;
                case SDL_WINDOWEVENT: {
                    switch(event.window.event)
                        case SDL_WINDOWEVENT_RESIZED:       OnWindowResized();  break;
                        case SDL_WINDOWEVENT_FOCUS_GAINED:  OnFocusGained();    break;
                        case SDL_WINDOWEVENT_FOCUS_LOST:    OnFocusLost();      break;
                    break;
                }
            }
        }
    
        PreUpdate();
        Update();
        PostUpdate();

        PreRender();
        Render();
        PostRender();
    }

    SDL_Quit();
}

void Interface::PreUpdate() {}
void Interface::Update() {

}

void Interface::PostUpdate() {

}

void Interface::PreRender() {
    mainWindow->Clear();
}

void Interface::Render() {
	Vector2D<int> dimensions = mainWindow->GetWindowDimensions();

    SDL_Rect topPart = { 0, 0, dimensions.X, 96 };
    SDL_Renderer* windowRenderer = mainWindow->GetSDLRenderer();

    int height = FC_GetHeight(internalManager->GetFont("title"), "Nokutoka Music");
    int iconHeight = FC_GetHeight(internalManager->GetFont("icons"), ICON_FA_SEARCH);
    
    roundedBoxRGBA(windowRenderer, 0, topPart.h + 32, topPart.w, dimensions.Y + 32, 24, 34, 34, 34, 255);
    
    FC_DrawAlign(internalManager->GetFont("icons"), windowRenderer, topPart.w - 128, ((topPart.h / 2) - (iconHeight / 2)), FC_ALIGN_RIGHT, ICON_FA_SEARCH);
    FC_Draw(internalManager->GetFont("title"), windowRenderer, 32, ((topPart.h / 2) - (height / 2)), "Nokutoka Music");

    albumPage->Draw();
}

void Interface::PostRender() {
    mainWindow->Display();
}

double Interface::DeltaTime() {
    return deltaTime;
}

ResourceManager* Interface::GetManager() {
    return internalManager;
}

Interface* Interface::Main() {
    return Instance;
}
