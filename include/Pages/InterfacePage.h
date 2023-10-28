#ifndef NOKU_MUSIC_INTERFACE_PAGE
#define NOKU_MUSIC_INTERFACE_PAGE

#include <vector>

#include "./SDL2/SDL.h"

#include "./Components/InterfaceComponent.h"
#include "Utilities/Window.h"
#include "./Utilities/Vector.h"


namespace NokuMusic {
    class Interface;

    class InterfacePage {
        public:
            virtual void Init(Window* window);
            virtual void Update();
            virtual void Draw();

            void SetDimensions(int x, int y);

            InterfaceComponent* AddComponent(InterfaceComponent* component);
            bool RemoveComponent(InterfaceComponent* component);
        protected:
            Vector2D<int> Position = { 0, 0 };
            Vector2D<int> Dimensions = { 0, 0 };
            SDL_Rect Viewport = { 0, 0, 0, 0 };
            std::vector<InterfaceComponent*> Components;
            Window* window;
    };
}

#endif
