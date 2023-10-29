#ifndef NOKU_MUSIC_INTERFACE_H
#define NOKU_MUSIC_INTERFACE_H

#include "SDL2/SDL.h"

#include "Utilities/Window.h"
#include "Utilities/ResourceManager.h"
#include "Pages/InterfacePage.h"
#include "Pages/AlbumPage.h"

namespace NokuMusic {
    class Interface {
        public:
            static void Initialize();
            static void CleanUp();

            void LoadResources();

            void ScanFolders(int n);

            Interface();
            ~Interface();

            void Quit();

            void Run();

            void PreUpdate();
            void Update();
            void PostUpdate();

            void PreRender();
            void Render();
            void PostRender();
	        double DeltaTime();

            ResourceManager* GetManager();

            static Interface* Main();
        private:
            std::vector<InterfacePage*> Pages;
            static Interface* Instance;
            Window* mainWindow;
            AlbumPage* albumPage = nullptr;
            InterfacePage* currentPage = nullptr;
            bool initPages = false;
            // Manager for things that are general to each individual interface. For example, SDL Textures (since they are 
            // Renderer bound...).
            ResourceManager* internalManager;
            bool isRunning = true;
	    	double deltaTime = 0;
    };
}

#endif
